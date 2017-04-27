#ifndef _IMMUTBAG_H
#define _IMMUTBAG_H

#include <cstddef>

namespace Ent {
	template<typename E>
	class ImmutableBag {
		public:
			virtual ~ImmutableBag() {
			}

			virtual E									get(int index) = 0;
			virtual int									getCapacity() = 0;
			virtual int									getCount() = 0;
			virtual bool								isEmpty() = 0;
	};

	template<typename E>
	class Bag : public ImmutableBag<E> {
		public:
			Bag() {
				init(20);
			}

			Bag(int capacity) {
				init(capacity);
			}

			virtual ~Bag<E>() {
				delete[] data;
			}

			//Adiciona um objeto à Bag
			void add(E o) {
				if(size == count) {
					grow();
				}
				data[count++] = o;
			}

			void addAll(Bag<E>& bag) {
				int bagSize = bag.size;
				for(int i(0); i!=bagSize; ++i) {
					add(bag.data[i]);
				}
			}

			//Põe todos os apontadores a null mas não apaga nada
			void clear() {
				for(int i(0); i!=size; ++i) {
					data[i] = NULL;
				}
				count = 0;
			}

			bool contains(E o) {
				for(int i(0); i!=count; ++i) {
					if(o == data[i]) {
						return true;
					}
				}
				return false;
			}

			bool set(int index, E o) {
				if(index >= size) {
					grow(index*2);
				} if(o == NULL && data[index] != NULL) {
					count--;
				} else if(o != NULL && data[index] == NULL) {
					count++;
				}
				data[index] = o;
				return true;
			}

			virtual E get(int index) {
				if (index >= size) {
					return NULL;
				}
				return (E)data[index];
			}

			virtual int getCount() {
				return count;
			}

			virtual int getCapacity() {
				return size;
			}

			virtual bool isEmpty() {
				return count == 0;
			}

			//Uma Bag pode ter "buracos" pelo meio, isto resolve esse problema
			Bag<E>* getGapless() {
				Bag<E>* bag = new Bag<E>(this->count);
				int thisSize = this->size;
				for(int i(0); i!=thisSize; ++i) {
					if(this->data[i] != NULL) {
						bag->add(data[i]);
					}
				}
				return bag;
			}

			bool remove(E o) {
				for(int i(0); i!=count; ++i) {
					if(o == data[i]) {
						remove(i);
						return true;
					}
				}
				return false;
			}

			E remove(int index) {
				if(count == 0) {
					return NULL;
				}
				E object = data[index];
				data[index] = data[count-1];
				data[count-1] = NULL;
				count--;
				return (E) object;
			}

			E removeLast() {
				if(!isEmpty()) {
					E object = data[count-1];
					data[count-1] = NULL;
					--count;
					return (E) object;
				}
				return NULL;
			}

			bool removeAll(Bag<E> bag) {
				bool mod = false;
				int bagCount = bag.count;
				for(int i=0; i<bagCount; i++) {
					for(int j=0; j<count; j++) {
						if(bag.data[i] == data[j]) {
							remove(j);
							j--;
							mod = true;
							break;
						}
					}
				}
				return mod;
			}

			void deleteData() {
				for(int i=0; i<size; i++) {
					delete data[i];
					data[i] = NULL;
				}
				count = 0;
			}

			void operator += (Bag<E> &bag) {
				addAll(bag);
			}

		private:
			E*											data;
			int											count;
			int											size;

			void init(int capacity) {
				size = capacity;
				count = 0;
				data = new E[capacity];
				clear();
			}
    
			void grow() {
				int newCapacity = (size * 3.0f) * 0.5f + 1.0f;
				grow(newCapacity);
			}
    
			void grow(int newCapacity) {
				E* newData = new E[newCapacity];
				for (int i(0); i!=size; ++i) {
					newData[i] = data[i];
				}
				for (int i(size); i!=newCapacity; ++i) {
					newData[i] = NULL;
				}
				delete[] data;
				size = newCapacity;
				data = newData;
			}
	};
};

#endif
