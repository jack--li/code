//
//  main.c
//  test
//
//  Created by lipengfei on 2019/8/18.
//  Copyright © 2019年 lipengfei. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN        51
#define MAX_WORD_COUNT      1000


struct dic {
    char data[MAX_WORD_COUNT][MAX_WORD_LEN];
    int count;
};
struct dic dic;




static int find(char *Word)
{
    for (int i = 0; i < dic.count; i++) {
        if (strcmp(Word, dic.data[i]) == 0) {
            return 0;
        }
    }
    return -1;
}

int AddOneWord(char *Word)
{
    if (find(Word) == 0) {
        return -1;
    } else {
        strcpy(dic.data[dic.count], Word);
        dic.count++;
        return 0;
    }
}

int FindSimilarWordNum(char *Word)
{
    int count = 0;
    int map[255] = {0};
    for (int i = 0; i < strlen(Word); i++) {
        map[Word[i]]++;
    }
    
    for (int i = 0; i < dic.count; i++) {
        int temp[255];
        memcpy(temp, map, sizeof(temp));
        if (strlen(dic.data[i]) != strlen(Word)) {
            continue;
        }
        if (strcmp(Word, dic.data[i]) == 0) {
            continue;
        }
        for (int j = 0; j < strlen(dic.data[i]); j++) {
            int k = temp[dic.data[i][j]]--;
            if (k < 0) {
                continue;
            }
        }
        count++;
    }
    
    return count;
}

void swap(char *str1, char *str2)
{
    char temp_string[51] = {0};
    strcpy(temp_string, str1);
    strcpy(str1, str2);
    strcpy(str2, temp_string);
}

void sort(char (*strings)[51], int count)
{
    for (int i = count - 1; i > 0; i--) {
        for (int j = 0; j <= i - 1; j++) {
            if (strcmp(strings[j], strings[j + 1]) > 0) {
                swap(strings[j], strings[j + 1]);
            }
        }
    }
}

int FindOneSimilarWord(const char *Word, int Seq, char *SimilarWord)
{
    int map[255] = {0};
    struct dic brother_dic;
    
    memset(&brother_dic, 0, sizeof(brother_dic));
    for (int i = 0; i < strlen(Word); i++) {
        map[Word[i]]++;
    }
    
    for (int i = 0; i < dic.count; i++) {
        int temp[255];
        memcpy(temp, map, sizeof(temp));
        if (strlen(dic.data[i]) != strlen(Word)) {
            continue;
        }
        if (strcmp(Word, dic.data[i]) == 0) {
            continue;
        }
        for (int j = 0; j < strlen(dic.data[i]); j++) {
            int k = temp[dic.data[i][j]]--;
            if (k < 0) {
                continue;
            }
        }
    
        strcpy(brother_dic.data[brother_dic.count], dic.data[i]);
        brother_dic.count++;
    }
    
    if (Seq > brother_dic.count) {
        *SimilarWord = '\0';
        return -1;
    }
    
    sort(brother_dic.data, brother_dic.count);
    strcpy(SimilarWord, brother_dic.data[Seq - 1]);
    return 0;
}


void Log()
{
    for (int i = 0; i < dic.count; i++) {
        printf("%s\n", dic.data[i]);
    }
    return ;
}
void ClearAllWords(void)
{
    memset(&dic, 0, sizeof(dic));
}

int main()
{
    AddOneWord("abc");
    AddOneWord("abc");
    AddOneWord("bac");
    AddOneWord("bac");
    AddOneWord("cab");
    AddOneWord("cab");
    AddOneWord("acb");
    AddOneWord("acb");
    AddOneWord("aaab");
    AddOneWord("aaba");
    AddOneWord("abaa");
    AddOneWord("baaa");
    Log();
    int a = FindSimilarWordNum("aaab");
    printf("%d \n", a);
    char p[51] = {0};
    char word[] = "aaab";
   int c =  FindOneSimilarWord(word, 3, p);
    printf("%s\n", p);
    return 0;
}

