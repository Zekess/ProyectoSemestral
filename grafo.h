#ifndef __GRAFO_MAT__
#define __GRAFO_MAT__

#include <iostream>
#include <string>
#include <vector>

//"TweetId","TweetDate","TweetText","UserId"

class Grafo_mat3{

	public:
		Grafo_mat3(int n, int n1, int n2, int n3);
    void insertDate(std::string T_id, int j);
    bool IsDateInserted(int j);
    void insertWord(int j);
    bool IsWordInserted(int j);
    void insertUser(int j);
    bool IsUserInserted(int j);
		void insertWordUser(int i, int j);
    void insertDateWord(int i, int j);
		//bool areAdjacent(int a, int b);
    int numVertices();
    int numVerticesTweetId();
		int numVerticesDate();
    int numVerticesWord();
    int numVerticesUser();
		int numEdges();
    void printAdj();
    int degTweetId(int j);
    int degDate(int j);
    int degWord(int j);
    int degUser(int j);
    int maxdegTweetId();
    int* maxdegDate();
    int* maxdegWord();
    int* maxdegUser();
    int mindegTweetId();
    int* mindegDate();
    int* mindegWord();
    int* mindegUser();
    std::vector<int> getUserFromWord(int word_hash);
    std::vector<int> getDatesFromWord(std::vector<int> words_hashes);


	private:
    int m;
    std::vector<std::string> data_TweetId;
    int n_tid;                                 // Número de TweetId's
		std::vector<std::vector<int>> Mat_date;   // Matriz ady para Dates
    int n_date;                               // Número de TweetDate's
    std::vector<std::vector<int>> Mat_word;   // Matriz ady para palabras de Text
    int n_word;                               // Número de palabras
    std::vector<std::vector<int>> Mat_user;   // Matriz ady para UserId
    int n_uid;                               // Número de UserId's
    int n_edges;

		std::vector<std::vector<int>> Mat_word_user;    //Matriz auxiliar palabra x usuarios
    std::vector<std::vector<int>> Mat_date_word;    //Matriz auxiliar fecha x palabra
};




#endif
