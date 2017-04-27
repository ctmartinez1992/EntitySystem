#ifndef COMPONENT_H
#define COMPONENT_H

#include "World.h"

namespace Ent {
	class Component {
		protected:
			Component() {};

		public:
			virtual ~Component() = 0;
	};
};

#endif
