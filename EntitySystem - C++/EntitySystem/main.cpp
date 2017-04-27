#include <iostream>
#include <conio.h>
#include <windows.h>

#include "World.h"
#include "Component.h"
#include "EntityProcessingSystem.h"
#include "ComponentMapper.h"
#include "SystemManager.h"
#include "Entity.h"

class VelocityComponent : public Ent::Component {
public:
    float x;
    float y;

    VelocityComponent(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

class PositionComponent : public Ent::Component {
public:
    float x;
    float y;
    PositionComponent(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

class MovementSystem : public Ent::EntityProcessingSystem {
private:
    Ent::ComponentMapper<VelocityComponent> velocityMapper;
    Ent::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        addComponentType<VelocityComponent>();
        addComponentType<PositionComponent>();
    }

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    }

    virtual void processEntity(Ent::Entity& e) {
        positionMapper.get(e)->x += velocityMapper.get(e)->x * world->getDelta();
        positionMapper.get(e)->y += velocityMapper.get(e)->y * world->getDelta();
    }
};

int main(int argc, char **argv) {
    Ent::World world;
    Ent::SystemManager* sm = world.getSystemManager();
    MovementSystem* movementsys = (MovementSystem*) sm->setSystem(new MovementSystem());
    Ent::EntityManager* em = world.getEntityManager();

    sm->initializeAll();

    Ent::Entity& player = em->create();

    player.addComponent(new VelocityComponent(2,4));
    player.addComponent(new PositionComponent(0,0));
    player.refresh();
	
    PositionComponent* comp = (PositionComponent*) player.getComponent<PositionComponent>();

    while(true) {
        world.loopStart();
        world.setDelta(0.0016f);
        movementsys->process();

        std::cout << "X:"<< comp->x << std::endl;
        std::cout << "Y:"<< comp->y << std::endl;

		Sleep(1000);
    }
    return 0;
}
