#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 定义结构体来存储文件信息
typedef struct {
    char name[1024];        // 记录文件名称
    time_t mtime;           // 记录文件修改时间
    int file_type_priority; // 标记文件类型优先级
} FileInfo;

//根据文件修改时间排序（降序）
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

//根据文件类型优先级排序
int compare_file_type_priority(const void *a, const void *b)
{
    const FileInfo *fileA = (const FileInfo *)a;
    const FileInfo *fileB = (const FileInfo *)b;

    return fileA->file_type_priority - fileB->file_type_priority;
}

//根据文件扩展名确定文件类型优先级
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
void traverse_path(const char *path, FileInfo *fileInfos, int *count)
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
                traverse_path(file_path, fileInfos, count);
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

    traverse_path(path, fileInfos, &count);

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

    system("PAUSE");

    return 0;
}