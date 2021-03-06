//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#include "world/tree/BigAssTree.h"
#include "GameAssets.h"
#include "ForestScreen.h"

BigAssTree::BigAssTree(Forest& forest, const b2Vec2& position)
	: Tree(forest, position)
{
    maxHealth = 100;
	setHealth(maxHealth);
    setDestroyedTexture(forest.getAssets().get(GameAssets::GREAT_OAK_STUMP));
    setDamageStateSprite(&sprite);
	sprite.setTexture(*forest.getAssets().get(GameAssets::GREAT_OAK), true);
    whiteTreeSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_GREAT_OAK), true);
}

b2Vec2 BigAssTree::getSize() const {
	return {15.0f, 15.0f};
}

void BigAssTree::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
    sf::Vector2f worldMousePos = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

    sf::Vector2f clickV = {worldMousePos.x, 100 - worldMousePos.y};
    sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
    sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

    if(this->forest.getScreen().getEntityClickSelection().getSelectedEntity() == this)
    {
        whiteTreeSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
        whiteTreeSprite.setOrigin({0.5f * whiteTreeSprite.getTexture()->getSize().x, 0.5f * whiteTreeSprite.getTexture()->getSize().y});
        whiteTreeSprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
        whiteTreeSprite.setColor(sf::Color(255, 255, 255, 255));
        target.draw(whiteTreeSprite);
    }
    else if(((clickV.x - this->getPosition().x)*(clickV.x - this->getPosition().x) +
              (clickV.y - this->getPosition().y)*(clickV.y - this->getPosition().y)) < 61)
    {
        whiteTreeSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
        whiteTreeSprite.setOrigin({0.5f * whiteTreeSprite.getTexture()->getSize().x, 0.5f * whiteTreeSprite.getTexture()->getSize().y});
        whiteTreeSprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
		whiteTreeSprite.setColor(sf::Color(50, 255, 50, 255));
        target.draw(whiteTreeSprite);
    }

    sprite.setColor(sf::Color(255, 255, 255, 255));
    sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
    target.draw(sprite);

    target.draw(healthBar);
}

float BigAssTree::getZOrder() const {
    return -getPosition().y + 100 - .5f;
}

void BigAssTree::tick(float delta) {

}
