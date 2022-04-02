//
// Created by cedric on 2022-04-02.
//

#include "world/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"
#include "world/Forest.h"


Tree::Tree(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::TREE));

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x / 4;

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 0.f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

b2Body* Tree::getBody() const {
	return body;
}

b2Vec2 Tree::getPosition() const {
	return body->GetPosition();
}

b2Vec2 Tree::getSize() const {
	return b2Vec2(5.0f, 5.0f);
}

Forest& Tree::getForest() const {
	return forest;
}
