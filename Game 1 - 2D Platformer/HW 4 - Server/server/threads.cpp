#include "threads.hpp"

void Thread::run(std::vector<std::unique_ptr<GameObject>>* entityList, int64_t* frame_delta, zmq::socket_t* server, Timeline* time, EventManager* m)
{
    if (i == 0)
    {
        while (1)
        {
            _mutex->lock();
            std::string add = recieveFromClients(*server);
            _mutex->unlock();

            _mutex->lock();
            processMessages(add, entityList, *frame_delta, time, m);
            _mutex->unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            _condition_variable->notify_all();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    else
    {
        while (1)
        {
            std::unique_lock<std::mutex> lock(*_mutex);
            _condition_variable->wait(lock);
            sendToClients(*server, entityList);
        }
    }

}