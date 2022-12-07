

#include "Player.h"
#include "utilities.h"

Player::Player(const char *name, int maxHp, int force) : m_level(1), m_coins(0)
{
    m_name = name;

    if (maxHp <= 0)
    {
        m_maxHP = DEFAULT_MAX_HP;
    }
    else
    {
        m_maxHP = maxHp;
    }
    m_HP = maxHp;

    if (force <= 0)
    {
        m_force = DEFAULT_FORCE;
    }
    else
    {
        m_force = force;
    }
}

int Player::getLevel() const
{
    return m_level;
}

void Player::levelUp()
{
    if (m_level < MAX_LEVEL)
    {
        m_level++;
    }
}

void Player::buff(int buffLevel)
{
    if (buffLevel > 0)
    {
        m_force += buffLevel;
    }
}

void Player::heal(int healLevel)
{
    /* Can't heal by a negative amount. */
    if (healLevel > 0)
    {
        m_HP += healLevel;
    }

    if (m_HP > m_maxHP)
    {
        m_HP = m_maxHP;
    }
}

void Player::damage(int hpLost)
{
    /* Can't take negative damage. */
    if (hpLost > 0)
    {
        m_HP -= hpLost;
    }

    if (m_HP < 0)
    {
        m_HP = 0;
    }
}

bool Player::isKnockedOut() const
{
    return m_HP == 0;
}

void Player::addCoins(int money)
{
    /* Can't gain negative money. */
    if (money > 0)
    {
        m_coins += money;
    }
}

bool Player::pay(int payment)
{
    /* Can't pay a negative price. */
    if (payment < 0)
    {
        return true;
    }

    if (m_coins < payment)
    {
        return false;
    }

    m_coins -= payment;
    return true;
}

int Player::getAttackStrength() const
{
    return m_level + m_force;
}

void Player::printInfo() const
{
    printPlayerInfo(m_name,m_level,m_force,m_HP,m_coins);
}
