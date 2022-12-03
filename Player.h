


#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <string>

#define DEFAULT_MAX_HP 100
#define DEFAULT_FORCE 5

class Player
{
    const char *m_name;
    int m_level;
    int m_force;
    int m_maxHP;
    int m_HP;
    int m_coins;

public:
    Player (const char *name, int max_hp = DEFAULT_MAX_HP, int force = DEFAULT_FORCE);

    Player (const Player &) = default;

    ~Player () = default;

    Player& operator=(const Player& other) = default;

    int getLevel () const;

    void levelUp ();

    void buff (int buff_level = 0);

    void heal (int heal_level = 0);

    void damage(int dmg=0);

    bool isKnockedOut() const;

    void addCoins(int money = 0);

    bool pay(int payment = 0);

    int  getAttackStrength() const;

    void printInfo() const;

};


#endif //EX2_PLAYER_H
