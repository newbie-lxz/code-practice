#include <algorithm>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <system_error>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

struct Difficulty {
    string name;
    int rows;
    int cols;
    int mines;
};

enum class CellState {
    Covered = 0,
    Opened = 1,
    Flagged = 2
};

struct Cell {
    bool hasMine = false;
    int aroundMines = 0;
    CellState state = CellState::Covered;
};

class MinesweeperGame {
private:
    vector<vector<Cell>> board;
    Difficulty level;
    bool mineGenerated = false;
    bool gameOver = false;
    bool win = false;
    int openedCount = 0;
    int flagCount = 0;
    long long elapsedBeforeStart = 0;
    chrono::steady_clock::time_point startTime;
    mt19937 rng;

    const string saveDirectory = "saves";
    const string saveExtension = ".txt";
    const string historyFile = "minesweeper_history.txt";
    string statusMessage;

public:
    MinesweeperGame() : rng(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count())) {}

    void mainMenu() {
        while (true) {
            cout << "\n==============================\n";
            cout << "        Console Minesweeper\n";
            cout << "==============================\n";
            cout << "1. Start new game\n";
            cout << "2. Load saved game\n";
            cout << "3. Show history\n";
            cout << "4. Delete saved game\n";
            cout << "0. Exit\n";
            cout << "Please enter your choice: ";

            int choice;
            if (!(cin >> choice)) {
                if (cin.eof()) {
                    cout << "\nEnd of input.\n";
                    return;
                }
                clearInput();
                cout << "Input error. Please enter a number.\n";
                continue;
            }
            clearInput();

            if (choice == 1) {
                chooseDifficulty();
                playLoop();
            } else if (choice == 2) {
                if (loadGame()) {
                    playLoop();
                }
            } else if (choice == 3) {
                showHistory();
                pauseForEnter();
            } else if (choice == 4) {
                deleteSave();
            } else if (choice == 0) {
                cout << "End of program.\n";
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        }
    }

private:
    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int readIntInRange(const string& prompt, int low, int high) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= low && value <= high) {
                clearInput();
                return value;
            }
            if (cin.eof()) {
                cout << "\nEnd of input.\n";
                exit(0);
            }
            clearInput();
            cout << "Input error. Range is [" << low << ", " << high << "].\n";
        }
    }

    void clearScreen() const {
#ifdef _WIN32
        system("cls");
#else
        cout << "\033[2J\033[H";
#endif
    }

    void pauseForEnter(const string& prompt = "Press Enter to continue...") const {
        cout << "\n" << prompt;
        string ignored;
        getline(cin, ignored);
    }

    void setStatus(const string& message) {
        statusMessage = message;
    }

    string trim(const string& text) const {
        size_t begin = 0;
        while (begin < text.size() && isspace(static_cast<unsigned char>(text[begin]))) {
            ++begin;
        }
        size_t end = text.size();
        while (end > begin && isspace(static_cast<unsigned char>(text[end - 1]))) {
            --end;
        }
        return text.substr(begin, end - begin);
    }

    string lowerCopy(string text) const {
        for (char& ch : text) {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }
        return text;
    }

    bool endsWithTxt(const string& text) const {
        string lower = lowerCopy(text);
        return lower.size() >= saveExtension.size()
            && lower.substr(lower.size() - saveExtension.size()) == saveExtension;
    }

    string normalizeSaveName(const string& rawName) const {
        string name = trim(rawName);
        if (endsWithTxt(name)) {
            name = trim(name.substr(0, name.size() - saveExtension.size()));
        }
        return name;
    }

    bool isValidSaveName(const string& name, string& reason) const {
        if (name.empty()) {
            reason = "Save name cannot be empty.";
            return false;
        }
        if (name == "." || name == "..") {
            reason = "Save name cannot be . or ...";
            return false;
        }
        const string invalidChars = "<>:\"/\\|?*";
        for (char ch : name) {
            unsigned char value = static_cast<unsigned char>(ch);
            if (value < 32 || invalidChars.find(ch) != string::npos) {
                reason = "Save name contains invalid characters: <>:\"/\\|?*";
                return false;
            }
        }
        if (name.back() == '.' || name.back() == ' ') {
            reason = "Save name cannot end with a dot or space.";
            return false;
        }
        return true;
    }

    fs::path savePathForName(const string& name) const {
        return fs::path(saveDirectory) / (name + saveExtension);
    }

    string displaySaveName(const fs::path& path) const {
        return path.stem().string();
    }

    bool ensureSaveDirectory() {
        error_code ec;
        fs::path dir(saveDirectory);
        if (fs::exists(dir, ec)) {
            if (!fs::is_directory(dir, ec)) {
                setStatus("Cannot create save folder because a file named saves already exists.");
                cout << statusMessage << '\n';
                return false;
            }
            return true;
        }
        if (!fs::create_directories(dir, ec) || ec) {
            setStatus("Failed to create save folder.");
            cout << statusMessage << '\n';
            return false;
        }
        return true;
    }

    vector<fs::path> listSaveFiles() const {
        vector<fs::path> saves;
        error_code ec;
        fs::path dir(saveDirectory);
        if (!fs::exists(dir, ec) || !fs::is_directory(dir, ec)) {
            return saves;
        }
        for (const fs::directory_entry& entry : fs::directory_iterator(dir, ec)) {
            if (ec) break;
            if (!entry.is_regular_file(ec)) continue;
            if (lowerCopy(entry.path().extension().string()) == saveExtension) {
                saves.push_back(entry.path());
            }
        }
        sort(saves.begin(), saves.end(), [](const fs::path& a, const fs::path& b) {
            return a.filename().string() < b.filename().string();
        });
        return saves;
    }

    fs::path chooseSaveFile(const string& action) {
        vector<fs::path> saves = listSaveFiles();
        if (saves.empty()) {
            setStatus("No saved game found.");
            cout << statusMessage << '\n';
            return {};
        }

        cout << "\nSaved games:\n";
        for (int i = 0; i < static_cast<int>(saves.size()); ++i) {
            cout << setw(2) << i + 1 << ". " << displaySaveName(saves[i]) << '\n';
        }
        int choice = readIntInRange("Choose a save to " + action + " (0 to cancel): ", 0, static_cast<int>(saves.size()));
        if (choice == 0) {
            setStatus("Save " + action + " cancelled.");
            return {};
        }
        return saves[choice - 1];
    }

    void chooseDifficulty() {
        cout << "\nChoose difficulty:\n";
        cout << "1. Beginner     9 x 9, 10 mines\n";
        cout << "2. Intermediate 16 x 16, 40 mines\n";
        cout << "3. Expert       16 x 30, 99 mines\n";
        cout << "4. Custom\n";
        int choice = readIntInRange("Your choice: ", 1, 4);

        if (choice == 1) {
            level = {"Beginner", 9, 9, 10};
        } else if (choice == 2) {
            level = {"Intermediate", 16, 16, 40};
        } else if (choice == 3) {
            level = {"Expert", 16, 30, 99};
        } else {
            int r = readIntInRange("Rows (5-30): ", 5, 30);
            int c = readIntInRange("Cols (5-30): ", 5, 30);
            int maxMines = r * c - 9;
            if (maxMines < 1) maxMines = r * c - 1;
            int m = readIntInRange("Mines: ", 1, maxMines);
            level = {"Custom", r, c, m};
        }
        resetBoard();
    }

    void resetBoard() {
        board.assign(level.rows, vector<Cell>(level.cols));
        mineGenerated = false;
        gameOver = false;
        win = false;
        openedCount = 0;
        flagCount = 0;
        elapsedBeforeStart = 0;
        startTime = chrono::steady_clock::now();
        setStatus("New game started. Dig with d row col.");
    }

    bool inBounds(int r, int c) const {
        return r >= 0 && r < level.rows && c >= 0 && c < level.cols;
    }

    vector<pair<int, int>> neighbors(int r, int c) const {
        vector<pair<int, int>> result;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr == 0 && dc == 0) continue;
                int nr = r + dr, nc = c + dc;
                if (inBounds(nr, nc)) result.push_back({nr, nc});
            }
        }
        return result;
    }

    bool protectedOnFirstClick(int r, int c, int fr, int fc) const {
        if (r == fr && c == fc) return true;
        return abs(r - fr) <= 1 && abs(c - fc) <= 1 && level.rows * level.cols - level.mines >= 9;
    }

    void generateMines(int firstR, int firstC) {
        vector<pair<int, int>> candidates;
        for (int r = 0; r < level.rows; ++r) {
            for (int c = 0; c < level.cols; ++c) {
                if (!protectedOnFirstClick(r, c, firstR, firstC)) {
                    candidates.push_back({r, c});
                }
            }
        }
        shuffle(candidates.begin(), candidates.end(), rng);
        for (int i = 0; i < level.mines && i < static_cast<int>(candidates.size()); ++i) {
            board[candidates[i].first][candidates[i].second].hasMine = true;
        }
        calculateNumbers();
        mineGenerated = true;
    }

    void calculateNumbers() {
        for (int r = 0; r < level.rows; ++r) {
            for (int c = 0; c < level.cols; ++c) {
                if (board[r][c].hasMine) continue;
                int count = 0;
                for (auto [nr, nc] : neighbors(r, c)) {
                    if (board[nr][nc].hasMine) ++count;
                }
                board[r][c].aroundMines = count;
            }
        }
    }

    long long elapsedSeconds() const {
        if (gameOver) return elapsedBeforeStart;
        auto now = chrono::steady_clock::now();
        return elapsedBeforeStart + chrono::duration_cast<chrono::seconds>(now - startTime).count();
    }

    string currentTimeString() const {
        auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);
        tm* local = localtime(&t);
        stringstream ss;
        ss << put_time(local, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void displayBoard(bool revealAll = false) const {
        cout << "\nDifficulty: " << level.name << "  Size: " << level.rows << "x" << level.cols
             << "  Mines: " << level.mines << "  Flags: " << flagCount
             << "  Time: " << elapsedSeconds() << "s\n";
        cout << "    ";
        for (int c = 0; c < level.cols; ++c) cout << setw(2) << c + 1 << ' ';
        cout << "\n";
        for (int r = 0; r < level.rows; ++r) {
            cout << setw(3) << r + 1 << ' ';
            for (int c = 0; c < level.cols; ++c) {
                const Cell& cell = board[r][c];
                char ch = '#';
                if (revealAll && cell.hasMine) {
                    ch = '*';
                } else if (cell.state == CellState::Flagged) {
                    ch = 'F';
                } else if (cell.state == CellState::Covered) {
                    ch = '#';
                } else if (cell.hasMine) {
                    ch = '*';
                } else if (cell.aroundMines == 0) {
                    ch = '.';
                } else {
                    ch = static_cast<char>('0' + cell.aroundMines);
                }
                cout << ' ' << ch << ' ';
            }
            cout << "\n";
        }
    }

    void openCell(int r, int c) {
        if (!inBounds(r, c)) {
            setStatus("Coordinate out of range.");
            return;
        }
        Cell& cell = board[r][c];
        if (cell.state == CellState::Flagged) {
            setStatus("This cell is flagged. Cancel the flag before digging.");
            return;
        }
        if (cell.state == CellState::Opened) {
            setStatus("This cell has already been opened.");
            return;
        }
        if (!mineGenerated) generateMines(r, c);

        if (board[r][c].hasMine) {
            board[r][c].state = CellState::Opened;
            elapsedBeforeStart = elapsedSeconds();
            gameOver = true;
            win = false;
            setStatus("Game Over! You stepped on a mine.");
            appendHistory("Lose");
            return;
        }

        if (board[r][c].aroundMines == 0) {
            autoOpen(r, c);
        } else {
            board[r][c].state = CellState::Opened;
            ++openedCount;
        }
        checkWin();
        if (!gameOver) {
            setStatus("Opened row " + to_string(r + 1) + ", col " + to_string(c + 1) + ".");
        }
    }

    void autoOpen(int r, int c) {
        if (!inBounds(r, c)) return;
        Cell& cell = board[r][c];
        if (cell.state == CellState::Opened || cell.state == CellState::Flagged || cell.hasMine) return;
        cell.state = CellState::Opened;
        ++openedCount;
        if (cell.aroundMines != 0) return;
        for (auto [nr, nc] : neighbors(r, c)) {
            autoOpen(nr, nc);
        }
    }

    void toggleFlag(int r, int c) {
        if (!inBounds(r, c)) {
            setStatus("Coordinate out of range.");
            return;
        }
        Cell& cell = board[r][c];
        if (cell.state == CellState::Opened) {
            setStatus("Opened cell cannot be flagged.");
            return;
        }
        if (cell.state == CellState::Covered) {
            if (flagCount >= level.mines) {
                setStatus("The number of flags has reached the number of mines.");
                return;
            }
            cell.state = CellState::Flagged;
            ++flagCount;
            setStatus("Flagged row " + to_string(r + 1) + ", col " + to_string(c + 1) + ".");
        } else {
            cell.state = CellState::Covered;
            --flagCount;
            setStatus("Removed flag at row " + to_string(r + 1) + ", col " + to_string(c + 1) + ".");
        }
        checkWin();
    }

    void checkWin() {
        int safeCells = level.rows * level.cols - level.mines;
        if (openedCount == safeCells) {
            elapsedBeforeStart = elapsedSeconds();
            gameOver = true;
            win = true;
            setStatus("Victory! All safe cells have been opened.");
            appendHistory("Win");
        }
    }

    bool parseCommand(const string& line, char& op, int& r, int& c) {
        stringstream ss(line);
        if (!(ss >> op)) return false;
        if (op == 'd' || op == 'D' || op == 'f' || op == 'F') {
            if (!(ss >> r >> c)) return false;
            --r;
            --c;
            return true;
        }
        return op == 's' || op == 'S' || op == 'h' || op == 'H'
            || op == 'q' || op == 'Q' || op == 'l' || op == 'L'
            || op == 'x' || op == 'X';
    }

    void playLoop() {
        bool quitToMenu = false;
        while (!gameOver) {
            clearScreen();
            displayBoard();
            if (!statusMessage.empty()) {
                cout << "\nStatus: " << statusMessage << '\n';
            }
            cout << "\nCommand: d row col = dig, f row col = flag/cancel, s = save, l = load, x = delete save, h = history, q = quit\n";
            cout << "Input command: ";
            string line;
            getline(cin, line);
            if (trim(line).empty()) {
                setStatus("Please enter a command.");
                continue;
            }

            char op = 0;
            int r = 0, c = 0;
            if (!parseCommand(line, op, r, c)) {
                setStatus("Invalid command format. Example: d 3 5 or f 2 6.");
                continue;
            }
            if (op == 'd' || op == 'D') {
                openCell(r, c);
            } else if (op == 'f' || op == 'F') {
                toggleFlag(r, c);
            } else if (op == 's' || op == 'S') {
                saveGame();
            } else if (op == 'l' || op == 'L') {
                loadGame();
            } else if (op == 'h' || op == 'H') {
                clearScreen();
                showHistory();
                pauseForEnter();
                setStatus("Returned from history.");
            } else if (op == 'x' || op == 'X') {
                deleteSave();
            } else if (op == 'q' || op == 'Q') {
                quitToMenu = true;
                break;
            }
        }
        if (gameOver) {
            clearScreen();
            displayBoard(true);
            if (!statusMessage.empty()) {
                cout << "\n" << statusMessage << '\n';
            }
            pauseForEnter("Press Enter to return to the main menu...");
        } else if (quitToMenu) {
            cout << "Return to main menu.\n";
        }
    }

    bool writeGameToFile(const fs::path& path) {
        ofstream out(path);
        if (!out) {
            setStatus("Failed to open save file.");
            cout << statusMessage << '\n';
            return false;
        }
        out << "MINESWEEPER_SAVE_V1\n";
        out << level.name << '\n';
        out << level.rows << ' ' << level.cols << ' ' << level.mines << '\n';
        out << mineGenerated << ' ' << openedCount << ' ' << flagCount << ' ' << elapsedSeconds() << '\n';
        for (int r = 0; r < level.rows; ++r) {
            for (int c = 0; c < level.cols; ++c) {
                const Cell& cell = board[r][c];
                out << cell.hasMine << ' ' << cell.aroundMines << ' ' << static_cast<int>(cell.state) << ' ';
            }
            out << '\n';
        }
        return true;
    }

    void saveGame() {
        if (!ensureSaveDirectory()) return;

        while (true) {
            cout << "\nSave name (0 to cancel, .txt optional): ";
            string rawName;
            getline(cin, rawName);
            string name = normalizeSaveName(rawName);
            if (name == "0") {
                setStatus("Save cancelled.");
                return;
            }

            string reason;
            if (!isValidSaveName(name, reason)) {
                cout << reason << '\n';
                continue;
            }

            fs::path path = savePathForName(name);
            error_code ec;
            if (fs::exists(path, ec)) {
                while (true) {
                    cout << "Save \"" << name << "\" already exists. Overwrite (o), rename (r), cancel (c): ";
                    string answer;
                    getline(cin, answer);
                    answer = lowerCopy(trim(answer));
                    if (answer == "o" || answer == "overwrite" || answer == "y" || answer == "yes") {
                        break;
                    }
                    if (answer == "r" || answer == "rename") {
                        path.clear();
                        break;
                    }
                    if (answer == "c" || answer == "cancel" || answer == "0") {
                        setStatus("Save cancelled.");
                        return;
                    }
                    cout << "Please enter o, r, or c.\n";
                }
                if (path.empty()) {
                    continue;
                }
            }

            if (writeGameToFile(path)) {
                setStatus("Game saved to " + path.string() + ".");
                cout << statusMessage << '\n';
            }
            return;
        }
    }

    bool readGameFromFile(const fs::path& path) {
        ifstream in(path);
        if (!in) {
            setStatus("Failed to open save file.");
            cout << statusMessage << '\n';
            return false;
        }
        string magic;
        getline(in, magic);
        if (magic != "MINESWEEPER_SAVE_V1") {
            setStatus("Save file format error.");
            cout << statusMessage << '\n';
            return false;
        }
        getline(in, level.name);
        in >> level.rows >> level.cols >> level.mines;
        in >> mineGenerated >> openedCount >> flagCount >> elapsedBeforeStart;
        if (!in || level.rows <= 0 || level.cols <= 0 || level.mines <= 0 || level.mines >= level.rows * level.cols) {
            setStatus("Save file content error.");
            cout << statusMessage << '\n';
            return false;
        }
        board.assign(level.rows, vector<Cell>(level.cols));
        for (int r = 0; r < level.rows; ++r) {
            for (int c = 0; c < level.cols; ++c) {
                int hasMine, state;
                in >> hasMine >> board[r][c].aroundMines >> state;
                board[r][c].hasMine = (hasMine != 0);
                if (state < 0 || state > 2) state = 0;
                board[r][c].state = static_cast<CellState>(state);
            }
        }
        if (!in) {
            setStatus("Failed to read saved board.");
            cout << statusMessage << '\n';
            return false;
        }
        gameOver = false;
        win = false;
        startTime = chrono::steady_clock::now();
        setStatus("Game loaded from " + path.string() + ".");
        cout << statusMessage << '\n';
        return true;
    }

    bool loadGame() {
        fs::path path = chooseSaveFile("load");
        if (path.empty()) return false;
        return readGameFromFile(path);
    }

    void deleteSave() {
        fs::path path = chooseSaveFile("delete");
        if (path.empty()) return;

        cout << "Delete save \"" << displaySaveName(path) << "\"? (y/n): ";
        string answer;
        getline(cin, answer);
        answer = lowerCopy(trim(answer));
        if (answer != "y" && answer != "yes") {
            setStatus("Delete cancelled.");
            cout << statusMessage << '\n';
            return;
        }

        error_code ec;
        if (fs::remove(path, ec) && !ec) {
            setStatus("Deleted save \"" + displaySaveName(path) + "\".");
        } else {
            setStatus("Failed to delete save.");
        }
        cout << statusMessage << '\n';
    }

    void appendHistory(const string& result) {
        ofstream out(historyFile, ios::app);
        if (!out) return;
        out << currentTimeString() << ',' << level.name << ','
            << level.rows << 'x' << level.cols << ',' << level.mines << ','
            << result << ',' << elapsedSeconds() << "s\n";
    }

    void showHistory() const {
        ifstream in(historyFile);
        cout << "\nGame history:\n";
        cout << "Time,Difficulty,Size,Mines,Result,Elapsed\n";
        if (!in) {
            cout << "No history record.\n";
            return;
        }
        string line;
        vector<string> records;
        while (getline(in, line)) {
            if (!line.empty()) records.push_back(line);
        }
        if (records.empty()) {
            cout << "No history record.\n";
            return;
        }
        int start = max(0, static_cast<int>(records.size()) - 10);
        for (int i = start; i < static_cast<int>(records.size()); ++i) {
            cout << records[i] << '\n';
        }
    }
};

int main() {
    MinesweeperGame game;
    game.mainMenu();
    return 0;
}
