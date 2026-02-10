#include <stdio.h>
#include <stdlib.h>

#define V 7          // Number of vertices
#define INF 999999   // Large number representing no direct edge

// Edge structure for Kruskal
typedef struct {
    int u, v;
    int weight;
} Edge;

// For Union-Find
int parent[V];
int rank[V];

// Comparator for sorting edges by weight
int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Find with path compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// Union by rank
void union_sets(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        if (rank[px] > rank[py])
            parent[py] = px;
        else if (rank[px] < rank[py])
            parent[px] = py;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
}

// Print adjacency matrix
void print_adjacency_matrix(int adj[V][V]) {
    char nodes[] = {'A','B','C','D','E','F','G'};
    
    printf("\nAdjacency Matrix (cost in millions $):\n");
    printf("   ");
    for (int i = 0; i < V; i++)
        printf(" %c  ", nodes[i]);
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%c  ", nodes[i]);
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == INF)
                printf("  - ");
            else
                printf("%3d ", adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // 1. Adjacency matrix (symmetric, undirected graph)
    int adj[V][V] = {
        // A   B   C   D   E   F   G
        {  0,  6,INF,  5,INF,INF,INF},
        {  6,  0, 11, 17,INF,INF,INF},
        {INF, 11,  0,INF,INF,INF, 25},
        {  5, 17,INF,  0, 22, 22,INF},
        {INF,INF,INF, 22,  0, 10,INF},
        {INF,INF,INF, 22, 10,  0,INF},
        {INF,INF, 25,INF,INF,INF,  0}  
    };

    print_adjacency_matrix(adj);

    // 2. Collect all edges (only upper triangle to avoid duplicates)
    Edge edges[20];
    int edge_count = 0;

    for (int i = 0; i < V; i++) {
        for (int j = i+1; j < V; j++) {
            if (adj[i][j] != INF && adj[i][j] != 0) {
                edges[edge_count].u = i;
                edges[edge_count].v = j;
                edges[edge_count].weight = adj[i][j];
                edge_count++;
            }
        }
    }

    // Sort edges by increasing weight
    qsort(edges, edge_count, sizeof(Edge), compare);

    // Initialize Union-Find
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Kruskal's algorithm
    Edge mst[V-1];
    int mst_count = 0;
    int total_cost = 0;

    printf("\nApplying Kruskal's Algorithm...\n");
    printf("Edges considered (sorted by cost):\n");

    for (int i = 0; i < edge_count && mst_count < V-1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        printf("  %c-%c : $%dM   ", 'A'+u, 'A'+v, w);

        if (find(u) != find(v)) {
            union_sets(u, v);
            mst[mst_count++] = edges[i];
            total_cost += w;
            printf("→ ADDED\n");
        } else {
            printf("→ REJECTED (cycle)\n");
        }
    }

    // 3 & 4. Output result
    printf("\nMinimum Spanning Tree (MST) selected links:\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < mst_count; i++) {
        printf("%c -- %c    cost: %d million $\n",
               'A' + mst[i].u, 'A' + mst[i].v, mst[i].weight);
    }

    printf("\nTotal installation cost = %d million $\n", total_cost);
    printf("Number of links used = %d (should be %d for %d nodes)\n", mst_count, V-1, V);

    return 0;
}