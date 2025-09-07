#pragma once
#include "SFML/Graphics.hpp"
#include "global.h"

class Hand
{
private:
	sf::RectangleShape shape;

	void initShape();

public:
	Hand();
	virtual ~Hand();

	const sf::Vector2f getSize() const;
	const sf::Vector2f getPosition() const;

	void render(sf::RenderTarget& target);
};
