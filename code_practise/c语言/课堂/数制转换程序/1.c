#include <stdio.h>
#include <string.h>
#include <math.h>

// 8进制转十进制
void O(int len, char num[]);
// 2进制转十进制
void B(int len, char num[]);
// 16进制转十进制
void H(int len, char num[]);

int main(int argc, char *argv[]) {
    if (argc == 3) {
        int a, b;
        // 正确比较命令行参数
        if (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-b") == 0) {
            a = 2;
            b = 1;
        } else {
            a = 1;
            b = 2;
        }
        char num[strlen(argv[a]) + 1];
        strcpy(num, argv[a]);
        int len = strlen(num);
        if (strcmp(argv[b], "-o") == 0) {
            O(len, num);
        } else if (strcmp(argv[b], "-b") == 0) {
            B(len, num);
        } else {
            H(len, num);
        }
    } else if(argc == 2) {
        char num[strlen(argv[1]) + 1];
        strcpy(num, argv[1]);
        int len = strlen(num);
        O(len, num);
    }else{
        printf("Usage: 1.exe [-o]R[-b][-h] target\n");
        printf("-o the target is an octal number\n");   
        printf("-b the target is a binary number\n");
        printf("-h the target is a hexadecimal number\n");
        printf("If all optional parameters are omitted, by default, the target is an octal number\n");
    }
    return 0;
}

void O(int len, char num[]){
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += (num[len - i - 1] - '0') * pow(8, i);
    }
    printf("The decimal value is:%d", sum);
}

void B(int len, char num[]){
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += (num[len - i - 1] - '0') * pow(2, i);
    }
    printf("The decimal value is:%d", sum);
}

void H(int len, char num[]){
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (num[len - i - 1] >= '0' && num[len - i - 1] <= '9') {
            sum += (num[len - i - 1] - '0') * pow(16, i);
        } else if (num[len - i - 1] >= 'A' && num[len - i - 1] <= 'F') {
            sum += (num[len - i - 1] - 'A' + 10) * pow(16, i);
        } else if (num[len - i - 1] >= 'a' && num[len - i - 1] <= 'f') {
            sum += (num[len - i - 1] - 'a' + 10) * pow(16, i);
        }
    }
    printf("The decimal value is:%d", sum);
}