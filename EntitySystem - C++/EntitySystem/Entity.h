#ifndef ENTITY_H
#define ENTITY_H

#include <bitset>
#include <string>
#include <cstddef>
#include <typeinfo>
#include "BitSize.h"
#include "ImmutableBag.h"
#include "EntityManager.h"
#include "ComponentTypeManager.h"

namespace Ent {
	class Component;
	class ComponentType;
	class World;
  
	// As entidades só podem ser instanciadas apartir da class world
	class Entity {
		private:
			Entity(const Entity&);
			Entity& operator =(const Entity&);
			
			World*									world;
			EntityManager*							entityManager;
			std::bitset<BITSIZE>					typeBits;
			std::bitset<BITSIZE>					systemBits;
			int										id;
			long int								uniqueId;
    
		public:
			Entity(World* world, int id);
			~Entity();
			
			void									addComponent(Component* c);
			void									removeComponent(ComponentType& type);
			Component *								getComponent(ComponentType& type);
			ImmutableBag<Component*>&				getComponents();
			void									reset();
			void									refresh();
			void									remove();
			std::string								toString();
			void									setUniqueId(long int uniqueId);
			long int								getUniqueId();
			void									setTypeBits(std::bitset<BITSIZE> typeBits);
			std::bitset<BITSIZE>					getTypeBits();
			void									addTypeBit(std::bitset<BITSIZE> bit);
			void									removeTypeBit(std::bitset<BITSIZE> bit);
			void									setSystemBits(std::bitset<BITSIZE> systemBits);
			std::bitset<BITSIZE>					getSystemBits();
			void									addSystemBit(std::bitset<BITSIZE> bit);
			void									removeSystemBit(std::bitset<BITSIZE> bit);
			void									setGroup(std::string group);
			void									setTag(std::string tag);
			int										getId();
			bool									isActive();

			template<typename c>
			void removeComponent() {
				entityManager->removeComponent(*this, ComponentTypeManager::getTypeFor<c>());
			}
    
			template<typename c>
			Component* getComponent() {
				return (c*)entityManager->getComponent(*this, ComponentTypeManager::getTypeFor<c>());
			}
	};
};

#endif
