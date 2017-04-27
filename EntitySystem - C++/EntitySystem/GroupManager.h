#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H

#include "ImmutableBag.h"
#include <map>
#include <string>

namespace Ent {
	class Entity;
  
	//Usado para agrupar v�rias entidades em um grupo, obt�m-se apartir de uma inst�ncia do mundo.
	class GroupManager {
		private:
			Bag<Entity*>											emptyBag;
			std::string												emptyString;
			Bag<std::string*>										groupByEntity;
			std::map<std::string, Bag<Entity*>*>					entitiesByGroup;

		public:
			GroupManager();
			~GroupManager();

			void													set(std::string group, Entity& e);
			void													remove(Entity& e);
			ImmutableBag<Entity*>*									getEntities(std::string group);
			std::string												getGroupOf(Entity& e);
			bool													isGrouped(Entity& e);
			bool													isInGroup(std::string group, Entity& e);
	};
};

#endif