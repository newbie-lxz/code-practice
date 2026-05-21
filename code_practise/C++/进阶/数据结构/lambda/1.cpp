//Lambda 表达式 = 匿名函数 + 捕获变量 + 简洁语法
/*
[capture](parameters) -> return_type {
    // function body
};

capture：捕获外部变量（可空）
parameters：参数列表（可省略）
return_type：返回类型（可自动推导，省略）
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << add(3, 4);  // 输出 7
    return 0;
}

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> path;

        auto dfs = [&](this auto&& dfs, int i) -> void {
            ans.push_back(path);
            for (int j = i; j < n; j++) {
                if (j > i && nums[j] == nums[j - 1]) {
                    continue;
                }
                path.push_back(nums[j]);
                dfs(j + 1);
                path.pop_back(); 
            }
        };

        dfs(0);
        return ans;
    }
};

/*
capture
 []      | 不捕获任何外部变量            
 [=]     | 按值捕获所有外部变量（只读）   
 [&]     | 按引用捕获所有外部变量        
 [x]     | 只按值捕获变量 `x`      
 [&x]    | 只按引用捕获变量 `x`     
 [=, &x] | 默认按值捕获，但 `x` 按引用 

*/