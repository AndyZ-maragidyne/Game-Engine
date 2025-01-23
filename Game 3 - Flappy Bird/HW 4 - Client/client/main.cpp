#include "main.hpp"
#include <memory>
#include <iostream>
#include <zmq.hpp>
using namespace std;


int main(int argc, char* argv[])
{
    //Call the initialization functions
    initSDL();
    //Call the setup function in game.cpp
    //setup();


    //create the client and connect it to the server
    zmq::context_t context(4);
    zmq::socket_t client(context, ZMQ_REQ);
    client.connect("tcp://localhost:5555");

    //get the client's process ID
    std::string processId = std::to_string(GetCurrentProcessId());

    std::vector<std::unique_ptr<GameObject>> entityList;
    std::mutex m;
    std::condition_variable cv;
    Thread net(0, NULL, &m, &cv);
    Thread draw(1, NULL, &m, &cv);
    
  
    while (1)
    {
        //Prepare the scene
        prepareScene();

        //Start threads
        std::string input = getClientInput();
        Event* e = new Event(EventType::INPUT_EVENT);
        e->parameters["input"] = input;
        e->parameters["id"] = processId;
        std::thread comm(run_wrapper, &net, &client, &entityList, *e);
        std::thread screen(run_wrapper, &draw, &client, &entityList, *e);

        //Join threads
        comm.join();
        screen.join();

        //Inserting 16ms delay at the end for a budget frame-limiter.
        SDL_Delay(16);
    }

    return 0;
}