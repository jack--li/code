// 二级：垃圾短信发送者，采用有向图
//  main.c
//  test
//
//  Created by lipengfei on 2019/8/18.
//  Copyright © 2019年 lipengfei. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORD_ID 100
int record[100][100];
int L = 2;
int M = 2;
int N = 2;

void AppendSmsRecord(unsigned int SenderId, unsigned int ReceiveId)
{
    record[SenderId][ReceiveId]++;
}

unsigned int IsJunkSmsSmsSender(unsigned int SenderId)
{
    int num = 0;
    //A发送短信的接收者中，没有发送给A的人数 > L
    for (int i = 0; i < MAX_RECORD_ID; i++) {
        if (record[SenderId][i] > 0) {
            if (record[i][SenderId] == 0) {
                num++;
            }
        }
    }
    if (num > L) {
        return 1;
    }
    
    num = 0;
    //A发送的短信数-A接收的短信数 > M
    for (int i = 0; i < MAX_RECORD_ID; i++) {
        num += record[SenderId][i];
        num -= record[i][SenderId];
    }
    if (num > M) {
        return 1;
    }
    
    //如果存在x， A发送给X的短信数-X发送给A的短信数 N
    for (int i = 0; i < MAX_RECORD_ID; i++) {
        if (record[SenderId][i] - record[i][SenderId] > N) {
            return 1;
        }
    }
    
    return 0;
}

void Clear(void)
{
    memset(record, 0, sizeof(record));
}


int main()
{
    AppendSmsRecord(1, 2);
    AppendSmsRecord(1, 3);
    printf("%d\n", IsJunkSmsSmsSender(1));
    return 0;
}

