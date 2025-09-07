#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

class Button
{
private:
	std::optional<sf::Sprite> sprite;
	sf::Texture texture;
	bool isMouseClicked;
	sf::Vector2f position;
public:
	std::function<void()> onClick;
	Button(const std::filesystem::path& aTextureFile, sf::Vector2f aPosition);
	void update(const sf::RenderWindow* aWindow);
	void render(sf::RenderTarget* aTarget);
};
