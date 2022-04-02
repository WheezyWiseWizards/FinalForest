//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Tree.h"
#include <stdlib.h>

Forest::Forest(const wiz::AssetLoader& assetLoader) : assetLoader(assetLoader), world(b2Vec2_zero) {

    float minDistance = 50.f;
    int totalTrees = 30;
    std::vector<Tree *> trees;
    while (trees.size() < totalTrees) {
        float x = (float) (rand() % 100);
        float y = (float) (rand() % 100);
        b2Vec2 position(x, y);

        if(b2DistanceSquared(position, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f)
            continue;

        for (Tree *tree : trees) {
            if (b2DistanceSquared(tree->getPosition(), position) < minDistance * minDistance) {
                continue;
            }
        }

        trees.push_back(new Tree(*this, position));
    }

    for(Tree* tree : trees)
        objects.push_back(tree);
}

Forest::~Forest() {
	for(Entity* entity : objects)
		delete entity;
	objects.clear();
}

void Forest::tick(float delta) {
	for(Entity* obj : objects) {
		Tickable* tickable = dynamic_cast<Tickable*>(obj);
		if(tickable)
			tickable->tick(delta);
	}

	world.Step(delta / 1000.0f, 6, 2);
}

void Forest::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	for(Entity* obj : objects) {
		sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(obj);
		if(drawable)
			target.draw(*drawable, states);
	}
}

b2World& Forest::getB2World() {
	return world;
}

const wiz::AssetLoader& Forest::getAssets() const {
	return assetLoader;
}
