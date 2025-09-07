#include "Hand.h"

void Hand::initShape()
{
	shape.setPosition(sf::Vector2f(gbl::grid::offsetX, gbl::screen::HEIGHT - gbl::grid::offsetX - shape.getSize().y));
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(2.f);
	shape.setFillColor(sf::Color(40, 40, 60, 255));
}

Hand::Hand()
	: shape(sf::Vector2f(gbl::screen::WIDTH - 2 * gbl::grid::offsetX, (gbl::screen::WIDTH - 2 * gbl::grid::offsetX) / 3))
{
	this->initShape();
}

Hand::~Hand()
{
}

const sf::Vector2f Hand::getSize() const
{
	return shape.getSize();
}

const sf::Vector2f Hand::getPosition() const
{
	return shape.getPosition();
}

void Hand::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
