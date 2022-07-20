#ifndef __HASH_TABLE__
#define __HASH_TABLE__

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "md5.h"

class Hash_table{

	public:
		Hash_table(int n);											//Constructor
		void insertWord(std::string word);			//Inserción
    int getIndex(std::string word);					//Obtener índice de una palabra
    std::string getWord(int index);					//Obtener palabra en cierto índice
    int getSize();													//Tamaño de la tabla hash
    int getNumElements();										//Buckets usados
    void printHashTable();									//Imprimit tabla hash

	private:
		int hash_function(std::string word, int mod);		//Función de hash que se adapta al tamaño
		std::string fillword = ".";							//¿Una stopword?
    int size;																//Tamaño de la tabla hash
    int nused;               								//Buckets usados
    int p = 333;                             // Numero primo para linear probing
    float alfa = 0.7;												// Cota factor de carga
		void resize();													//Reajustar tamaño según factor de carga
    std::vector<std::string> list;          // Tabla Hash
};




#endif
