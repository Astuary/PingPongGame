#include "Human.h"
#include <random>
#include <ctime>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

Human::Human():
    _frames(0)
{
    //ctor
}

Human::~Human()
{
    //dtor
}

void Human::init(float speed, glm::vec2 pos){

    std::random_device rd;
    static std::mt19937 randomEngine(rd());
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _health = 20;

    _color.r = 255;
    _color.g = 255;
    _color.b = 255;
    _color.a = 255;
    _speed = speed;
    _position = pos;
    m_textureID = Bengine::resourceManager::getTexture("Textures/human.png").id;

    m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    //std::cout<<randDir<<std::endl;
    if(m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);

    m_direction = glm::normalize(m_direction);
}

void Human::update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies,
                        float deltaTime){

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-40.0f * 3.14159265359f / 180, 40.0f * 3.14159265359f / 180);

    _position += m_direction * _speed * deltaTime;
    if(_frames == 20) {
            m_direction = glm::rotate(m_direction, randRotate(randomEngine));
            _frames = 0;
    }
    else _frames++;

    collideWithLevel(levelData);

    if(collideWithLevel(levelData)){
        m_direction = glm::rotate(m_direction, randRotate(randomEngine));
    }
}
