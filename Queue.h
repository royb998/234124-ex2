#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <cassert>
#include <exception>
#include "Node.h"

template<class T>
class Queue
{
    queueNode<T> *m_first;
    queueNode<T> *m_last;
    int m_size;

public:
    class Empty
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
    return Iterator(this->m_first);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    assert(this->m_last != nullptr);
    return Iterator(this->m_last->next);
}

template<class T>
Queue<T>::Queue():m_size(0), m_first(NULL), m_last(NULL)
{}

template<class T>
Queue<T>::~Queue()
{
    queueNode<T> *n = m_first;
    while (n)
    {
        queueNode<T> *tmp = n;
        n = n->next;
        delete tmp;
    }
}

template<class T>
Queue<T>::Queue(const Queue &q):m_first(NULL), m_last(NULL), m_size(q.m_size)
{
    try
    {
        m_first = new queueNode<T>(q.m_first);
        if (q.size == 1)
        {
            m_last = m_first;
            return;
        }

        queueNode<T> *current = m_first;
        queueNode<T> *q_current = q.m_first;
        while (q_current->next)
        {
            current->next = new queueNode<T>(q_current->next);

            current = current->next;
            q_current = q_current->next;
        }

        m_last = current;
    } catch (...)
    {
        delete this;
    }
}

template<class T>
void Queue<T>::pushBack(const T &x)
{
    if (m_size == 0)
    {
        m_first = new queueNode<T>(x);
        m_last = m_first;
        m_size++;

        return;
    }

    m_last->next = new queueNode<T>(x);
    m_last = m_last->next;
    m_size++;
}

template<class T>
T &Queue<T>::front()
{
    if (m_size == 0)
    {
        throw Empty();
    }

    return m_first->data;
}

template<class T>
const T &Queue<T>::front() const
{
    if (m_size == 0)
    {
        throw Empty();
    }

    return m_first->data;
}

template<class T>
void Queue<T>::popFront()
{
    if (m_size == 0)
    {
        throw Empty();
    }

    if (m_size == 1)
    {
        delete m_first;
        m_first = NULL;
        m_last = NULL;

        return;
    }

    queueNode<T> *second = m_first->next;
    delete m_first;

    m_first = second;
}

template<class T>
int Queue<T>::size()
{
    return m_size;
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
