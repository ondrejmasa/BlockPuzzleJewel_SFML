#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "global.h"
#include "Block.h"
#include <unordered_set>

class Grid
{
private:
	sf::Vector2i offset;
	gbl::GridArr gridArr;
	std::unordered_set<size_t> potentialFullRows;
	std::unordered_set<size_t> potentialFullCols;
	unsigned int potentialFullColor;

public:
	Grid(sf::Vector2i aOffset);
	virtual ~Grid();
	void placeBlock(Block* aBlock);
	bool canBlockBePlaced(const Block* aBlock);
	bool canBlockBePlaced(const sf::Vector2i& aIndexes, const gbl::Positions& aBlockPositions);
	bool canBlockBePlacedSomewhere(const Block* aBlock);
	unsigned char checkFullRowsOrCols();
	void checkPotentialFullRowsOrCols(const Block* aBlock);
	void restartGrid();
	void clearPotentialFullRowsAndColsSets();

	void render(sf::RenderTarget& target);
};
