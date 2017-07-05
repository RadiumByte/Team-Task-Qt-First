#include <QCoreApplication>
#include "dlist.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DList list;
    list.push_back(5);
    list.push_front(4);
    list.push_back(10);

    for(auto i = list.begin(); i != list.end(); ++i)
        cout << *i << " ";

    return a.exec();
}
