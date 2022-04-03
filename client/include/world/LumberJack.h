//
// Created by William on 2022-04-02.
//

#ifndef LD50_CLIENT_LUMBERJACK_H
#define LD50_CLIENT_LUMBERJACK_H

#include <world/state/LumberJackState.h>
#include "SFML/Graphics/Drawable.hpp"
#include "Physical.h"
#include "Tickable.h"
#include "Tree.h"
#include "Damager.h"
#include "SFML/Graphics/Sprite.hpp"

#define MIN_DISTANCE_FOR_CONTACT 8.f

class LumberJackState;

class LumberJack : public Renderable, public Physical, public Tickable, public Damager {

    b2Body* body;

	std::vector<ForestNode*> path;
	int pathIndex = -1;
	b2Vec2 destination = b2Vec2(50.0f, 50.0f);
	bool destinationChanged = false;

    Tree* target;
	float speed = 10.0f;
	bool facingRight = false;

    std::shared_ptr<LumberJackState> state;
protected:
    Forest& forest;
    mutable sf::Sprite sprite, debugSprite;

public:
    std::shared_ptr<LumberJackState> getState() const;

    void setState(std::shared_ptr<LumberJackState> state);

	Forest& getForest() const override;

    LumberJack(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

    b2Vec2 getDestination() const;

	void setDestination(b2Vec2 destination);

	float getSpeed() const;

    Tree* getTarget() const;

    void setSpeed(float speed);

    void setFacingRight(bool facingRight);

    void targetNearestTree();

    void tick(float delta) override;

	float getZOrder() const override;
};


#endif //LD50_CLIENT_LUMBERJACK_H
