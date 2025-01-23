#include "game.hpp"
#include "Timeline.hpp"
#include <memory>
#include <iostream>



int turn;
bool playerWin;
physics p;
std::vector<std::unique_ptr<GameObject>> * entityList = new std::vector<std::unique_ptr<GameObject>>();
std::vector<std::unique_ptr<GameObject>>* invisibleEntityList = new std::vector<std::unique_ptr<GameObject>>();
Timeline* t = new Timeline();
std::unique_ptr<EventManager> manager = std::make_unique<EventManager>(t);
std::unique_ptr<SpawnHandler> spawnHandler = std::make_unique<SpawnHandler>(manager.get());
std::unique_ptr<InputHandler> inputHandler = std::make_unique<InputHandler>(manager.get(), entityList);
std::unique_ptr<DeathHandler> deathHandler = std::make_unique<DeathHandler>(manager.get());
std::unique_ptr<CollisionHandler> collisionHandler = std::make_unique<CollisionHandler>(manager.get());


EventManager* setup(int64_t* frame_delta) {
	manager->registerEvent({ EventType::SPAWN_EVENT }, spawnHandler.get());
	manager->registerEvent({ EventType::DEATH_EVENT }, deathHandler.get());
	inputHandler->setFrameD(frame_delta);
	manager->registerEvent({ EventType::INPUT_EVENT }, inputHandler.get());
	manager->registerEvent({ EventType::COLLISION_EVENT }, collisionHandler.get());
	auto e1 = std::make_unique<GameObject>(0, 0, 50, 1500);
	e1->addComponent(new DrawComponent(e1.get()));


	//first floor
	auto e2 = std::make_unique<GameObject>(-100, 900, 2000, 50);
	e2->addComponent(new DrawComponent(e2.get()));
	//second floor
	auto e3 = std::make_unique<GameObject>(-100, 50, 2000, 50);
	e3->addComponent(new DrawComponent(e3.get()));

	//moving platform
	auto e4 = std::make_unique<GameObject>(1800, 0, 50, 1500);
	e4->addComponent(new DrawComponent(e4.get()));

	//large platform after moving platform
	auto e5 = std::make_unique<GameObject>(3300, 880, 1500, 50);
	e5->addComponent(new DrawComponent(e5.get()));
	//top wall
	auto e6 = std::make_unique<GameObject>(3800, 0, 50, 500);
	e6->addComponent(new DrawComponent(e6.get()));
	//bottom wall
	auto e7 = std::make_unique<GameObject>(4500, 180, 50, 700);
	e7->addComponent(new DrawComponent(e7.get()));
	//bottom platform
	auto e8 = std::make_unique<GameObject>(4350, 660, 150, 50);
	e8->addComponent(new DrawComponent(e8.get()));
	//middle platform
	auto e9 = std::make_unique<GameObject>(4050, 560, 150, 50);
	e9->addComponent(new DrawComponent(e9.get()));
	//top platform
	//auto e10 = std::make_unique<GameObject>(3800, 460, 150, 50);
	//e10->addComponent(new DrawComponent(e10.get()));
	////roof right
	//auto e11 = std::make_unique<GameObject>(4300, 130, 250, 50);
	//e11->addComponent(new DrawComponent(e11.get()));
	////roof left
	//auto e12 = std::make_unique<GameObject>(4050, 180, 150, 50);
	//e12->addComponent(new DrawComponent(e12.get()));

	//
	////mid air jump 1
	//auto e16 = std::make_unique<GameObject>(5000, 680, 300, 50);
	//e16->addComponent(new DrawComponent(e16.get()));
	//e4->addComponent(new AIComponent(e16.get(), 0, 1, 49, entityList, frame_delta));
	////mid air jump 2
	//auto e25 = std::make_unique<GameObject>(5500, 480, 300, 50);
	//e25->addComponent(new DrawComponent(e25.get()));
	////mid air jump 3
	//auto e26 = std::make_unique<GameObject>(6000, 280, 300, 50);
	//e26->addComponent(new DrawComponent(e26.get()));

	////long bar in between the up jumps and down jumps
	//auto e18 = std::make_unique<GameObject>(6375, 200, 50, 1000);
	//e18->addComponent(new DrawComponent(e18.get()));

	////mid air jump 4
	//auto e27 = std::make_unique<GameObject>(6500, 280, 300, 50);
	//e27->addComponent(new DrawComponent(e27.get()));
	////mid air jump 5
	//auto e28 = std::make_unique<GameObject>(7000, 480, 300, 50);
	//e28->addComponent(new DrawComponent(e28.get()));
	////mid air jump 6
	//auto e29 = std::make_unique<GameObject>(7500, 680, 300, 50);
	//e29->addComponent(new DrawComponent(e29.get()));

	////long bar at the end of up jumps and down jumps
	//auto e30 = std::make_unique<GameObject>(8300, 0, 50, 600);
	//e30->addComponent(new DrawComponent(e30.get()));

	////final platform
	//auto e31 = std::make_unique<GameObject>(8200, 880, 3000, 50);
	//e31->addComponent(new DrawComponent(e31.get()));

	//


	////death zone for falling into the void
	//auto e17 = std::make_unique<GameObject>(-1000, 2000, 10000000, 50);
	//e17->addComponent(new DrawComponent(e17.get(), 0x00, 0xFF, 0x00));
	//e17->addComponent(new DeathZoneComponent(e17.get(), entityList, invisibleEntityList, manager.get()));

	//

	////Scrollers, e19 is the right side scroller, e20 is the left side scroller
	//auto e19 = std::make_unique<GameObject>(1500, 0, 100000, 1100);
	//auto e20 = std::make_unique<GameObject>(-99600, 0, 100000, 1100);

	//e19->addComponent(new DrawComponent(e19.get(), 0x00, 0x00, 0xFF, 0x00));
	//e19->addComponent(new SidescrollComponent(e19.get(),e20.get(), entityList, invisibleEntityList, frame_delta));

	//e20->addComponent(new DrawComponent(e20.get(), 0x00, 0x00, 0xFF, 0x00));
	//auto sidescrollComponent = new SidescrollComponent(e20.get(), e19.get(), entityList, invisibleEntityList, frame_delta);
	//sidescrollComponent->setScroll(10);
	//e20->addComponent(sidescrollComponent);

	////Spawn points
	//auto e21 = std::make_unique<GameObject>(600, 400, 50, 50);
	//e21->addComponent(new DrawComponent(e21.get(), 0x55, 0x55, 0x00));
	//e21->addComponent(new SpawnpointComponent(e1.get(), e21.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 600, 400));
	//e21->setSpawn(true);

	//auto e22 = std::make_unique<GameObject>(1500, 650, 50, 50);
	//e22->addComponent(new DrawComponent(e22.get(), 0x55, 0x55, 0x00));
	//e22->addComponent(new SpawnpointComponent(e1.get(), e22.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 1500, 750));
	//e22->setSpawn(true);

	//auto e24 = std::make_unique<GameObject>(3300, 650, 50, 50);
	//e24->addComponent(new DrawComponent(e24.get(), 0x55, 0x55, 0x00));
	//e24->addComponent(new SpawnpointComponent(e1.get(), e24.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 0, 750));
	//e24->setSpawn(true);

	//auto e23 = std::make_unique<GameObject>(4600, 650, 50, 50);
	//e23->addComponent(new DrawComponent(e23.get(), 0x55, 0x55, 0x00));
	//e23->addComponent(new SpawnpointComponent(e1.get(), e23.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 0, 750));
	//e23->setSpawn(true);


	entityList->push_back(std::move(e1));
	entityList->push_back(std::move(e2));
	entityList->push_back(std::move(e3));
	entityList->push_back(std::move(e4));
	entityList->push_back(std::move(e5));
	entityList->push_back(std::move(e6));
	entityList->push_back(std::move(e7));
	entityList->push_back(std::move(e8));
	entityList->push_back(std::move(e9));

	turn = 0;
	playerWin = false;
	return manager.get();
}

/**
* Runs game here
*/
void runGame(int64_t frame_delta)
{
	for (auto& e : *entityList) {
		e->run();
	}
	for (auto& e : *invisibleEntityList) {
		e->run();
	}
	manager->handleEvents();

	//p.applyGravity(entityList, frame_delta); //apply physics to entities
	/*if (turn < 100) {
		(*entityList)[3]->move(3, 0, entityList, frame_delta);
		turn++;
	}
	else if (turn >= 100 && turn <= 200) {
		(*entityList)[3]->move(-3, 0, entityList, frame_delta);
		turn++;
		if (turn >= 200) {
			turn = 0;
		}
	}*/
}


//Get entity list for input reading
std::vector<std::unique_ptr<GameObject>>* getList()
{
	return entityList;
}

std::vector<std::unique_ptr<GameObject>>* getInvisibleList()
{
	return invisibleEntityList;
}


void setList(std::vector<std::unique_ptr<GameObject>>* newList)
{
	entityList = newList;
}

//Get physics to apply gravity
physics getPhysics()
{
	return p;
}

EventManager* getManager() {
	return manager.get();
}




