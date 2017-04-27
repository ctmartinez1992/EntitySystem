#include "SystemManager.h"
#include "World.h"
#include "EntitySystem.h"
#include "SystemBitManager.h"

namespace Ent {
	SystemManager::SystemManager(World& world) {
		this->world = &world;
	}
  
	SystemManager::~SystemManager(){
		systems.clear();
		bagged.deleteData();
		bagged.clear();
	}
  
	void SystemManager::initializeAll() {
		for(int i(0); i!=bagged.getCount(); ++i) {
			bagged.get(i)->initialize();
		}
	}
  
	EntitySystem* SystemManager::setSystem(EntitySystem* stm) {
		bool bitFlag = false;
		int index = 0;
    
		//Verifica se o sistema é conhecido.
		for(int i(0); i!=bagged.getCount(); ++i) {
			if(typeid(*stm) == typeid(*bagged.get(i))){
				bitFlag = true;
				index = i;
			}
		}
		if(bagged.get(index) != stm) {
			if(bitFlag){
				delete stm;
				stm = bagged.get(index);
			} else {
				stm->setWorld(world);
				systems[&typeid(*stm)] = stm;
				bagged.add(stm);
				stm->setSystemBit(SystemBitManager::getBitFor(typeid(*stm)));
			}
		}
		return stm;
	}
  
	Bag<EntitySystem*>& SystemManager::getSystems() {
		return bagged;
	}
}
