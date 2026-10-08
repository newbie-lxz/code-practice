class Node:
    def __init__(self, data=None):
        self.data = data
        self.left = None
        self.right = None

def rebuild_huffman_tree(s, index):
    if index[0] >= len(s):
        return None

    if s[index[0]] == '1':
        index[0] += 1  # 跳过'1'
        ch = s[index[0]]
        index[0] += 1  # 读取字符
        return Node(ch)
    elif s[index[0]] == '0':
        index[0] += 1  # 跳过'0'
        node = Node()
        node.left = rebuild_huffman_tree(s, index)
        node.right = rebuild_huffman_tree(s, index)
        return node
    return None

# 辅助函数：打印树结构
def print_tree(root, prefix=""):
    if root is None:
        return

    if root.data is not None:
        print(f"{prefix}Leaf: {root.data}")
    else:
        print(f"{prefix}Internal Node")
    print_tree(root.left, prefix + "  ")
    print_tree(root.right, prefix + "  ")

# 使用示例
if __name__ == "__main__":
    encoded_tree = "001a1b1c"  # 示例编码
    index = [0]  # 使用列表来传递可变索引
    root = rebuild_huffman_tree(encoded_tree, index)

    print("Rebuilt Huffman Tree:")
    print_tree(root)