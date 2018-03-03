#include "Player.h"
#include <SDL/sdl.h.>
#include "Gun.h"



Player::Player() :
	_currentGunIndex(-1)
{
}


Player::~Player()
{
}

void Player::init(float spd, glm::vec2 pos, Bengine::InputManager* inputManager, Bengine::Camera2D *camera, std::vector<Bullet>* bullets) {
	_speed = spd;
	_position = pos;
	_health = 150;
	_color = Bengine::ColorRGBA8(150, 0, 0, 255);
	/*_color.r = 0;
	_color.g = 0;
	_color.b = 100;
	_color.a = 255;*/
	_inputManager = inputManager;
	_camera = camera;
	_bullets = bullets;
	m_textureID = Bengine::resourceManager::getTexture("Textures/player.png").id;
}

void Player::addGun(Gun* gun) {
	//Add gun to player inv.
	_guns.push_back(gun);

	//If no gun equipped:
	if (_currentGunIndex == -1) {
		_currentGunIndex = 0;
	}
}

void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies, float deltaTime) {
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_a)) {
		_position.x -= _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_d)) {
		_position.x += _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_1) & _guns.size() >= 0) {
		_currentGunIndex = 0;
	}

	if (_inputManager->isKeyDown(SDLK_2) & _guns.size() >= 1) {
		_currentGunIndex = 1;
	}

	if (_inputManager->isKeyDown(SDLK_3) & _guns.size() >= 2) {
		_currentGunIndex = 2;
	}

	glm::vec2 mouseCoords = _inputManager->getMouseCoords();
    mouseCoords = _camera->convertScreenToWorld(mouseCoords);
    glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
    m_direction = glm::normalize(mouseCoords - centerPosition);

	if (_currentGunIndex != -1) {

		_guns[_currentGunIndex]->update(_inputManager->isKeyDown(SDL_BUTTON_LEFT),centerPosition, m_direction, *_bullets, deltaTime);
	}

	collideWithLevel(levelData);
}
