import turtle as t

def draw_rose():
    t.hideturtle()
    t.speed(9)
    t.pencolor('red')

    # 绘制玫瑰
    for _ in range(36):
        t.circle(10, 90)
        t.left(10)
        t.circle(10, 90)
        t.left(190)

    t.done()

draw_rose()
