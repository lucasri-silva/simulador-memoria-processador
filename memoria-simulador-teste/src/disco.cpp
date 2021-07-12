#include "disco.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void Disco::carregarDisco()
{
	string linha, diretorio;
	ifstream myfile;
	myfile.open("/home/lucas/Desktop/memoria-simulador-teste/dataset/arquivos_exemplo.txt");
	if(myfile.is_open())
	{
		contarLinhas(myfile);
		inicializarMatrizDisco();
		while(getline(myfile, linha))
		{
			tokenizar(linha);
			this->i++;
			this->j=0;
		}
		imprimeMatrizDisco();
		cout << "\nDisco carregado com sucesso";
		voltarMenu();
		myfile.close();
	}
	else
		cout << "Erro ao abrir arquivo" << endl;
}

void Disco::inicializarMatrizDisco()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna; j++)
		{
			this->arquivos.valores[i][j] = "-1";
			this->arquivos.indices[i][j] = -1;
		}
	}
}

void Disco::contarLinhas(ifstream& myfile)
{
	char character;
	int count=0;
	while(myfile.get(character))
	{
		if(character == ',')
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

void Disco::tokenizar(string linha)
{	
	string elemento;
	char *token = strtok(&linha[0], ", ' '");
	while(token != NULL)
	{
		if(!isdigit(token[0]))
			token = strtok(NULL, ", ' '");
		elemento = token;
		setMatrizDisco(elemento);
		this->j++;
		token = strtok(NULL, ", ' '");
   	 }
}

int Disco::getTotalLinha()
{
	return this->totalLinha;
}


void Disco::setMatrizDisco(string elemento)
{
	this->arquivos.valores[this->i][this->j] = elemento;
}

void Disco::writeDisco(int intArq, int y, string pedaco)
{
	int indiceCol = this->arquivos.indices[y][0];
	cout << "intArq : " << intArq-1 << " x = " << y << " pedaco : " << pedaco << " indiceCol : " << indiceCol << endl; 
	this->arquivos.valores[intArq-1][indiceCol] = pedaco;
}

void Disco::imprimeMatrizDisco()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna; j++)
			cout << this->arquivos.valores[i][j] << '\t';
		cout << endl;
	}
}

void Disco::imprimeMatrizDiscoInd()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < this->maxColuna; j++)
			cout << this->arquivos.indices[i][j] << '\t';
		cout << endl;
	}
}

bool Disco::readDisco(int intArq, string pedaco, int n, int posMemoria)
{
	for(int i=0; i < this->maxColuna; i++)//percorre matriz disco por linha
	{
		if(this->arquivos.valores[intArq-1][i] == pedaco)
		{
			this->arquivos.valores[intArq-1][i] = "-1";
			this->arquivos.indices[n][posMemoria] = i;
			return true;
		}
	}
	return false;
}

void Disco::voltarMenu()
{
	cout << "\n\nPressione qualquer tecla para continuar...";
	getchar();
	system("cls||clear");
}

Disco::Disco()
{
	this->i=0;
	this->j=0;
	this->totalLinha=0;
	this->maxColuna=0;
}
