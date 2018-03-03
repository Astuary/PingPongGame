#include "Bullet.h"
#include <resourceManager.h>
#include <Vertex.h>

#include "Human.h"
#include "Zombie.h"
#include "Agent.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed):
    _damage(damage),
    _position(position),
    _direction(direction),
    _speed(speed)
{
    //ctor
}

Bullet::~Bullet()
{
    //dtor
}

bool Bullet::update(const std::vector<std::string>& levelData, float deltaTime){
    _position += _direction * _speed * deltaTime;
    return collideWithWorld(levelData);
}

void Bullet::draw(Bengine::SpriteBatch& spriteBatch){
    glm::vec4 destRect(_position.x + BULLET_WIDTH,
                       _position.y + BULLET_WIDTH,
                       BULLET_WIDTH * 2,
                       BULLET_WIDTH * 2);
    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Bengine::ColorRGBA8 color;
    color.r = 200;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    spriteBatch.draw(destRect, uvRect, Bengine::resourceManager::getTexture("Texture/circle.png").id, 0.0f, color);
}

bool Bullet::collideWithAgent(Agent* agent){
    const float MIN_DISTANCE = AGENT_RADIUS + BULLET_WIDTH;

    glm::vec2 centerPosA = _position;
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);
    float collisionDepth = MIN_DISTANCE - distance;

    if(collisionDepth > 0){
        return true;
    }
    return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData){
    glm::ivec2 gridPosition;
    gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
    gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

    if(gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
       gridPosition.y < 0 || gridPosition.y >= levelData.size()){
        return true;
    }

    return (levelData[gridPosition.y][gridPosition.x] != '.');
}
