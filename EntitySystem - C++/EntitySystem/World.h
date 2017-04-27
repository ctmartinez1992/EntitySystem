#ifndef WORLD_H
#define WORLD_H

#include "ImmutableBag.h"
#include "TagManager.h"
#include "GroupManager.h"

namespace Ent {
	class Entity;
	class EntityManager;
	class SystemManager;

	/**
	* O cora��o da framework.
	* Cont�m todos os gestores (managers).The primary instance for the framework.
	* Usado para criar, obter e remover todas as entidades.
	* Conv�m atualizar sempre o delta em cada loop e, inicializ�-lo antes de entrar nesse mesmo loop.
	**/
	class World {
		public:
			World();
			~World();
			
			void											loopStart();
			SystemManager*									getSystemManager();
			EntityManager*									getEntityManager();
			TagManager*										getTagManager();
			GroupManager*									getGroupManager();
			void											setDelta(float delta);
			float											getDelta();
			Entity&											createEntity();
			void											refreshEntity(Entity& e);
			Entity&											getEntity(int entityId);
			void											deleteEntity(Entity& e);

		private:
			SystemManager*									systemManager;
			EntityManager* 									entityManager;
			TagManager* 									tagManager;
			GroupManager* 									groupManager;
			float 											delta;
			Bag<Entity*> 									refreshed;
			Bag<Entity*>									deleted;
	};
};

#endif
