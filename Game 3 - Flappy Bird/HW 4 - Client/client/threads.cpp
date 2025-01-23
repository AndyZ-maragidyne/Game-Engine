#include "threads.hpp"

void Thread::run(zmq::socket_t* client, std::vector<std::unique_ptr<GameObject>>* entityList, Event e)
{
    if (i == 0)
    {
        sendToServer(*client, e);

        *entityList = recieveFromServer(*client);

    }
    else
    {
        setList(entityList);

        for (auto&& e : *entityList) {
            e->run();
        }

        presentScene();
    }
}