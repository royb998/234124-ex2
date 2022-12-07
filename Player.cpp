

#include "Player.h"
#include "utilities.h"

Player::Player (const char *name, int max_hp, int force) : m_level(1), m_coins(0)
{
    m_name = name;
    m_maxHP = max_hp;
    m_force = force;
    m_HP = max_hp;
}

int Player::getLevel () const
{
    return m_level;
}

void Player::levelUp ()
{
    if (m_level < 10)
    {
        m_level++;
    }
}

void Player::buff (int buff_level)
{
    m_force += buff_level;
}

void Player::heal (int heal_level)
{
    if (m_HP + heal_level > m_maxHP)
    {
        m_HP = m_maxHP;
    }
    else
    {
        m_HP += heal_level;
    }
}

void Player::damage (int dmg)
{
    if (dmg > m_HP)
    {
        m_HP = 0;
    } else
    {
        m_HP -= dmg;
    }
}

bool Player::isKnockedOut () const
{
    return m_HP == 0;
}

void Player::addCoins (int money)
{
    m_coins += money;
}

bool Player::pay (int payment)
{
    if (m_coins < payment)
    {
        return false;
    }
    m_coins -= payment;
    return true;
}

int Player::getAttackStrength () const
{
    int total = m_level + m_force;
    return total;
}

void Player::printInfo () const
{
    printPlayerInfo(m_name,m_level,m_force,m_HP,m_coins);
}
