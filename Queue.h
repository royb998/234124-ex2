#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <exception>
#include "Node.h"

/* ---------- Classes ---------- */

template<class T>
class Queue
{
    queueNode<T> *m_first;
    queueNode<T> *m_last;
    int m_size;

public:
    class EmptyQueue
    {
    };

    Queue();
    ~Queue();
    Queue(const Queue &q);
    Queue& operator=(Queue const& other) = default;

    void pushBack(const T &x);
    T &front() const;
    void popFront();

    int size() const;

    class Iterator;
    class ConstIterator;
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;
};

template<class T>
class Queue<T>::Iterator
{
private:
    queueNode<T>* m_current;

    explicit Iterator(queueNode<T>* const& node);

    friend class Queue<T>;

public:
    T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& other);

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation {};
};

template<class T>
class Queue<T>::ConstIterator
{
private:
    queueNode<T>* m_current;

    explicit ConstIterator(queueNode<T>* const& node);

    friend class Queue<T>;

public:
    T operator*() const;
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& other);
    bool operator!=(const Iterator& other);

    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation {};
};

/* ---------- Functions ---------- */

template<class T>
Queue<T> filter(Queue<T> queue, bool (* predicate)(T))
{
    Queue<T> filtered;

    for (T i : queue)
    {
        if (predicate(i))
        {
            filtered.pushBack(i);
        }
    }

    return filtered;
}

template <class T>
void transform(Queue<T>& queue, void (* map)(T&))
{
    for (T& i : queue)
    {
        map(i);
    }
}

/* ---------- Queue Implementation ---------- */

template<class T>
Queue<T>::Queue():m_size(0), m_first(NULL), m_last(NULL)
{}

template<class T>
Queue<T>::~Queue()
{
    queueNode<T> *n = m_first;
    while (n != NULL)
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
        if (q.size() == 1)
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
T &Queue<T>::front() const
{
    if (m_size == 0)
    {
        throw EmptyQueue();
    }

    return m_first->data;
}

template<class T>
void Queue<T>::popFront()
{
    if (m_size == 0)
    {
        throw EmptyQueue();
    }

    if (m_size == 1)
    {
        delete m_first;
        m_first = NULL;
        m_last = NULL;
        m_size--;

        return;
    }

    queueNode<T> *second = m_first->next;
    delete m_first;

    m_first = second;
    m_size--;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this->m_first);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(nullptr);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return Queue::ConstIterator(this->m_first);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(nullptr);
}

template<class T>
int Queue<T>::size() const
{
    return m_size;
}

/* ---------- Iterator Implementation ---------- */

template<class T>
Queue<T>::Iterator::Iterator(queueNode<T>* const& node) :
    m_current(node)
{}

template<class T>
T& Queue<T>::Iterator::operator*() const
{
    if (this->m_current == nullptr)
    {
        throw InvalidOperation();
    }
    return this->m_current->data;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (this->m_current == nullptr)
    {
        throw InvalidOperation();
    }
    this->m_current = this->m_current->next;
    return *this;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& other)
{
    return this->m_current != other.m_current;
}

/* ---------- ConstIterator Implementation ---------- */

template<class T>
Queue<T>::ConstIterator::ConstIterator(queueNode<T>* const& node) :
    m_current(node)
{}

template<class T>
T Queue<T>::ConstIterator::operator*() const
{
    if (this->m_current == nullptr)
    {
        throw InvalidOperation();
    }
    return this->m_current->data;
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (this->m_current == nullptr)
    {
        throw InvalidOperation();
    }
    this->m_current = this->m_current->next;
    return *this;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& other)
{
    return this->m_current != other.m_current;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const Iterator& other)
{
    return this->m_current != other.m_current;
}

#endif //EX3_QUEUE_H
