#include "EventManager.hpp"


EventManager::EventManager(Timeline * t) : t(t) {}

void EventManager::registerEvent(std::list<EventType> types, EventHandler* handler)
{
	for (const auto& e : types) {
		if (handlers.find(e) != handlers.end()) {
			handlers[e].push_back(handler);
		}
		else {
			std::list<EventHandler*> handlerList;
			handlerList.push_back(handler);
			handlers[e] = handlerList;
		}
	}
}

void EventManager::deregister(std::list<EventType> types, EventHandler* handler)
{
	for (const auto& e : types) {
		auto it = handlers.find(e);
		if (it != handlers.end()) {
			std::list<EventHandler*>& handlerList = it->second;

			handlerList.remove(handler);

			if (handlerList.empty()) {
				handlers.erase(it);
			}
		
		}
	}
}

void EventManager::raise(Event e)
{
	if (e.getType() == EventType::COLLISION_EVENT || e.getType() == EventType::INPUT_EVENT) {
		e.setTimeStamp(t->getTime());
	}
	else {
		e.setTimeStamp(t->getTime() + 1);
	}
	raisedEvents.push_back(e);

	/*handleEvents();*/


}

std::mutex mutex;

void EventManager::handleEvents() {
	std::lock_guard<std::mutex> lock(mutex);
	for (auto e = raisedEvents.begin(); e != raisedEvents.end(); ) {
		if (e->getTimeStamp() <= t->getTime()) {
			auto it = handlers.find(e->getType());
			if (it != handlers.end()) {
				std::list<EventHandler*>& handlerList = it->second;

				for (EventHandler* h : handlerList) {
					h->onEvent(*e);
				}
			}
			e = raisedEvents.erase(e);

		} else{
			e++;
		}
	}

}
