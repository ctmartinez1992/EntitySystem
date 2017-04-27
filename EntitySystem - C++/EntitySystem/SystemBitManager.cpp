#include "SystemBitManager.h"

namespace Ent {
	int SystemBitManager::POS = 0;
	std::map<const std::type_info*, std::bitset<BITSIZE>*, type_info_comparator> SystemBitManager::systemBits;
  
	void SystemBitManager::removeBitSets(){
		std::map< const std::type_info*, std::bitset<BITSIZE>*, type_info_comparator >::iterator it;
		for(it=systemBits.begin(); it!=systemBits.end(); ++it) {
			delete it->second;
		}
		systemBits.clear();
		POS = 0;
	}
  
	std::bitset<BITSIZE> & SystemBitManager::getBitFor(const std::type_info& type) {
		std::bitset<BITSIZE>* bit = systemBits[&type];
		if(bit == NULL) {
			bit = new std::bitset<BITSIZE>(1);
			(*bit) <<= POS++;
			systemBits[&type] = bit;
		}
		return *bit;
	}
}
