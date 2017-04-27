#ifndef SYSBITMANAGER_H
#define SYSBITMANAGER_H

#include <bitset>
#include <map>
#include "TypeInfoComparator.h"
#include "BitSize.h"

namespace Ent {
	
	class EntitySystem;
	
	class SystemBitManager {
		private:
			static std::map<const std::type_info*, std::bitset<BITSIZE>*, type_info_comparator>		systemBits;
			static int																				POS;

		public:
			static void																				removeBitSets();
			static std::bitset<BITSIZE>&															getBitFor(const std::type_info & type);

			template<typename system>
			static std::bitset<BITSIZE>& getBitFor() {
				return getBitFor(typeid(system));
			}
	};
};

#endif
