#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <SpriteBatch.h>
#include <glm/glm.hpp>

const int TILE_WIDTH = 64;

class Level{
public:
    Level(const std::string& fileName);///Load the level
    virtual ~Level();

    void draw();

    int getWidth() const {return _levelData[0].size();}
    int getHeight() const {return _levelData.size();}
    int getNumHumans() const {return _numHumans;}
    const std::vector<std::string>& getLevelData() const{return _levelData;}
    glm::vec2 getStartPlayerPos() const {return _startPlayerPos;}
    const std::vector<glm::vec2>& getZombieStartPos() const {return _zombieStartPosition;}

protected:

private:
    std::vector<std::string> _levelData;
    int _numHumans;
    Bengine::SpriteBatch _spriteBatch;
    glm::vec2 _startPlayerPos;
    std::vector<glm::vec2> _zombieStartPosition;
};

#endif // LEVEL_H
