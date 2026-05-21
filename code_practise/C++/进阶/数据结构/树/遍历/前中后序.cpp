#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 二叉树节点结构体
struct TreeNode {
    int val;                // 节点值
    TreeNode* left;         // 左子节点指针
    TreeNode* right;        // 右子节点指针
    // 构造函数
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 递归前序遍历（参数：根节点，结果数组引用）
void preorderRecur(TreeNode* root, vector<int>& res) {
    if (root == nullptr) return;  // 递归终止：节点为空
    res.push_back(root->val);     // 1. 先访问根节点
    preorderRecur(root->left, res);  // 2. 递归遍历左子树
    preorderRecur(root->right, res); // 3. 递归遍历右子树
}

// 对外接口（封装递归函数，返回结果）
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    preorderRecur(root, res);
    return res;
}

// 递归中序遍历
void inorderRecur(TreeNode* root, vector<int>& res) {
    if (root == nullptr) return;
    inorderRecur(root->left, res);   // 1. 递归遍历左子树
    res.push_back(root->val);        // 2. 访问根节点
    inorderRecur(root->right, res);  // 3. 递归遍历右子树
}

// 对外接口
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    inorderRecur(root, res);
    return res;
}

// 递归后序遍历
void postorderRecur(TreeNode* root, vector<int>& res) {
    if (root == nullptr) return;
    postorderRecur(root->left, res);   // 1. 递归遍历左子树
    postorderRecur(root->right, res);  // 2. 递归遍历右子树
    res.push_back(root->val);          // 3. 访问根节点
}

// 对外接口
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> res;
    postorderRecur(root, res);
    return res;
}