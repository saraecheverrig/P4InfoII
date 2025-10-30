#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <limits.h>
#include <vector>

const int INF = INT_MAX; // Valor para representar la distancia infinita

using namespace std;

void dijkstra(vector<vector<int>> vectores, int src, vector<vector<int>> &caminos);
int minDistance(int dist[], bool sptSet[], int len);

#endif // FUNCIONES_H
