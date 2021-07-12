#ifndef __DISCO_HPP
#define __DISCO_HPP
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#define NUMROWD 5
#define NUMCOLUMND 10

using namespace std;

class Disco
{
	private:
		struct Arquivos{
			string valores[NUMROWD][NUMCOLUMND]; 
			int indices[NUMROWD][NUMCOLUMND];
		}arquivos;
		int i, j, totalLinha, maxColuna;
	public:
		Disco();
		void carregarDisco();
		void inicializarMatrizDisco();
		void tokenizar(string linha);
		void setMatrizDisco(string elemento);
		void contarLinhas(ifstream& myfile);
		void imprimeMatrizDisco();
		bool readDisco(int intArq, string pedaco, int n, int posMemoria);
		void writeDisco(int intArq, int y, string pedaco);
		void voltarMenu();
		int getTotalLinha();
		void imprimeMatrizDiscoInd();
};

#endif
