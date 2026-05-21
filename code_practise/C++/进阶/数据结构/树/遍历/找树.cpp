#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BuildTree {
private:
    // 哈希表：中序值 → 索引（避免每次遍历查找，优化时间）
    unordered_map<int, int> inorderMap;

    // 递归构建：pre[preL, preR] + in[inL, inR] → 子树根节点
    TreeNode* buildPreIn(vector<int>& pre, int preL, int preR,
                         vector<int>& in, int inL, int inR) {
        if (preL > preR || inL > inR) return nullptr; // 递归终止：无节点

        // 1. 前序首元素为根
        int rootVal = pre[preL];
        TreeNode* root = new TreeNode(rootVal);

        // 2. 找根在中序的索引，分割左右子树
        int rootIdx = inorderMap[rootVal];
        int leftSize = rootIdx - inL; // 左子树节点数

        // 3. 递归构建左子树：
        // 前序：[preL+1, preL+leftSize]，中序：[inL, rootIdx-1]
        root->left = buildPreIn(pre, preL+1, preL+leftSize, in, inL, rootIdx-1);

        // 4. 递归构建右子树：
        // 前序：[preL+leftSize+1, preR]，中序：[rootIdx+1, inR]
        root->right = buildPreIn(pre, preL+leftSize+1, preR, in, rootIdx+1, inR);

        return root;
    }

    // 递归构建：post[postL, postR] + in[inL, inR] → 子树根节点
    TreeNode* buildPostIn(vector<int>& post, int postL, int postR,
                          vector<int>& in, int inL, int inR) {
        if (postL > postR || inL > inR) return nullptr;

        // 1. 后序尾元素为根
        int rootVal = post[postR];
        TreeNode* root = new TreeNode(rootVal);

        // 2. 找根在中序的索引，分割左右子树
        int rootIdx = inorderMap[rootVal];
        int leftSize = rootIdx - inL; // 左子树节点数

        // 3. 递归构建左子树：
        // 后序：[postL, postL+leftSize-1]，中序：[inL, rootIdx-1]
        root->left = buildPostIn(post, postL, postL+leftSize-1, in, inL, rootIdx-1);

        // 4. 递归构建右子树：
        // 后序：[postL+leftSize, postR-1]，中序：[rootIdx+1, inR]
        root->right = buildPostIn(post, postL+leftSize, postR-1, in, rootIdx+1, inR);

        return root;
    }

public:
    // 前序+中序构建树
    TreeNode* buildTreePreIn(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) {
            return nullptr;
        }
        // 构建中序值→索引的哈希表
        inorderMap.clear();
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }
        return buildPreIn(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }

    // 后序+中序构建树
    TreeNode* buildTreePostIn(vector<int>& postorder, vector<int>& inorder) {
        if (postorder.empty() || inorder.empty() || postorder.size() != inorder.size()) {
            return nullptr;
        }
        // 构建中序值→索引的哈希表
        inorderMap.clear();
        for (int i = 0; i < inorder.size(); ++i) {
            inorderMap[inorder[i]] = i;
        }
        return buildPostIn(postorder, 0, postorder.size()-1, inorder, 0, inorder.size()-1);
    }

    // 辅助：前序遍历打印（验证构建结果）
    void preorderPrint(TreeNode* root) {
        if (!root) return;
        cout << root->val << " ";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }

    // 辅助：中序遍历打印（验证构建结果）
    void inorderPrint(TreeNode* root) {
        if (!root) return;
        inorderPrint(root->left);
        cout << root->val << " ";
        inorderPrint(root->right);
    }

    // 辅助：释放树内存
    void deleteTree(TreeNode* root) {
        if (!root) return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
};

// 测试
int main() {
    BuildTree bt;

    // 测试用例：
    // 树结构：
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    vector<int> preorder = {1,2,4,5,3};  // 前序
    vector<int> inorder = {4,2,5,1,3};   // 中序
    vector<int> postorder = {4,5,2,3,1}; // 后序

    // 1. 前序+中序构建树
    TreeNode* root1 = bt.buildTreePreIn(preorder, inorder);
    cout << "前序+中序构建后，前序遍历：";
    bt.preorderPrint(root1); // 输出：1 2 4 5 3
    cout << "\n前序+中序构建后，中序遍历：";
    bt.inorderPrint(root1);  // 输出：4 2 5 1 3
    cout << endl;

    // 2. 后序+中序构建树
    TreeNode* root2 = bt.buildTreePostIn(postorder, inorder);
    cout << "后序+中序构建后，前序遍历：";
    bt.preorderPrint(root2); // 输出：1 2 4 5 3
    cout << "\n后序+中序构建后，中序遍历：";
    bt.inorderPrint(root2);  // 输出：4 2 5 1 3
    cout << endl;

    // 释放内存
    bt.deleteTree(root1);
    bt.deleteTree(root2);

    return 0;
}