#include"dlist.h"
#include"utility.h"
#include<limits>
#include<QString>
#include<QTextStream>
#include<iostream>

using namespace std;

void Program1(DList &list1)
{
    cout<<"The line terminator is '.'"<<endl;
    QString b;
    QTextStream IN(stdin);
    int max=numeric_limits<int>::min();

    do
    {
        IN>>b;
        if (b=='.')
            break;
        else
            if (list1.is_empty())    // если пустой - добавляем
            {
                list1.push_front(b.toInt());
                max=b.toInt();
            }
            else
                if (list1.find(b.toInt())==list1.end())  // если нет повторений
                {
                    if (b.toInt()>max)
                    {
                        max=b.toInt();
                        list1.push_back(b.toInt());
                    }
                    else
                        list1.insert_before(list1.findFEGG(b.toInt()),b.toInt());
                }

    }
    while (b!='.');

    if (list1.is_empty()) throw std::runtime_error("List is empty");
    else cout<<list1;
}
