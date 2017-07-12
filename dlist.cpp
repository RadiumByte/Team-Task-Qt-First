#include "dlist.h"

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

DList::DList()
{
    first = last = nullptr;
}

DList::DList(const DList & l)
{
    copy_DList(l.first, l.last);
}


DList::DList(const std::initializer_list<int> & list)
{
    first = last = nullptr;
    for(auto i=list.begin();i!=list.end();++i)
    {
        this->push_back(*i);
    }
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

void DList::push_back(const int &x)
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
        return;
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
    while (current_in_DList != last)
    {
        count++;
        current_in_DList = current_in_DList->next;
    }
    return count + 1;
}

void DList::erase()
{
    node*temp = this->begin().current;
    this->first = this->last = nullptr;
    delete temp;
}

std::ostream &operator<<(std::ostream &os, DList &l)
{
    for (auto i = l.begin(); i != l.end(); ++i)
        os << *i << " ";
    os << std::endl;
    return os;
}

bool operator==(DList &l1, DList &l2)
{
    if (l1.is_empty() && l2.is_empty())
        return true;
    if (l1.size() != l2.size())
        return false;
    else
    {
        auto i = l1.begin();
        auto j = l2.begin();
        {
            while (i != l1.end())
            {
                if (*i != *j)
                    return false;
                else
                {
                    ++i;
                    ++j;
                }
            }
        }
        return true;
    }
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
    if (*this == this->collection->end())
        throw std::out_of_range("Attempt to go out of the collection");

    return this->current->data;
}

DList::DIterator& DList::DIterator::operator++()
{
    if (this->current == nullptr)
        throw std::out_of_range("Attempt to go out of the collection");

    this->current = this->current->next;
    return *this;
}

DList::DIterator DList::DIterator::operator++(int)
{
    DIterator old(this->collection, this->current);

    if (this->current == nullptr)
        throw std::out_of_range("Attempt to go out of the collection");

    this->current = this->current->next;
    return old;
}

DList::DIterator& DList::DIterator::operator--()
{
    if (this->current == nullptr)
        throw std::out_of_range("Attempt to go out of the collection");

    this->current = this->current->prev;
    return *this;
}

DList::DIterator DList::DIterator::operator--(int)
{
    DIterator old(this->collection, this->current);

    if (this->current == nullptr)
        throw std::out_of_range("Attempt to go out of the collection");

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
    return (this->current->data > it.current->data);
}

bool DList::DIterator::operator >(const DIterator &it) const
{
    return (this->current->data < it.current->data);
}

DList::DIterator DList::find(const int &x)
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

//the first element that is greater than the given
DList::DIterator DList::findFEGG(const int &x)
{
    DIterator DList_DIterator = this->begin();
    DIterator end_DIterator = this->end();
    if (this->size() > 1)
    {
        if ((DList_DIterator.current->prev == nullptr) &&
                (DList_DIterator.current->data > x))
            return DList_DIterator;
        while (DList_DIterator != end_DIterator)
        {
            if ((DList_DIterator.current->data < x) &&
                    (DList_DIterator.current->next->data > x))
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

    if (DList_DIterator.current->prev != nullptr)
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

    if (DList_DIterator == this->begin())       //if deleting first
        this->pop_front();
    else if (it.current->next==nullptr)    //if deleting last
        this->pop_back();
    else                              //if deleting from the middle
    {
        node *temp;
        temp = DList_DIterator.current;
        DList_DIterator.current->prev->next = DList_DIterator.current->next;
        DList_DIterator.current->next->prev = DList_DIterator.current->prev;
        delete temp;
    }
}
