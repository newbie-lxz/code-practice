#include <stdio.h>
#include <stdlib.h>

#define N 8

int board[N][N];

// 检查是否可以在特定位置放置皇后
int isSafe(int row, int col) {
    int i, j;

    // 检查同一列
    for (i = 0; i < row; i++) {
        if (board[i][col]) {
            return 0;
        }
    }

    // 检查左上对角线
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return 0;
        }
    }

    // 检查右上对角线
    for (i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j]) {
            return 0;
        }
    }

    return 1;
}

// 递归函数用于放置皇后
int solveNQueens(int row) {
    if (row == N) {
        // 找到了一种解决方案，打印棋盘
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;
    }

    int foundSolution = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            foundSolution = solveNQueens(row + 1) || foundSolution;
            board[row][col] = 0; // 回溯
        }
    }

    return foundSolution;
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    if (!solveNQueens(0)) {
        printf("No solution found.\n");
    }

    return 0;
}