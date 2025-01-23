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
	auto e1 = std::make_unique<GameObject>(0, 580, 50, 500);
	//e1->addComponent(new PhysicsComponent(e1.get(), 10, entityList, frame_delta));
	//e1->addComponent(new ControllableComponent(e1.get(), entityList, frame_delta));
	e1->addComponent(new DrawComponent(e1.get()));
	//e1->setCollide(true);
	//e1->setPlayer(true);

	//first floor
	auto e2 = std::make_unique<GameObject>(-1000, 880, 2000, 50);
	e2->addComponent(new DrawComponent(e2.get()));
	//second floor
	auto e3 = std::make_unique<GameObject>(1300, 880, 500, 50);
	e3->addComponent(new DrawComponent(e3.get()));

	//platform above second floor
	auto e13 = std::make_unique<GameObject>(1600, 580, 150, 50);
	e13->addComponent(new DrawComponent(e13.get()));
	//platform 1 above moving platform
	auto e14 = std::make_unique<GameObject>(1850, 430, 250, 50);
	e14->addComponent(new DrawComponent(e14.get()));
	//platform 2 above moving platform
	auto e15 = std::make_unique<GameObject>(2500, 430, 250, 50);
	e15->addComponent(new DrawComponent(e15.get()));

	//moving platform
	auto e4 = std::make_unique<GameObject>(1800, 880, 400, 50);
	e4->addComponent(new DrawComponent(e4.get()));
	e4->addComponent(new AIComponent(e4.get(), 1, 0, 700, entityList, frame_delta));
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
	auto e10 = std::make_unique<GameObject>(3800, 460, 150, 50);
	e10->addComponent(new DrawComponent(e10.get()));
	//roof right
	auto e11 = std::make_unique<GameObject>(4300, 130, 250, 50);
	e11->addComponent(new DrawComponent(e11.get()));
	//roof left
	auto e12 = std::make_unique<GameObject>(4050, 180, 150, 50);
	e12->addComponent(new DrawComponent(e12.get()));

	
	//mid air jump 1
	auto e16 = std::make_unique<GameObject>(5000, 680, 300, 50);
	e16->addComponent(new DrawComponent(e16.get()));
	e4->addComponent(new AIComponent(e16.get(), 0, 1, 49, entityList, frame_delta));
	//mid air jump 2
	auto e25 = std::make_unique<GameObject>(5500, 480, 300, 50);
	e25->addComponent(new DrawComponent(e25.get()));
	//mid air jump 3
	auto e26 = std::make_unique<GameObject>(6000, 280, 300, 50);
	e26->addComponent(new DrawComponent(e26.get()));

	//long bar in between the up jumps and down jumps
	auto e18 = std::make_unique<GameObject>(6375, 200, 50, 1000);
	e18->addComponent(new DrawComponent(e18.get()));

	//mid air jump 4
	auto e27 = std::make_unique<GameObject>(6500, 280, 300, 50);
	e27->addComponent(new DrawComponent(e27.get()));
	//mid air jump 5
	auto e28 = std::make_unique<GameObject>(7000, 480, 300, 50);
	e28->addComponent(new DrawComponent(e28.get()));
	//mid air jump 6
	auto e29 = std::make_unique<GameObject>(7500, 680, 300, 50);
	e29->addComponent(new DrawComponent(e29.get()));

	//long bar at the end of up jumps and down jumps
	auto e30 = std::make_unique<GameObject>(8300, 0, 50, 600);
	e30->addComponent(new DrawComponent(e30.get()));

	//final platform
	auto e31 = std::make_unique<GameObject>(8200, 880, 3000, 50);
	e31->addComponent(new DrawComponent(e31.get()));

	


	//death zone for falling into the void
	auto e17 = std::make_unique<GameObject>(-1000, 2000, 10000000, 50);
	e17->addComponent(new DrawComponent(e17.get(), 0x00, 0xFF, 0x00));
	e17->addComponent(new DeathZoneComponent(e17.get(), entityList, invisibleEntityList, manager.get()));

	

	//Scrollers, e19 is the right side scroller, e20 is the left side scroller
	auto e19 = std::make_unique<GameObject>(1500, 0, 100000, 1100);
	auto e20 = std::make_unique<GameObject>(-99600, 0, 100000, 1100);

	e19->addComponent(new DrawComponent(e19.get(), 0x00, 0x00, 0xFF, 0x00));
	e19->addComponent(new SidescrollComponent(e19.get(),e20.get(), entityList, invisibleEntityList, frame_delta));

	e20->addComponent(new DrawComponent(e20.get(), 0x00, 0x00, 0xFF, 0x00));
	auto sidescrollComponent = new SidescrollComponent(e20.get(), e19.get(), entityList, invisibleEntityList, frame_delta);
	sidescrollComponent->setScroll(10);
	e20->addComponent(sidescrollComponent);

	//Spawn points
	auto e21 = std::make_unique<GameObject>(600, 400, 50, 50);
	e21->addComponent(new DrawComponent(e21.get(), 0x55, 0x55, 0x00));
	e21->addComponent(new SpawnpointComponent(e1.get(), e21.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 600, 400));
	e21->setSpawn(true);

	auto e22 = std::make_unique<GameObject>(1500, 650, 50, 50);
	e22->addComponent(new DrawComponent(e22.get(), 0x55, 0x55, 0x00));
	e22->addComponent(new SpawnpointComponent(e1.get(), e22.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 1500, 750));
	e22->setSpawn(true);

	auto e24 = std::make_unique<GameObject>(3300, 650, 50, 50);
	e24->addComponent(new DrawComponent(e24.get(), 0x55, 0x55, 0x00));
	e24->addComponent(new SpawnpointComponent(e1.get(), e24.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 0, 750));
	e24->setSpawn(true);

	auto e23 = std::make_unique<GameObject>(4600, 650, 50, 50);
	e23->addComponent(new DrawComponent(e23.get(), 0x55, 0x55, 0x00));
	e23->addComponent(new SpawnpointComponent(e1.get(), e23.get(), e19.get(), e20.get(), entityList, invisibleEntityList, manager.get(), 0, 750));
	e23->setSpawn(true);


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
	entityList->push_back(std::move(e25));
	entityList->push_back(std::move(e26));
	entityList->push_back(std::move(e27));
	entityList->push_back(std::move(e28));
	entityList->push_back(std::move(e29));
	entityList->push_back(std::move(e30));
	entityList->push_back(std::move(e31));

	

	invisibleEntityList->push_back(std::move(e19));
	invisibleEntityList->push_back(std::move(e20));
	invisibleEntityList->push_back(std::move(e21));
	invisibleEntityList->push_back(std::move(e22));
	invisibleEntityList->push_back(std::move(e23));
	invisibleEntityList->push_back(std::move(e24));
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
	if (!playerWin) {
		for (auto& e : *entityList) {
			if (e->getPlayer() && e->getxPosition() > (*entityList)[23]->getxPosition()) {
				playerWin = true;
				//you win message
				auto e34 = std::make_unique<GameObject>(1750, 50, 50, 100);
				e34->addComponent(new DrawComponent(e34.get()));
				e34->run();
				auto e32 = std::make_unique<GameObject>(1950, 50, 50, 100);
				e32->addComponent(new DrawComponent(e32.get()));
				auto e33 = std::make_unique<GameObject>(1850, 250, 50, 150);
				e33->addComponent(new DrawComponent(e33.get()));
				auto e35 = std::make_unique<GameObject>(1800, 150, 50, 100);
				e35->addComponent(new DrawComponent(e35.get()));
				auto e36 = std::make_unique<GameObject>(1900, 150, 50, 100);
				e36->addComponent(new DrawComponent(e36.get()));
				auto e37 = std::make_unique<GameObject>(2050, 250, 150, 50);
				e37->addComponent(new DrawComponent(e37.get()));
				auto e38 = std::make_unique<GameObject>(2050, 300, 50, 100);
				e38->addComponent(new DrawComponent(e38.get()));
				auto e39 = std::make_unique<GameObject>(2150, 300, 50, 100);
				e39->addComponent(new DrawComponent(e39.get()));
				auto e40 = std::make_unique<GameObject>(2100, 350, 50, 50);
				e40->addComponent(new DrawComponent(e40.get()));
				auto e41 = std::make_unique<GameObject>(2250, 250, 50, 150);
				e41->addComponent(new DrawComponent(e41.get()));
				auto e42 = std::make_unique<GameObject>(2300, 350, 50, 50);
				e42->addComponent(new DrawComponent(e42.get()));
				auto e43 = std::make_unique<GameObject>(2350, 250, 50, 150);
				e43->addComponent(new DrawComponent(e43.get()));

				auto e44 = std::make_unique<GameObject>(1750, 450, 50, 150);
				e44->addComponent(new DrawComponent(e44.get()));
				auto e45 = std::make_unique<GameObject>(1800, 600, 50, 50);
				e45->addComponent(new DrawComponent(e45.get()));
				auto e46 = std::make_unique<GameObject>(1850, 550, 50, 50);
				e46->addComponent(new DrawComponent(e46.get()));
				auto e47 = std::make_unique<GameObject>(1900, 600, 50, 50);
				e47->addComponent(new DrawComponent(e47.get()));
				auto e48 = std::make_unique<GameObject>(1950, 450, 50, 150);
				e48->addComponent(new DrawComponent(e48.get()));

				auto e49 = std::make_unique<GameObject>(2050, 450, 50, 50);
				e49->addComponent(new DrawComponent(e49.get()));
				auto e50 = std::make_unique<GameObject>(2050, 550, 50, 100);
				e50->addComponent(new DrawComponent(e50.get()));

				auto e51 = std::make_unique<GameObject>(2150, 500, 50, 150);
				e51->addComponent(new DrawComponent(e51.get()));
				auto e52 = std::make_unique<GameObject>(2200, 500, 50, 50);
				e52->addComponent(new DrawComponent(e52.get()));
				auto e53 = std::make_unique<GameObject>(2250, 500, 50, 150);
				e53->addComponent(new DrawComponent(e53.get()));

				auto e54 = std::make_unique<GameObject>(2350, 450, 50, 100);
				e54->addComponent(new DrawComponent(e54.get()));
				auto e55 = std::make_unique<GameObject>(2350, 600, 50, 50);
				e55->addComponent(new DrawComponent(e55.get()));

				entityList->push_back(std::move(e32));
				entityList->push_back(std::move(e33));
				entityList->push_back(std::move(e34));
				entityList->push_back(std::move(e35));
				entityList->push_back(std::move(e36));
				entityList->push_back(std::move(e37));
				entityList->push_back(std::move(e38));
				entityList->push_back(std::move(e39));
				entityList->push_back(std::move(e40));
				entityList->push_back(std::move(e41));
				entityList->push_back(std::move(e42));
				entityList->push_back(std::move(e43));
				entityList->push_back(std::move(e44));
				entityList->push_back(std::move(e45));
				entityList->push_back(std::move(e46));
				entityList->push_back(std::move(e47));
				entityList->push_back(std::move(e48));
				entityList->push_back(std::move(e49));
				entityList->push_back(std::move(e50));
				entityList->push_back(std::move(e51));
				entityList->push_back(std::move(e52));
				entityList->push_back(std::move(e53));
				entityList->push_back(std::move(e54));
				entityList->push_back(std::move(e55));
			}
		}
	}
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




