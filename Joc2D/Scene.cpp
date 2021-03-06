#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <stdio.h>
#include "Scene.h"
#include "Game.h"
#include "Bubble.h"

#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25

std::vector<int> gmap = {
	4,  3,  4,  5,  3,  0,  6,  5,
	1,  6,  2,  3,  1,  1,  4,
	1,  4,  4,  2,  1,  3,  4,  4,
	1,  0,  0,  5,  2,  0,  0,
	3,  1,  0,  0,  1,  0,  4,  6,
	-1, -1, -1, -1, -1,  6,  4,
	-1, -1, -1, -1, -1, -1,  0
};

Scene::Scene()
{
	//map = NULL;
	//player = NULL;
}

Scene::~Scene()
{
	//if(map != NULL)
	//	delete map;
	//if(player != NULL)
	//	delete player;
}

void Scene::changeLevel(int lvl){
	std::vector<Bubble *> map;

	Grid::loadLevel(levels[currentLvl], map, m_bubbles, texProgram);
	//std::vector<Bubble*> bubbles = loadBubbleMap();
	grid = new Grid(map);
	rowOffset = 0;
	currentTime = 0.0f;
}

void Scene::init()
{
	initShaders();

	Bubble::load_textures();
	bubblelauncher = new BubbleLauncher();
	bubblelauncher->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, &s_bubbleLaunched);

	bg_texture.loadFromFile("images/background-scaled.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(640,480) , glm::vec2(1), &bg_texture, &texProgram);
	background->setPosition(glm::ivec2(320,240));

	//levels.push_back("levels/level00.txt");
	levels.push_back("levels/level01.txt");
	levels.push_back("levels/level02.txt");
	levels.push_back("levels/level03.txt");
	levels.push_back("levels/level04.txt");
	levels.push_back("levels/level05.txt");

	currentLvl = 0;

	changeLevel(currentLvl);
	grid->testGrid();

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	scoreBoard = new Text();
	scoreBoard->init("fonts/DroidSerif.ttf");

	levelBoard = new Text();
	scoreBoard->init("fonts/DroidSerif.ttf");
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	if (m_bubbles.size() == 0) {
		if (currentLvl < levels.size()) {
			currentLvl++;
			changeLevel(currentLvl);
		}
	}

	int newOffset = currentTime / 30000;
	if (rowOffset != newOffset) {
		rowOffset = newOffset;
		grid->setMarginTop(42.f + rowOffset * 32.f);
		for (unsigned int i = 0; i < m_bubbles.size(); i++) {
			if (m_bubbles[i]->isHooked()) {
				glm::vec2 pos = m_bubbles[i]->getPosition();
				pos.y += 32.0f;
				m_bubbles[i]->setPosition(pos);
			}
		}

		// Check if the game's over
		for (unsigned int i = 0; i < 8; i++) {
			int row = 11 - rowOffset;
			int col = i - (row / 2);
			if (grid->isValidHex(glm::vec2(row, col))) {
				if (grid->isOccupiedHex(row, col)) {
					//TODO: Hacer game over
					exit(0);
				}
			}
		}
	}

	bubblelauncher->update(deltaTime);
	for (unsigned int i = 0; i < m_bubbles.size(); i++) {
		m_bubbles[i]->update(deltaTime);
	}
}

void Scene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background->render();
	bubblelauncher->render();
	for (unsigned int i = 0; i < m_bubbles.size(); i++) {
		m_bubbles[i]->render();
	}

	sprintf_s(scoreBoardBuffer, "Score: %d", score);
	scoreBoard->render(scoreBoardBuffer, glm::vec2(50,50), 20+scoreChanged/4,
				glm::vec4(0.f+scoreChanged/10,1-scoreChanged/10,0.f,1.0f)  );
	if ( scoreChanged > 0 ) scoreChanged--;

	scoreBoard->render(" Lvl: " + std::to_string(currentLvl + 1), glm::vec2(530, 50), 20, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

std::vector<Bubble*> Scene::loadBubbleMap() 
{
	std::vector<Bubble*> result;
	for (unsigned int i = 0; i < gmap.size(); i++) {
		if (gmap[i] > -1) {
			Bubble* b = new Bubble();
			Bubble::Color c;
			switch (gmap[i]) {
				case 0:
					c = Bubble::Color::Blue; break;
				case 1:
					c = Bubble::Color::Dark; break;
				case 2:
					c = Bubble::Color::Green; break;
				case 3:
					c = Bubble::Color::Orange; break;
				case 4:
					c = Bubble::Color::Purple; break;
				case 5:
					c = Bubble::Color::Red; break;
				case 6:
					c = Bubble::Color::White; break;
				case 7:
					c = Bubble::Color::Yellow; break;
			}
			b->init(c, texProgram, true);
			m_bubbles.push_back(b);
			result.push_back(b);
		}
		else result.push_back(NULL);
	}
	return result;
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void Scene::addBubble(Bubble* b) {
	m_bubbles.push_back(b);
}

void Scene::removeBubble(Bubble* b) {
	std::vector<Bubble*>::iterator it;
	it = std::find(m_bubbles.begin(), m_bubbles.end(), b);
	m_bubbles.erase(it);
	delete b;
}

void Scene::addPoints(int points){
	this->score += points;
	scoreChanged += 50;
}

void Scene::s_bubbleLaunched(Bubble* bubble) {
	Game::instance().getScene().addBubble(bubble);
}
