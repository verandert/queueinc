/*队列和有序链表模拟银行业务窗口; 事件驱动(客户到达事件和客户离开事件)*/
#ifndef _BANK_H
#define _BANK_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define closetime 60*17//银行五点关门

typedef struct {
    int OccurTime; //事件发生时刻
    int EventType; //事件发生类型0代表客户到达，1/2/3/4表示1～4号窗口客户离开
}Event;
typedef struct {
    int ArrivalTime; //客户到达时刻
    int Duration; //办理事务时间
}Customer;

typedef int bool;
//单链表数据定义
typedef Event elemtype;
typedef struct LNode
{
    elemtype data;
    struct LNode *next;
}LNode, *LinkList;//链表用做事件表

//队列数据定义
typedef Customer SqElemtype;
typedef struct
{
    SqElemtype *base;
    int front, rear;
}SqQueue;//单向队列

typedef LinkList EventList;
LNode L;
EventList Ev;
Event En, DelEn;
Customer customer;
int TotalTime;
int CustomerNum;
SqQueue q[5];

void InitList(LinkList head);
elemtype GetElem(LinkList head, int i);
elemtype DeleteList(LinkList head, int i);
void InsertList(LinkList head, int i, elemtype data);
bool IsListEmpty(LinkList head);

void InitQueue(SqQueue *Q);
int QueueLength(SqQueue *Q);
void EnQueue(SqQueue *Q, SqElemtype data);
SqElemtype DeQueue(SqQueue *Q);
bool IsQueueEmpty(SqQueue *Q);
SqElemtype GetQueueHead(SqQueue *Q);

#endif