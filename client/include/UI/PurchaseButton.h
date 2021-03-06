//
// Created by root on 2022-04-02.
//

#ifndef LD50_CLIENT_PURCHASEBUTTON_H
#define LD50_CLIENT_PURCHASEBUTTON_H


#include "Button.h"
#include "WIZ/asset/TextureAsset.h"

class PurchaseButton : public Button {
    sf::Sprite sprite;
    sf::Sprite currencySprite;
    Currency currency;
    sf::Text priceText;
    sf::Text labelText;

    int calculateCurrencyCount();

protected:
    virtual void click() override;

public:
    int price;

    PurchaseButton(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType, Currency currency, int price, int yAnimalPadding);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void tick(float delta) override;
};


#endif //LD50_CLIENT_PURCHASEBUTTON_H
