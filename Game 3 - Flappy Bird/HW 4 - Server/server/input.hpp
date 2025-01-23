#pragma once 
#include <SDL.h>
#include <vector>
#include <memory>
#include "structs.hpp"
#include "entity.hpp"
#include "defs.hpp"
#include "Timeline.hpp"

extern App* app;

void doInput(std::vector<std::unique_ptr<Entity>>*, int64_t frame_delta);

void doClientInput(std::vector<std::unique_ptr<Entity>>* entityList, int64_t frame_delta, std::string clientID, std::string inputs, Timeline *t);