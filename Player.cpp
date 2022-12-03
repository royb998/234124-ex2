

#include "Player.h"
#include <iostream>

Player::Player (const char *name, int max_hp, int force) : m_coins(0), m_level(1)
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
    m_HP += heal_level;
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
//int main ()
//{
//    Player player1("efrat", 150, 2);
//    player1.levelUp();
//    int x = player1.getLevel();
//    player1.buff(10);
//    player1.damage(200);
//    bool y = player1.isKnockedOut();
//    int a = 5;
//    return 0;
//}
