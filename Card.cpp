//
// Created by Roy Bar-On on 12/3/22.
//

#include "Card.h"

/* Functions */

/**
 * Handle battle encounter as defined in the guidelines.
 *
 * @param player Player that encountered the card.
 * @param stats Stats of the card encountered.
 * */
void encounterBattle(Player &player, const CardStats &stats)
{
    bool win = player.getAttackStrength() >= stats.force;

    if (win)
    {
        player.levelUp();
        player.addCoins(stats.loot);
    }
    else
    {
        player.damage(stats.hpLossOnDefeat);
    }
    printBattleResult(win);
}

/**
 * Handle heal encounter as defined in the guidelines.
 *
 * @param player Player that encountered the card.
 * @param stats Stats of the card encountered.
 * */
void encounterHeal(Player &player, const CardStats &stats)
{
    if (player.pay(stats.cost))
    {
        player.heal(stats.heal);
    }
}

/**
 * Handle buff encounter as defined in the guidelines.
 *
 * @param player Player that encountered the card.
 * @param stats Stats of the card encountered.
 * */
void encounterBuff(Player &player, const CardStats &stats)
{
    if (player.pay(stats.cost))
    {
        player.buff(stats.buff);
    }
}

/**
 * Handle treasure encounter as defined in the guidelines.
 *
 * @param player Player that encountered the card.
 * @param stats Stats of the card encountered.
 * */
void encounterTreasure(Player &player, const CardStats &stats)
{
    player.addCoins(stats.loot);
}

/* "Card" methods */

Card::Card(CardType type, const CardStats &stats) {
    this->m_effect = type;
    this->m_stats = stats;
}

void Card::applyEncounter(Player &player) const {
    switch (this->m_effect) {
        case CardType::Battle:
            encounterBattle(player, this->m_stats);
            break;
        case CardType::Heal:
            encounterHeal(player, this->m_stats);
            break;
        case CardType::Buff:
            encounterBuff(player, this->m_stats);
            break;
        case CardType::Treasure:
            encounterTreasure(player, this->m_stats);
            break;
    }
}

void Card::printInfo() const {
    switch (this->m_effect) {
        case CardType::Battle:
            printBattleCardInfo(this->m_stats);
            break;
        case CardType::Heal:
            printHealCardInfo(this->m_stats);
            break;
        case CardType::Buff:
            printBuffCardInfo(this->m_stats);
            break;
        case CardType::Treasure:
            printTreasureCardInfo(this->m_stats);
            break;
    }
}

