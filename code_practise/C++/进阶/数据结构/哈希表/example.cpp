#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<string>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string& s : strs) {
            string sorted_s = s;
            sort(sorted_s.begin(),sorted_s.end()); 
            m[sorted_s].push_back(s);
        }

        vector<vector<string>> ans;
        ans.reserve(m.size()); 
        for (auto& [_, value] : m) {
            ans.push_back(value); 
        }
        //_：代表键（key），下划线是编程惯例，表示「这个变量我不用，只是占位」；
        return ans;
    }
};
//字母异位词分组