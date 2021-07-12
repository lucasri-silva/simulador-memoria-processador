#include "processos.hpp"
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fstream>

int Processos::getTotalLinha()
{
	return this->totalLinha;
}

void Processos::carregarProcessos()
{
	string linha;
	ifstream myfile;
	myfile.open ("/simulador-memoria-processador/memoria-simulador-teste/dataset/processos_exemplo.txt");
	if(myfile.is_open())
	{
		contarLinhas(myfile);
		inicializarMatrizProcessos();
		inicializarMatrizSwap();
		inicializarPageMiss();
		inicializarFileRequest(d);
		while(getline(myfile, linha))
		{
			replace(linha.begin(), linha.end(), ',', ' ');
			tokenizar(linha);
			this->i++;
			this->j=0;
		}
		system("cls||clear");
		imprimeMatrizProcessos();
		cout << "\nProcessos carregados com sucesso";
		voltarMenu();
		myfile.close();
	}
	else
		cout << "Erro ao abrir arquivo" << endl;
}

void Processos::inicializarPageMiss()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		pageMiss[i] = 0;
	}
	for(long unsigned int i=0; i < sizeof(pageMiss)/sizeof(pageMiss[0]); i++)
	{
		cout << pageMiss[i] << endl;
	}
}

void Processos::inicializarFileRequest(Disco d)
{
	for(int i=0; i < d.getTotalLinha(); i++)
	{
		fileRequest[i] = 0;
	}
}

void Processos::inicializarMatrizProcessos()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna; j++)
			this->processos[i][j] = "-1";
	}
}

void Processos::inicializarMatrizSwap()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna-5; j++)//pior caso da swap: 5 primeiros elementos sao armazenados na memoria
			this->swap[i][j] = "-1";
	}
}

//void Processos::inicializaMatrizIndices()
//{
//	for(int i=0; i < this->totalLinha; i++)
//	{
//		for(int j=0; j < NUMCOLUMNP; j++)
//			this->indices[i][j] = -1;
//	}
//}

void Processos::contarLinhas(ifstream& myfile)
{
	char character;
	int count=0;
	
	while(myfile.get(character))
	{
		if(character == 'A')
			count++;
		if(character == '\n')
		{
			this->totalLinha++;
			if(this->maxColuna < count)
				this->maxColuna = count;
			count = 0;
		}
	}
	myfile.clear();
	myfile.seekg(0, myfile.beg);
}

void Processos::tokenizar(string linha)
{	
	string elemento;
	char *token = strtok(&linha[0], "< > ' '");
	while(token != NULL)
	{
		if(token[0] == 'P')
			token = strtok(NULL, "< > ' '");
		else if(token[0] == 'A')
		{
			elemento = token;
			token = strtok(NULL, "< > ' '");
		}
		else
		{
			setMatrizProcessos(elemento+' '+token);
			this->j++;
			token = strtok(NULL, "< > ' '");
		}
   	 }
}

void Processos::setMatrizProcessos(string elemento)
{
	this->processos[this->i][this->j] = elemento;
}

void Processos::setMatrizSwap(int n, int colSwap, string arquivo, string pedaco)//OK
{
	this->swap[n][colSwap] = arquivo+' '+pedaco;
}

void Processos::executarProcessos(Disco d, Memoria m)
{
	string arquivoEpedaco, arquivo, pedaco;
	int posMemoria;//se arquivo nao se encontra na memoria e disco entao mantem a posicao da coluna onde esta (em vez de passar para a prox e ficar -1 na posicao)
	int colSwap;	
	for(int n=0; n < this->totalLinha; n++)
	{
		posMemoria=0;
		colSwap=0;
		for(int k=0; k < this->maxColuna; k++)
		{
			arquivoEpedaco = processos[n][k];
			if(arquivoEpedaco == "-1")//se processo for igual a -1
				break;
			char *token = strtok(&arquivoEpedaco[0], "' '");
			arquivo = token;
			string arq = arquivo.substr(1);//corta 'digito' de 'Adigito' para percorrer matriz disco direto na linha correspondente
			int intArq = stoi(arq);//"digito" string para int
			token = strtok(NULL, "' '");
			pedaco = token;
			this->fileRequest[intArq]++;
			if(posMemoria < 5)
			{
				if(m.readMemoria(arquivo, pedaco))
				{
					m.writeMemoria(n, posMemoria, arquivo, pedaco);
					cout << "Arquivo " << arquivo+' '+pedaco << " já se encontra na memória\n";
					posMemoria++;
					imprimeMatrizes(d, m);
					//imprimeLeitura(n, acessoValido, erroLeitura, arqNaoEncontrado);
				}
				else if(d.readDisco(intArq, pedaco, n, posMemoria))
				{
					m.writeMemoria(n, posMemoria, arquivo, pedaco); 
					cout << "Arquivo " << arquivo+' '+pedaco << " estava no disco e foi movido para a memória\n";
					posMemoria++;
					this->pageMiss[n]++;
					imprimeMatrizes(d, m);
					//imprimeLeitura(n, acessoValido, erroLeitura, arqNaoEncontrado);
				}
				else
				{
					cout << "Arquivo " << arquivo+' '+pedaco << " não se encontra na memória nem no disco\n";
					//arqNaoEncontrado++;
					imprimeMatrizes(d, m);
					//imprimeLeitura(n, acessoValido, erroLeitura, arqNaoEncontrado);
				}
			} 
			else 
			{
				cout << "Memória cheia. Preenchendo Swap..." << endl;
				setMatrizSwap(n, colSwap, arquivo, pedaco);
				imprimeMatrizes(d, m);
			}
			voltarMenu();
		}
	}
	showResults(d);
	voltarMenu();
	memoriaParaDisco(d, m);
}

//void Processos::swapParaMemoria(Disco d, maxColuna)
//{
//	for(int j=0; j < this->totalLinha; j++)
//	{
//		for(int i=0; i < this->maxColuna-5; i++)
//		{
//			d.memoriaParaDisco(j, i);
//		}
//	}
//}

void Processos::memoriaParaDisco(Disco d, Memoria m)
{
	string arquivo, pedaco, arquivoEpedaco;
	for(int y=0; y < this->totalLinha; y++)
	{
		arquivoEpedaco = m.getElemento(y);
		char *token = strtok(&arquivoEpedaco[0], " ");
		arquivo = token;
		token = strtok(NULL, " ");
		pedaco = token;
		//cout << "arq : " << arquivo << " pedaco : " << pedaco << endl;
		string arq = arquivo.substr(1);//corta 'digito' de 'Adigito' para percorrer matriz disco direto na linha correspondente
		int intArq = stoi(arq);//"digito" string para int
		m.apagarDaMemoria(y);
		d.writeDisco(intArq, y, pedaco);
		imprimeMatrizes(d, m);
		voltarMenu();
		//m.writeMemoria();
	}
}

void Processos::voltarMenu()
{
	cout << "\n\nPressione qualquer tecla para continuar...";
	getchar();
	system("cls||clear");
}

void Processos::imprimeMatrizProcessos()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna; j++)
			cout << this->processos[i][j] << '\t';
		cout << endl;
	}
}

void Processos::imprimeMatrizSwap()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna-5; j++)
			cout << this->swap[i][j] << '\t';
		cout << endl;
	}
}

void Processos::imprimeMatrizes(Disco d, Memoria m)
{
	cout << "\nMATRIZ PROCESSOS\n";
	imprimeMatrizProcessos();
	cout << "\nMATRIZ DISCO\n";
	d.imprimeMatrizDisco();
	cout << "\nMATRIZ INDICES DISCO\n";
	d.imprimeMatrizDiscoInd();
	cout << "\nMATRIZ MEMÓRIA\n";
	m.imprimeMatrizMemoria();
	cout << "\nMATRIZ SWAP\n";
	imprimeMatrizSwap();
	cout << endl;
}

void Processos::showResults(Disco d)
{
	cout << "Page Miss: ";
	for(int i=0; i < totalLinha; i++)
		cout << " P" << i+1 << ": " << this->pageMiss[i];
	
	cout << "\nFile Request: ";
	for(int i=0; i < d.getTotalLinha(); i++)
		cout << " A" << i+1 << ": " << this->fileRequest[i];
}

Processos::Processos()
{
	this->i=0;
	this->j=0;
	this->totalLinha=0;
	this->maxColuna=0;
}
