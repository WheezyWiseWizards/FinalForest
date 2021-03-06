//
// Created by Cedric on 2022-04-03.
//

#ifndef LD50_COMMON_NUTSHOT_H
#define LD50_COMMON_NUTSHOT_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Tickable.h"
#include "Damageable.h"
#include "world/enemy/Enemy.h"
#include "Forest.h"

class NutShot : virtual public Renderable, virtual public Tickable, virtual public Damager {
public:
    NutShot(Forest& forest, sf::Vector2f pos, Enemy* target);
    void tick(float delta) override;

    Forest &getForest() override;

    float getZOrder() const override;

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

private:
        mutable sf::Sprite sprite;
        sf::Vector2f pos;
        Enemy* target;
        float speed;
        float damage;
        Forest& forest;

};


#endif //LD50_COMMON_NUTSHOT_H
