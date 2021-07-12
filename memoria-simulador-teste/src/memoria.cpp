#include "memoria.hpp"
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fstream>

void Memoria::inicializarMatrizMemoria()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < NUMCOLUMNM; j++)
			this->memoria[i][j] = "-1";
	}
}

void Memoria::setTotalLinha(int totalLinhaProcesso)
{
	this->totalLinha = totalLinhaProcesso;
}

bool Memoria::readMemoria(string arquivo, string pedaco)
{
	for(int i=0; i < this->totalLinha; i++)//
	{
		for(int j=0; j < NUMCOLUMNM; j++)
		{
			if(this->memoria[i][j] == arquivo+' '+pedaco)
				return true;
		}
	}
	return false;
}

void Memoria::writeMemoria(int n, int k, string arquivo, string pedaco)
{
	this->memoria[n][k] = arquivo+' '+pedaco;
}

string Memoria::getElemento(int y)
{
	return this->memoria[y][0];
}

void Memoria::apagarDaMemoria(int y)
{
	this->memoria[y][0] = "-1";
}

void Memoria::imprimeMatrizMemoria()
{
	for(int i=0; i < this->totalLinha; i++)
	{
		for(int j=0; j < NUMCOLUMNM; j++)
			cout << this->memoria[i][j] << '\t';
		cout << endl;
	}
}

void Memoria::voltarMenu()
{
	cout << "\n\nPressione qualquer tecla para continuar...";
	getchar();
	system("cls||clear");
}

Memoria::Memoria()
{
	this->i=0;
	this->j=0;
}
