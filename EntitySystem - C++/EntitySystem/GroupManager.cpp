#include "GroupManager.h"
#include "Entity.h"

namespace Ent {
	GroupManager::GroupManager() : emptyBag(1) {
		emptyString.clear();
	}
	
	GroupManager::~GroupManager() {
		groupByEntity.deleteData();		
		std::map<std::string, Bag<Entity*>*>::iterator it;
		for(it = entitiesByGroup.begin(); it != entitiesByGroup.end(); it++) {
			delete it->second;
		}
		entitiesByGroup.clear();
	}

	void GroupManager::set(std::string group, Entity& e) {
		remove(e);
		Bag<Entity*>* entities = entitiesByGroup[group];
		if(entities == NULL) {
			entities = new Bag<Entity*>(32);
			entitiesByGroup[group] = entities;
		}
		entities->add(&e);
		entities = NULL;
		groupByEntity.set(e.getId(), new std::string(group));
	}

	void GroupManager::remove(Entity& e) {
		if(e.getId() < groupByEntity.getCapacity()) {
			std::string* groupId = groupByEntity.get(e.getId());
			if(groupId != NULL) {
				groupByEntity.set(e.getId(), NULL);
				Bag<Entity*>* entities = entitiesByGroup[*groupId];
				if(entities != NULL){
					entities->remove(&e);
				}
				entities = NULL;
				delete groupId;
				groupId = NULL;
			}
			groupId = NULL;
		}
	}

	ImmutableBag<Entity*>* GroupManager::getEntities(std::string group) {
		Bag<Entity*>* bag = entitiesByGroup[group];
		if(bag == NULL) {
			bag = new Bag<Entity*>(32);
			entitiesByGroup[group] = bag;
		}
		return bag;
	}

	std::string GroupManager::getGroupOf(Entity& e) {
		if(e.getId() < groupByEntity.getCapacity()) {
			std::string* group = groupByEntity.get(e.getId());
			if(group == NULL) {
				return emptyString;
			}
			return *group;
		}
		return emptyString;
	}

	bool GroupManager::isGrouped(Entity& e) {
		return !getGroupOf(e).empty();
	}

	bool GroupManager::isInGroup(std::string group, Entity& e) {
		return group.compare(getGroupOf(e)) == 0;
	}
};
