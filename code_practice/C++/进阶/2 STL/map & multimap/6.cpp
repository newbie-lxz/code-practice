// lower_bound(key)	返回指向第一个键 ≥ key 的元素的迭代器；若所有键都 < key，返回 end()
// upper_bound(key)	返回指向第一个键 > key 的元素的迭代器；若所有键都 ≤ key，返回 end()


// equal_range（进阶：一次获取 lower+upper）
// map 还提供 equal_range(key)，返回 pair<iterator, iterator>，
// 第一个是 lower_bound(key)，第二个是 upper_bound(key)，等价于一次调用两个函数，更简洁：