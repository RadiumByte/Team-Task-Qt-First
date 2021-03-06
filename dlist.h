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
    DList(const std::initializer_list<int> & list);
    ~DList();

    size_t size() const;

    bool is_empty() const
    {
        return first == nullptr && last == nullptr;
    }

    void   push_back   (const int &x);
    void   pop_back    ();
    int    back        () const;

    void   push_front  (const int &x);
    void   pop_front   ();
    int    front       () const;
    void   erase       ();

private:
    struct node
    {
        int data;
        node *prev, *next;
    };

    node *first, *last;
    void   copy_DList   (const node *from_first, const node *from_last);
    void   delete_DList ();

public:
    class DIterator
    {
    private:
        node *current;
        DList *collection;
        DIterator(DList *collection, node *current);

    public:
        int &operator*();

        // Increment (prefix)
        DIterator &operator++();
        // Increment (postfix)
        DIterator operator++(int);
        // Decrement (prefix)
        DIterator &operator--();
        // Decrement (postfix)
        DIterator operator--(int);

        bool  operator==  (const DIterator &it) const;
        bool  operator!=  (const DIterator &it) const;
        bool  operator<   (const DIterator &it) const;
        bool  operator>   (const DIterator &it) const;

        friend class DList;

    }; //--class DIterator--//

    DIterator begin();
    DIterator end();

    DIterator find(const int &x);
    DIterator findFEGG(const int &x);

    // Inserting of element after element, pointed by iterator
    void insert_after(const DIterator &it, const int &x);

    // Inserting of element before element, pointed by iterator
    void insert_before(const DIterator &it, const int &x);

    // Deleting of element, pointed by iterator
    void remove(const DIterator &it);

    friend bool operator==(DList &l1, DList &l2);
};   //--class DList--//

std::ostream &operator<<(std::ostream &os, DList &l);
QTextStream &operator<<(QTextStream &os, DList &l);
#endif // DDList_H
