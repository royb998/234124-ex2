//
// Created by royb9 on 28/12/2022.
//

#ifndef _NODE_H
#define _NODE_H

#include <cstdio>

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

    queueNode(const queueNode &n) : next(NULL)
    {
        data = n.data;
    }

    explicit queueNode(const queueNode *n) : next(NULL)
    {
        data = n->data;
    }

    queueNode &operator=(const queueNode<T> &) = default;

    ~queueNode() = default;
};

#endif //_NODE_H
