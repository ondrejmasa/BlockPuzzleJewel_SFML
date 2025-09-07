#include "Game.h"
#include "Button.h"


void Game::restartGame()
{
	unplacedBlocks.clear();
	getNewBlocks();
	grid.restartGrid();
	score = 0u;
	isGameOver = false;
}

void Game::getNewBlocks()
{
	for (size_t i = 0; i < 3; i++)
	{
		unsigned short r = rand() % 10;
		Block* b = nullptr;
		switch (r)
		{
		case 0:
			b = new FiveIBlock;
			break;
		case 1:
			b = new OBlock;
			break;
		case 2:
			b = new LBlock;
			break;
		case 3:
			b = new JBlock;
			break;
		case 4:
			b = new ThreeIBlock;
			break;
		case 5:
			b = new FourIBlock;
			break;
		case 6:
			b = new TwoIBlock;
			break;
		case 7:
			b = new OneIBlock;
			break;
		case 8:
			b = new KBlock;
			break;
		case 9:
			b = new BigOBlock;
			break;
		}
		r = rand() % 2;
		if (r == 0)
			b->flip();
		float ratio = (1.f + 2.f * i) / 6.f;
		if (b != nullptr)
		{
			b->scale = handScale;
			b->offset = hand.getPosition() + sf::Vector2f(ratio * hand.getSize().x, hand.getSize().y / 2.f) - b->getSize() / 2.f;
			b->offsetDef = b->offset;
			unplacedBlocks.push_back(b);
		}
	}
}

void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(gbl::screen::WIDTH, gbl::screen::HEIGHT)), "Block Puzzle Jewel", sf::Style::Close | sf::Style::Titlebar);
}

void Game::pollEvents()
{
	while (const std::optional event = window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window->close();

		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				this->window->close();

			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
			{
				if (isGameOver)
				{
					restartGame();
				}
			}
		}

		else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
				setSelectedBlock(mouseButtonPressed->position);
			}
		}

		else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseButtonReleased->button == sf::Mouse::Button::Left)
			{
				if (selectedBlock != nullptr)
				{
					if (grid.canBlockBePlaced(selectedBlock))
					{
						placeSelectedBlock();
					}
					else
						returnSelectedBlock();
				}
			}
		}
	}
}

void Game::setSelectedBlock(const sf::Vector2i aMousePos)
{
	for (auto it = unplacedBlocks.begin(); it != unplacedBlocks.end(); ++it)
	{
		Block* b = *it;
		if (!b->isEnabled) continue;
		if (b->offset.x <= aMousePos.x and b->offset.x + b->getSize().x >= aMousePos.x and b->offset.y <= aMousePos.y and b->offset.y + b->getSize().y >= aMousePos.y)
		{
			selectedBlock = b;
			clickOffset = static_cast<sf::Vector2i>((b->offset - static_cast<sf::Vector2f>(aMousePos)) / selectedBlock->scale);
			selectedBlock->scale = 1.f;
			size_t i = std::distance(unplacedBlocks.begin(), it);
			size_t n = unplacedBlocks.size();
			std::swap(unplacedBlocks[i], unplacedBlocks[n-1]);
			break;
		}
	}
}

void Game::returnSelectedBlock()
{
	this->selectedBlock->offset = this->selectedBlock->offsetDef;
	this->selectedBlock->scale = handScale;
	selectedBlock = nullptr;
}

void Game::updateSelectedBlock()
{
	if (selectedBlock == nullptr)
		return;
	sf::Vector2f o = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window) + clickOffset);
	o.x = std::max(0.f, std::min(o.x, static_cast<float>(window->getSize().x - selectedBlock->getSize().x)));
	o.y = std::max(0.f, std::min(o.y, static_cast<float>(window->getSize().y - selectedBlock->getSize().y)));
	float x = gbl::grid::offsetX + std::round((o.x - gbl::grid::offsetX) / (gbl::grid::cellSize + gbl::grid::gap)) * (gbl::grid::cellSize + gbl::grid::gap);
	float y = gbl::grid::offsetY + std::round((o.y - gbl::grid::offsetY) / (gbl::grid::cellSize + gbl::grid::gap)) * (gbl::grid::cellSize + gbl::grid::gap);
	selectedBlock->offset = o;
	if (grid.canBlockBePlaced(selectedBlock))
	{
		selectedBlock->offsetSnap = sf::Vector2f(x, y);
		selectedBlock->isSnapped = true;
	}
	else
		selectedBlock->isSnapped = false;
	grid.checkPotentialFullRowsOrCols(selectedBlock);
}

void Game::placeSelectedBlock()
{
	grid.placeBlock(selectedBlock);
	score += selectedBlock->positions.size();
	auto it = std::find(unplacedBlocks.begin(), unplacedBlocks.end(), selectedBlock);
	unplacedBlocks.erase(it);
	delete selectedBlock;
	selectedBlock = nullptr;
	if (unplacedBlocks.size() == 0)
	{
		getNewBlocks();
	}
	unsigned char n = grid.checkFullRowsOrCols();
	score += 10 * n * (n + 1) / 2;
	bool go = true;
	for (Block* b : unplacedBlocks)
	{
		if (!grid.canBlockBePlacedSomewhere(b))
			b->isEnabled = false;
		else
		{
			b->isEnabled = true;
			go = false;
		}
	}
	isGameOver = go;
	if (isGameOver and score > highScore)
	{
		highScore = score;
		saveHighScore(highScore);
	}
}

void Game::initText()
{
	if (!font.openFromFile("source/resources/fonts/Minecraft.ttf"))
	{
		std::cout << "ERROR in loading font \n";
	}
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(3.f);
	gameOverText.setOrigin(gameOverText.getGlobalBounds().size / 2.f + gameOverText.getGlobalBounds().position);
	gameOverText.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	scoreText.setCharacterSize(25u);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(2.f);

	highScoreText.setCharacterSize(25u);
	highScoreText.setOutlineColor(sf::Color::Black);
	highScoreText.setOutlineThickness(2.f);
}

void Game::renderGameOver()
{
	window->draw(gameOverText);
	restartButton.render(window);
}

void Game::renderScore()
{
	scoreText.setString("SCORE: " + std::to_string(score));
	scoreText.setOrigin(sf::Vector2f(0.f, scoreText.getLocalBounds().size.y / 2.f) + scoreText.getLocalBounds().position);
	scoreText.setPosition(sf::Vector2f(scoreRect.getPosition().x + gbl::grid::offsetX, scoreRect.getPosition().y + scoreRect.getSize().y / 2));

	highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
	highScoreText.setOrigin(sf::Vector2f(highScoreText.getLocalBounds().size.x, highScoreText.getLocalBounds().size.y / 2.f) + highScoreText.getLocalBounds().position);
	highScoreText.setPosition(sf::Vector2f(scoreRect.getPosition().x + scoreRect.getSize().x - gbl::grid::offsetX, scoreRect.getPosition().y + scoreRect.getSize().y / 2));

	window->draw(scoreRect);
	window->draw(scoreText);
	window->draw(highScoreText);
}

void Game::initScore()
{
	scoreRect.setPosition(sf::Vector2f(gbl::grid::offsetX, gbl::grid::offsetY / 4));
	scoreRect.setFillColor(sf::Color(30, 30, 50, 255));
	scoreRect.setOutlineColor(sf::Color::Black);
	scoreRect.setOutlineThickness(2.f);
}

unsigned int Game::loadHighScore()
{
	std::ifstream file(gbl::save::highScorePath);
	unsigned int hs = 0;
	if (file.is_open())
		file >> hs;
	return hs;
}

void Game::saveHighScore(const unsigned int aHighScore) const
{
	std::ofstream file(gbl::save::highScorePath);
	if (!file.is_open()) return;
	file << highScore;
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void Game::update()
{
	pollEvents();
	grid.clearPotentialFullRowsAndColsSets();
	if (!isGameOver)
	{
		updateSelectedBlock();
	}
	else
	{
		restartButton.update(window);
	}
}

void Game::render()
{
	window->clear(sf::Color(28, 28, 38, 255));

	grid.render(*window);
	hand.render(*window);
	renderScore();

	for (Block* b : unplacedBlocks)
	{
		b->render(*window);
	}

	if (isGameOver)
	{
		renderGameOver();
	}

	window->display();
}

Game::Game()
	:	handScale(hand.getSize().x / (18.f * (gbl::grid::cellSize + gbl::grid::gap))),
		grid(sf::Vector2i(gbl::grid::offsetX, gbl::grid::offsetY)),
		isGameOver { false },
		gameOverText(font, "Game Over!", 60),
		restartButton { "source/resources/textures/restart.png", sf::Vector2f(gbl::screen::WIDTH / 2, gbl::screen::HEIGHT / 2 + 60)},
		scoreText { font },
		scoreRect{ sf::Vector2f(gbl::screen::WIDTH - 2 * gbl::grid::offsetX, gbl::grid::offsetY / 2) }, 
		highScore{ loadHighScore() },
		highScoreText { font }
{
	initWindow();
	getNewBlocks();
	initScore();
	initText();
	restartButton.onClick = std::bind(&Game::restartGame, this);
}

Game::~Game()
{
	delete window;
	for (Block* b : unplacedBlocks)
	{
		if (b != nullptr)
		{
			delete b;
		}
	}
}
