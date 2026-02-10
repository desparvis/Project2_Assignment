#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define V 10          
#define INF 9999999

typedef struct {
    int u, v, w;
} Edge;

char nodes[V] = {'A','B','C','D','E','F','G','H','I','J'};

// Helper: find index from letter
int get_index(char ch) {
    for (int i = 0; i < V; i++)
        if (nodes[i] == ch) return i;
    return -1;
}

// Print path using predecessor array
void print_path(int pred[], int j) {
    if (pred[j] == -1) {
        printf("%c", nodes[j]);
        return;
    }
    print_path(pred, pred[j]);
    printf(" → %c", nodes[j]);
}

void bellman_ford(int src, Edge edges[], int edge_count) {
    int dist[V];
    int pred[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[src] = 0;

    // Relax |V-1| times
    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < edge_count; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
            }
        }
    }

    // Check for negative-weight cycle
    int has_negative_cycle = 0;
    for (int j = 0; j < edge_count; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            has_negative_cycle = 1;
            break;
        }
    }

    // Output results
    printf("\n=== Bellman-Ford Results from Branch A ===\n");
    printf("Branch\tMin Cost\tPath\n");
    printf("--------------------------------------------\n");

    for (int i = 0; i < V; i++) {
        if (i == src) {
            printf("%c\t0\t\tA\n", nodes[i]);
            continue;
        }
        if (dist[i] == INF) {
            printf("%c\tINF\t\tNo path\n", nodes[i]);
        } else {
            printf("%c\t%d\t\t", nodes[i], dist[i]);
            print_path(pred, i);
            printf("\n");
        }
    }

    if (has_negative_cycle) {
        printf("\n*** NEGATIVE-WEIGHT CYCLE DETECTED ***\n");
        printf("Warning: Some paths may be unstable or exploitable.\n");
        printf("Shortest-path distances are not reliable in presence of negative cycles.\n");
    } else {
        printf("\nNo negative-weight cycles detected.\n");
    }
}

int main() {
    // All undirected edges
    Edge edges[50];
    int edge_count = 0;

    // Format: {u, v, w}

    // A --4--> B
    edges[edge_count++] = (Edge){0,1,4};
    edges[edge_count++] = (Edge){1,0,4};

    // B --6--> C
    edges[edge_count++] = (Edge){1,2,6};
    edges[edge_count++] = (Edge){2,1,6};

    // C --9--> G
    edges[edge_count++] = (Edge){2,6,9};
    edges[edge_count++] = (Edge){6,2,9};

    // G --13--> H
    edges[edge_count++] = (Edge){6,7,13};
    edges[edge_count++] = (Edge){7,6,13};

    // A --16--> D
    edges[edge_count++] = (Edge){0,3,16};
    edges[edge_count++] = (Edge){3,0,16};

    // D --7--> E
    edges[edge_count++] = (Edge){3,4,7};
    edges[edge_count++] = (Edge){4,3,7};

    // E --2--> I
    edges[edge_count++] = (Edge){4,8,2};
    edges[edge_count++] = (Edge){8,4,2};

    // E --10--> F
    edges[edge_count++] = (Edge){4,5,10};
    edges[edge_count++] = (Edge){5,4,10};

    // F --10--> G
    edges[edge_count++] = (Edge){5,6,10};
    edges[edge_count++] = (Edge){6,5,10};

    // D --7--> J
    edges[edge_count++] = (Edge){3,9,7};
    edges[edge_count++] = (Edge){9,3,7};

    // J --3--> F
    edges[edge_count++] = (Edge){9,5,3};
    edges[edge_count++] = (Edge){5,9,3};

    // B --6--> J 
    edges[edge_count++] = (Edge){1,9,6};
    edges[edge_count++] = (Edge){9,1,6};

    // assuming the 7 is B–D
    edges[edge_count++] = (Edge){1,3,7};
    edges[edge_count++] = (Edge){3,1,7};

    printf("Bank Inter-Branch Transaction Network Analysis\n");
    printf("Source: Central Clearing Branch A\n");
    printf("Edges modeled as bidirectional with same cost.\n\n");

    bellman_ford(0, edges, edge_count);  // 0 = A

    return 0;
}