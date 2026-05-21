a=[1,2,3,4,5,6,7,8,9]
print(0 in a)
print(1 in a)               #in运算符判断列表是否有要查找的字符，有输出true否则false

my_list = ["apple", "banana", "cherry"]
fruit = "banana"
if fruit in my_list:
    print(f"{fruit} is in the list.")               #f是格式化字符串字面值，相当于%s那类，一个f对应多个变量，无论{fruit}在哪里都行
else:
    print(f"{fruit} is not in the list.")

my_string = "Hello, World!"
print("W" in my_string)                     #检查字符是否在字符串，也可以检查子字符串是否在

my_set = {1, 2, 3}
print(3 in my_set)                          #也用于集合中