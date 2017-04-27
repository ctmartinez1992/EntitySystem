#include "TagManager.h"
#include "Entity.h"

namespace Ent {
	TagManager::TagManager() {
	}
	
	void TagManager::subscribe(std::string tag, Entity &e){
		remove(e);
		tagByEntity[tag] = &e;
	}
  
	void TagManager::unSubscribe(const std::string tag) {
		tagByEntity.erase(tag);
	}
  
	bool TagManager::isSubscribed(const std::string tag) {
		return (tagByEntity[tag] != NULL);
	}
  
	void TagManager::remove(Entity &e) {
		//Otimizar
		std::map<std::string, Entity*>::iterator it;
		for (it = tagByEntity.begin(); it!=tagByEntity.end(); ++it) {
			if(it->second == &e) {
				tagByEntity.erase(it->first);
				return;
			}
		}
	}
  
	Entity& TagManager::getEntity(const std::string tag) {
		return *tagByEntity[tag];
	}
}
