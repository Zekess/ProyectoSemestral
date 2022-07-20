#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "hash_table.h"
#include "grafo.h"

using namespace std;

//"TweetId","TweetDate","TweetText","UserId"

int main(){
  // Creamos el grafo que se define en el proyecto

  // Cargamos las tablas hash para las 4 columnas del CSV
  //Hash_table TweetId(1);
  Hash_table TweetDate(1000);
  Hash_table TweetText(1000);
  Hash_table UserId(1000);
  cout << "Tablas creadas:";
  // Preparamos las variables a usar.
  // line: leerá columnas completas.
  // columna: leerá el contenido de cada columna en la linea "line".
  // tweet_id: leerá el contenido de la columna asociada a TweetId
  // palabra: leerá las palabras de la columna asociada a TweetText.
  string line, columna, tweet_id, palabra;
  // j: leerá el vértice asociado a la columnas TweetDate, UserId
  // k: leerá el vértice asociado a las palabras de la columna TweetText
  int j, k;

  // Cargamos el CSV
  string fname;
  fname = "Dataset_Filtrado.csv";
  fstream file(fname, ios::in);
  // Primera pasada para cargar la tabla hash:
  if(file.is_open()){
    // Saltamos primera línea (headers)
    getline(file, line);

    // Leemos cada linea hasta que no queden
    while(getline(file, line)){
      //Creamos stringstream str a partir de "line" para procesar cada columna
      //(separadas por una coma).
      stringstream str(line);

      // Columna con TweetId
      getline(str, columna, ',');
      //TweetId.insertWord(columna);

      // Columna con TweetDate
      getline(str, columna, ',');
      TweetDate.insertWord(columna);
      // Columna con TweetText
      getline(str, columna, ',');
      // Procesamos las de palabras TweetText:
      stringstream str2(columna);

      while(getline(str2, palabra, ' ')){
        TweetText.insertWord(palabra);

      }
      // Columna con UserId
      getline(str, columna, ',');
      UserId.insertWord(columna);
    }
  }
  else cout<<"No se pudo abrir el archivo\n";

  cout << "Elementos en las tablas: " << TweetDate.getNumElements() << " - " << TweetText.getNumElements() << " - " <<UserId.getNumElements();
  Grafo_mat3 grafo(5113, TweetDate.getSize(), TweetText.getSize(), UserId.getSize());

  fstream file2(fname, ios::in);
  // Seguna pasada para insertar al grafo:
  if(file2.is_open()){
    // Saltamos primera línea (headers)
    getline(file2, line);

    // Leemos cada linea hasta que no queden
    while(getline(file2, line)){
      //Creamos stringstream str a partir de "line" para procesar cada columna
      //(separadas por una coma).
      stringstream str(line);

      // Columna con TweetId
      getline(str, columna, ',');
      //TweetId.insertWord(columna);
      tweet_id =  columna;                      //Primera coordenada de la arista a insertar

      // Columna con TweetDate
      getline(str, columna, ',');
      j =  TweetDate.getIndex(columna);
      grafo.insertDate(tweet_id, j);                     //Insertamos la arista (i,j)

      // Columna con TweetText
      getline(str, columna, ',');
      // Procesamos las de palabras TweetText:
      stringstream str2(columna);

      while(getline(str2, palabra, ' ')){
        k = TweetText.getIndex(palabra);
        grafo.insertWord(k);
        grafo.insertDateWord(j, k);               //Insertamos la arista (i,j)
      }

      // Columna con UserId
      getline(str, columna, ',');
      j =  UserId.getIndex(columna);
      grafo.insertUser(j)  ;                //Insertamos la arista (i,j)
    }
  }
  else cout<<"No se pudo abrir el archivo\n";
  cout << "Se completó todo...\n";
  /*
  cout << endl;
  cout << "\nTweetId:\n";
  cout << "(grafo) La cantidad de TweetId's insertados es: " << grafo.numVerticesTweetId() << endl;
  //cout << "El tamaño de la tabla hash es: " << TweetId.getSize() << endl;

  cout << "\nTweetDate:\n";
  cout << "(hash) La cantidad de fechas insertadas es: " << TweetDate.getNumElements() << endl;
  cout << "(grafo) La cantidad de fechas insertadas es: " << grafo.numVerticesDate() << endl;
  cout << "El tamaño de la tabla hash es: " << TweetDate.getSize() << endl;

  cout << "\nTweetText:\n";
  cout << "(hash) La cantidad de palabras insertadas es: " << TweetText.getNumElements() << endl;
  cout << "(grafo) La cantidad de palabras insertadas es: " << grafo.numVerticesWord() << endl;
  cout << "El tamaño de la tabla hash es: " << TweetText.getSize() << endl;

  cout << "\nUserId:\n";
  cout << "(hash) La cantidad de usuarios insertados es: " << UserId.getNumElements() << endl;
  cout << "(grafo) La cantidad de usuarios insertadas es: " << grafo.numVerticesUser() << endl;
  cout << "El tamaño de la tabla hash es: " << UserId.getSize() << endl;
  */
  //grafo.printAdj();
  /*
  cout << "Máximo grado de TweetId: " << grafo.maxdegTweetId() << endl;
  cout << "Mínimo grado de TweetId: " << grafo.mindegTweetId() << endl;

  int* max = grafo.maxdegDate();
  cout << "Máximo grado de Date: " << max[0] << ". Y la fecha es: " << TweetDate.getWord(max[1]) << endl;
  int* min = grafo.mindegDate();
  cout << "Mínimo grado de Date: " << min[0] << ". Y la fecha es: " << TweetDate.getWord(min[1]) << endl;

  max = grafo.maxdegWord();
  cout << "Máximo grado de Word: " << max[0] << ". Y la palabra es: " << TweetText.getWord(max[1]) << endl;
  min = grafo.mindegWord();
  cout << "Mínimo grado de Word: " << min[0] << ". Y la palabra es: " << TweetText.getWord(min[1]) << endl;

  max = grafo.maxdegUser();
  cout << "Máximo grado de User: " << max[0] << ". Y el user es: " << UserId.getWord(max[1]) << endl;
  min = grafo.mindegUser();
  cout << "Mínimo grado de User: " << min[0] << ". Y el user es: " << UserId.getWord(min[1]) << endl;

  string word = "google";
  cout << "Usuarios que han dicho " << word << ": ";
  int word_hash = TweetText.getIndex(word);
  vector<int> users = grafo.getUserFromWord(word_hash);
  for(int i=0;i<users.size();i++){
    cout << users[i] << " - ";
  }
  cout << "\nEn total son: " << users.size() << endl;*/

  string palabras[2] = {"@apple", "iphone"};
  std::vector<int> hashes_words;
  for(int i=0;i<2;i++){
    hashes_words.push_back(TweetText.getIndex(palabras[i]));
  }

  std::vector<int> hashes_dates = grafo.getDatesFromWord(hashes_words);
  cout << "Fechas encontradas:\n";
  for(int i=0;i<hashes_dates.size();i++){
    cout << TweetDate.getWord(hashes_dates[i]) << endl;
  }
  return 0;
}
