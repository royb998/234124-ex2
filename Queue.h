#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <exception>

/* ---------- Classes ---------- */

template<class T>
class Queue
{
    struct Node;

    Node *m_first;
    Node *m_last;
    int m_size;

public:
    class EmptyQueue
    {
    };

    Queue();
    ~Queue();
    Queue(const Queue &q);
    Queue& operator=(const Queue& other);

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
struct Queue<T>::Node
{
    T data;
    Node *next;

    explicit Node(const T &x);
    Node(const Node &n);
    explicit Node(const Node *n);

    Node &operator=(const Node&) = default;

    ~Node() = default;
};

template<class T>
class Queue<T>::Iterator
{
private:
    Node* m_current;

    explicit Iterator(Node* const& node);

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
    Node* m_current;

    explicit ConstIterator(Node* const& node);

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

template<class T, class Predicate>
Queue<T> filter(Queue<T> queue, Predicate predicate)
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

template <class T, class Map>
void transform(Queue<T>& queue, Map map)
{
    for (T& i : queue)
    {
        map(i);
    }
}

/* ---------- Node Implementation ---------- */

template <class T>
Queue<T>::Node::Node(const T &x)
{
    data = x;
    next = nullptr;
}

template <class T>
Queue<T>::Node::Node(const Node &n) : next(nullptr)
{
    data = n.data;
}

template <class T>
Queue<T>::Node::Node(const Node *n) : next(nullptr)
{
    data = n->data;
}

/* ---------- Queue Implementation ---------- */

template<class T>
Queue<T>::Queue() : m_first(nullptr), m_last(nullptr), m_size(0) {}

template<class T>
Queue<T>::~Queue()
{
    Node *n = m_first;
    while (n != nullptr)
    {
        Node *tmp = n;
        n = n->next;
        delete tmp;
    }
}

template<class T>
Queue<T>::Queue(const Queue &q): m_first(nullptr), m_last(nullptr), m_size(q.m_size)
{
    try
    {
        m_first = new Node(q.m_first);
        if (q.size() == 1)
        {
            m_last = m_first;
            return;
        }

        Node *current = m_first;
        Node *q_current = q.m_first;
        while (q_current->next)
        {
            current->next = new Node(q_current->next);

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
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != &other)
    {
        Node *n = this->m_first;
        while (n != nullptr)
        {
            Node *tmp = n;
            n = n->next;
            delete tmp;
        }
        this->m_first = nullptr;
        this->m_last = nullptr;

        for (T i : other)
        {
            this->pushBack(i);
        }
    }

    return *this;
}

template<class T>
void Queue<T>::pushBack(const T &x)
{
    if (m_size == 0)
    {
        m_first = new Node(x);
        m_last = m_first;
        m_size++;

        return;
    }

    m_last->next = new Node(x);
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
        m_first = nullptr;
        m_last = nullptr;
        m_size--;

        return;
    }

    Node *second = m_first->next;
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
Queue<T>::Iterator::Iterator(Node* const& node) :
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
Queue<T>::ConstIterator::ConstIterator(Node* const& node) :
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
