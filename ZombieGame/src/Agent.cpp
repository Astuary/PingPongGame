#include "Agent.h"
#include <algorithm>

Agent::Agent()
{
    //ctor
}

Agent::~Agent()
{
    //dtor
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData){
    std::vector<glm::vec2> collideTilePosition;

    ///1st corner
    checkTilePosition(levelData, collideTilePosition, _position.x, _position.y);
    ///2nd corner
    checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y);
    ///3rd corner
    checkTilePosition(levelData, collideTilePosition, _position.x, _position.y + AGENT_WIDTH);
    ///4th corner
    checkTilePosition(levelData, collideTilePosition, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

    if(collideTilePosition.size() == 0){
        return false;
    }

    for(int i = 0; i < collideTilePosition.size(); i++){
        collideWithTile(collideTilePosition[i]);
    }
    return true;
}

bool Agent::collideWithAgent(Agent* agent){
    const float MIN_DISTANCE = 2 * AGENT_RADIUS;

    glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);
    float collisionDepth = MIN_DISTANCE - distance;

    if(collisionDepth > 0){

        glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

        _position += collisionDepthVec / 2.0f;
        agent->_position -= collisionDepthVec / 2.0f;
        return true;
    }
    return false;
}

void Agent::draw(Bengine::SpriteBatch& spriteBatch){

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    glm::vec4 destRect;
    destRect.x = _position.x;
    destRect.y = _position.y;
    destRect.z = AGENT_WIDTH;
    destRect.w = AGENT_WIDTH;

    spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, _color, m_direction);
}

bool Agent::applyDamage(float damage){
    _health -= damage;
    if(_health <= 0){
        return true;
    }
    return false;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
                              std::vector<glm::vec2>& collideTilePosition,
                              float x, float y){
    ///check 4 corners
    glm::vec2 cornerPos = glm::vec2 (floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH)); ///First Corner

    if(cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
       cornerPos.y < 0 || cornerPos.y >= levelData.size()){
            return;
    }

    if(levelData[cornerPos.y][cornerPos.x] != '.'){
        collideTilePosition.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH /2.0f));
    }
}

///AABB Collision
void Agent::collideWithTile(glm::vec2 tilePos){

    const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

    glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
    glm::vec2 distVec = centerPlayerPos - tilePos;

    float xdepth = MIN_DISTANCE - abs(distVec.x);
    float ydepth = MIN_DISTANCE - abs(distVec.y);

    if(xdepth > 0 && ydepth > 0){
        if(std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f)){
            if(distVec.x < 0){
                _position.x -= xdepth;
            }
            else{
                _position.x += xdepth;
            }
        }
        else{
            if(distVec.y < 0){
                _position.y -= ydepth;
            }
            else{
                _position.y += ydepth;
            }
        }
    }
}
