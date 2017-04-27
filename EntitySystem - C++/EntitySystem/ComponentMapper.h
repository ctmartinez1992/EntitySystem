#ifndef COMPONENTMAPPER_H
#define COMPONENTMAPPER_H

#include "EntityManager.h"
#include "World.h"

namespace Ent {
	//Alta performance, usar isto quando for preciso ir buscar v�rias entities e v�rias vezes.
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
    
			//Retorna a componente ligada � entidade, se n�o tem retorna NULL
			componentT * get(Entity& e) {
				return (componentT*) entityManager->getComponent<componentT>(e);
			}
	};
};

#endif
