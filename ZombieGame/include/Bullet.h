#ifndef BULLET_H
#define BULLET_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <SpriteBatch.h>

class Human;
class Zombie;
class Agent;

const int BULLET_WIDTH = 5;

class Bullet
{
    public:
        Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);
        virtual ~Bullet();

        bool update(const std::vector<std::string>& levelData, float deltaTime);
        void draw(Bengine::SpriteBatch& spriteBatch);

        bool collideWithAgent(Agent* agent);
        float getDamage()const {return _damage;}

        glm::vec2 getPosition() const {return _position;}

    protected:

    private:
        bool collideWithWorld(const std::vector<std::string>& levelData);

        float _damage;
        glm::vec2 _position;
        glm::vec2 _direction;
        float _speed;
};

#endif // BULLET_H
