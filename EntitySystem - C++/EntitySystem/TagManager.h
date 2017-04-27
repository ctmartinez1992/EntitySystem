#ifndef TAG_MANAGER_H
#define TAG_MANAGER_H

#include <map>
#include <string>

namespace Ent {

	class Entity;
  
	//Usado para pôr uma tag em qualquer entidade, exemplo "Player" ou "Boss"
	class TagManager {
		private:
			std::map<std::string, Entity*>					tagByEntity;
		
		public:
			TagManager();

			void											subscribe(const std::string tag, Entity &e);
			void											unSubscribe(const std::string tag);
			bool											isSubscribed(const std::string tag);
			void											remove(Entity &e);
			Entity&											getEntity(const std::string tag);
	};
};

#endif
