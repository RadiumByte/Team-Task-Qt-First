#include <QCoreApplication>
#include <iostream>
#include "dlist.h"
#include "utility.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    try
    {
        DList list;
        Task(list);
    }
    catch (std::runtime_error e)
    {
        cout << e.what() << endl;
    }
    catch (std::exception e)
    {
        cout << e.what() << endl;
    }

    return a.exec();
}
