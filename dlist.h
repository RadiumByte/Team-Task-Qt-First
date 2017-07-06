#ifndef DDList_H
#define DDList_H

#include <ostream>
#include <QTextStream>

using namespace std;

class DList
{
public:
    DList();
    DList(const DList &l);
    DList &operator=(const DList &l);
    ~DList();

    // returns the count of elements
    size_t size() const;

    bool is_empty() const
    {
        return first == nullptr && last == nullptr;
    }

    void push_back(const int &x);
    void pop_back();
    int back() const;

    void push_front(const int &x);
    void pop_front();
    int front() const;

private:
    struct node
    {
        int data;
        node *prev, *next;
    };

    node *first, *last;
    void copy_DList(const node *from_first, const node *from_last);
    void delete_DList();

public:
    class DIterator
    {
        node *current;
        DList *collection;
        DIterator(DList *collection, node *current);
    public:
        int &operator*();

        // increment (prefix)
        DIterator &operator++();
        // increment (postfix)
        DIterator operator++(int);
        // decrement (prefix)
        DIterator &operator--();
        // decrement (postfix)
        DIterator operator--(int);

        bool operator==(const DIterator &it) const;
        bool operator!=(const DIterator &it) const;
        bool operator<(const DIterator &it) const;
        bool operator>(const DIterator &it) const;
        friend class DList;

    }; //--class DIterator--//

    // returns iterator to the head of list
    DIterator begin();

    // returns iterator to the element after last
    DIterator end();

    // returns iterator to the found element X
    DIterator find(const int &x) const;

    // returns interator to the first element larger than X
    DIterator findFEGG(const int &x) const;

    // inserts element after iterator
    void insert_after(const DIterator &it, const int &x);

    // inserts element before iterator
    void insert_before(const DIterator &it, const int &x);

    // deleting element pointed by iterator
    void remove(const DIterator &it);

};  //--class DList--//

std::ostream &operator<<(std::ostream &os, DList &l);
QTextStream &operator<<(QTextStream &os, DList &l);
#endif // DDList_H
