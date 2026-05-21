#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 步骤1：将字典转为无序集合，优化查询效率
        auto wordDictSet = unordered_set <string> ();
        for (auto word: wordDict) {
            wordDictSet.insert(word);
        }

        // 步骤2：定义DP数组并初始化边界
        auto dp = vector <bool> (s.size() + 1);
        dp[0] = true; // 边界条件：空字符串视为可拆分

        // 步骤3：动态规划状态转移
        for (int i = 1; i <= s.size(); ++i) { // 遍历前i个字符（i从1到s长度）
            for (int j = 0; j < i; ++j) { // 遍历所有可能的拆分点j（0<=j<i）
                // 核心条件：前j个字符可拆分 + j到i的子串在字典中
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true; // 前i个字符可拆分
                    break; // 找到一个拆分点即可，无需继续遍历j
                }
            }
        }

        // 步骤4：返回结果（整个字符串是否可拆分）
        return dp[s.size()];
    }
};