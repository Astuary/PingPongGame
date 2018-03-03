#ifndef GUN_H
#define GUN_H

#include<string>
#include<vector>
#include<glm/glm.hpp>

#include "Bullet.h"

#include <AudioEngine.h>
class Gun
{
    public:
        Gun(std::string name, int fireRate, int bulletsPerShot,
            float spread, float bulletDamage, float bulletSpeed, Bengine::SoundEffect fireEffect);
        virtual ~Gun();

        void update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);

    protected:

    private:
        Bengine::SoundEffect m_fireEffect;

        void fire(const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets);

        std::string _name;
        int _fireRate; ///in terms of frames
        int _bulletsPerShot; ///at a time fired bullets
        float _spread; ///accuracy
        float _bulletSpeed;
        float _bulletDamage;
        float _frameCounter;
};

#endif // GUN_H
