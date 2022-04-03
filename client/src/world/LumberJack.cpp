//
// Created by William Wells on 2022-04-02.
//

#include <world/state/LumberJackIdleState.h>
#include <world/state/LumberJackGoAttackState.h>

#include "world/LumberJack.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderTarget.hpp"

LumberJack::LumberJack(Forest& forest, b2Vec2 position) : forest(forest) {
    sprite.setTexture(*forest.getAssets().get(GameAssets::LUMBERJACKAXE));

    // Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

    this->state = std::make_shared<LumberJackIdleState>(&this->forest, this);

    targetNearestTree();
}

void LumberJack::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

	float flip = facingRight > 0 ? 1.0f : -1.0f;

	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

void LumberJack::tick(float delta) {
    if (target->isDestroyed()) {
        this->state = std::make_shared<LumberJackIdleState>(&this->forest, this);
        targetNearestTree();
    }

    this->state->tick(delta);
}

b2Body* LumberJack::getBody() const {
	return body;
}

b2Vec2 LumberJack::getPosition() const {
	return body->GetPosition();
}

b2Vec2 LumberJack::getSize() const {
	return b2Vec2(1.5f, 1.5f);
}

b2Vec2 LumberJack::getDestination() const {
    return destination;
}

Forest& LumberJack::getForest() const {
	return forest;
}

float LumberJack::getSpeed() const {
    return speed;
}

Tree* LumberJack::getTarget() const {
    return target;
}

int LumberJack::getAttack() const {
    return attack;
}

void LumberJack::setSpeed(float speed) {
    this->speed = speed;
}

void LumberJack::setAttack(float attack) {
    this->attack = attack;
}

void LumberJack::setFacingRight(bool facingRight) {
    this->facingRight = facingRight;
}

void LumberJack::targetNearestTree() {
    std::vector<Tree*> trees(forest.getAliveTrees());

    std::sort(trees.begin(), trees.end(), [this](Tree* a, Tree* b){
        float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
        float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
        return a_dis < b_dis;
    });

    target = trees.front();
    destination = target->getPosition();

    this->state = std::make_shared<LumberJackGoAttackState>(&this->forest, this);
}

std::shared_ptr<LumberJackState> LumberJack::getState() const {
    return state;
}

void LumberJack::setState(std::shared_ptr<LumberJackState> state) {
    LumberJack::state = state;
}