#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <vector>
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "resource_manager.h"


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
    // level state
    std::vector<GameObject> Bricks;
    // constructor
    GameLevel() { }
    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer& renderer);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};
