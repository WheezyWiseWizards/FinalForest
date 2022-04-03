//
// Created by william on 2022-04-02.
//

#include "world/state/LumberJackGoAttackState.h"
#include "world/state/LumberJackAttackState.h"

LumberJackGoAttackState::LumberJackGoAttackState(Forest *forest, LumberJack *lumberJack) : LumberJackState(forest, lumberJack) {}

void LumberJackGoAttackState::tick(float delta) {
    LumberJack* lumberJack = getLumberJack();
    if(b2DistanceSquared(lumberJack->getDestination(), lumberJack->getPosition()) < MIN_DISTANCE_FOR_CONTACT) {
        lumberJack->setState(std::make_shared<LumberJackAttackState>(this->getForest(), lumberJack));
        return;
    }

    b2Vec2 direction = lumberJack->getDestination() - lumberJack->getPosition();
    lumberJack->setFacingRight(direction.x > 0);
    direction.Normalize();
    lumberJack->getBody()->SetLinearVelocity(lumberJack->getSpeed() * direction);
}
