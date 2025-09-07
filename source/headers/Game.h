#pragma once
#include "global.h"
#include "Grid.h"
#include "Hand.h"
#include "Block.h"
#include "Button.h"
#include <algorithm>
#include <fstream>

class Game
{
private:
	sf::RenderWindow* window;
	Grid grid;
	Hand hand;
	std::vector<Block*> unplacedBlocks;
	float handScale;
	Block* selectedBlock;
	sf::Vector2i clickOffset;
	sf::Font font;
	sf::Text gameOverText;
	bool isGameOver;
	Button restartButton;
	sf::Texture restartTexture;
	unsigned int score;
	sf::Text scoreText;
	sf::RectangleShape scoreRect;
	unsigned int highScore;
	sf::Text highScoreText;

	void restartGame();
	void getNewBlocks();
	void initWindow();
	void pollEvents();
	void setSelectedBlock(const sf::Vector2i aMousePos);
	void returnSelectedBlock();
	void updateSelectedBlock();
	void placeSelectedBlock();
	void initText();
	void renderGameOver();
	void renderScore();
	void initScore();
	unsigned int loadHighScore();
	void saveHighScore(const unsigned int aHighScore) const;

public:
	Game();
	virtual ~Game();

	void run();
	void update();
	void render();
};

