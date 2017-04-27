#include "World.h"
#include "Entity.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "SystemBitManager.h"
#include "ComponentType.h"

namespace Ent {
	World::World() {
		this->systemManager = new SystemManager(*this);
		this->entityManager = new EntityManager(*this);
		this->groupManager = new GroupManager();
		this->tagManager = new TagManager();
		delta = 0;
	}
  
	World::~World() {
		refreshed.clear();
		deleted.clear();
		delete entityManager;
		delete systemManager;
		delete groupManager;
		delete tagManager;
		ComponentTypeManager::deleteComponentTypes();
		SystemBitManager::removeBitSets();
		ComponentType::reset();
	}

	void World::loopStart() {
		if(!refreshed.isEmpty()) {
			for(int i(0); i!=refreshed.getCount(); ++i) {
				entityManager->refresh(*refreshed.get(i));
			}
			refreshed.clear();
		}
		if(!deleted.isEmpty()) {
			for(int i(0); i!=deleted.getCount(); ++i) {
				Entity& e = *deleted.get(i);
				groupManager->remove(e);
				tagManager->remove(e);
				entityManager->remove(e);
			}
			deleted.clear();
		}
	}

	SystemManager* World::getSystemManager() {
		return systemManager;
	}

	EntityManager* World::getEntityManager() {
		return entityManager;
	}

	GroupManager* World::getGroupManager(){
		return groupManager;
	}

	TagManager* World::getTagManager(){
		return tagManager;
	}
  
	void World::setDelta(float delta) {
		this->delta = delta;
	}

	float World::getDelta() {
		return this->delta;
	}

	Entity& World::createEntity() {
		return entityManager->create();
	}

	void World::refreshEntity(Entity& e) {
		refreshed.add(&e);
	}

	Entity& World::getEntity(int entityId) {
		return entityManager->getEntity(entityId);
	}

	void World::deleteEntity(Entity& e) {
		if(!deleted.contains(&e)) {
			deleted.add(&e);
		}
	}
};
