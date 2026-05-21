#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 二叉树节点结构体
struct TreeNode {
    int val;                // 节点值
    TreeNode* left;         // 左子节点指针
    TreeNode* right;        // 右子节点指针
    // 构造函数
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//栈先压右子节点，再压左子节点（栈是「后进先出」，保证弹出时先处理左子树），每次弹出节点时直接访问。
vector<int> preorderIter(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    stack<TreeNode*> st;
    st.push(root);  // 根节点先入栈

    while (!st.empty()) {
        TreeNode* cur = st.top();  // 取出栈顶节点
        st.pop();
        res.push_back(cur->val);   // 访问当前节点（根）

        // 先压右子节点（后处理），再压左子节点（先处理）
        if (cur->right != nullptr) st.push(cur->right);
        if (cur->left != nullptr) st.push(cur->left);
    }
    return res;
}

//先遍历到左子树最底部（一路压栈），弹出时访问节点，再处理右子树。
vector<int> inorderIter(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* cur = root;

    while (cur != nullptr || !st.empty()) {
        // 1. 先遍历到左子树最底部，沿途节点入栈
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        // 2. 弹出栈顶节点（左子树最底部），访问
        cur = st.top();
        st.pop();
        res.push_back(cur->val);
        // 3. 处理右子树
        cur = cur->right;
    }
    return res;
}

//前序改顺序（根→右→左），再反转结果（左→右→根）
vector<int> postorderIter1(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* cur = st.top();
        st.pop();
        res.push_back(cur->val);  // 先访问根（和前序一致）
        // 先压左子节点，再压右子节点（栈后进先出，弹出顺序：右→左）
        if (cur->left != nullptr) st.push(cur->left);
        if (cur->right != nullptr) st.push(cur->right);
    }
    // 此时res是「根→右→左」，反转后得到「左→右→根」（后序）
    reverse(res.begin(), res.end());
    return res;
}