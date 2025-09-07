#include "Grid.h"

Grid::Grid(sf::Vector2i aOffset)
	:	gridArr(),
		offset{ aOffset },
		potentialFullCols { },
		potentialFullRows { },
		potentialFullColor { 0 }
{
}

Grid::~Grid()
{
}

void Grid::placeBlock(Block* aBlock)
{
	double x = (aBlock->offset.x - offset.x) / (gbl::grid::cellSize + gbl::grid::gap);
	double y = (aBlock->offset.y - offset.y) / (gbl::grid::cellSize + gbl::grid::gap);
	for (sf::Vector2i pos : aBlock->positions)
	{
		gridArr[std::round(y) + pos.y][std::round(x) + pos.x] = aBlock->colorId;
	}
}

bool Grid::canBlockBePlaced(const Block* aBlock)
{
	double x = (aBlock->offset.x - offset.x) / (gbl::grid::cellSize + gbl::grid::gap);
	double y = (aBlock->offset.y - offset.y) / (gbl::grid::cellSize + gbl::grid::gap);
	return canBlockBePlaced(sf::Vector2i(std::round(x), std::round(y)), aBlock->positions);
}

bool Grid::canBlockBePlaced(const sf::Vector2i& aIndexes, const gbl::Positions& aBlockPositions)
{
	for (sf::Vector2i pos : aBlockPositions)
	{
		short i = aIndexes.y + pos.y;
		short j = aIndexes.x + pos.x;
		if (i < 0 or i >= gbl::grid::rows or j < 0 or j >= gbl::grid::columns or gridArr[i][j] != 0)
		{
			return false;
		}
	}
	return true;
}

bool Grid::canBlockBePlacedSomewhere(const Block* aBlock)
{
	for (size_t r = 0u; r < gridArr.size(); ++r)
	{
		for (size_t c = 0u; c < gridArr[r].size(); c++)
		{
			if (canBlockBePlaced(sf::Vector2i(r, c), aBlock->positions))
				return true;
		}
	}
	return false;
}

unsigned char Grid::checkFullRowsOrCols()
{
	for (size_t i = 0u; i < gridArr.size(); ++i)
	{
		for (size_t j = 0u; j < gridArr[i].size(); ++j)
		{
			if (potentialFullRows.find(i) != potentialFullRows.end() or potentialFullCols.find(j) != potentialFullCols.end())
				gridArr[i][j] = 0u;
		}
	}
	return potentialFullRows.size() + potentialFullCols.size();
}

void Grid::checkPotentialFullRowsOrCols(const Block* aBlock)
{
	if (!canBlockBePlaced(aBlock)) return;
	double x = (aBlock->offset.x - offset.x) / (gbl::grid::cellSize + gbl::grid::gap);
	double y = (aBlock->offset.y - offset.y) / (gbl::grid::cellSize + gbl::grid::gap);
	for (sf::Vector2i pos : aBlock->positions)
	{
		size_t r = std::round(y) + pos.y;
		// check rows
		bool b = true;
		for (size_t c = 0; c < gbl::grid::columns; c++)
		{

			if (gridArr[r][c] == 0 and std::find(aBlock->positions.begin(), aBlock->positions.end(), sf::Vector2i(c - std::round(x), r - std::round(y))) == aBlock->positions.end())
			{
				b = false;
				break;
			}
		}
		if (b)
		{
			potentialFullRows.insert(r);
		}
		size_t c = std::round(x) + pos.x;
		// check columns
		b = true;
		for (size_t r = 0; r < gbl::grid::rows; r++)
		{
			if (gridArr[r][c] == 0 and std::find(aBlock->positions.begin(), aBlock->positions.end(), sf::Vector2i(c - std::round(x), r - std::round(y))) == aBlock->positions.end())
			{
				b = false;
				break;
			}
		}
		if (b)
		{
			potentialFullCols.insert(c);
		}
	}
	potentialFullColor = aBlock->colorId;
}

void Grid::restartGrid()
{
	gridArr = {};
}

void Grid::clearPotentialFullRowsAndColsSets()
{
	potentialFullRows = {};
	potentialFullCols = {};
}

void Grid::render(sf::RenderTarget& target)
{
	sf::RectangleShape cell(sf::Vector2f(static_cast<float>(gbl::grid::cellSize), static_cast<float>(gbl::grid::cellSize)));
	cell.setOutlineColor(sf::Color::Black);
	cell.setOutlineThickness(2.f);
	for (size_t i = 0; i < gbl::grid::rows; i++)
	{
		for (size_t j = 0; j < gbl::grid::columns; j++)
		{
			if (potentialFullRows.find(i) != potentialFullRows.end() or potentialFullCols.find(j) != potentialFullCols.end())
				cell.setFillColor(gbl::colors[potentialFullColor]);
			else 
				cell.setFillColor(gbl::colors[gridArr[i][j]]);
			cell.setPosition(sf::Vector2f(offset.x + j * (gbl::grid::cellSize + gbl::grid::gap), offset.y + i * (gbl::grid::cellSize + gbl::grid::gap)));
			target.draw(cell);
		}
	}
}
