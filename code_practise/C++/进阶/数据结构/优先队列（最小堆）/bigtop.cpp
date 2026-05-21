#include <iostream>
#include <vector>
using namespace std;

// 大顶堆（最大堆）
class MaxHeap {
private:
    vector<int> heap;
    int size;

    // 上浮操作：子节点 > 父节点 → 交换（违反大顶堆序）
    void up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) { // 仅此处和小顶堆不同
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // 下沉操作：找左右孩子中更大的，父节点 < 更大的孩子 → 交换
    void down(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index; // 仅此处和小顶堆不同

            if (left < size && heap[left] > heap[largest]) { // 仅此处和小顶堆不同
                largest = left;
            }
            if (right < size && heap[right] > heap[largest]) { // 仅此处和小顶堆不同
                largest = right;
            }

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    // 构造函数（空堆）
    MaxHeap() : size(0) {}

    // 构造函数（数组构建大顶堆）
    MaxHeap(vector<int>& nums) {
        heap = nums;
        size = nums.size();
        for (int i = size / 2 - 1; i >= 0; --i) {
            down(i);
        }
    }

    // 插入元素（逻辑和小顶堆一致）
    void insert(int val) {
        heap.push_back(val);
        size++;
        up(size - 1);
    }

    // 删除堆顶（最大值）（逻辑和小顶堆一致）
    void pop() {
        if (size == 0) {
            cout << "堆为空，无法删除！" << endl;
            return;
        }
        swap(heap[0], heap[size - 1]);
        heap.pop_back();
        size--;
        down(0);
    }

    // 获取堆顶（最大值）
    int top() {
        if (size == 0) {
            cout << "堆为空！" << endl;
            return -1;
        }
        return heap[0];
    }

    // 判空、获取大小、打印（和小顶堆一致）
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }
    void printHeap() {
        for (int num : heap) {
            cout << num << " ";
        }
        cout << endl;
    }
};