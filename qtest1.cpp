#include "dlist.h"
#include "qtest1.h"
#include "utility.h"

using namespace  std;

Test_DList::Test_DList(QObject *parent) :
    QObject(parent)
{}

void Test_DList::initTestCase()
{   cout << "________________________________________________________________" << endl;
    cout << "START TESTS!!!" << endl;
}

void Test_DList::push_back()
{
    DList mc = {1,2,3,4};
    DList expected = {1,2,3,4,5};
    mc.push_back(5);
    QVERIFY(mc == expected);
}
void Test_DList::push_front()
{
    DList mc;
    DList expected = {1};
    mc.push_front(1);
    QVERIFY2(mc == expected, "Test 1:push_front FAIL");
    DList mc1 = {5,1,2};
    DList expected1 = {6,5,1,2};
    mc1.push_front(6);
    QVERIFY2(mc1 == expected1, "Test 2:push_front FAIL");
}

void Test_DList::is_empty()
{
    DList mc = {};
    QVERIFY2(mc.is_empty() == true, "Test 1:is_empty FAIL");
    mc = {1,2,3,4};
    QVERIFY2(mc.is_empty() == false, "Test 2:is_empty FAIL");
}

void Test_DList::pop_back()
{
    DList mc = {1,2,3,4,5};
    DList expected = {1,2,3,4};
    mc.pop_back();
    QVERIFY2(mc == expected, "Test 1:pop_back FAIL");
    DList mc1 = {};
    DList expected1 = {};
    mc1.pop_back();
    QVERIFY2(mc1 == expected1, "Test 2:pop_back FAIL");
}
void Test_DList::pop_front()
{
    DList mc = {1,2,3,4};
    DList expected = {2,3,4};
    mc.pop_front();
    QVERIFY2(mc == expected, "Test 1:pop_front FAIL");
    DList mc1 = {};
    DList expected1 = {};
    mc1.pop_front();
    QVERIFY2(mc1 == expected1, "Test 2:pop_front FAIL");
}
void Test_DList::back()
{
    DList mc = {1,2,3,4};
    QVERIFY(mc.back() == 4);
}
void Test_DList::front()
{
    DList mc = {1,2,3,4};
    QVERIFY(mc.front() == 1);
}

void Test_DList::message()
{
    cout << "START TEST CLASS DITERATOR" << endl;
}

//DIterator
void Test_DList::begin()
{
    DList mc = {1,2,3,4};
    QVERIFY(*(mc.begin()) == 1);
}
void Test_DList::end()
{
    bool flag;
    DList mc = {1,2,3,4};
    try
    {
        mc.end();
        flag = true;
        QVERIFY(*(mc.end()) == 4 && flag);
    }
    catch(std::out_of_range e)
    {
        flag = false;
    }
}

void Test_DList::find()
{
    DList mc = {1,2,3,4};
    QVERIFY(*(mc.find(3)) == 3);
}
void Test_DList::findFEGG()
{
    DList mc = {1,5,3,4};
    QVERIFY(*(mc.findFEGG(3)) == 5);
}
void Test_DList::insert_after()
{
     DList mc = {1,5,3,4};
     DList expected = {1,5,3,6,4};
     mc.insert_after(mc.find(3),6);
     QVERIFY(mc == expected);
}
void Test_DList::insert_before()
{
    DList mc = {1,5,3,4};
    DList expected = {1,5,6,3,4};
    mc.insert_before(mc.find(3),6);
    QVERIFY(mc == expected);
}
void Test_DList::remove()
{
    DList mc = {1,5,3,4};
    DList expected = {1,3,4};
    mc.remove(mc.find(5));
    QVERIFY2(mc == expected, "Test 1:remove FAIL");
    DList mc1 = {1,5,3,4};
    DList expected1 = {5,3,4};
    mc1.remove(mc1.find(1));
    QVERIFY2(mc1 == expected1, "Test 2:remove FAIL");
    DList mc2 = {1,5,3,4};
    DList expected2 = {1,5,3};
    mc2.remove(mc2.find(4));
    QVERIFY2(mc2 == expected2, "Test 3:remove FAIL");
}

void Test_DList::cleanupTestCase()
{
    cout << "END TESTS!!!" << endl;
    cout << "________________________________________________________________" << endl;

}
