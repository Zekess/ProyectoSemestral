#include "grafo.h"

Grafo_mat3::Grafo_mat3(int n, int n1, int n2, int n3){
  //Inicializamos contadores de vértices y artistas
  m = n;
  n_tid = 0;
  n_date = 0;
  n_word = 0;
  n_uid = 0;
  n_edges = 0;

  // Inicializamos el arreglo de TweetIds
  for(int i = 0; i < n; i++){
    data_TweetId.push_back(" ");
  }

  //Inicializamos las matrices de adyacencia:
  // Mat_date (Fechas)
  for(int i = 0; i < n; i++){
    std::vector<int> fila;
    for(int j=0;j<n1;j++){
      fila.push_back(0);
    }
    Mat_date.push_back(fila);
  }
  // Mat_word (palabras)
  for(int i = 0; i < n; i++){
    std::vector<int> fila;
    for(int j=0;j<n2;j++){
      fila.push_back(0);
    }
    Mat_word.push_back(fila);
  }
  // Mat_user (Usuarios)
  for(int i = 0; i < n; i++){
    std::vector<int> fila;
    for(int j=0;j<n3;j++){
      fila.push_back(0);
    }
    Mat_user.push_back(fila);
  }

  // Mat_word_user (Matriz Mat_word_user, tercera función)
  for(int i = 0; i < n2; i++){
    std::vector<int> fila;
    for(int j=0;j<n3;j++){
      fila.push_back(0);
    }
    Mat_word_user.push_back(fila);
  }

  // Mat_date_word (Matriz auxiliar, cuarta función)
  for(int i = 0; i < n1; i++){
    std::vector<int> fila;
    for(int j=0;j<n2;j++){
      fila.push_back(0);
    }
    Mat_date_word.push_back(fila);
  }
}

void Grafo_mat3::insertDate(std::string T_id, int j){
  // Agregamos el TweetID. Siempre se debe insertar la fecha primero
  data_TweetId[n_tid] = T_id;
  n_tid += 1;
  // Insertamos la fecha y aumetamos los contadores según corresponda
  if(!(Grafo_mat3::IsDateInserted(j))) n_date += 1;
  if(Mat_date[n_tid-1][j] == 0) n_edges += 1;
  Mat_date[n_tid-1][j] = 1;
}

bool Grafo_mat3::IsDateInserted(int j){
  // Revisar si la fecha en j está como vértice
  for(int k=0;k<m;k++){
    if(Mat_date[k][j] == 1){
      return true;
    }
  }
  return false;
}

void Grafo_mat3::insertWord(int j){
  // Insertamos la palabra y aumetamos los contadores según corresponda
  if(!(Grafo_mat3::IsWordInserted(j))) n_word += 1;
  if(Mat_word[n_tid-1][j] == 0) n_edges += 1;
  Mat_word[n_tid-1][j] = 1;
}

bool Grafo_mat3::IsWordInserted(int j){
  // Revisar si la palabra en j está como vértice
  for(int k=0;k<m;k++){
    if(Mat_word[k][j]==1) return true;
  }
  return false;
}

void Grafo_mat3::insertUser(int j){
  // Insertamos el usuario y aumetamos los contadores según corresponda
  if(!(Grafo_mat3::IsUserInserted(j))) n_uid += 1;
  if(Mat_user[n_tid-1][j] == 0) n_edges += 1;
  Mat_user[n_tid-1][j] = 1;
}

bool Grafo_mat3::IsUserInserted(int j){
  // Revisar si el usuario en j está como vértice
  for(int k=0;k<m;k++){
    if(Mat_user[k][j]==1) return true;
  }
  return false;
}

void Grafo_mat3::insertWordUser(int i, int j){
  // i: Hash de la fecha correspondiente
  // j: Hash de la palabra correspondiente
  Mat_word_user[i][j] = 1;
}

void Grafo_mat3::insertDateWord(int i, int j){
  // i: Hash de la fecha correspondiente
  // j: Hash de la palabra correspondiente
  Mat_date_word[i][j] = 1;
}

int Grafo_mat3::numVertices(){
  return n_tid+n_date+n_word+n_uid;
}

int Grafo_mat3::numVerticesTweetId(){
  return n_tid;
}

int Grafo_mat3::numVerticesDate(){
  return n_date;
}

int Grafo_mat3::numVerticesWord(){
  return n_word;
}

int Grafo_mat3::numVerticesUser(){
  return n_uid;
}

int Grafo_mat3::numEdges(){
  return n_edges;
}

void Grafo_mat3::printAdj(){
  int m1, m2, m3;
  m1 = Mat_date[0].size();
  m2 = Mat_word[0].size();
  m3 = Mat_user[0].size();

  // Imprimir matriz cuadrada de orde n_tid+n_date+n_word+n_uid:

  // Primeras n_tid filas:
  for(int i=0;i<n_tid;i++){
    // Primer bloque (n_tid columnas):
    for(int j=0;j<n_tid;j++){
      std::cout << "0 ";
    }
    // Segundo bloque (n_date columnas):
    for(int j=0;j<m1;j++){
      if(Grafo_mat3::IsDateInserted(j)) std::cout << Mat_date[i][j] << " ";
    }
    // Tercer bloque (n_word columnas):
    for(int j=0;j<m2;j++){
      if(Grafo_mat3::IsWordInserted(j)) std::cout << Mat_word[i][j] << " ";
    }
    // Cuarto bloque (n_uid columnas):
    for(int j=0;j<m3;j++){
      if(Grafo_mat3::IsUserInserted(j)) std::cout << Mat_user[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Siguientes n_date filas:
  for(int i=0;i<m1;i++){
    // Si existe la fila, imprimimos.
    if(Grafo_mat3::IsDateInserted(i)){
      //Primeras n_tid columnas
      for(int j=0;j<n_tid;j++){
        std::cout << Mat_date[j][i] << " ";
      }
      // Siguientes n_date+n_word+n_uid columnas
      for(int j=0;j<n_date+n_word+n_uid;j++){
        std::cout << "0 ";
      }
      std::cout << std::endl;
    }
  }

  // Siguientes n_word filas:
  for(int i=0;i<m2;i++){
    // Si existe la fila, imprimimos.
    if(Grafo_mat3::IsWordInserted(i)){
      //Primeras n_tid columnas
      for(int j=0;j<n_tid;j++){
        std::cout << Mat_word[j][i] << " ";
      }
      // Siguientes n_date+n_word+n_uid columnas
      for(int j=0;j<n_date+n_word+n_uid;j++){
        std::cout << "0 ";
      }
      std::cout << std::endl;
    }
  }

  // Siguientes n_uid filas:
  for(int i=0;i<m3;i++){
    // Si existe la fila, imprimimos.
    if(Grafo_mat3::IsUserInserted(i)){
      //Primeras n_tid columnas
      for(int j=0;j<n_tid;j++){
        std::cout << Mat_user[j][i] << " ";
      }
      // Siguientes n_date+n_word+n_uid columnas
      for(int j=0;j<n_date+n_word+n_uid;j++){
        std::cout << "0 ";
      }
      std::cout << std::endl;
    }
  }
}

int Grafo_mat3::degTweetId(int j){
  int deg = 0;
  for(int k=0;k<n_date;k++){
    deg += Mat_date[j][k];
  }
  for(int k=0;k<n_word;k++){
    deg += Mat_word[j][k];
  }
  for(int k=0;k<n_uid;k++){
    deg += Mat_user[j][k];
  }
  return deg;
}

int Grafo_mat3::degDate(int j){
  int deg = 0;
  for(int k=0;k<n_tid;k++){
    deg += Mat_date[k][j];
  }
  return deg;
}

int Grafo_mat3::degWord(int j){
  int deg = 0;
  for(int k=0;k<n_tid;k++){
    deg += Mat_word[k][j];
  }
  return deg;
}

int Grafo_mat3::degUser(int j){
  int deg = 0;
  for(int k=0;k<n_tid;k++){
    deg += Mat_user[k][j];
  }
  return deg;
}

int Grafo_mat3::maxdegTweetId(){
  int deg = 0;
  for(int k=0;k<n_tid;k++){
    int aux = Grafo_mat3::degTweetId(k);
    if(aux>deg) deg=aux;
  }
  return deg;
}

int* Grafo_mat3::maxdegDate(){
  //int deg_index[2] = {0,0};
  int* deg_index = new int[2];
  deg_index[0] = 0;

  for(int k=0;k<n_date;k++){
    int aux = Grafo_mat3::degDate(k);
    if(aux>deg_index[0]){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

int* Grafo_mat3::maxdegWord(){
  int* deg_index = new int[2];
  deg_index[0] = 0;
  for(int k=0;k<n_word;k++){
    int aux = Grafo_mat3::degWord(k);
    if(aux>deg_index[0]){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

int* Grafo_mat3::maxdegUser(){
  int* deg_index = new int[2];
  deg_index[0] = 0;
  for(int k=0;k<n_uid;k++){
    int aux = Grafo_mat3::degUser(k);
    if(aux>deg_index[0]){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

int Grafo_mat3::mindegTweetId(){
  int deg = 3 + n_word; //1 Fecha+1 Usuario+ n_word Palabras
  for(int k=0;k<n_tid;k++){
    int aux = Grafo_mat3::degTweetId(k);
    if(aux<deg) deg=aux;
  }
  return deg;
}

int* Grafo_mat3::mindegDate(){
  int* deg_index = new int[2];
  deg_index[0] = Grafo_mat3::numVertices();
  for(int k=0;k<n_date;k++){
    int aux = Grafo_mat3::degDate(k);
    if(aux<deg_index[0] && aux>0){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

int* Grafo_mat3::mindegWord(){
  int* deg_index = new int[2];
  deg_index[0] = Grafo_mat3::numVertices();
  for(int k=0;k<n_word;k++){
    int aux = Grafo_mat3::degWord(k);
    if(aux<deg_index[0] && aux>0){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

int* Grafo_mat3::mindegUser(){
  int* deg_index = new int[2];
  deg_index[0] = Grafo_mat3::numVertices();
  for(int k=0;k<n_uid;k++){
    int aux = Grafo_mat3::degUser(k);
    if(aux<deg_index[0] && aux>0){
      deg_index[0] = aux;
      deg_index[1] = k;
    }
  }
  return deg_index;
}

std::vector<int> Grafo_mat3::getUserFromWord(int word_hash){
  std::vector<int> users;
  // Buscar TweetIds conectadas a word_hash:
  for(int i=0;i<n_uid;i++){
    if(Mat_word_user[word_hash][i] == 1) users.push_back(i);
  }
  return users;
}

std::vector<int> Grafo_mat3::getDatesFromWord(std::vector<int> words_hashes){
  std::vector<int> dates;
  int flag;
  for(int i=0;i<n_date;i++){
    flag = 0;
    for(int j=0;j<words_hashes.size();j++){
      if(Mat_date_word[i][words_hashes[j]] == 0){
          flag = 1;
          break;
      }
    }
    if(!flag) dates.push_back(i);
  }
  return dates;
}
