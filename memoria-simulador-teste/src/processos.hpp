#ifndef __PROCESSOS_HPP
#define __PROCESSOS_HPP
#include "disco.hpp"
#include "memoria.hpp"
#include <string>
#define NUMROWP 10
#define NUMCOLUMNP 10
#define NUM 5

using namespace std;

class Processos
{
	private:
		string processos[NUMROWP][NUMCOLUMNP];
		string swap[NUMROWP][NUMCOLUMNP];
		int pageMiss[NUM];
		int fileRequest[NUM];
		int i, j, totalLinha, maxColuna;
		Disco d;
	public:
		Processos();
		void carregarProcessos();
		void inicializarMatrizProcessos();
		void inicializarMatrizSwap();
		void tokenizar(string linha);
		void setMatrizProcessos(string elemento);
		void setMatrizSwap(int n, int colSwap, string arquivo, string pedaco);
		void imprimeMatrizProcessos();
		void imprimeMatrizSwap();
		void executarProcessos(Disco d, Memoria m);
		void contarLinhas(ifstream& myfile);
		int getTotalLinha();
		void imprimeMatrizes(Disco d, Memoria m);
		void memoriaParaDisco(Disco, Memoria m);
		void showResults(Disco d);
		void inicializarPageMiss();
		void inicializarFileRequest(Disco d);
		//void inicializaMatrizIndices();
		void voltarMenu();
};
#endif
