#pragma once
#include "structs.hpp"
#include "init.hpp"
#include "draw.hpp"
#include "input.hpp"
#include "entity.hpp"
#include "physics.hpp"
#include "game.hpp"
#include "Timeline.hpp"
#include "threads.hpp"
#include "client.hpp"
#include "Event.hpp"
#include <windows.h>
#include <memory>

// SDL render and window context
extern App* app;

int main(int argc, char* argv[]);

/**
 * Wrapper function because threads can't take pointers to member functions.
 */
void run_wrapper(Thread* fe, zmq::socket_t* client, std::vector<std::unique_ptr<GameObject>>* entityList, Event e)
{
    fe->run(client, entityList, e);
}