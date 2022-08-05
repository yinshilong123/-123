//
// Created by 张文馨 on 2022/5/15.
//

#ifndef SVC_SUANFA_H
#define SVC_SUANFA_H
#include <string>
#include <iostream>
using namespace std;
const int MAXSIZE=50;

//客户信息结构体
struct customer {
    string customer_name;                     //客户姓名
    string customer_number;                   //身份证号
    string customer_phone;                    //手机号
    int book_tickets;                          //订票量
};
//客户信息链表
struct customerLink {
    customer date;
    customerLink *next;
};
//路线车次信息结构体
struct Route {
    string station;                           //出发站
    string final_station;                     //终点站
    string car_number;                       //车次
    string time;                              //出发时间
    int people_number;                     //乘员定额
    int remaining_tickets;                   //余票量
    customerLink *customerLink;               //指向客户的链表
};
//路线车次信息链表
struct RouteLink {
    Route date;
    RouteLink *next;
};

//路线车次信息链表
struct HouBu {
    string car_number;                       //车次
    string customer_name;                     //客户姓名
    string customer_number;                   //身份证号
    string customer_phone;                    //手机号
    int book_tickets;                          //订票量
};


struct Queue
{
    HouBu data[MAXSIZE];      //存储数据的数组
    int rear,front;         //头尾指针
    int m;                  //用于记录队列中的总人数
};


customer c[3] = {
        {"张1", "100", "188", 15},
        {"李1", "101", "187", 2},
        {"王1", "102", "159", 13} };
customerLink* L = nullptr;

customer c2[3] = {
        {"张2", "100", "188", 15},
        {"李2", "101", "187", 12},
        {"王2", "102", "159", 3} };
customerLink* L2 = nullptr;

customer c3[3] = {
        {"张3", "100", "188", 10},
        {"李3", "101", "187", 10},
        {"王3", "102", "159", 10} };
customerLink* L3 = nullptr;

customer c4[3] = {
        {"张4", "100", "188", 11},
        {"李4", "101", "187", 9},
        {"王4", "102", "159", 10} };
customerLink* L4 = nullptr;

Route R[4] = {
        {"沧州", "唐山",  "111", "下午五点", 50, 20, L},
        {"沧州", "上海",  "222", "下午9点", 50, 20, L2},
        {"沧州", "张家口", "333", "下午4点", 50, 20,  L3},
        {"沧州", "北京",  "444", "下午1点", 50, 20, L4},
};


customerLink* m = nullptr;
RouteLink* p= nullptr;
Route search_R;
customer search_c;
HouBu h;

int A = true;



void menu();                                                                            //开始页面
void ImitList(customerLink *&L);                                                        //初始化客户单链表
void CreateList(customerLink *&L, customer a[], int n);                                 //头插法插入客户信息数据
void ImitList(customerLink *&L);                                                        //初始化客户信息单链表
void DispListc(customerLink *L);                                                        //输出客户信息
void CreateListR(RouteLink *&L, Route a[], int n);                                      //头插法插入路线车次
void ImitListR(RouteLink *&L);                                                          //初始化路线车次信息单链表
void DispListR(RouteLink *L);                                                           //输出路线车次信息
Route fuzhi();                                                                          //赋值
bool ListInsertR(RouteLink *&L, int i, Route route);                                    //将route结构体插入到RouteLink链表中
RouteLink *LocateRoute(RouteLink *L, Route route);                                      //查找路线信息，查找到后返回客户链表指针
int tuipiao(RouteLink *R,customerLink *L, customer customer);                           //使用查找到的客户链表指针，及输入的客户信息退票
bool charu(customerLink*& L, int i, customer customer);                                 //使用查询到的路线信息，将订票客户数据插入到客户链表中
Queue Create_SeQueue();                                                                 //创建一个队列
int Push_SeQueue(Queue *p,HouBu x);                                                     //候补入队
bool isEmpty(Queue *Q);
bool getHead(Queue *Q,HouBu &H);

#endif //SVC_SUANFA_H
