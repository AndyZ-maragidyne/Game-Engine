#include "game.hpp"
#include <memory>
#include <iostream>



int turn;
physics p;
std::vector<std::unique_ptr<GameObject>>* entityList = new std::vector<std::unique_ptr<GameObject>>();
std::vector<std::unique_ptr<GameObject>>* invisibleEntityList = new std::vector<std::unique_ptr<GameObject>>();

void setup(int64_t* frame_delta) {
	auto e1 = std::make_unique<GameObject>(600, 200, 50, 100);
	e1->addComponent(new PhysicsComponent(e1.get(), 10, entityList, frame_delta));
	e1->addComponent(new ControllableComponent(e1.get(), entityList, frame_delta));
	e1->addComponent(new DrawComponent(e1.get(), 0xFF, 0x00, 0x00));
	e1->setCollide(true);

	auto e2 = std::make_unique<GameObject>(0, 880, 1920, 50);
	e2->addComponent(new DrawComponent(e2.get()));
	auto e3 = std::make_unique<GameObject>(500, 600, 50, 400);
	e3->addComponent(new DrawComponent(e3.get()));
	auto e4 = std::make_unique<GameObject>(1400, 800, 200, 50);
	e4->addComponent(new DrawComponent(e4.get()));
	auto e5 = std::make_unique<GameObject>(1200, 900, 100, 50);
	e5->addComponent(new DrawComponent(e5.get()));
	auto e6 = std::make_unique<GameObject>(1125, 700, 150, 50);
	e6->addComponent(new DrawComponent(e6.get()));
	auto e7 = std::make_unique<GameObject>(975, 675, 100, 50);
	e7->addComponent(new DrawComponent(e7.get()));
	auto e8 = std::make_unique<GameObject>(800, 690, 100, 50);
	e8->addComponent(new DrawComponent(e8.get()));
	auto e9 = std::make_unique<GameObject>(675, 600, 100, 50);
	e9->addComponent(new DrawComponent(e9.get()));
	auto e10 = std::make_unique<GameObject>(875, 450, 100, 50);
	e10->addComponent(new DrawComponent(e10.get()));
	auto e11 = std::make_unique<GameObject>(1150, 425, 150, 50);
	e11->addComponent(new DrawComponent(e11.get()));
	auto e12 = std::make_unique<GameObject>(1400, 350, 100, 50);
	e12->addComponent(new DrawComponent(e12.get()));
	auto e13 = std::make_unique<GameObject>(1550, 300, 75, 50);
	e13->addComponent(new DrawComponent(e13.get()));
	auto e14 = std::make_unique<GameObject>(1350, 150, 100, 50);
	e14->addComponent(new DrawComponent(e14.get()));
	auto e15 = std::make_unique<GameObject>(1150, 150, 100, 50);
	e15->addComponent(new DrawComponent(e15.get()));
	auto e16 = std::make_unique<GameObject>(950, 150, 100, 50);
	e16->addComponent(new DrawComponent(e16.get()));

	auto e17 = std::make_unique<GameObject>(750, 150, 100, 50);
	e17->addComponent(new DrawComponent(e17.get(), 0x00, 0xFF, 0x00));
	e17->addComponent(new DeathZoneComponent(e17.get(), entityList));

	auto e18 = std::make_unique<GameObject>(550, 150, 100, 50);
	e18->addComponent(new DrawComponent(e18.get()));

	//Scrollers, e19 is the right side scroller, e20 is the left side scroller
	auto e19 = std::make_unique<GameObject>(1500, 150, 100, 900);
	auto e20 = std::make_unique<GameObject>(300, 150, 100, 900);

	e19->addComponent(new DrawComponent(e19.get(), 0x00, 0x00, 0xFF, 0x00));
	e19->addComponent(new SidescrollComponent(e19.get(), e1.get(), e20.get(), entityList, invisibleEntityList, frame_delta));

	e20->addComponent(new DrawComponent(e20.get(), 0x00, 0x00, 0xFF, 0x00));
	auto sidescrollComponent = new SidescrollComponent(e20.get(), e1.get(), e19.get(), entityList, invisibleEntityList, frame_delta);
	sidescrollComponent->setScroll(10);
	e20->addComponent(sidescrollComponent);

	//Spawn points
	auto e21 = std::make_unique<GameObject>(600, 400, 50, 50);
	e21->addComponent(new DrawComponent(e21.get(), 0x55, 0x55, 0x00));
	e21->addComponent(new SpawnpointComponent(e1.get(), e21.get(), e19.get(), e20.get(), entityList, invisibleEntityList, 600, 400));

	auto e22 = std::make_unique<GameObject>(1000, 800, 50, 50);
	e22->addComponent(new DrawComponent(e22.get(), 0x55, 0x55, 0x00));
	e22->addComponent(new SpawnpointComponent(e1.get(), e22.get(), e19.get(), e20.get(), entityList, invisibleEntityList, 1000, 800));

	entityList->push_back(std::move(e1));
	entityList->push_back(std::move(e2));
	entityList->push_back(std::move(e3));
	entityList->push_back(std::move(e4));
	entityList->push_back(std::move(e5));
	entityList->push_back(std::move(e6));
	entityList->push_back(std::move(e7));
	entityList->push_back(std::move(e8));
	entityList->push_back(std::move(e9));
	entityList->push_back(std::move(e10));
	entityList->push_back(std::move(e11));
	entityList->push_back(std::move(e12));
	entityList->push_back(std::move(e13));
	entityList->push_back(std::move(e14));
	entityList->push_back(std::move(e15));
	entityList->push_back(std::move(e16));
	invisibleEntityList->push_back(std::move(e17));
	entityList->push_back(std::move(e18));
	invisibleEntityList->push_back(std::move(e19));
	invisibleEntityList->push_back(std::move(e20));
	invisibleEntityList->push_back(std::move(e21));
	invisibleEntityList->push_back(std::move(e22));
	turn = 0;
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
	//p.applyGravity(entityList, frame_delta); //apply physics to entities
	if (turn < 100) {
		(*entityList)[3]->move(3, 0, entityList, frame_delta);
		turn++;
	}
	else if (turn >= 100 && turn <= 200) {
		(*entityList)[3]->move(-3, 0, entityList, frame_delta);
		turn++;
		if (turn >= 200) {
			turn = 0;
		}
	}
}


//Get entity list for input reading
std::vector<std::unique_ptr<GameObject>>* getList()
{
	return entityList;
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






