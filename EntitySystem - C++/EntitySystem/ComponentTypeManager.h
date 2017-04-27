#ifndef COMPTYPE_MANAGER_H
#define COMPTYPE_MANAGER_H

#include <assert.h>
#include <bitset>
#include "TypeInfoComparator.h"
#include "ComponentType.h"
#include "Component.h"
#include <map>

namespace Ent {
	//Faz a gestão de cada bitset e id para cada componente baseado no seu tipo
	class ComponentTypeManager {
		private:
			ComponentTypeManager();

			static std::map<const std::type_info*, ComponentType*, type_info_comparator>	componentTypes;
        
		public:
			static void																		deleteComponentTypes();
			static ComponentType&															getTypeFor(const std::type_info& t);
    
			//Dá o component type object
			template<typename c>
			static ComponentType& getTypeFor() {
				return getTypeFor(typeid(c));
			}
    
			template<typename c>
			static std::bitset<BITSIZE> getBit() {
				return getTypeFor(typeid(c)).getBit();
			}

			template<typename c>
			static int getId() {
				return getTypeFor(typeid(c)).getId();
			}
	};
};

#endif
