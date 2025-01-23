#pragma once
#include "structs.hpp"
#include "init.hpp"
#include "draw.hpp"
#include "input.hpp"
#include "entity.hpp"
#include "physics.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include "PhysicsComponent.hpp"
#include "DrawComponent.hpp"
#include "ControllableComponent.hpp"
#include "DeathZoneComponent.hpp"
#include "SpawnpointComponent.hpp"
#include "SidescrollComponent.hpp"
#include "AIComponent.hpp"
#include "EventManager.hpp"
#include "SpawnHandler.hpp"
#include "DeathHandler.hpp"
#include "InputHandler.hpp"
#include "CollisionHandler.hpp"
#include "Event.hpp"
#include <memory>

EventManager* setup(int64_t* frame_delta);

void runGame(int64_t frame_delta);

std::vector<std::unique_ptr<GameObject>>* getList();

std::vector<std::unique_ptr<GameObject>>* getInvisibleList();

void setList(std::vector<std::unique_ptr<GameObject>>* newList);

physics getPhysics();

EventManager* getManager();