//
// Created by Alexander Winter🤤 on 2022-03-12.
//

#ifndef WIZENGINEQUICKSTART_CLIENT_TITLESCREEN_H
#define WIZENGINEQUICKSTART_CLIENT_TITLESCREEN_H

#include <WIZ/game/Screen.h>
#include <SW/SelbaWard.hpp>
#include <SW/Common.hpp>
#include "SFML/Graphics/Text.hpp"
#include "SFML/Audio/Sound.hpp"

class TitleScreen : public wiz::Screen, public wiz::WindowListener {
	std::string name = "TitleScreen";

	sf::Text playWithMouse;
	sf::Text clickToPlay;

	sf::Sound click;

	sf::Sprite logo;
	sf::Sprite background;
public:
	TitleScreen(wiz::Game& game);

	void tick(float delta) override;

	void render(sf::RenderTarget& target) override;

	void show() override;

	void hide() override;

	const std::string& getName() const override;

	void windowClosed() override;
};


#endif //WIZENGINEQUICKSTART_CLIENT_TITLESCREEN_H
