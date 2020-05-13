// Entrega 1 IAA - Matias Moreno - 201673508-9

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void suma(int& a){
    a = 3;
}

int main()
{
    vector<int> vect;
    vect.push_back(10); 
    vect.push_back(20); 
    vect.push_back(30); 
  
    for (int x : vect) 
        cout << x << " "; 
  
    cout << "\nReference operator [g] : g1[2] = " << vect[1] << endl; 

    vector <int> rutas[3];
    rutas[0].push_back(0);
/*      rutas[0].push_back(1);
    rutas[1].push_back(10);
    rutas[1].push_back(11);
    rutas[2].push_back(20);
    rutas[2].push_back(21);
    cout << "Posicion rutas[0][0]: " << rutas[0][0] << endl;
    cout << "Posicion rutas[1][0]: " << rutas[1][0] << endl;
    cout << "Posicion rutas[2][0]: " << rutas[2][0] << endl;
    cout << "Posicion rutas[0][1]: " << rutas[0][1] << endl;
    cout << "Posicion rutas[1][1]: " << rutas[1][1] << endl;
    cout << "Posicion rutas[2][1]: " << rutas[2][1] << endl; */
    cout << "Tamano vector: " << rutas[0].size() << endl;
    int i = 0;
    suma(i);
    cout << "i : " << i << endl;
    return 0;
}