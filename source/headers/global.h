#pragma once
#include "SFML/Graphics.hpp"
#include <array>
#include <iostream>
#include <map>

namespace gbl
{
	namespace screen
	{
		constexpr unsigned short HEIGHT = 848;
		constexpr unsigned short WIDTH = 477;
	}

	namespace grid
	{
		constexpr unsigned short offsetX = 10;
		constexpr unsigned short offsetY = 150;
		constexpr unsigned short gap = 2;
		constexpr unsigned short rows = 8;
		constexpr unsigned short columns = 8;
		constexpr unsigned short cellSize = (screen::WIDTH - 2 * offsetX - gap * (columns - 1)) / columns;
	}

	namespace save
	{
		constexpr char highScorePath[] = "source/resources/data/highscore.txt";
	}

	inline std::map<unsigned short, sf::Color> colors = {
		{0, sf::Color(50, 50, 70, 255)},
		{1, sf::Color(220, 20, 60)},
		{2, sf::Color(255, 140, 0)},
		{3, sf::Color(255, 215, 0)},
		{4, sf::Color(50, 205, 50)},
		{5, sf::Color(30, 144, 255)},
		{6, sf::Color(138, 43, 226)}};


	using GridArr = std::array<std::array<unsigned short, gbl::grid::columns>, gbl::grid::rows>;
	using Positions = std::vector<sf::Vector2i>;
}