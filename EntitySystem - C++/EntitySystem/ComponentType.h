#ifndef COMPTYPE_H
#define COMPTYPE_H

#include <bitset>
#include "BitSize.h"

namespace Ent {
    //Guarda o bitset e o id de um componente
	class ComponentType {
		private:
			std::bitset<BITSIZE>				bit;
			static std::bitset<BITSIZE>			nextBit;
			int									id;
			static int							nextId;
    
		public:
			ComponentType();

			std::bitset<BITSIZE>				getBit() const;
			int									getId() const;
			static void							reset();

		private:
			void								init();
	};
};

#endif
