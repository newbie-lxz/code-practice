/*
普通解法（如 multiset）虽然能删任意元素，但erase(find(x))的常数较大；
而LazyHeap（懒删除堆）是对priority_queue的优化 
——先标记要删除的元素，等该元素到堆顶时再真正删除，
既保留了堆的O(logn)操作效率，又解决了 “删除任意元素” 的问题。
*/

//leetcode 480   滑动窗口中位数
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt; // 每个元素剩余需要删除的次数
    size_t sz = 0; // 实际大小

    // 正式执行删除操作
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }

public:
    size_t size() {
        return sz;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++; // 懒删除
        sz--;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top();
    }

    // 出堆
    T pop() {
        apply_remove();
        sz--;
        T x = pq.top();
        pq.pop();
        return x;
    }

    // 入堆
    void push(T x) {
        pq.push(x);
        sz++;
    }

    // push(x) 然后 pop()
    T push_pop(T x) {
        if (sz > 0 && Compare()(x, top())) { // 可以替换堆顶
            pq.push(x);
            x = pq.top();
            pq.pop();
        }
        return x;
    }
};

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> ans(n - k + 1);
        LazyHeap<int> left; // 最大堆
        LazyHeap<int, greater<>> right; // 最小堆

        for (int i = 0; i < n; i++) {
            // 1. 进入窗口
            int in = nums[i];
            if (left.size() == right.size()) {
                left.push(right.push_pop(in));
            } else {
                right.push(left.push_pop(in));
            }

            int l = i + 1 - k;
            if (l < 0) { // 窗口大小不足 k
                continue;
            }

            // 2. 计算答案
            if (k % 2) {
                ans[l] = left.top();
            } else {
                ans[l] = ((long long) left.top() + right.top()) / 2.0;
            }

            // 3. 离开窗口
            int out = nums[l];
            if (out <= left.top()) {
                left.remove(out);
                if (left.size() < right.size()) {
                    left.push(right.pop()); // 平衡两个堆的大小
                }
            } else {
                right.remove(out);
                if (left.size() > right.size() + 1) {
                    right.push(left.pop()); // 平衡两个堆的大小
                }
            }
        }

        return ans;
    }
};