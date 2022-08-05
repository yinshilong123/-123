#include <iostream>
#include <string>
#include "suanfa.h"
using namespace std;

Queue queue=Create_SeQueue();

int main() {
    ImitList(L);
    CreateList(L, c, 3);
    ImitList(L2);
    CreateList(L2, c2, 3);
    ImitList(L3);
    CreateList(L3, c3, 3);
    ImitList(L4);
    CreateList(L4, c4, 3);

    ImitListR(p);
    CreateListR(p, R, 4);

    while (A) {

        //选择办理的业务，通过序号进行判断；
        menu();
        cout << "请输入您要办理的业务序号" << endl;

        int B;
        cin >> B;
        Route route;
        switch (B) {
            case 1:
                route = fuzhi();
                ListInsertR(p, 3, route);
                break;
            case 2:
                DispListR(p);
                break;
            case 3:
                RouteLink* q;
                cout << "请输入路线车次" << endl;
                cin >> search_R.car_number;
                q = LocateRoute(p,search_R);
                if(q!=NULL) {
                    cout << "请输入乘客信息" << endl;
                    cin >> search_c.customer_name >> search_c.customer_number >> search_c.customer_phone
                        >> search_c.book_tickets;
                    m = q->date.customerLink;
                    if (q->date.remaining_tickets >= search_c.book_tickets) {
                        charu(m, 1, search_c);
                        cout << "订票成功" << endl;
                        q->date.remaining_tickets -= search_c.book_tickets;
                        //修改路线车次信息的余票量值
                    } else {
                        cout << "票数不足，先将余票订购给客户" << endl;

                        int syxgps;//剩余想购票数
                        syxgps = search_c.book_tickets - q->date.remaining_tickets;
                        search_c.book_tickets = q->date.remaining_tickets;//将余票付给乘客所需票数
                        charu(m, 1, search_c);//乘客将余票全部订购
                        cout << "订票成功" << endl;

                        cout<<"将剩余的想购票数写入候补队列"<<endl;
                        //将剩余的想购票数写入候补队列

                        h.car_number = search_R.car_number;
                        h.customer_name = search_c.customer_name;
                        h.customer_number = search_c.customer_number;
                        h.customer_phone = search_c.customer_phone;
                        h.book_tickets = syxgps;
                        q->date.remaining_tickets -= search_c.book_tickets;

                        int i = Push_SeQueue(&queue, h);
                        if (i != 0)
                            cout << "候补成功" << endl;
                    }
                }
                break;
            case 4:
                cout << "您选择办理退票业务" << endl;
                cout << "请输入路线车次" << endl;
                cin >> search_R.car_number;
                q = LocateRoute(p,search_R);
                if(q!=NULL) {
                    cout << "请输入乘客信息" << endl;
                    cin >> search_c.customer_name >> search_c.customer_number >> search_c.customer_phone
                        >> search_c.book_tickets;
                    m = q->date.customerLink;
                    if (m != NULL) {
                        if (int tphps = tuipiao(q,m, search_c)){
                            q->date.remaining_tickets+=tphps;
                            //判断退票后的余票数是否大于等于队列中第一个排队的人的所需票数
                            //若第一个人所需票数后仍有剩余，查看第二个人所需票数是否够
                            //重复以上步骤

                            //判断队列是否为空
                            if (isEmpty(&queue)){
                                //获取队头元素的值
                                getHead(&queue,h);
                                cout<<h.customer_number<<endl;
                            }

                        }
                    }
                }
                break;
            case 5:
                break;
        }
        if (B == 5) {
            A = false;
        }
    }
    return 0;
}
