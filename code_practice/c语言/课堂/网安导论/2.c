#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define e 17

int randomnumber(int min, int max);
int is_prime(int num);
int extend_gcd(int a, int b, int *x, int *y);
int mod_inverse(int a, int m);
int mod_pow(int base, int exponent, int modulus);
int rsa_encrypt(int public_key_e, int n, int plaintext);
int rsa_decrypt(int private_key_d, int n, int ciphertext);

int main() {
    srand(time(NULL));
    int min = 1 << 14;
    int max = (1 << 16) - 1;

    // 生成两个不同的素数 p 和 q
    int p = randomnumber(min, max);
    int q = 0;
    do {
        q = randomnumber(min, max);
    } while (q == p || ((p - 1) * (q - 1) % e == 0));


    int Euler_totient_function = (p - 1) * (q - 1);


    int x, y;
    int d = extend_gcd(e, Euler_totient_function, &x, &y);
    if (d == -1) {
        printf("扩展欧几里得算法计算失败，可能 e 和 phi 不互质\n");
        return 0;
    } else {
        d = (x % Euler_totient_function + Euler_totient_function) % Euler_totient_function;
    }


    int n = p * q;


    // 加密和解密过程
    char message[100];
    printf("请输入要加密的明文：\n");
    fgets(message, sizeof(message) / sizeof(char), stdin);
    message[strcspn(message, "\n")] = '\0';
    int len = strlen(message);
    int encrypted_message[len];
    for (int i = 0; i < len; i++) {
        encrypted_message[i] = rsa_encrypt(e, n, (int)message[i]);
    }


    // 输出加密后的消息
    printf("加密后的消息: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", encrypted_message[i]);
    }
    printf("\n");


    // 改进：清除输入缓冲区中的多余字符
    printf("是否进行解密？解密请输入 Y 或者 y\n");
    char judge;
    scanf(" %c", &judge);
    while (getchar()!= '\n');
    if (judge == 'Y' || judge == 'y') {
        // 解密
        char decrypted_message[len + 1];
        for (int i = 0; i < len; i++) {
            decrypted_message[i] = (char)rsa_decrypt(d, n, encrypted_message[i]);
        }
        decrypted_message[len] = '\0';
        printf("解密后的消息: %s\n", decrypted_message);
    }


    return 0;
}


// 生成随机数
int randomnumber(int min, int max) {
    int prime = 0;
    do {
        prime = min + rand() % (max - min + 1);
    } while (is_prime(prime) == 0);
    return prime;
}


// 判断是否是素数
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num == 2 || num == 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    int i = 5;
    while (i * i <= num) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
        i += 6;
    }
    return 1;
}


// 扩展欧几里得算法
int extend_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extend_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}


// 计算模逆元
int mod_inverse(int a, int m) {
    int x, y;
    int g = extend_gcd(a, m, &x, &y);
    if (g!= 1) {
        printf("模逆元不存在\n");
        exit(EXIT_FAILURE);
    } else {
        return (x % m + m) % m;
    }
}


// 快速幂取模运算
int mod_pow(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}


// RSA 加密
int rsa_encrypt(int public_key_e, int n, int plaintext) {
    return mod_pow(plaintext, public_key_e, n);
}


// RSA 解密
int rsa_decrypt(int private_key_d, int n, int ciphertext) {
    return mod_pow(ciphertext, private_key_d, n);
}