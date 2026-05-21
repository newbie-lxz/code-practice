#include <iostream>
#include <vector>
#include <stack>
#include <utility> // pair需要
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 1. 标记法实现前序遍历（根→左→右）
vector<int> preorderMark(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    stack<pair<TreeNode*, bool>> st;
    st.push({root, false});

    while (!st.empty()) {
        auto [cur, visited] = st.top();
        st.pop();

        if (!visited) {
            // 前序：逆序入栈（右→左→根），保证弹出顺序（根→左→右）
            if (cur->right) st.push({cur->right, false}); // 先压右（后处理）
            if (cur->left) st.push({cur->left, false});   // 再压左（先处理）
            st.push({cur, true});                         // 最后压根（标记为已访问）
        } else {
            res.push_back(cur->val); // 已访问，直接取值
        }
    }
    return res;
}

// 2. 标记法实现中序遍历（左→根→右）
vector<int> inorderMark(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    stack<pair<TreeNode*, bool>> st;
    st.push({root, false});

    while (!st.empty()) {
        auto [cur, visited] = st.top();
        st.pop();

        if (!visited) {
            // 中序：逆序入栈（右→根→左），保证弹出顺序（左→根→右）
            if (cur->right) st.push({cur->right, false}); // 先压右（最后处理）
            st.push({cur, true});                         // 再压根（中间处理）
            if (cur->left) st.push({cur->left, false});   // 最后压左（先处理）
        } else {
            res.push_back(cur->val);
        }
    }
    return res;
}

// 3. 标记法实现后序遍历（左→右→根）
vector<int> postorderMark(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    stack<pair<TreeNode*, bool>> st;
    st.push({root, false});

    while (!st.empty()) {
        auto [cur, visited] = st.top();
        st.pop();

        if (!visited) {
            // 后序：逆序入栈（根→右→左），保证弹出顺序（左→右→根）
            st.push({cur, true});                         // 先压根（最后处理）
            if (cur->right) st.push({cur->right, false}); // 再压右（中间处理）
            if (cur->left) st.push({cur->left, false});   // 最后压左（先处理）
        } else {
            res.push_back(cur->val);
        }
    }
    return res;
}

// 辅助函数：打印vector
void printVec(const vector<int>& vec) {
    for (int num : vec) cout << num << " ";
    cout << endl;
}

// 测试
int main() {
    // 构建测试树：
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "标记法前序：";
    printVec(preorderMark(root));  // 输出：1 2 4 5 3
    cout << "标记法中序：";
    printVec(inorderMark(root));   // 输出：4 2 5 1 3
    cout << "标记法后序：";
    printVec(postorderMark(root)); // 输出：4 5 2 3 1

    // 释放内存（可选，避免内存泄漏）
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    system("pause");
    return 0;
}