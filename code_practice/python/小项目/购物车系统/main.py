import subprocess
import platform

def clear():
    if platform.system() == "Windows":
        subprocess.run("cls", shell=True)
    else:
        subprocess.run("clear", shell=True)

menu = """
################################
        1.添加购物车
        2.修改购物车
        3.删除购物车
        4.查询购物车
        5.退出购物车
################################
"""
shopping_cart = {}

while True:
    clear()
    print(menu)
    choice = input("请输入您的选择：")
    match choice:
        case "1":
            item = input("请输入要添加的商品名称：")
            if item in shopping_cart:
                print(f"{item}已经在购物车当中，请勿重复添加")
            else:
                price = float(input("请输入商品价格："))
                number= int(input("请输入商品数量："))
                shopping_cart[item] = {"价格": price, "数量": number}
                print(f"{item}已成功添加到购物车！")
        case "2":
            item = input("请输入要修改的商品名称：")
            if item in shopping_cart:
                price = float(input("请输入新的商品价格："))
                number = int(input("请输入新的商品数量："))
                shopping_cart[item] = {"价格": price, "数量": number}
                print(f"{item}已成功修改！")
            else:
                print(f"{item}不在购物车中，请先添加该商品！")
        case "3":
            item = input("请输入要删除的商品名称：")
            if item in shopping_cart:
                del shopping_cart[item]
                print(f"{item}已成功从购物车中删除！")
            else:
                print(f"{item}不在购物车中，请先添加该商品！")
        case "4":
            if shopping_cart:
                print("购物车中的商品如下：")
                for item, info in shopping_cart.items():
                    print(f"{item} - 价格: {info['价格']}, 数量: {info['数量']}")
            else:
                print("购物车为空！")
        case "5":
            print("感谢使用购物车系统，再见！")
            input("\n按回车键退出") 
            break
        case _:
            print("无效的选择，请重新输入！")
    input("\n按回车键返回菜单...")
