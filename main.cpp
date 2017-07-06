#include <QCoreApplication>
#include "dlist.h"
#include <iostream>
#include"utility.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DList list;
    Program1(list);

    return a.exec();
}
