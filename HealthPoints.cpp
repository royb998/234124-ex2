//
// Created by royb9 on 21/12/2022.
//

#include "HealthPoints.h"

HealthPoints::HealthPoints(int maxHp)
{
    if (maxHp <= 0)
    {
        throw HealthPoints::InvalidArgument();
    }

    this->m_maxHP = maxHp;
    this->m_currentHP = maxHp;
}

HealthPoints::HealthPoints(int maxHp, int currentHP)
{
    if (maxHp <= 0)
    {
        throw HealthPoints::InvalidArgument();
    }

    this->m_maxHP = maxHp;
    this->setHP(currentHP);
}

void HealthPoints::setHP(int value)
{
    if (value > this->m_maxHP)
    {
        value = this->m_maxHP;
    }
    if (value < 0)
    {
        value = 0;
    }

    this->m_currentHP = value;
}

/* Arithmetic operators */

HealthPoints HealthPoints::operator+(int value) const
{
    return HealthPoints(this->m_maxHP,
                        this->m_currentHP + value);
}

HealthPoints operator+(int value, const HealthPoints& hp)
{
    return HealthPoints(hp.m_maxHP,
                        hp.m_currentHP + value);
}

HealthPoints HealthPoints::operator-(int value) const
{
    return HealthPoints(this->m_maxHP,
                        this->m_currentHP - value);
}

HealthPoints operator-(int value, const HealthPoints& hp)
{
    return HealthPoints(hp.m_maxHP,
                        hp.m_currentHP - value);
}

void HealthPoints::operator+=(int value)
{
    this->setHP(this->m_currentHP + value);
}

void HealthPoints::operator-=(int value)
{
    this->setHP(this->m_currentHP - value);
}

/* Comparison operators */

bool HealthPoints::operator==(HealthPoints other) const
{
    return this->m_currentHP == other.m_currentHP;
}

bool HealthPoints::operator!=(HealthPoints other) const
{
    return this->m_currentHP != other.m_currentHP;
}

bool HealthPoints::operator>(HealthPoints other) const
{
    return this->m_currentHP > other.m_currentHP;
}

bool HealthPoints::operator<(HealthPoints other) const
{
    return this->m_currentHP < other.m_currentHP;
}

bool HealthPoints::operator>=(HealthPoints other) const
{
    return this->m_currentHP >= other.m_currentHP;
}

bool HealthPoints::operator<=(HealthPoints other) const
{
    return this->m_currentHP <= other.m_currentHP;
}

/* IO operators */

std::ostream& operator<<(std::ostream& os, const HealthPoints& hp)
{
    return os << hp.m_currentHP << "(" << hp.m_maxHP << ")";
}
