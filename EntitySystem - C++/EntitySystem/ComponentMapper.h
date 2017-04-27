#ifndef COMPONENTMAPPER_H
#define COMPONENTMAPPER_H

#include "EntityManager.h"
#include "World.h"

namespace Ent {
	//Alta performance, usar isto quando for preciso ir buscar várias entities e várias vezes.
	template<typename componentT>
	class ComponentMapper {
		private:
			EntityManager* entityManager;
    
		public:
			~ComponentMapper() {
				entityManager = NULL;
			}
    
			void init(World& world) {
				entityManager = world.getEntityManager();
			}
    
			//Retorna a componente ligada à entidade, se não tem retorna NULL
			componentT * get(Entity& e) {
				return (componentT*) entityManager->getComponent<componentT>(e);
			}
	};
};

#endif
