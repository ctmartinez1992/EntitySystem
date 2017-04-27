#include "EntitySystem.h"
#include "World.h"
#include "Entity.h"

namespace Ent {
	EntitySystem::~EntitySystem() {
		world = NULL;
	}
  
	void EntitySystem::process() {
		if(checkProcessing()) {
			begin();
			processEntities(actives);
			end();
		}
	}
  
	void EntitySystem::change(Entity& e) {
		bool contains = (systemBit & e.getSystemBits()) == systemBit;
		bool interest = (typeFlags & e.getTypeBits()) == typeFlags;
		if(interest && !contains && typeFlags.any()) {
			actives.add(&e);
			e.addSystemBit(systemBit);
			added(e);
		} else if(!interest && contains && typeFlags.any()) {
			this->remove(e);
		}
	}
  
	void  EntitySystem::setSystemBit(std::bitset<BITSIZE> bit) {
		systemBit = bit;
	}
  
	void EntitySystem::setWorld(World *world) {
		this->world = world;
	}
  
	int EntitySystem::getEntityCount(){
		return actives.getCount();
	}
  
	void EntitySystem::remove(Entity &e) {
		actives.remove(&e);
		e.removeSystemBit(systemBit);
		removed(e);
	}
};
