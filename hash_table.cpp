#include "hash_table.h"

Hash_table::Hash_table(int n){
  size = n;
  nused = 0;

  //Creamos el arreglo con la palabra de relleno escogida (".")
  for(int i = 0; i < size; i++){
    list.push_back(fillword);
  }
}

int Hash_table::hash_function(std::string word, int mod){
  // Extraemos los primeros 4 caracteres del hash de md5
  std::string hash = md5(word).substr(0,4);
  // Los pasamos a números decimal (desde hexadecimal)
  int index;
  std::sscanf(hash.c_str(), "%x", &index);
  // Nos aseguramos que esté entre 0 y mod-1
  return index % mod;
}

void Hash_table::insertWord(std::string word){
  // Utilizamos la función de hash que siempre estará
  //entre 0 y size-1 para obtener el indice a revisar
  int index = Hash_table::hash_function(word, size);

  // Linear probing con p un número primo predefinido;
  while(list[index]!=fillword){
    // Si encuentra la palabra, no hace nada
    if(list[index]==word){
      return;
    }
    index = (index + p) % size;
  }
  // Insertamos
  list[index] = word;
  nused += 1;

  // Reajustamos la tabla hash (de tamaño) según la cota del factor de carga
  if((float)nused/size >=alfa){
    Hash_table::resize();
  }
}

int Hash_table::getIndex(std::string word){
  // Utilizamos la función de hash que siempre estará
  //entre 0 y size-1 para obtener el indice a revisar
  int index = Hash_table::hash_function(word, size);

  while(list[index]!=word){
    if(list[index] == fillword) return -1;  //En este caso la palabra no existe
    index = (index + p) % size;
  }
  return index;
}

std::string Hash_table::getWord(int index){
  std::string word = list[index];
  return word;
}

int Hash_table::getSize(){
  return size;
}

int Hash_table::getNumElements(){
  return nused;
}

void Hash_table::printHashTable(){
  for(int i=0;i<size;i++){
    std::cout << list[i] << " ";
  }
  std::cout  << std::endl;
}

void Hash_table::resize(){
  // Creamos nuevo arreglo del doble de tamaño con puros "fillword" e Insertamos
  //los elementos de la tabla original
  std::vector<std::string> list_aux;
  for(int i = 0; i < 2*size; i++){
    list_aux.push_back(fillword);
  }

  for(int j=0;j<size;j++){
    std::string word = list[j] ;
    if(word != fillword){
      // Inserción en list_aux
      // Utilizamos la función de hash que siempre estará
      //entre 0 y 2*size-1 para obtener el indice a revisar
      int index = Hash_table::hash_function(word, 2*size);
      // Linear probing con p un número primo predefinido;
      while(list_aux[index]!=fillword){
        //No es necesario verificar si la palabra ya está insertada, pues
        //eso ya se hizo en el arreglo "list" original
        index = (index + p) % (2*size);
      }
      // Insertamos
      list_aux[index] = word;
    }
  }

  // Guardamos este nuevo arreglo en la variable original "list" y reajustamos
  //el tamaños del arreglo "size".
  list = list_aux;
  size = 2*size;
}
