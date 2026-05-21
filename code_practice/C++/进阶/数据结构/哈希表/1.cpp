/*
C++ 标准库中的哈希表主要基于 无序容器 实现，
核心包括 unordered_map、unordered_set、unordered_multimap、unordered_multiset，
均位于 <unordered_map>/<unordered_set> 头文件。
哈希表的核心特性是 平均 O (1) 时间复杂度 的插入 / 查找 / 删除，
代价是 无序性（底层基于哈希桶实现）。
*/
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include <string>
using namespace std;

void test01() {
    // 1. 默认构造
    unordered_map<string, int> um1;
    // 2. 列表初始化
    unordered_map<string, int> um2 = {{"a",1}, {"b",2}};
    // 3. 拷贝构造
    unordered_map<string, int> um3(um2);                            //um2依旧保留原来的数据，相当于把um2的数据一个个复制到um3
    // 4. 移动构造（um2 后续为空）
    unordered_map<string, int> um4(move(um2));                      //move把um2的数据移动到um4，um2相当于变空了，效率高
    // 5. 拷贝赋值
    um1 = um3;
    // 6. 列表赋值
    um1 = {{"c",3}, {"d",4}};
}

void test02() {
    unordered_map<string, int> um = {{"apple", 5}};
    // 1. operator[]：存在则修改，不存在则插入
    um["apple"] = 10;       // 修改：apple→10
    um["banana"];           // 插入：banana→0（仅访问也会插入）
    cout << um["banana"] << endl; // 输出 0

    // 2. at()：安全访问，不存在抛异常
    try {
        um.at("apple") = 15; // 修改为 15
        cout << um.at("apple") << endl; // 输出 15
        um.at("orange"); // 抛异常
    }
    //try块用来运行可能出错的代码，把错误存在try{}中，触发错误 → 程序立刻停止执行 try 块剩余代码，转而跳转到匹配的 catch 块。
    catch (const out_of_range& e) {
        cout << "异常：" << e.what() << endl;
    }
    //专门 “接住” try 块中抛出的 out_of_range 类型异常，避免程序崩溃。
    //const out_of_range& e：声明要捕获的异常类型是 out_of_range，e 是这个异常的对象（加 const& 是为了高效，避免拷贝）；
    //e.what()：异常对象的成员函数，返回一个字符串，描述异常的具体原因（比如 “invalid unordered_map<K,V> key”）。
}

void test03() {
    unordered_map<string, int> um;
    // 1. insert 单个元素
    auto ret = um.insert({"apple", 5});
    if (ret.second) {
        cout << "插入成功：" << ret.first->first << ":" << ret.first->second << endl;
    } else {
        cout << "插入失败，键已存在：" << ret.first->first << endl;
    }
    //第一个成员（first）：unordered_map 的迭代器（指向容器中的某个键值对）；
    //第二个成员（second）：布尔值（bool），标记插入是否成功。

    ret = um.insert({"apple", 10}); // 键已存在，插入失败
    cout << "第二次插入 apple:" << (ret.second ? "成功" : "失败") << endl;

    // 2. insert 批量元素
    um.insert({{"banana", 3}, {"orange", 7}});

    // 3. emplace 原地构造（更高效）
    um.emplace("grape", 9); // 直接构造，无临时 pair

    // 4. emplace_hint（提示迭代器，仅优化）
    auto it = um.begin();
    um.emplace_hint(it, "pear", 8);
    /*
    告诉编译器 “我建议你把新元素插在it迭代器指向的位置附近”；
    插入成功：指向刚构造的键值对 {"pear", 8}；
    插入失败（键 "pear" 已存在）：指向容器中已存在的 "pear" 键值对；
    区别于 emplace：emplace 返回 pair<迭代器, bool>（能直接判断是否插入成功），而 emplace_hint 只返回迭代器，无 bool 标记。
    */

    // 遍历验证
    for (const auto& p : um) {
        cout << p.first << ":" << p.second << " ";
    } 
    // 输出：apple:5 banana:3 orange:7 grape:9 pear:8（顺序不固定）
}

void test04() {
    unordered_map<string, int> um = {{"a",1},{"b",2},{"c",3},{"d",4}};

    // 1. 按键删除
    size_t del_cnt = um.erase("b");
    cout << "删除 b 的个数：" << del_cnt << endl; // 输出 1
    //size_t 是 C/C++ 标准定义的无符号整数类型
    //unordered_map::erase(键) 的返回值是成功删除的元素个数, 0表示不存在，1存在

    // 2. 按迭代器删除
    auto it = um.find("c");
    if (it != um.end()) {
        it = um.erase(it); // 返回下一个元素的迭代器（指向 d）
        cout << "删除 c 后，迭代器指向：" << it->first << endl; // 输出 d
    }

    // 3. 按范围删除
    auto first = um.find("a");
    auto last = um.end();
    um.erase(first, last); // 删除 a 和 d ， 左闭右开区间

    // 4. 清空容器
    um.clear();
    cout << "清空后大小：" << um.size() << endl; // 输出 0

    // 5. 交换容器
    unordered_map<string, int> um2 = {{"x",10},{"y",20}};
    um.swap(um2);
    cout << "交换后 um 的大小：" << um.size() << endl; // 输出 2
}

void test05() {
    unordered_map<string, int> um = {{"apple",5},{"banana",3}};

    // 1. find 查找
    auto it = um.find("apple");
    if (it != um.end()) {
        cout << "找到 apple:" << it->second << endl; // 输出 5
    }
    it = um.find("orange");
    if (it == um.end()) {
        cout << "未找到 orange" << endl;
    }

    // 2. count 统计
    cout << "apple 个数：" << um.count("apple") << endl; // 输出 1
    cout << "orange 个数：" << um.count("orange") << endl; // 输出 0

    // 3. equal_range（unordered_map 中范围最多 1 个元素）
    auto range = um.equal_range("banana");
    for (auto i = range.first; i != range.second; ++i) {
        cout << "banana:" << i->second << endl; // 输出 3
    }
    /*
    equal_range(key) 会在容器中查找所有键等于 key 的元素，返回一个 pair，包含两个迭代器：
    pair.first：指向第一个键等于 key 的元素（起始迭代器）；
    pair.second：指向最后一个键等于 key 的元素的下一个位置（结束迭代器）；
    整体是左闭右开区间：[range.first, range.second)（包含 first，不包含 second）。
    */
}

void test06() {
    unordered_map<int, int> um;

    cout << "初始是否为空：" << boolalpha << um.empty() << endl; // 输出 true
    cout << "初始大小：" << um.size() << endl; // 输出 0
    cout << "最大容量：" << um.max_size() << endl; // 输出系统相关值（如 18446744073709551615）

    um.insert({{1,10}, {2,20}, {3,30}});
    cout << "插入后是否为空：" << um.empty() << endl; // 输出 false
    cout << "插入后大小：" << um.size() << endl; // 输出 3
}

void test07() {
    unordered_map<int, int> um;

    // 预分配桶，避免频繁 rehash
    um.reserve(100);

    // 插入 50 个元素
    for (int i = 0; i < 50; ++i) {
        um[i] = i * 10;
    }

    // 桶相关查询
    cout << "当前桶数：" << um.bucket_count() << endl; // 输出 ≥ 50/1.0=50（如 64）
    //桶数会取「大于等于计算值的最小 2 的幂」（比如 50→64，100→128），目的是哈希分配更均匀；
    cout << "负载因子：" << um.load_factor() << endl; // 输出 50/64≈0.78125
    cout << "最大负载因子：" << um.max_load_factor() << endl; // 输出 1.0

    // 修改最大负载因子
    um.max_load_factor(0.75);
    cout << "修改后最大负载因子：" << um.max_load_factor() << endl; // 输出 0.75
    //负载因子越低，哈希冲突越少（桶越空）。
    //修改为 0.75 后，只要 load_factor > 0.75，就会触发自动 rehash（更严格的扩容规则，减少哈希冲突）

    // 强制 rehash 到 100 个桶
    um.rehash(100);
    cout << "rehash 后桶数：" << um.bucket_count() << endl; // 输出 100
    //rehash 后，所有元素会重新计算哈希值，分配到新的桶里（迭代器会失效）。
    //reserve(n)：按 “元素数” 预分配桶（计算方式：n / 最大负载因子）；
    //rehash(n)：直接按 “桶数” 分配（桶数≥n）；

    // 查询键 10 所在的桶及桶大小
    size_t bucket_num = um.bucket(10);
    cout << "键 10 所在桶编号：" << bucket_num << endl;
    cout << "该桶元素数：" << um.bucket_size(bucket_num) << endl;
}

void test08() {
    unordered_map<int, int> um = {{1,10}, {2,20}, {3,30}, {4,40}};

    // 1. 遍历所有元素
    cout << "遍历所有元素：" << endl;
    for (auto it = um.begin(); it != um.end(); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    cout << endl;

    // 2. 遍历指定桶的元素（比如桶 0）
    size_t bucket_num = 0;
    cout << "\n遍历桶 " << bucket_num << " 的元素：" << endl;
    for (auto it = um.begin(bucket_num); it != um.end(bucket_num); ++it) {
        cout << it->first << ":" << it->second << " ";
    }
    //一个桶多个元素
}

// void test09() {
//     unordered_map<string, int> um;

//     // 获取哈希函数并验证
//     auto hash_func = um.hash_function();
//     string key = "apple";
//     cout << "键 \"" << key << "\" 的哈希值：" << hash_func(key) << endl;

//     // 获取相等判断规则并验证
//     auto eq_func = um.key_eq();
//     string key1 = "apple", key2 = "apple";
//     cout << "key1 与 key2 是否相等：" << boolalpha << eq_func(key1, key2) << endl; // 输出 true
// }