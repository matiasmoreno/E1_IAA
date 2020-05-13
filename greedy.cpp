// Entrega 1 IAA - Matias Moreno - 201673508-9

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int main()
{
	ifstream inFile;
	inFile.open("MC/Instances/instancia1.dat");

	string line;
	string word;

	int nFarms, nTrucks, minPrize, i, j;

	// Obtener tamaño de arreglos

	// LLegar hasta predios productores
	while (inFile >> word)
	{
		if (word == "I:=")
		{
			break;
		}
	}

	nFarms = 1;
    // Recorrer predios
	while (inFile >> word)
	{
		nFarms = nFarms + 1;
        size_t found = word.find(";");
        if (found != string::npos) 
        {
            break;
        }
	}

    // LLegar hasta camiones
	while (inFile >> word)
	{
		if (word == "K:=")
		{
			break;
		}
	}

    // Recorrer camiones
    nTrucks = 0;
	while (inFile >> word)
	{
        nTrucks = nTrucks + 1;
        size_t found = word.find(";");
        if (found != string::npos) 
        {
            break;
        }
	}

	int capacity [nTrucks], production [nFarms], cost[nFarms][nFarms];

	// LLegar hasta #capacidades
	while (inFile >> word)
	{
		if (word == "param")
		{
			break;
		}
	}

	// Salta 'Q:='
	getline(inFile, line);

	// Obtener capacidades
	i = 0;
	inFile >> word;
	while (word != ";")
	{
		// Capacidad
		inFile >> word;
		capacity[i] = stoi(word);
		// N° Camion o ;
		inFile >> word;
		i = i + 1;
	}
	
	// Cantidad a recolectar

    while (inFile >> word)
	{
		if (word == "P:=")
		{
			inFile >> word;
			minPrize = stoi(word);
			break;
		}
	}

	// LLegar hasta #producción
	while (inFile >> word)
	{
		if (word == "param")
		{
			break;
		}
	}
	// Salto qu :=
	getline(inFile, line);
	// Salto producción de planta 0
	getline(inFile, line);

	// Obtener producciones
	i = 0;
	inFile >> word;
	while (word != ";")
	{
		// Produccion
		inFile >> word;
		production[i] = stoi(word);
		// N° granja ;
		inFile >> word;
		i = i + 1;
	}

	// LLegar hasta #costos :
	while (inFile >> word)
	{
		if (word == ":")
		{
			break;
		}
	}
	// Salto primera fila
	getline(inFile, line);

	for (i = 0; i < nFarms; i++)
	{
		// Salto la primera palabra de cada fila (La que corresponde al nodo de salida)
		inFile >> word;
		for (j = 0; j < nFarms; j++)
		{
			inFile >> word;
			if (i == j)
			{
				cost[i][j] = 0;
			}
			else
			{
				cost[i][j] = stoi(word);
			}
		}
	}
	cout << cost[38][39] << endl;
	cout << cost[38][40] << endl;
	cout << cost[39][39] << endl;
	cout << cost[39][40] << endl;
	cout << cost[40][39] << endl;
	cout << cost[40][40] << endl;

	inFile.close();

	// Sets de rutas dinamicos: vector de vectores? arreglo de vectores?

	// Función para añadir optimo local a las rutas dinamicas

	// Repetir Función hasta alcanzar minimo de producción

	// Printear solución y costo asociado

	return 0;
}