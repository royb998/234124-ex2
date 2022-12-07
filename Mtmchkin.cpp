//
// Created by Roy Bar-On on 12/3/22.
//

#include "Mtmchkin.h"


Mtmchkin::Mtmchkin(const char* playerName, const Card* cardsArray, int numOfCards):
        m_player(playerName) {
    this->m_deck = cardsArray;
    this->m_deckSize = numOfCards;
    this->m_currentCardIndex = 0;
}

GameStatus Mtmchkin::getGameStatus() const {
    if (this->m_player.getLevel() == MAX_LEVEL)
    {
        return GameStatus::Win;
    }
    else if (this->m_player.isKnockedOut())
    {
        return GameStatus::Loss;
    }
    else
    {
        return GameStatus::MidGame;
    }
}

void Mtmchkin::playNextCard() {
    /* Don't pull a card from an empty deck. */
    if (this->m_deckSize == 0)
    {
        return;
    }

    Card currentCard = this->m_deck[this->m_currentCardIndex];
    this->m_currentCardIndex = (this->m_currentCardIndex + 1) % this->m_deckSize;
    currentCard.printInfo();

    currentCard.applyEncounter(this->m_player);
    m_player.printInfo();
}

bool Mtmchkin::isOver() const {
    return this->getGameStatus() != GameStatus::MidGame;
}
