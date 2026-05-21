#include <iostream>
#include <vector>
using namespace std;

// 小顶堆（最小堆）
class MinHeap {
private:
    vector<int> heap; // 存储堆元素的数组
    int size;         // 堆的实际大小

    // 上浮操作：从index位置向上调整，满足小顶堆性质
    void up(int index) {
        // 未到根节点时循环
        while (index > 0) {
            int parent = (index - 1) / 2; // 父节点索引
            // 小顶堆：子节点 < 父节点 → 交换（违反堆序）
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent; // 继续向上检查
            } else {
                break; // 满足堆序，退出
            }
        }
    }

    // 下沉操作：从index位置向下调整，满足小顶堆性质
    void down(int index) {
        while (true) {
            int left = 2 * index + 1;  // 左孩子
            int right = 2 * index + 2; // 右孩子
            int smallest = index;      // 记录当前节点、左/右孩子中最小值的索引

            // 找左右孩子中更小的那个
            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }

            // 如果最小值不是当前节点 → 交换，继续下沉
            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break; // 满足堆序，退出
            }
        }
    }

public:
    // 构造函数：空堆
    MinHeap() : size(0) {}

    // 构造函数：用无序数组构建小顶堆
    MinHeap(vector<int>& nums) {
        heap = nums;
        size = nums.size();
        // 从最后一个非叶子节点开始下沉（堆化）
        for (int i = size / 2 - 1; i >= 0; --i) {
            down(i);
        }
    }

    // 插入元素
    void insert(int val) {
        heap.push_back(val); // 放到数组末尾
        size++;
        up(size - 1); // 从最后一个位置上浮
    }

    // 删除堆顶（最小值）
    void pop() {
        if (size == 0) {
            cout << "堆为空，无法删除！" << endl;
            return;
        }
        swap(heap[0], heap[size - 1]); // 堆顶和最后一个元素交换
        heap.pop_back(); // 删除最后一个元素（原堆顶）
        size--;
        down(0); // 从堆顶位置下沉
    }

    // 获取堆顶元素（最小值）
    int top() {
        if (size == 0) {
            cout << "堆为空！" << endl;
            return -1; // 异常标记，可根据需求调整
        }
        return heap[0];
    }

    // 判断堆是否为空
    bool isEmpty() {
        return size == 0;
    }

    // 获取堆的大小
    int getSize() {
        return size;
    }

    // 打印堆（按数组顺序，对应完全二叉树层序遍历）
    void printHeap() {
        for (int num : heap) {
            cout << num << " ";
        }
        cout << endl;
    }
};