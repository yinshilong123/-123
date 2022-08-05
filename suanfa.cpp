//
// Created by 张文馨 on 2022/5/15.
//


/*
 * 在执行插入车次信息时
 * 1、从键盘录入车次信息
 * 2、判断成员定额和余票量之间的关系
 * 3、输入客户名单信息
 * 4、判断客户订票数和已经订出去的票的关系（成员定额-余票量）
 * 5、将客户信息利用头插法插入客户链表
 * 6、插入车次信息
 */


/*
 * 退票操作
 * 1、输入车次信息，可以只输入车次号
 * 2、根据车次号查找本车次的车次指针，并返回客户链表指针
 * 3、输入乘客信息
 * 4、根据查找到的酷户链表指针查找乘客信息
 * 5、退票
 */

#include "suanfa.h"
//页面函数
void menu() {
    cout << "-------------------------------------------" << endl;
    cout << "----------欢迎来到沧州客运站定票系统------------" << endl;
    cout << "-----------------1、录入信息-----------------" << endl;
    cout << "-----------------2、查询路线-----------------" << endl;
    cout << "-----------------3、定票业务-----------------" << endl;
    cout << "-----------------4、退票业务-----------------" << endl;
    cout << "-----------------5、退出系统-----------------" << endl;
    cout << "-------------------------------------------" << endl;
}


//头插法插入客户信息数据
void CreateList(customerLink *&L, customer a[], int n) {
    customerLink *s;
    L = new customerLink;                                            //分配储存空间
    L->next = NULL;                                                  //初始化
    for (int i = 0; i < n; i++) {
        s = new customerLink;                                        //分配内存空间
        s->date = a[i];
        s->next = L->next;
        L->next = s;
    }
}

//初始化客户信息单链表
void ImitList(customerLink *&L) {
    L = new customerLink;
    L->next = NULL;                                                  //初始化
}

//输出客户信息
void DispListc(customerLink *L) {
    customerLink *p = L->next;
    while (p != NULL) {
        printf("乘客姓名：%s\t", p->date.customer_name.c_str());
        printf("乘客手机号：%s\t", p->date.customer_phone.c_str());
        printf("乘客购票量：%d\n", p->date.book_tickets);
        p = p->next;
    }
}

//头插法插入路线车次
void CreateListR(RouteLink *&L, Route a[], int n) {
    RouteLink *s;
    L = new RouteLink;                                              //new相当于malloc
    L->next = NULL;
    for (int i = 0; i < n; i++) {
        s = new RouteLink;
        s->date =  a[i];
        s->next = L->next;
        L->next = s;
    }
}

//初始化路线车次信息单链表
void ImitListR(RouteLink *&L) {
    L = new RouteLink;
    L->next = NULL;
}

//输出路线车次信息
void DispListR(RouteLink *L) {
    RouteLink *p = L->next;
    while (p != NULL) {
        printf("出发站：沧州\t");
        printf("终点站：%s\t", p->date.final_station.c_str());      //将string转化为char的数组输出
        printf("车次：%s\t", p->date.car_number.c_str());
        printf("出发时间：%s\t", p->date.time.c_str());
        printf("乘员定额：%d\t", p->date.people_number);
        printf("余票量：%d\n", p->date.remaining_tickets);
        customerLink *q = p->date.customerLink;                    //将车次的单链表放到q中
        DispListc(q);                                           //输出客户链表
        p = p->next;
    }
}

//赋值
Route fuzhi() {
    Route route;
    int n;
    customer customer[1024];                                       // 乘客信息数组
    printf("请输入终点站名、车次、出发时间、乘员定额、余票量。\n");
    cin >> route.final_station >> route.car_number >> route.time >> route.people_number >> route.remaining_tickets;
    printf("请输入客户数。\n");
    cin >> n;
    //判断余票数是否大于成员定额，如果大于说明输入有误需要重新输入
    if (route.people_number < route.remaining_tickets) {
        cout << "输入错误，请重新输入" << endl;
        fuzhi();
    } else {
        if (n <= route.people_number - route.remaining_tickets)                       //如果人数少于定票量，则把乘客信息写入乘客数组
        {
            int j;
            do {
                j = 0;
                for (int i = 0; i < n; ++i) {
                    printf("请输入第%d个乘客的信息\n", i + 1);
                    cin >> customer[i].customer_name >> customer[i].customer_number >> customer[i].customer_phone
                        >> customer[i].book_tickets;
                    j += customer[i].book_tickets;
                }
            } while (j != route.people_number - route.remaining_tickets);//如果乘客总的订票数不等于成员定额减去余票说明输入的客户信息有误需要重新输入
            //创建客户链表
            customerLink *L;
            //利用头插法插入客户链表
            CreateList(L, customer, n);
            route.customerLink = L;
            return route;
        }
    }
}

//将route结构体插入到RouteLink链表中
bool ListInsertR(RouteLink *&L, int i, Route route) {
    int j = 0;
    RouteLink *p = L, *s;                                     //p指向头节点
    if (i < 0)
        return false;
    while (j < i + 1 && p != NULL) {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else {
        s = new RouteLink;
        s->date = route;
        s->next = p->next;
        p->next = s;
        return true;
    }
}

//查找客户链表，查找客户订票信息
//当客户将购买的票退完后，删除客户信息
//退票
//查找路线信息，查找到后返回路线车次链表指针
RouteLink *LocateRoute(RouteLink *L, Route route) {
    int i = 0;
    customerLink *m= nullptr;
    RouteLink *p = L->next;
    while (p != NULL && p->date.car_number != route.car_number) {
        p = p->next;
        i++;
    }
    if (p != NULL) {
        return p;
    } else{
        cout<<"没找到路线车次"<<endl;
        return p;
    }

}

//使用查找到的客户链表指针，及输入的客户信息退票
int tuipiao(RouteLink *R,customerLink *L, customer customer) {
    int piaoshu;
    cout << "请输入退票数" << endl;
    cin >> piaoshu;
    int i = 1;
    customerLink *p = L, *q = L->next;
    while (q != NULL && q->date.customer_number != customer.customer_number) {
        p = q;
        q = q->next;
        i++;
    }
    if (q != NULL) {
        //判断票数
        if (q->date.book_tickets - piaoshu == 0) {
            R->date.remaining_tickets+=piaoshu;
            p->next = q->next;
            delete q;
            return R->date.remaining_tickets;
        } else if (q->date.book_tickets - piaoshu >= 0){
            q->date.book_tickets -= piaoshu;
            R->date.remaining_tickets+=piaoshu;
            return R->date.remaining_tickets;
        } else{
            cout<<"退票失败"<<endl;
            return 0;
        }
        //退票后余票量增加
    }else{
        cout<<"没找到乘客信息"<<endl;
        return 0;
    }
}

//订票
//先查询路线信息，通过路线信息查找
bool charu(customerLink*& L, int i, customer customer)
{
    int j = 0;
    customerLink* p = L, * s;
    if (i <= 0)
        return false;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else
    {
        s = new customerLink;
        s->date = customer;
        s->next = p->next;
        p->next = s;
        return true;
    }
}

//创建一个队列
Queue Create_SeQueue()
{
    Queue* p;
    p = new Queue;
    p->rear = -1;
    p->front = -1;
    p->m = 0;
    return *p;
}
//入队操作
int Push_SeQueue(Queue *p,HouBu x)
{
    if(p->m == MAXSIZE)
        return 0;
    else
    {
        p->data[++(p->rear)] = x;
        return 1;
    }
}


bool isEmpty(Queue *Q){
    return (Q->front==Q->rear);
}
bool getHead(Queue *Q,HouBu &H){
    if (Q->front == Q->rear){
        return false;
    } else{
        H = Q->data[Q->front];
        return true;
    }
}

