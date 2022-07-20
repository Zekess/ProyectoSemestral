#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
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
  // Preparamos las variables a usar.
  // line: leerá columnas completas.
  // columna: leerá el contenido de cada columna en la linea "line".
  // tweet_id: leerá el contenido de la columna asociada a TweetId
  // palabra: leerá las palabras de la columna asociada a TweetText.
  string line, columna, tweet_id, palabra;
  // j: leerá el vértice asociado a la columnas TweetDate, UserId
  // k: leerá el vértice asociado a las palabras de la columna TweetText
  int j, k, l;

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

      // Columna con UserId
      getline(str, columna, ',');
      l =  UserId.getIndex(columna);
      grafo.insertUser(l);                //Insertamos la arista (i,j)

      while(getline(str2, palabra, ' ')){
        k = TweetText.getIndex(palabra);
        grafo.insertWord(k);
        grafo.insertDateWord(j, k);               //Insertamos la arista (i,j)
        grafo.insertWordUser(k,l);
      }


    }
  }
  else cout<<"No se pudo abrir el archivo\n";
  /*
  // Comienza la experimentación con las estructuras ya creadas.
  int rep = 100;
  int* aux;
  clock_t begin, end;
  // La fecha en la que se han publicado más tweets

  string date_maxdeg;
  begin = clock();
  for(int i=0; i<rep; i++){
      aux = grafo.maxdegDate();
      date_maxdeg = TweetDate.getWord(aux[1]);
  }
  end = clock();
  cout << date_maxdeg << ";" << double(end - begin) / (rep * CLOCKS_PER_SEC) << endl;

  //El usuario que ha publicado más tweets
  string user_maxdeg;
  int* aux2;
  begin = clock();
  for(int i=0; i<rep; i++){
      aux2 = grafo.maxdegUser();
      user_maxdeg = UserId.getWord(aux[1]);
  }
  end = clock();
  cout << user_maxdeg << ";" << double(end - begin) / (rep * CLOCKS_PER_SEC) << endl;

  //La lista de usuarios que han publicado tweets que contengan una palabra dada por entrada
  vector<int> aux3;
  begin = clock();
  vector<string> users_google2;
  for(int i=0; i<rep; i++){
      vector<string> users_google;
      aux3 = grafo.getUserFromWord(TweetText.getIndex("google"));
      for(int j=0;j<aux3.size();j++){
        users_google.push_back(UserId.getWord(aux3[j]));
      }
      users_google2 = users_google;
  }
  end = clock();
  for(int i=0;i<users_google2.size();i++){
    cout << users_google2[i] << " ";
  }
  cout << ";" << double(end - begin) / (rep * CLOCKS_PER_SEC) << endl;

  vector<int> aux4;
  begin = clock();
  vector<string> users_apple2;
  for(int i=0; i<rep; i++){
      vector<string> users_apple;
      aux4 = grafo.getUserFromWord(TweetText.getIndex("apple"));
      for(int j=0;j<aux4.size();j++){
        users_apple.push_back(UserId.getWord(aux4[j]));
      }
      users_apple2 = users_apple;
  }
  end = clock();
  for(int i=0;i<users_apple2.size();i++){
    cout << users_apple2[i] << " ";
  }
  cout << ";" << double(end - begin) / (rep * CLOCKS_PER_SEC) << endl;

  //Las fechas en las que se han publicado todas las palabras de una lista dada por entrada.
  vector<int> aux5;
  string palabras[3] = {"apple", "iphone", "crack"};
  vector<string> dates2;
  begin = clock();
  for(int i=0; i<rep; i++){
    vector<int> index;
    for(int j=0;j<3;j++){
      index.push_back(TweetText.getIndex(palabras[j]));
    }
    aux5 = grafo.getDatesFromWord(index);
    vector<string> dates;
    for(int j=0;j<aux5.size();j++){
      dates.push_back(TweetDate.getWord(aux5[j]));
    }
    dates2 = dates;
  }
  end = clock();
  for(int i=0;i<dates2.size();i++){
    cout << dates2[i] << " ";
  }
  cout << ";" << double(end - begin) / (rep * CLOCKS_PER_SEC) << endl;

  */
  cout << "Mínimo grado de TweetId: " << grafo.maxdegTweetId() << endl;
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
    cout << UserId.getWord(users[i]) << " - ";
  }
  cout << "\nEn total son: " << users.size() << endl;

  cout << "size: " << sizeof(Grafo_mat3);
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
