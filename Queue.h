#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <stdio.h>
#include <exception>

template<class T>
struct queueNode
{
    T data;
    queueNode *next;

    explicit queueNode(const T &x)
    {
        data = x;
        next = NULL;
    }

    queueNode(const queueNode &n)
    {
        data = n.data;
    }

    explicit queueNode(const queueNode *n)
    {
        data = n->data;
    }

    queueNode &operator=(const queueNode<T> &) = default;

    ~queueNode() = default;
};

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
};

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

#endif //EX3_QUEUE_H
