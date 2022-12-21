//
// Created by Roy Bar-On on 21/12/2022.
//

#ifndef _HEALTHPOINTS_H
#define _HEALTHPOINTS_H

#include <iostream>

class HealthPoints
{
private:
    const static int DEFAULT_MAX_HP = 100;

    int m_maxHP;
    int m_currentHP;

    HealthPoints(int maxHp, int currentHP);

    void setHP(int value);

public:
    HealthPoints(int maxHp=DEFAULT_MAX_HP);

    HealthPoints operator+(int value);
    HealthPoints operator-(int value);
    friend HealthPoints operator+(int value, const HealthPoints& hp);
    friend HealthPoints operator-(int value, const HealthPoints& hp);
    void operator+=(int value);
    void operator-=(int value);

    bool operator==(HealthPoints other);
    bool operator!=(HealthPoints other);
    bool operator>(HealthPoints other);
    bool operator<(HealthPoints other);
    bool operator>=(HealthPoints other);
    bool operator<=(HealthPoints other);

    friend std::ostream& operator<<(std::ostream& os, const HealthPoints& hp);

    /* Exceptions */
    class InvalidArgument{};
};


#endif //_HEALTHPOINTS_H
