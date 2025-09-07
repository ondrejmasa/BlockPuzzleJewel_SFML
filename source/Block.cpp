#include "Block.h"

Block::Block(const gbl::Positions& aPos)
	:	positions(aPos),
		scale{ 1.f },
		colorId { 1 + rand() % (gbl::colors.size()-1)},
		colorAlpha {255},
		isSnapped { false },
		isEnabled { true }
{
}

Block::~Block()
{
}

const sf::Vector2f Block::getSize() const
{
	sf::Vector2i s{};
	for (const sf::Vector2i& pos : positions)
	{
		s.x = std::max(s.x, pos.x);
		s.y = std::max(s.y, pos.y);
	}
	s.x += 1;
	s.y += 1;
	return static_cast<sf::Vector2f>((gbl::grid::cellSize + gbl::grid::gap) * s) * scale;
}

void Block::setAlpha(const std::uint8_t aAlpha)
{
	colorAlpha = aAlpha;
}

void Block::render(sf::RenderTarget& target)
{
	sf::RectangleShape r(sf::Vector2f(gbl::grid::cellSize, gbl::grid::cellSize) * scale);
	sf::Color c = gbl::colors[colorId];
	if (!isEnabled)
		c.a = 100;
	r.setFillColor(c);
	r.setOutlineThickness(1.f);
	r.setOutlineColor(sf::Color::Black);

	if (isSnapped)
	{
		sf::RectangleShape r2 = r;
		c.a = 100;
		r2.setFillColor(c);
		for (const sf::Vector2i& pos : positions)
		{

			r2.setPosition(offsetSnap + (gbl::grid::cellSize * scale) * static_cast<sf::Vector2f>(pos) + std::max(1.f, scale * gbl::grid::gap) * static_cast<sf::Vector2f>(pos));
			target.draw(r2);

		}
	}

	for (const sf::Vector2i& pos : positions)
	{
		r.setPosition(offset + (gbl::grid::cellSize * scale) * static_cast<sf::Vector2f>(pos) + std::max(1.f, scale * gbl::grid::gap) * static_cast<sf::Vector2f>(pos));
		target.draw(r);
	}
}

void Block::flip()
{
	for (sf::Vector2i& pos : positions)
	{
		int t = pos.x;
		pos.x = pos.y;
		pos.y = t;
	}
}

OBlock::OBlock()
	: Block({ {0, 0}, {0, 1}, {1, 0}, {1, 1} })
{
}

FiveIBlock::FiveIBlock()
	: Block({ {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0} })
{
}

LBlock::LBlock()
	: Block({ {0, 0}, {0, 1}, {0, 2}, {1, 2}, {2, 2} })
{
}

JBlock::JBlock()
	: Block({ {1, 0}, {1, 1}, {1, 2}, {0, 2} })
{
}

ThreeIBlock::ThreeIBlock()
	: Block({ {0, 0}, {1, 0}, {2, 0} })
{
}

FourIBlock::FourIBlock()
	: Block({ {0, 0}, {1, 0}, {2, 0}, {3, 0} })
{
}

TwoIBlock::TwoIBlock()
	: Block({ {0, 0}, {1, 0} })
{
}

OneIBlock::OneIBlock()
	: Block({ {0, 0} })
{
}

KBlock::KBlock()
	: Block({ {1, 0}, {0, 1}, {1, 1}, {2, 1} })
{
}

BigOBlock::BigOBlock()
	: Block({ {0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2,1}, {2, 2} })
{
}
