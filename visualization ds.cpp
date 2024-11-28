#include <stdio.h>
#include <string.h>
#include <conio.h>
#define INFINITY 9999
#define MAX 10

void dijkstra(int G[MAX][MAX], int n, int startnode, char names[MAX][20]);
void generateGraphviz(int G[MAX][MAX], int n, char names[MAX][20]);

int main() {
    int G[MAX][MAX], i, j, n, u;
    char names[MAX][20];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter the name of vertex %d: ", i + 1);
        scanf("%s", names[i]);
    }

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                G[i][j] = 0;
            } else {
                char from[20], to[20];
                printf("Enter the weight from vertex %s to vertex %s (or 0 if no connection): ", names[i], names[j]);
                scanf("%d", &G[i][j]);
            }
        }
    }

    printf("Enter the starting node (0 to %d): ", n - 1);
    scanf("%d", &u);

    printf("Generated Graphviz code for visualization:\n");
    generateGraphviz(G, n, names);

    dijkstra(G, n, u, names);

    return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode, char names[MAX][20]) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    // pred[] stores the predecessor of each node
    // count gives the number of nodes seen so far
    // create the cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];
    // initialize pred[], distance[] and visited[]
    for (i = 0; i < n; i++) {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1) {
        mindistance = INFINITY;
        // nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        // check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i]) {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
    // print the path and distance of each node
    for (i = 0; i < n; i++) {
        if (i != startnode) {
            printf("\nDistance from %s to %s = %d", names[startnode], names[i], distance[i]);
            printf("\nPath: %s", names[i]);
            j = i;
            do {
                j = pred[j];
                printf(" <- %s", names[j]);
            } while (j != startnode);
        }
    }
}

void generateGraphviz(int G[MAX][MAX], int n, char names[MAX][20]) {
    printf("digraph G {\n");

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i != j && G[i][j] != 0) {
                printf("  %s -> %s [label=\"%d\"];\n", names[i], names[j], G[i][j]);
            }
        }
    }

    printf("}\n");
}

