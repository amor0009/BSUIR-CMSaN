#define V 9                                         // количество вершин в графе

// структура для хранения информации о станции метро
struct Station {
    char name[50]; // название станции
    int line; // номер линии метро, на которой находится станция
};

// структура для хранения информации о ребре между двумя станциями метро
struct Edge {
    int u; // номер первой станции
    int v; // номер второй станции
    int weight; // вес ребра (время в пути)
};

int min_distance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int i = 0; i < V; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int graph[V][V], int start, int end, struct Station stations[]) {
    int dist[V]; // массив расстояний от стартовой вершины
    int visited[V]; // массив посещенных вершин
    int prev[V]; // массив предыдущих вершин на пути
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < V - 1; i++) {
        int u = min_distance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (visited[v] == 0 && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // выводим результат
    if (dist[end] == INT_MAX) {
        printf("No path found\n");
        return;
    }

    printf("Shortest path from %s (line %d) to %s (line %d):\n", stations[start].name, stations[start].line, stations[end].name, stations[end].line);
    printf("%s (line %d)", stations[end].name, stations[end].line);

    int current = end;
    while (prev[current] != -1) {
        if (stations[current].line != stations[prev[current]].line) {
            printf(" -> Transfer -> %s (line %d)", stations[prev[current]].name, stations[prev[current]].line);
        }
        else {
            printf(" -> %s (line %d)", stations[prev[current]].name, stations[prev[current]].line);
        }
        current = prev[current];
    }
    printf("\n");
}

int main()
{
    int graph[V][V] =
    {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 2, 0, 1},
        {0, 2, 0, 0, 3, 0, 0, 8, 0},
    };
    dijkstra(graph, 0, V, )
}