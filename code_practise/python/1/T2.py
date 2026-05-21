import turtle

# 创建海龟对象
t = turtle.Turtle()

# 设置画笔速度
t.speed(5)

# 设置画笔颜色和宽度
t.pencolor('blue')
t.pensize(3)

# 绘制正方形
for _ in range(4):
    t.forward(100)
    t.right(90)

# 开始填充
t.begin_fill()
t.fillcolor('yellow')

# 绘制圆形
t.circle(50)

# 结束填充
t.end_fill()

# 提起画笔移动到新位置
t.penup()
t.goto(150, 0)
t.pendown()

# 绘制三角形
for _ in range(3):
    t.forward(80)
    t.left(120)

# 隐藏海龟
t.hideturtle()#t.showturtle()

# 设置背景颜色
turtle.bgcolor('green')

# 清除屏幕
# t.clear()

# 重置海龟和屏幕
# t.reset()

# 设置绘图窗口大小和背景颜色
turtle.screensize(600, 400, 'purple')

turtle.done()