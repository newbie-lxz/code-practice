#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void test01() {
    // 1. 默认构造（大顶堆）
    priority_queue<int> pq1;

    // 2. 带比较器的构造（小顶堆）
    // 模板参数：元素类型、底层容器、比较器
    priority_queue<int, vector<int>, greater<int>> pq2;

    // 3. 基于已有容器构造
    vector<int> vec = {3,1,4,2};
    priority_queue<int> pq3(vec.begin(), vec.end()); // 构建大顶堆，堆顶4
    priority_queue<int, vector<int>, greater<int>> pq(vec.begin(), vec.end());

    // 4. 拷贝构造
    priority_queue<int> pq4(pq3);

    // 5. 移动构造（pq3后续为空）
    priority_queue<int> pq5(move(pq3));

    // 6. 赋值
    pq1 = pq4;
}

void test02() {
    vector<int> vec = {3,1,4,2};
    priority_queue<int> pq(vec.begin(), vec.end());

    // 1. 访问堆顶
    cout << "堆顶元素：" << pq.top() << endl; // 输出4

    // 2. 修改堆顶（仅非const版本）
    pq.pop();      // 去掉原堆顶
    pq.push(10);   // 把新值压进去
    cout << "修改后堆顶：" << pq.top() << endl;  // 输出 10

    // 3. 空队列调用top() → 崩溃！
    priority_queue<int> empty_pq;
    // cout << empty_pq.top() << endl; // 错误：未定义行为
}


void test04() {
    priority_queue<string> pq;
    //priority_queue<string, vector<string>, greater<string>> pq; 小顶

    // 1. push插入（拷贝）
    string s = "apple";
    pq.push(s);
    pq.push("banana"); // 直接传临时对象

    // 2. emplace原地构造（更高效）
    pq.emplace("cherry"); // 直接传构造参数，无临时string

    // 插入后堆顶是"cherry"（字符串按字典序大顶堆）
    cout << "堆顶：" << pq.top() << endl; // 输出cherry
}

void test05() {
    priority_queue<int> pq;

    cout << "初始是否为空：" << boolalpha << pq.empty() << endl; // true
    cout << "初始大小：" << pq.size() << endl; // 0

    pq.push(1); 
    pq.push(2); 
    pq.push(3);
    cout << "插入后是否为空：" << pq.empty() << endl; // false
    cout << "插入后大小：" << pq.size() << endl; // 3
}

void test06() {
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {4,5,6};
    priority_queue<int> pq1(v1.begin(), v1.end());
    priority_queue<int> pq2(v2.begin(), v2.end());

    pq1.swap(pq2);

    cout << "pq1堆顶：" << pq1.top() << endl; // 6
    cout << "pq2堆顶：" << pq2.top() << endl; // 3
}