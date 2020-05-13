// Entrega 1 IAA - Matias Moreno - 201673508-9

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;
void miope(int& bestTruck, int& bestFarm, int capacity[], int position[], int production[], int **cost, float minPrize, int nTrucks, int nFarms){
	float maxValue = 0;
	float value = 0;
	for (int i = 1; i < nTrucks; i++)
	{
		for (int j = 1; j < nFarms; j++)
		{
			if (cost[position[i]][j] != 0){
				if ((capacity[i] - production[j]) > 0)
				{
					value = float(production[j]) / float(cost[position[i]][j]);
					if (maxValue < value)
					{
						maxValue = value;
						bestTruck = i;
						bestFarm = j;
					}
				}
				
			}
		}
	}
}

int main()
{
	ifstream inFile;
	inFile.open("MC/Instances/instancia10.dat");

	string line;
	string word;

	int nFarms, nTrucks, i, j, origin;
	float minPrize;

	// Obtener nodo origin

	while (inFile >> word)
	{
		if (word == "-")
		{
			inFile >> word;
			origin = stoi(word);
			break;
		}
	}

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
    nTrucks = 1;
	while (inFile >> word)
	{
        nTrucks = nTrucks + 1;
        size_t found = word.find(";");
        if (found != string::npos) 
        {
            break;
        }
	}

	int capacity [nTrucks], position [nTrucks], load [nTrucks], production [nFarms];
	int **cost;
	cost = new int *[nFarms];
	for(int i = 0; i < nFarms; i++)
	{
    	cost[i] = new int[nFarms];
	}

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
	i = 1;
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
			minPrize = stof(word);
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
	i = 1;
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

	inFile.close();

	// Sets de rutas dinamicos: vector de vectores? arreglo de vectores?

	// Crear 3 vectores dinamicos para generar las rutas

	vector <int> routes[nTrucks];

	// Inicializar posiciones y carga de los camiones en el origen: nodo 0

	for (i = 1; i < nTrucks; i++)
	{
		position[i] = 0;
		load[i] = 0;
	}

	// Repetir Función añadir optimo local hasta alcanzar minimo de producción

	int bestTruck = 0, bestFarm = 0, actualPrize = 0;

	while (actualPrize < minPrize)
	{
		miope(bestTruck, bestFarm, capacity, position, production, cost, minPrize, nTrucks, nFarms);
		if (routes[bestTruck].size() == 0)
		{
			routes[bestTruck].push_back(origin);
		}
		routes[bestTruck].push_back(bestFarm);
		position[bestTruck] = bestFarm;
		capacity[bestTruck]	= capacity[bestTruck] - production[bestFarm];
		load[bestTruck] = load[bestTruck] + production[bestFarm];
		actualPrize = actualPrize + production[bestFarm];
		production[bestFarm] = 0;
	}
	
	// Volver a la planta
	int notEmptyRoutes = 0;

	for (i = 1; i < nTrucks; i++)
	{
		if (routes[i].size() != 0)
		{
			routes[i].push_back(origin);
			notEmptyRoutes++;
		}
	}

	// Calcular costo solución

	int costRoutes = 0;
	int distance;

	for (i = 1; i < nTrucks; i++)
	{
		distance = 0;
		if (routes[i].size() != 0)
		{
			for (j = 0; j < routes[i].size() - 1; j++)
			{
				if (routes[i][j] == origin)
				{
					costRoutes = costRoutes + cost[0][routes[i][j + 1]];
					distance = distance + cost[0][routes[i][j + 1]];
				}
				else if (routes[i][j + 1] == origin)
				{
					costRoutes = costRoutes + cost[routes[i][j]][0];
					distance = distance + cost[routes[i][j]][0];
				}
				else
				{
					costRoutes = costRoutes + cost[routes[i][j]][routes[i][j + 1]];
					distance = distance + cost[routes[i][j]][routes[i][j + 1]];
				}	
			}
		}
		if (routes[i].size() != 0)
		{
			routes[i].push_back(distance);
		}
	}

	// Printear solución y costo asociado

	cout << costRoutes << " " << actualPrize << " " << notEmptyRoutes << endl;

	for (i = 1; i < nTrucks; i++)
	{
		if (routes[i].size() != 0)
		{	
			cout << "Truck " << i << " ";
			for (j = 0; j < routes[i].size() - 1; j++)
			{
				if (routes[i][j] == origin)
				{
					if (j == 0)
					{
						cout << origin << "-";
					}
					else
					{
						cout << origin << " " << routes[i][j + 1] << " " << load[i] << endl;
					}	
				}
				else
				{
					cout << routes[i][j] << "-";
				}	
			}
		}
	}

	// Print de vicente
	// función de evaluación, total de leche recolectado, cantidad de rutas
	// rutas, distancia recorrida, leche recogida

	return 0;
}
