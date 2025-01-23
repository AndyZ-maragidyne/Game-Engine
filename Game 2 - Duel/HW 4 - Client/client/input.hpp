#pragma once 
#include <SDL.h>
#include <vector>
#include <memory>
#include "structs.hpp"
#include "entity.hpp"
#include "defs.hpp"

extern App* app;

void doInput(std::vector<std::unique_ptr<Entity>>*, int64_t frame_delta);

std::string getClientInput();