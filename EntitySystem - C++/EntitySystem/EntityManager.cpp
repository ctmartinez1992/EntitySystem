#include "EntityManager.h"
#include "EntitySystem.h"
#include "SystemManager.h"
#include "BitSize.h"
#include "World.h"
#include "Component.h"
#include "Entity.h"

namespace Ent {
	EntityManager::EntityManager(World& world) : componentsByType(64), nextAvailableId(0), count(0), uniqueEntityId(0), totalCreated(0), totalRemoved(0) {
		this->world = &world;
	}
  
	EntityManager::~EntityManager() {
		this->removeAllEntities();				//tira todas as entidades ativas e p�em em removeAndAvailable, chama removeComponentsOfEntity e, todos os sistemas fazem update e removem cada entidade
		this->removedAndAvailable.deleteData();
		for(int i(0); i!=componentsByType.getCapacity(); ++i) {
			if(componentsByType.get(i) == NULL) {
				continue;
			}
			componentsByType.get(i)->clear();
		}
		componentsByType.deleteData();
		componentsByType.clear();
		this->world = NULL;  
	}
  
	Entity& EntityManager::create() {
		Entity* e = this->removedAndAvailable.removeLast();
		if(e == NULL) {
			e = new Entity(this->world, nextAvailableId++);
		} else {
			e->reset();
		}
		e->setUniqueId(uniqueEntityId++);
		activeEntities.set(e->getId(),e);
		count++;
		totalCreated++;
		return *e;
	}
  
	void EntityManager::refresh(Entity& e) {
		SystemManager * systemManager = world->getSystemManager();
		Bag<EntitySystem*> & systems = systemManager->getSystems();
    
		for(int i(0); i!=systems.getCount(); ++i) {
			systems.get(i)->change(e);
		}
	}
  
	void EntityManager::addComponent(Entity &e, Component* c) {
		ComponentType type = ComponentTypeManager::getTypeFor(typeid(*c));
		if(type.getId() >= componentsByType.getCapacity()) {
			componentsByType.set(type.getId(), NULL);
		}
		Bag<Component*>* components = componentsByType.get(type.getId());
    
		if(components == NULL) {
			components = new Bag<Component*>();
			componentsByType.set(type.getId(), components);
		} else {
			if (components->get(e.getId()) != NULL) {
				removeComponent(e, type);
				refresh(e);
			}
		}

		components->set(e.getId(), c);
		e.addTypeBit(type.getBit());
		components = NULL;
	}
  
	void EntityManager::removeComponent(Entity &e, ComponentType & type) {
		Bag<Component* > * components = componentsByType.get(type.getId());
		delete components->get(e.getId());
		components->set(e.getId(), NULL);
		e.removeTypeBit(type.getBit());
		components = NULL;
	}
  
	void EntityManager::remove(Entity& e) {
		activeEntities.set(e.getId(), NULL);
		e.setTypeBits(0);
		refresh(e);
		removeComponentsOfEntity(e);
		count--;
		totalRemoved++;
		removedAndAvailable.add(&e);
	}
  
	void EntityManager::removeComponentsOfEntity(Entity& e) {
		for(int i(0); i!=componentsByType.getCapacity(); ++i) {
			Bag<Component*>* components = componentsByType.get(i);
			if(components != NULL && e.getId() < components->getCapacity()) {
				delete components->get(e.getId());
				components->set(e.getId(), NULL);
			}
			components = NULL;
		}
	}
  
	void EntityManager::removeAllEntities() {
		for(int i(0); i!=activeEntities.getCapacity(); ++i) {
			if(activeEntities.get(i) != NULL) {
				remove(*activeEntities.get(i));
			}
		}
	}
  
	Component * EntityManager::getComponent(Entity & e, ComponentType & type) {
		Bag<Component*>* bag = componentsByType.get(type.getId());
		if(bag != NULL && e.getId() < bag->getCapacity()) {
			return bag->get(e.getId());
		}
		return NULL;
	}
  
	//Todos os componentes para uma entidade
	Bag<Component*>& EntityManager::getComponents(Entity& e) {
		entityComponents.clear();
		for(int i(0); i!=componentsByType.getCapacity(); ++i) {
			Bag<Component*> * components = componentsByType.get(i);
			if(components != NULL && e.getId() < components->getCapacity()) {
				Component * c = components->get(e.getId());
				if(c != NULL) {
					entityComponents.add(c);
				}
			}
		}
		return entityComponents;
	}
  
	Entity& EntityManager::getEntity(int entityId) {
		return *activeEntities.get(entityId);
	}
  
	int EntityManager::getEntityCount() {
		return count;
	}
  
	long EntityManager::getTotalCreated() {
		return totalCreated;
	}
  
	long EntityManager::getTotalRemoved() {
		return totalRemoved;
	}
  
	bool EntityManager::isActive(int entityId) {
		return activeEntities.get(entityId) != NULL;
	}
};
