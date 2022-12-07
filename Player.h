
#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

const int DEFAULT_MAX_HP = 100;
const int DEFAULT_FORCE = 5;
const int MAX_LEVEL = 10;

class Player
{
    const char *m_name;
    int m_level;
    int m_force;
    int m_maxHP;
    int m_HP;
    int m_coins;

public:
    Player (const char *name, int maxHp = DEFAULT_MAX_HP, int force = DEFAULT_FORCE);

    Player (const Player &) = default;

    ~Player () = default;

    Player& operator=(const Player& other) = default;

    int getLevel () const;

    void levelUp ();

    void buff (int buffLevel = 0);

    void heal (int healLevel = 0);

    void damage(int hpLost=0);

    bool isKnockedOut() const;

    void addCoins(int money = 0);

    bool pay(int payment = 0);

    int  getAttackStrength() const;

    void printInfo() const;

};


#endif //EX2_PLAYER_H
