#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL/SDL.h>

#ifndef MAINGAME_H
#define MAINGAME_H

#include <random>
#include <ctime>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>
#include <algorithm>
#include <cstring>

#include <Window.h>
#include <GLSLProgram.h>
#include <Camera2D.h>
#include <InputManager.h>
#include <SpriteBatch.h>
#include <errors.h>
#include <Bengine.h>
#include <Timing.h>
#include <SpriteFont.h>
#include <ParticleEngine2D.h>
#include <ParticleBatch2D.h>
#include <resourceManager.h>

#include "Level.h"
#include "Human.h"
#include "Zombie.h"
#include "Player.h"
#include "Gun.h"
#include "Bullet.h"
#include "AudioEngine.h"

enum class GameState {PLAY, EXIT};

class Zombie;

class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();
    ///Init the level
    void initLevel();
    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

    ///updates all agents
    void updateAgent(float deltaTime);

    void updateBullets(float deltaTime);

    void checkVictory();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    ///draws the heads up display
    void drawHud();

    void addBlood(const glm::vec2& position, int numParticles);

private:
    /// Member Variables
    Bengine::Window _window; ///< The game window
    Bengine::GLSLProgram _textureProgram; ///< The shader program
    Bengine::InputManager _inputManager; ///< Handles input
    Bengine::Camera2D _camera; ///< Main Camera
    Bengine::Camera2D _hudCamera; ///< HUD Camera
    Bengine::SpriteBatch _agentSpriteBatch;
    Bengine::SpriteBatch _hudSpriteBatch;
    Bengine::ParticleEngine2D m_particleEngine;
    Bengine::ParticleBatch2D* m_bloodParticleBatch;

    std::vector<Level*> _levels;

    int _screenWidth;
    int _screenHeight;
    float _fps;
    int _currentLevel;

    Player* _player;
    std::vector<Human* > _humans;
    std::vector<Zombie* > _zombies;
    std::vector<Bullet> _bullets;

    int _numHumansKilled;
    int _numZombiesKilled;

    Bengine::SpriteFont* _spriteFont;

    Bengine::AudioEngine m_audioEngine;

    GameState _gameState;
};

#endif //MAINGAME_H

