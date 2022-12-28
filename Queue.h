#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <cassert>
#include <exception>
#include "Node.h"

template<class T>
class Queue
{
    queueNode<T> *first, *last;
    int size_;
public:
    class empty
    {
    };

    Queue();
    ~Queue();
    Queue(const Queue &q);

    void pushBack(const T &x);
    T &front();
    const T &front() const;
    void popFront();

    int size();

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
};

template<class T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(this->first);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    assert(this->last != nullptr);
    return Iterator(this->last->next);
}

template<class T>
Queue<T>::Queue():size_(0), first(NULL), last(NULL)
{}

template<class T>
Queue<T>::~Queue()
{
    queueNode<T> *n = first;
    while (n)
    {
        queueNode<T> *tmp = n;
        n = n->next;
        delete tmp;
    }
}

template<class T>
Queue<T>::Queue(const Queue &q):first(NULL), last(NULL), size_(q.size_)
{
    try
    {
        first = new queueNode<T>(q.first);
        if (q.size == 1)
        {
            last = first;
            return;
        }

        queueNode<T> *current = first;
        queueNode<T> *q_current = q.first;
        while (q_current->next)
        {
            current->next = new queueNode<T>(q_current->next);

            current = current->next;
            q_current = q_current->next;
        }

        last = current;
    } catch (...)
    {
        delete this;
    }
}

template<class T>
void Queue<T>::pushBack(const T &x)
{
    if (size_ == 0)
    {
        first = new queueNode<T>(x);
        last = first;
        size_++;

        return;
    }

    last->next = new queueNode<T>(x);
    last = last->next;
    size_++;
}

template<class T>
T &Queue<T>::front()
{
    if (size_ == 0)
    {
        throw empty();
    }

    return first->data;
}

template<class T>
const T &Queue<T>::front() const
{
    if (size_ == 0)
    {
        throw empty();
    }

    return first->data;
}

template<class T>
void Queue<T>::popFront()
{
    if (size_ == 0)
    {
        throw empty();
    }

    if (size_ == 1)
    {
        delete first;
        first = NULL;
        last = NULL;

        return;
    }

    queueNode<T> *second = first->next;
    delete first;

    first = second;
}

template<class T>
int Queue<T>::size()
{
    return size_;
}

template<class T>
class Queue<T>::Iterator
{
private:
    queueNode<T>* m_current;

    Iterator(queueNode<T>* const& node);

    friend class Queue<T>;

public:
    const T& operator*() const;

    Iterator& operator++();

    bool operator!=(const Iterator& other);

    Iterator(const Iterator&) = default;

    Iterator& operator=(const Iterator&) = default;
};

template<class T>
Queue<T>::Iterator::Iterator(queueNode<T>* const& node) :
    m_current(node)
{}

template<class T>
const T& Queue<T>::Iterator::operator*() const
{
    assert(this->m_current != nullptr);
    return this->m_current->data;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    this->m_current = this->m_current->next;
    return *this;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other)
{
    return this->m_current != other.m_current;
}

#endif //EX3_QUEUE_H
