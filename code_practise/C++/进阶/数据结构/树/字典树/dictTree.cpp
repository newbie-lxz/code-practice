#include<iostream>
#include<vector>
#include<string>
#include<functional>
using namespace std;

class Solution {
private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr}; 
        bool isEnd = false;          
    };

    TrieNode *root;
    vector<int> mem;

    void addWord(string word) {
        TrieNode* curr = root;
        for (char c : word) 
        {
            int idx = c - 'a';
            if (!curr->children[idx]) 
            { 
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx];
        }
        curr->isEnd = true; 
    }

    bool realSearch(const string& word, int idx, int length) {
        // 终止条件1：已匹配到字符串末尾 → 说明可拆分，返回true
        if(idx == length) {
            return true;
        }
        // 终止条件2：记忆化剪枝 → 该位置已确定无法拆分，直接返回false
        if(mem[idx]==1) {
            return false;
        }

        TrieNode *curr = root; // 每次匹配从字典树根节点开始
        for(int i=idx; i<length; i++) { // 从idx开始逐字符匹配
            // 情况1：当前字符的子节点不存在 → 前缀不匹配，返回false
            if(!curr->children[word[i]-'a']) {
                return false;
            } else {
                curr = curr->children[word[i]-'a']; // 移动到子节点
                // 情况2：当前节点是某个单词的结尾 → 尝试拆分，递归检查剩余子串
                if(curr->isEnd) {
                    // 递归检查：从i+1开始的子串是否可拆分
                    if(realSearch(word,i+1,length)) {
                        return true; // 剩余子串可拆分 → 整体可拆分
                    } else {
                        mem[i+1] = 1; // 标记i+1开始的子串无法拆分，后续剪枝
                    }
                }
            }
        }
        // 遍历完所有字符都没找到可拆分的情况 → 返回false
        return false;
    }

public:
    Solution()
    {
        root = new TrieNode();
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        for(string str : wordDict)
        {
            addWord(str);
        }
        mem.assign(s.size(),0);
        return realSearch(s,0,s.size());
    }

    ~Solution() {
        function<void(TrieNode*)> destroy;
        // 第二步：给 destroy 赋值 lambda，此时 lambda 捕获的是“已构造的 destroy 引用”
        destroy = [&](TrieNode* node) {
            if (!node) return;
            for (int i = 0; i < 26; ++i) {
                destroy(node->children[i]); // 此时 destroy 是合法的、可调用的
            }
            delete node;
        };
        destroy(root);
    }
};