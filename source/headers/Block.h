#pragma once
#include <vector>
#include "global.h"

class Block
{
private:
	unsigned short colorAlpha;
public:
	gbl::Positions positions;
	sf::Vector2f offset;
	sf::Vector2f offsetDef;
	sf::Vector2f offsetSnap;
	bool isSnapped;
	bool isEnabled;
	float scale;
	unsigned int colorId;

	Block(const gbl::Positions& aPos);
	virtual ~Block();
	const sf::Vector2f getSize() const;
	void setAlpha(const std::uint8_t aAlpha);
	void render(sf::RenderTarget& target);
	void flip();
};

class OBlock : public Block
{
public:
	OBlock();
};

class BigOBlock : public Block
{
public:
	BigOBlock();
};

class FiveIBlock : public Block
{
public:
	FiveIBlock();
};

class FourIBlock : public Block
{
public:
	FourIBlock();
};

class ThreeIBlock : public Block
{
public:
	ThreeIBlock();
};

class TwoIBlock : public Block
{
public:
	TwoIBlock();
};

class OneIBlock : public Block
{
public:
	OneIBlock();
};

class LBlock : public Block
{
public:
	LBlock();
};

class JBlock : public Block
{
public:
	JBlock();
};

class KBlock : public Block
{
public:
	KBlock();
};
