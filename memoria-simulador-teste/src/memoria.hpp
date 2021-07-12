#ifndef __MEMORIA_HPP
#define __MEMORIA_HPP
#include <string>
#define NUMROWM 5
#define NUMCOLUMNM 5

using namespace std;

class Memoria
{
	private:
		string memoria[NUMROWM][NUMCOLUMNM];
		int i, j, totalLinha;
	public:
		Memoria();
		bool readMemoria(string arquivo, string pedaco);
		void writeMemoria(int k, int n, string arquivo, string pedaco);
		void inicializarMatrizMemoria();
		void setMatrizMemoria(string elemento);
		void setTotalLinha(int totalLinhaProcesso);
		void imprimeMatrizMemoria();
		string getElemento(int y);
		void apagarDaMemoria(int y);
		void voltarMenu();
};
#endif
