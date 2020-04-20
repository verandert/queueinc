#include "./bank.h"

void OpenForDay();
int MinLengthQueue();
void OrderInsert(Event En);
void CustomerArrival();
void CustomerDeparture();
void bank_simulation();
   
int main()
{
    srand((unsigned)time(NULL));
    Ev = &L;
    bank_simulation();
    return 0;
}

//银行开门--即事件表，四个队列窗口初始化；
void OpenForDay()
{
    InitList(Ev); En.OccurTime = 0; En.EventType = 0;
    InsertList(Ev, 1, En);
    for (int i = 1; i < 5; i++)
    {
        InitQueue(&q[i]);
    }
}

//返回某时刻最短队列
int MinLengthQueue()
{
    int min = 1;
    for (int i = 2; i < 5; i++)
    {
        if (QueueLength(&q[i]) < QueueLength(&q[min])) min = i;
    }
    return min;
}

//按事件发生时刻将事件插入有序事件表中，并保持有序；
void OrderInsert(Event En)
{
    LinkList p, q;
    q = Ev;
    p = Ev->next;
    while (p && p->data.OccurTime < En.OccurTime)
    {
        q = p;
        p = p->next;
    }
    p = (LinkList)malloc(sizeof(LNode));
    if(!p) {printf("内存分配失败"); exit(-1);}
    p->next = q->next;
    p->data = En;
    q->next = p;     
}

//客户到达事件，用随机数模拟客户到达时间及办理事务需要的时间；
void CustomerArrival()
{
    int i, intertime, duration;
    ++CustomerNum;
    intertime = rand()%5 + 1;//表示0～5分钟内有客户到达      
    duration = rand()%21+ 10;//该客户的办理事件为10～30分钟
    //printf("(%d, %d)", intertime, duration);
    i = MinLengthQueue(); customer.ArrivalTime =DelEn.OccurTime; customer.Duration = duration;
    EnQueue(&q[i], customer);//进最短队列;
    if(QueueLength(&q[i])==1){//插入队列前为空，则插入离开事件;
        En.OccurTime = customer.ArrivalTime + duration;
        En.EventType = i;
        OrderInsert(En);
    }
    DelEn.OccurTime = DelEn.OccurTime + intertime;
    DelEn.EventType = 0;
    if(DelEn.OccurTime < closetime) OrderInsert(DelEn);//插入到达事件;
}

//客户离开事件
void CustomerDeparture()
{
    int i;
    i = DelEn.EventType; customer = DeQueue(&q[i]);
    //客户离开事件发生时刻大于下班时,则事件发生时刻按下班时间算。
    if(DelEn.OccurTime > closetime) TotalTime += closetime - customer.ArrivalTime;
    else TotalTime += DelEn.OccurTime - customer.ArrivalTime;
    //printf("(%d %d)", customer.ArrivalTime, DelEn.OccurTime);
    if(!IsQueueEmpty(&q[i]))//客户离开事件发生意味着插入另一个离开事件；
    {
        customer = GetQueueHead(&q[i]);
        DelEn.OccurTime = DelEn.OccurTime + customer.Duration;
        DelEn.EventType = i;
        OrderInsert(DelEn);
    }
}

//模拟银行客户平均逗留时间
void bank_simulation()
{
    OpenForDay();
    while(!IsListEmpty(Ev))
    {
        DelEn = DeleteList(Ev, 1);//取出事件表的头节点
        if(DelEn.EventType == 0) CustomerArrival();
        else CustomerDeparture();
    }
    printf("5分钟之内就有一个客户进入银行办事, 该客户且办理业务时间在10分钟～30分钟之间。银行共有四个办事窗口，银行下班时间为17点:\n");
    printf("客户平均待在银行时间为:");
    printf("%.2f分钟\n", ((float)TotalTime / (float)CustomerNum));
}
