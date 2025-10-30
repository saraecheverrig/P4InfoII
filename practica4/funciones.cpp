#include "funciones.h"


int minDistance(int dist[], bool sptSet[], int len)
{
    /*
    Analizar de las distancias cuál es la menor y que no haya sido procesada
    min: distancia más corta de los caminos que no han sido procesados
    */
    int min = INT_MAX, min_index;   // Inicializar valor mínimo como el número máximo, indicar que no ha sido procesado

    for (int v = 0; v < len; v++)
        if (sptSet[v] == false && dist[v] <= min)
            //Si: el camino no ha sido procesado y la distancia al enrutador v es menor a min
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(vector<vector<int>> vectoresOrg, int src, vector<vector<int>> &caminos)
{
    /*
    src: posición del enrutador al que le quiero calcular el camino más corto
    len:cantidad de enrutadores
    dist: almacen de distancias mínimas desde src a cada enrutador
    sptSet:shortest path tree set: arreglo que indica si se ha encontrado la distancia mínima a cada enrutador
    */
    int len = vectoresOrg.size();

    int dist[len];
    bool sptSet[len];
    for (int i = 0; i < len; i++)         //Inicializar todos los caminos como distancia máxima y vertice no procesado
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;          // La distancia del enrutador a si mismo es 0

    // Find shortest path for all vertices
    for (int count = 0; count < len - 1; count++) {

        int u = minDistance(dist, sptSet, len);         //camino mínimo del arreglo de distancias.
        //u en la primera iteración siempre es src
        //u: indice de la distancia más corta de los caminos que no han sido procesados

        sptSet[u] = true;       //el camino a u ha sido procesado

        for (int v = 0; v < len; v++)
            if (!sptSet[v] && vectoresOrg[u][v]        //sptSet[v] es false, cumple
                && dist[u] != INT_MAX
                && dist[u] + vectoresOrg[u][v] < dist[v])
                //la distancia que tiene almacenada más el enrutador
                //en la posición U con el enrutador a evaluar V es menor
                //a la distancia que se tiene en V
                dist[v] = dist[u] + vectoresOrg[u][v];
    }
    for (int i = 0; i < len; i++){
        caminos[src][i] = dist[i];
        vectoresOrg[src][i] = dist[i];
    }
}
