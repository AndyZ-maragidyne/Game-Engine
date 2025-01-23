#pragma once
#include "structs.hpp"
#include "init.hpp"
#include "draw.hpp"
#include "input.hpp"
#include "entity.hpp"
#include "physics.hpp"
#include "game.hpp"
#include "Timeline.hpp"
#include "server.hpp"
#include "threads.hpp"
#include <algorithm>
#include <zmq.hpp>
#include <unordered_map>
#include <memory>

// SDL render and window context
extern App* app;

extern int64_t frame_delta;

int main(int argc, char* argv[]);

/**
 * Wrapper function because threads can't take pointers to member functions.
 */
void run_wrapper(Thread* fe, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, zmq::socket_t* server, Timeline* time, EventManager* m);