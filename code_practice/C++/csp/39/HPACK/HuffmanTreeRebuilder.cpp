#include <iostream>
#include <string>
#include <memory>
using namespace std;

struct Node {
    char data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {}
    Node() : data('\0'), left(nullptr), right(nullptr) {}
};

shared_ptr<Node> rebuildHuffmanTree(const string& s, int& index) {
    if (index >= s.length()) return nullptr;

    if (s[index] == '1') {
        index++; // 跳过'1'
        char ch = s[index++]; // 读取字符
        return make_shared<Node>(ch);
    } else if (s[index] == '0') {
        index++; // 跳过'0'
        auto node = make_shared<Node>();
        node->left = rebuildHuffmanTree(s, index);
        node->right = rebuildHuffmanTree(s, index);
        return node;
    }
    return nullptr;
}

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node>& root, string prefix = "") {
    if (!root) return;

    if (root->data != '\0') {
        cout << prefix << "Leaf: " << root->data << endl;
    } else {
        cout << prefix << "Internal Node" << endl;
    }
    printTree(root->left, prefix + "  ");
    printTree(root->right, prefix + "  ");
}

int main() {
    string encodedTree = "001a1b1c"; // 示例：0表示内部节点，1表示叶子节点
    int index = 0;
    auto root = rebuildHuffmanTree(encodedTree, index);

    cout << "Rebuilt Huffman Tree:" << endl;
    printTree(root);

    return 0;
}