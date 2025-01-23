#include "main.hpp"
#include <memory>
#include <iostream>
#include <zmq.h>
using namespace std;

int64_t frame_delta = 0;

void run_wrapper(Thread* fe, std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, zmq::socket_t* server, Timeline* time, EventManager* m)
{
    fe->run(entityList, frame_delta, server, time, m);
}

int main(int argc, char* argv[])
{
    //Call the initialization functions
    //initSDL();
    
    //Call the setup function in game.cpp
    EventManager* manager = setup(&frame_delta);
    std::vector<std::unique_ptr<GameObject>>* entityList = getList();

    physics p = getPhysics();

    Timeline* t = new Timeline();
    Timeline* gameTime = new Timeline(t, 5); //gameTime is anchored off of the realtime

    bool connected = false;
    int64_t last_time = gameTime->getTime();

    //creates the server and binds it to the port
    zmq::context_t context(1);
    zmq::socket_t server(context, zmq::socket_type::rep);
    server.bind("tcp://*:5555");
    
    std::vector<int64_t> frameList;
    std::vector<std::string> messages;
    int W = 100;
    int count = 0;

    //Initialize objects for multithreading
    std::mutex m;
    std::mutex sm;
    std::condition_variable cv;
    std::condition_variable scv;
    Thread t1(0, NULL, &sm, &scv);
    Thread t2(1, NULL, &sm, &scv);

    //Start threads
    std::thread client(run_wrapper, &t1, entityList, &frame_delta, &server, gameTime, manager);
    std::thread send(run_wrapper, &t2, entityList, &frame_delta, &server, gameTime, manager);
   
    while (1)
    {
        //prepareScene();
        //get the entityList from game.cpp
        entityList = getList();
       
        int64_t current_time = gameTime->getTime();
        frame_delta = (current_time - last_time) / gameTime->getTic();
        last_time = current_time;
        
        if (frame_delta < 0 || gameTime->isPaused()) {
            frame_delta = 0;
        }

        if (frameList.size() < W) {
            frameList.push_back(frame_delta);
        }
        else {
            frameList[count] = frame_delta;
        }

        count = (count + 1) % W;

        int64_t sum = 0;
        if (frameList.size() < W) {
            for (int i = 0; i < frameList.size(); i++) {
                sum += frameList[i];
            }
        }
        else {
            for (int i = 0; i < W; i++) {
                sum += frameList[i];
            }
        }
        int64_t moving_average = sum/W;

        runGame(frame_delta);
        //presentScene();

        //Inserting 16ms delay at the end for a budget frame-limiter.
        SDL_Delay(16);
    }

    //Join threads
    client.join();
    send.join();

    return 0;
}