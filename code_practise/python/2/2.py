a = [1,2,3]
a.append(1)         
print(a)            #往后面加数

a.pop()
print(a)            #删数，无参数删最后一个

a.pop(1)
print(a)            #有参数删脚标对应的（0对应第一个，以此类推）

b = [1,1,1,5,2,2,3,4]
b.remove(1)
print(b)            #移除第一个等于参数的数

b.insert(0,1)       #在指定位置插入数字，在0号位插入1

print(len(b))       #长度

c = [1,2,3]
c.reverse()
print(c)            #逆转列表

print(b[3])
print(b[-1])        #访问具体值，和从数组一样从0开始，负数是倒数第几个，-1是倒数第一个

print(b[1:4])       #访问脚标1到3
print(b[1:])        #访问脚标1到最后
print(b[:])         #访问全部
print(b[-2:])       #从倒数第二个开始访问

b.sort()
print(b)            #从小到大排序，逆序再用reverse

d = [1,2,3,4]
e = [5,6,7,8]
f=d+e
print(f)            #+连接两个列表