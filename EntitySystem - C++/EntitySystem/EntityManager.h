#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "ImmutableBag.h"
#include "Component.h"
#include "ComponentTypeManager.h"

namespace Ent {
	class Entity;
	class World;

	class EntityManager {
		private:
			World*									world;
			Bag<Entity*>							activeEntities;
			Bag<Entity*>							removedAndAvailable;
			Bag<Bag<Component*>*>					componentsByType;
			Bag<Component*>							entityComponents;
			int										nextAvailableId;
			int										count;
			long									uniqueEntityId;
			long									totalCreated;
			long									totalRemoved;

		public:
			EntityManager(World& world);
			~EntityManager();

			Entity&									create();
			void									refresh(Entity& e);
			void									addComponent(Entity &e, Component* c);
			void									removeComponent(Entity& e, ComponentType& type);
			void									remove(Entity& e);
			void									removeComponentsOfEntity(Entity& e);
			void									removeAllEntities();
			Component*								getComponent(Entity& e, ComponentType& type);
			Bag<Component*>&						getComponents(Entity& e);
			Entity&									getEntity(int entityId);
			int										getEntityCount();
			long									getTotalCreated();
			long									getTotalRemoved();
			bool									isActive(int entityId);

			template<typename c>
			void removeComponent(Entity& e) {
				removeComponent(e,ComponentTypeManager::getTypeFor<c>());
			}

			template<typename c>
			Component* getComponent(Entity& e) {
				ComponentType type = ComponentTypeManager::getTypeFor<c>();
				return getComponent(e, type);
			}
	};
};
#endif
