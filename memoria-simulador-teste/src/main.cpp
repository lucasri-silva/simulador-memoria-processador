#include "disco.hpp"
#include "memoria.hpp"
#include "processos.hpp"
#include "iostream"
#include "locale.h"
#include <stdbool.h>

using namespace std;

int main()
{
	system("cls||clear");
	setlocale(LC_ALL, "Portuguese");
	int totalLinhaProcesso;
	bool on=true;
	int opcao;
	Disco d;
	Processos p;
	Memoria m;
	
	do
	{
		cout << "1. Carregar Disco\n2. Executar Processos\n3. Encerrar progama\n\nEscolha uma opção: ";
		cin >> opcao;
		cin.ignore();
		system("cls||clear");
		switch(opcao)
		{
			case 1:
				d.carregarDisco();//abre arquivos.txt; conta quant. linhas arquivos; inicializa matriz disco; carrega disco (tokeniza e salva em matriz disco)
				p.carregarProcessos();// abre processos.txt; conta quant. linhas processos; inicializa matriz processos; carrega processos (tokeniza e salva em matriz processos)
				break;
			case 2:
				totalLinhaProcesso = p.getTotalLinha();
				m.setTotalLinha(totalLinhaProcesso);
				m.inicializarMatrizMemoria();//inicializa matriz memoria (quant. de linhas matriz processos x 5)
				p.executarProcessos(d, m);//
				break;
			default:
				on=false;
		}
	}while(on);
	
	return 0;
}
