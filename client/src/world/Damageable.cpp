//
// Created by william on 2022-04-03.
//

#include "world/Damageable.h"
#include "world/Damager.h"

Damageable::Damageable() {}

float Damageable::getHealth() {
    return health;
}

void Damageable::setHealth(float health){
    this->health = health;
}

void Damageable::damage(Damager* attacker) {
    health -= attacker->getPower();
    if (health <= 0) {
		health = 0;
        destroyed = true;
        if(destroyedTexture)
            sprite->setTexture(*destroyedTexture);
    }
}

void Damageable::setDestroyedTexture(sf::Texture* destroyedTexture) {
    this->destroyedTexture = destroyedTexture;
}

void Damageable::setDamageStateSprite(sf::Sprite* sprite) {
    this -> sprite = sprite;
}

bool Damageable::isDestroyed() const {
    return destroyed;
}
