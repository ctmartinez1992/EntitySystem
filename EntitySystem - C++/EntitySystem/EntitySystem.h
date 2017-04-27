#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H

#include <bitset>
#include "BitSize.h"
#include "Component.h"
#include <iostream>
#include <assert.h>
#include <typeinfo>
#include <bitset>
#include "ImmutableBag.h"
#include "ComponentTypeManager.h"

namespace Ent {
	class Entity;
	class World;

	class EntitySystem {
		//Variables
		protected:
			World*										world;

		private:
			std::bitset<BITSIZE>						systemBit;
			std::bitset<BITSIZE>						typeFlags;
			Bag<Entity*>								actives;

		//Functions
		public:
			virtual	~EntitySystem();
			
			void										process();
			void										change(Entity& e);
			void										setSystemBit(std::bitset<BITSIZE> bit);
			void										setWorld(World* world);
			int											getEntityCount();
			
			virtual void initialize() {
			}

			void printTypeFlag() {
				std::cout << typeFlags;
			}

			std::bitset<BITSIZE> getSystemBit() {
				return systemBit;
			}

		protected:
			EntitySystem() { 
				this->world = NULL; 
			}

			//Override
			virtual void begin() {
			}

			virtual void end() {
			}

			virtual void removed(Entity& e) {
			}

			virtual void added(Entity& e) {
			}

			//Abstracts
			virtual void								processEntities(ImmutableBag<Entity*>& bag) = 0;
			virtual bool								checkProcessing() = 0;

			template<typename component_type>
			void addComponentType() {
				typeFlags |= ComponentTypeManager::getBit<component_type>();
			}

		private:
			void										remove(Entity& e);
	};
};

#endif
