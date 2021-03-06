#include <QCoreApplication>
#include <QTest>
#include <iostream>

#include "qtest1.h"
#include "dlist.h"
#include "utility.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTest::qExec(new Test_DList,argc, argv);
    DList list;

    cout << "The Program terminator is '/'" << endl;
    cout << "Next test '*'" << endl;
    char b;
    cout << "Print Teminator" << endl;
    cin >> b;
    while (b != '/')
    {
        Program1(list);
        cout << "Print Teminator" << endl;
        cin >> b;
        list.erase();

    }
    cout << "END PROGRAM" << endl;
    return a.exec();
}
