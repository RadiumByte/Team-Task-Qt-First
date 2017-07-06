#include "dlist.h"

void DList::delete_DList()
{
    while (first != last)
    {
        node *t = first;
        first = first->next;
        delete t;
    }
    delete last;
    first = nullptr;
    last = nullptr;
}

DList::DList()   // default constructor
{
    first = last = nullptr;
}

DList::DList(const DList & l)   // copy constructor
{
    copy_DList(l.first, l.last);
}

void DList::copy_DList(const node * from_first, const node * from_last)
{
    first = nullptr;
    last = nullptr;

    node **to = &first;
    const node *from = from_first;
    while (from != from_last->next)
    {
        node *prev = *to;
        *to = new node;

        (*to)->prev = prev;
        (*to)->data = from->data;
        to = &(*to)->next;

        from = from->next;
    }
    *to = nullptr;
    last = *to;
}

DList & DList::operator=(const DList & l)
{
    delete_DList();
    copy_DList(l.first, l.last);
    return *this;
}

DList::~DList()
{
    delete_DList();
}

void DList::push_back(const int & x)
{
    if (last == nullptr)
    {
        last = new node;
        last->prev = nullptr;
        last->next = nullptr;
        first = last;
    }
    else
    {
        last->next = new node;
        last->next->prev = last;
        last = last->next;
    }
    last->data = x;
    last->next = nullptr;
}

void DList::pop_back()
{
    if (last == nullptr)
        throw std::runtime_error("List is empty");
    else
    {
        node* to_delete = last;
        last = last->prev;
        last->next = nullptr;
        delete to_delete;
    }
}

int DList::back() const
{
    if (is_empty())
        throw std::out_of_range("List is empty");
    return last->data;
}

int DList::front() const
{
    if (is_empty())
        throw std::out_of_range("List is empty");
    return first->data;
}

void DList::push_front(const int &x)
{
    if (first == nullptr)
    {
        first = new node;
        first->next = nullptr;
        last = first;
    }
    else
    {
        first->prev = new node;
        first->prev->next = first;
        first = first->prev;
    }
    first->data = x;
    first->prev = nullptr;
}

void DList::pop_front()
{
    if (first == nullptr)
        return;
    else
    {
        node* to_delete = first;
        first = first->next;
        first->prev = nullptr;
        delete to_delete;
    }
}

size_t DList::size() const
{
    if (is_empty())
        return 0;
    size_t count = 0;
    node* current_in_DList = first;
    while (current_in_DList != last)  // counting of elements
    {
        count++;
        current_in_DList = current_in_DList->next;
    }
    return count + 1;
}

// Two overloads of stream output
std::ostream &operator<<(std::ostream &os, DList &l)
{
    for (DList::DIterator i = l.begin(); i != l.end(); ++i)
        os << *i << " ";
    os<<std::endl;
    return os;
}

QTextStream &operator<<(QTextStream &os, DList &l)
{
    for (DList::DIterator i = l.begin(); i != l.end(); ++i)
        os << *i << " ";
    return os;
}
/////////////////////////////////////////

DList::DIterator DList::begin()
{
    DIterator to_return(this, this->first);
    return to_return;
}

DList::DIterator::DIterator(DList *collection, node *current) : collection(collection), current(current)
{}

DList::DIterator DList::end()
{
    DIterator to_return(this, this->last->next);
    return to_return;
}

int& DList::DIterator::operator*()
{
    // if current position of iterator is null
    if (*this == this->collection->end())
        throw std::out_of_range("Out of range in list");

    return this->current->data;
}

DList::DIterator& DList::DIterator::operator++()
{
    if (this->current == nullptr)
        throw std::out_of_range("Out of range in list");

    this->current = this->current->next;
    return *this;
}

DList::DIterator DList::DIterator::operator++(int)
{
    DIterator old(this->collection, this->current);

    if (this->current == nullptr)
        throw std::out_of_range("Out of range in list");

    this->current = this->current->next;
    return old;
}

DList::DIterator& DList::DIterator::operator--()
{
    if (this->current == nullptr)
        throw std::out_of_range("Out of range in list");

    this->current = this->current->prev;
    return *this;
}

DList::DIterator DList::DIterator::operator--(int)
{
    DIterator old(this->collection, this->current);

    if (this->current == nullptr)
        throw std::out_of_range("Out of range in list");

    this->current = this->current->prev;
    return old;
}

bool DList::DIterator::operator==(const DIterator &it) const
{
    if (this->collection == it.collection && this->current == it.current)
        return true;
    return false;
}

bool DList::DIterator::operator!=(const DIterator &it) const
{
    return !(it == *this);
}

bool DList::DIterator::operator <(const DIterator &it) const
{
    return (this->current->data>it.current->data);
}

bool DList::DIterator::operator >(const DIterator &it) const
{
    return (this->current->data<it.current->data);
}

DList::DIterator DList::find(const int &x) const
{
    DIterator DList_DIterator = this->begin();
    DIterator end_DIterator = this->end();
    while (DList_DIterator != end_DIterator)
    {
        if (*DList_DIterator == x)
            return DList_DIterator;
        ++DList_DIterator;
    }
    return end_DIterator;
}

DList::DIterator DList::findFEGG(const int &x) const
{
    DIterator DList_DIterator = this->begin();
    DIterator end_DIterator = this->end();
    if (this->size() > 1)
    {
        if ((DList_DIterator.current->prev == nullptr) && (DList_DIterator.current->data > x))
            return DList_DIterator;
        while (DList_DIterator != end_DIterator)
        {
            if ((DList_DIterator.current->data < x) && (DList_DIterator.current->next->data > x))
                return ++DList_DIterator;
            else ++DList_DIterator;
        }
    }
    else if (DList_DIterator.current->data > x)
        return DList_DIterator;
}

void DList::insert_after(const DIterator &it, const int &x)
{
    DIterator DList_DIterator = this->begin();
    while (DList_DIterator != it)
        ++DList_DIterator;

    node* to_insert = new node;
    to_insert->data = x;
    to_insert->next = DList_DIterator.current->next;
    to_insert->prev = DList_DIterator.current;

    DList_DIterator.current->next->prev = to_insert;
    DList_DIterator.current->next = to_insert;
}

void DList::insert_before(const DIterator &it, const int &x)
{
    DIterator DList_DIterator = this->begin();
    while (DList_DIterator != it)
        ++DList_DIterator;

    node* to_insert = new node;

    if (DList_DIterator.current->prev!=nullptr)
    {
        to_insert->data = x;
        to_insert->next = DList_DIterator.current;
        to_insert->prev = DList_DIterator.current->prev;

        DList_DIterator.current->prev->next = to_insert;
        DList_DIterator.current->prev = to_insert;
    }
    else
    {
        to_insert->data = x;
        to_insert->next = DList_DIterator.current;
        to_insert->prev = nullptr;
        DList_DIterator.current->prev = to_insert;
        first = first->prev;
    }
}

void DList::remove(const DIterator &it)
{
    DIterator DList_DIterator = this->begin();

    while (DList_DIterator != it)
        ++DList_DIterator;

    // if removing the first element of list
    if (DList_DIterator == this->begin())
        this->pop_front();
    // if removing the last element of list
    else if (DList_DIterator.current == this->end().current->prev)
        this->pop_back();
    // if removing the element from the middle
    else
    {
        DIterator prev_DIterator = DList_DIterator--;
        DIterator next_DIterator = DList_DIterator++;
        node *temp = DList_DIterator.current;
        temp->next = nullptr;
        temp->prev = nullptr;

        prev_DIterator.current->next = next_DIterator.current;
        next_DIterator.current->prev = prev_DIterator.current;
        delete temp;
    }
}

