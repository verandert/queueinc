### 模拟随机事件--银行一天客户平均逗留时间
随机数模拟客户到达时间（0～5分钟）及办理事务时间（10～30分钟）；   
链表作为事件表，四个队列表示四个办事窗口；
```shell
gcc -o bank bank.c squeue.c linklist.c
./bank
```
