//
// Created by Roy Bar-On on 12/3/22.
//

#include "Card.h"

Card::Card(CardType type, const CardStats &stats) {
    this->m_effect = type;
    this->m_stats = stats;
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

