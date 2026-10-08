class Node {
    Character data;
    Node left;
    Node right;

    Node(Character data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }

    Node() {
        this.data = null;
        this.left = null;
        this.right = null;
    }
}

public class HuffmanTreeRebuilder {

    public static Node rebuildHuffmanTree(String s, int[] index) {
        if (index[0] >= s.length()) {
            return null;
        }

        if (s.charAt(index[0]) == '1') {
            index[0]++; // 跳过'1'
            char ch = s.charAt(index[0]);
            index[0]++; // 读取字符
            return new Node(ch);
        } else if (s.charAt(index[0]) == '0') {
            index[0]++; // 跳过'0'
            Node node = new Node();
            node.left = rebuildHuffmanTree(s, index);
            node.right = rebuildHuffmanTree(s, index);
            return node;
        }
        return null;
    }

    // 辅助函数：打印树结构
    public static void printTree(Node root, String prefix) {
        if (root == null) {
            return;
        }

        if (root.data != null) {
            System.out.println(prefix + "Leaf: " + root.data);
        } else {
            System.out.println(prefix + "Internal Node");
        }
        printTree(root.left, prefix + "  ");
        printTree(root.right, prefix + "  ");
    }

    public static void main(String[] args) {
        String encodedTree = "001a1b1c"; // 示例编码
        int[] index = {0}; // 使用数组来传递可变索引
        Node root = rebuildHuffmanTree(encodedTree, index);

        System.out.println("Rebuilt Huffman Tree:");
        printTree(root, "");
    }
}