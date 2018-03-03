#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Agent.h"

#include <resourceManager.h>

class Human;

class Zombie : public Agent
{
public:
    Zombie();
    virtual ~Zombie();

    void init(float speed, glm::vec2 pos);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies,
                        float deltaTime) override;

protected:

private:
    Human* getNearestHuman(std::vector<Human*>& humans);
};

#endif // ZOMBIE_H
