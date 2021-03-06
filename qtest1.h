#ifndef QTEST1_H
#define QTEST1_H

#include <QTest>
#include <iostream>
#include <QObject>

class Test_DList : public QObject
{
    Q_OBJECT
public:
    explicit Test_DList(QObject *parent = 0);

private slots: //they should be private
    //DList
    void initTestCase();
    void push_back();
    void push_front();
    void is_empty();
    void pop_back();
    void pop_front();
    void back();
    void front();

    /////////////////////////////////////////////

    void message();

    //DIterator
    void begin();
    void end();
    void find();
    void findFEGG();
    void insert_after();
    void insert_before();
    void remove();
    void cleanupTestCase();
};
#endif // QTEST1_H
