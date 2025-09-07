#include "Button.h"
#include <iostream>

Button::Button(const std::filesystem::path& aTextureFile, sf::Vector2f aPosition)
	:	texture { aTextureFile },
		position { aPosition },
		isMouseClicked { false }
{
	sprite.emplace(texture);
	sprite->setPosition(position - static_cast<sf::Vector2f>(texture.getSize()) * 0.5f);
}

void Button::update(const sf::RenderWindow* aWindow)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (!isMouseClicked)
		{
			isMouseClicked = true;
			if (onClick and sprite->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*aWindow))))
			{
				onClick();
			}
		}
	}
	else
	{
		isMouseClicked = false;
	}
}

void Button::render(sf::RenderTarget* aTarget)
{
	sf::CircleShape c(sprite->getGlobalBounds().size.x * 0.6);
	c.setPosition(position - static_cast<sf::Vector2f>(c.getGlobalBounds().size) * 0.5f);
	c.setFillColor(sf::Color(0, 0, 0, 180));
	aTarget->draw(c);
	aTarget->draw(*sprite);
}
