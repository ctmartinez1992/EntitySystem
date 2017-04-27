#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include "DelayedEntitySystem.h"

namespace Ent{
	/**
	* Sistema que executa em tempos variados.
	* Exemplo: Sistema de Expira��o que apaga uma entidade ap�s um certo tempo.
	* Exemplo: Sistema de Anima��o que anima uma entidade de x em x tempo.
	*/
	class DelayedEntityProcessingSystem : public DelayedEntitySystem {
		protected:
			virtual void						processEntities(ImmutableBag<Entity*>& bag, float accumulatedDelta);
			virtual void						processEntity(Entity& e, float accumulatedDelta) = 0;
	};
};

#endif
