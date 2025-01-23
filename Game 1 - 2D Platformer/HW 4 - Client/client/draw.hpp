#pragma once
#include "structs.hpp"
#include "entity.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>
#include <SDL.h>

// SDL render and window context
extern App* app;

// Prepare scene to be rendered to window
void prepareScene(void);
// Render scene to window
void presentScene(void);

// Draws created entity
void drawEntity(std::vector<std::unique_ptr<GameObject>>* entityList);