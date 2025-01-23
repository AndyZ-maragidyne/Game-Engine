#include "input.hpp"
#include "game.hpp"
#include "server.hpp"
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <iostream>

class Thread
{
    bool busy; // a member variable used to indicate thread "status"
    int i; // an identifier
    Thread* other;
    std::mutex* _mutex; // the object for mutual exclusion of execution
    std::condition_variable* _condition_variable; // for messaging between threads

public:
    Thread(int i, Thread* other, std::mutex* _mutex, std::condition_variable* _condition_variable)
    {
        this->i = i; // set the id of this thread
        if (i == 0) { busy = true; }
        else { this->other = other; }
        this->_mutex = _mutex;
        this->_condition_variable = _condition_variable;
    }

    bool isBusy()
    {
        std::lock_guard<std::mutex> lock(*_mutex);  // this locks the mutuex until the variable goes out of scope (i.e., when the function returns in this case)
        return busy;
    }

    void run(std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, zmq::socket_t* server, Timeline* time, EventManager* m);

};