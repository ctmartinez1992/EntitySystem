#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include "DelayedEntitySystem.h"

namespace Ent{
	/**
	* Sistema que executa em tempos variados.
	* Exemplo: Sistema de Expiração que apaga uma entidade após um certo tempo.
	* Exemplo: Sistema de Animação que anima uma entidade de x em x tempo.
	*/
	class DelayedEntityProcessingSystem : public DelayedEntitySystem {
		protected:
			virtual void						processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta);
			virtual void						processEntity(Entity& e, float accumulatedDelta) = 0;
	};
};

#endif
