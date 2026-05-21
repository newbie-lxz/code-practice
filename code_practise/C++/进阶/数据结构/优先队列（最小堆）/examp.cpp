#include<iostream>
#include<vector>
#include <queue>
//包括priority_queue
using namespace std;
//给k个升序链表合并

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 1. 自定义优先队列的比较器（仿函数）
    struct cmp {
        // 重载()运算符，定义“如何比较两个ListNode*”
        bool operator()(const ListNode* a, const ListNode* b) {
            // 返回 a->val > b->val → 构建“小顶堆”（堆顶是最小值）
            return a->val > b->val;
        }
    };
    //priority_queue默认大顶堆

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 2. 初始化优先队列（小顶堆）
        // 模板参数：元素类型、底层容器、比较器
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;

        // 3. 把每个链表的“非空头节点”加入堆（跳过空链表）
        for (auto head : lists) {
            if (head) { // 避免空链表的nullptr入堆
                pq.push(head);
            }
        }

        // 4. 虚拟头节点（dummy node）：简化边界处理
        ListNode *dummy = new ListNode(); // 虚拟头，值无意义
        ListNode *cur = dummy; // 游标，指向结果链表的尾部

        // 5. 循环取堆顶（最小值），构建结果链表
        while (!pq.empty()) {
            // 5.1 取出堆顶的最小节点
            ListNode *min_node = pq.top();
            pq.pop(); // 弹出堆顶

            // 5.2 把最小节点接在结果链表尾部
            cur->next = min_node;
            cur = cur->next; // 游标后移

            // 5.3 把最小节点的下一个节点（非空）加入堆
            if (min_node->next) {
                pq.push(min_node->next);
            }
        }

        // 6. 返回结果链表的真实头节点（跳过虚拟头）
        ListNode *result = dummy->next;
        delete dummy; // 释放虚拟头，避免内存泄漏（算法题可省略）
        return result;
    }
};