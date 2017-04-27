#include "Entity.h"
#include <sstream>
#include "Component.h"
#include "World.h"
//#include "EntityManager.h"

using namespace std;

namespace Ent {
  
	Entity::Entity(World * world, int id) {
		this->world = world;
		this->entityManager = world->getEntityManager();
		this->id = id;
	}
  
	Entity::~Entity() {
		world = NULL;
		entityManager = NULL;
	}
  
	void Entity::addComponent(Component* c){
		entityManager->addComponent(*this, c);
	}
  
	void Entity::removeComponent(ComponentType& type) {
		entityManager->removeComponent(*this, type);
	}
  
	Component* Entity::getComponent(ComponentType& type) {
		return entityManager->getComponent(*this, type);
	}
  
	ImmutableBag<Component*>& Entity::getComponents() {
		return entityManager->getComponents(*this);
	}
  
	void Entity::reset() {
		typeBits = 0;
		systemBits = 0;
	}
  
	void Entity::remove() {
		world->deleteEntity(*this);
	}
  
	void Entity::refresh() {
		world->refreshEntity(*this);
	}
  
	std::string Entity::toString() {
		std::ostringstream oss;
		oss << "Entity[" << id << "]\n";
		return oss.str();
	}
  
	void Entity::setUniqueId(long int uniqueId) {
		this->uniqueId = uniqueId;
	}
  
	long int Entity::getUniqueId() {
		return uniqueId;
	}
  
	void Entity::setTypeBits(bitset<BITSIZE> typeBits) {
		this->typeBits = typeBits;
	}
  
	bitset<BITSIZE> Entity::getTypeBits() {
		return typeBits;
	}
  
	void Entity::addTypeBit(bitset<BITSIZE> bit) {
		typeBits |= bit;
	}
  
	void Entity::removeTypeBit(bitset<BITSIZE> bit) {
		typeBits &= ~bit;
	}
  
	void Entity::setSystemBits(bitset<BITSIZE> systemBits) {
		this->systemBits = systemBits;
	}
  
	bitset<BITSIZE> Entity::getSystemBits() {
		return systemBits;
	}
  
	void Entity::addSystemBit(bitset<BITSIZE> bit) {
		systemBits |= bit;
	}
  
	void Entity::removeSystemBit(bitset<BITSIZE> bit) {
		systemBits &= ~bit;
	}
  
	void Entity::setGroup(string group) {
		world->getGroupManager()->set(group, *this);
	}
  
	void Entity::setTag(string tag) {
		world->getTagManager()->subscribe(tag, *this);
	}
  
	int Entity::getId() {
		return id;
	}
  
	bool Entity::isActive() {
		return entityManager->isActive(this->getId());
	}
};
