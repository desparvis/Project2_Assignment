#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_NODES 7
#define INF 9999

// Adjacency matrix (undirected graph - symmetric)
int adj[MAX_NODES][MAX_NODES] = {
    // A  B  C  D  E  F  G
    { 0, 6, 0, 5, 0, 0, 0}, // A
    { 6, 0,11,17, 0, 0, 0}, // B
    { 0,11, 0, 0, 0, 0,25}, // C
    { 5,17, 0, 0,22,22, 0}, // D
    { 0, 0, 0,22, 0,10, 0}, // E
    { 0, 0, 0,22,10, 0, 0}, // F
    { 0, 0,25, 0, 0, 0, 0}  // G
};

char nodes[MAX_NODES] = {'A','B','C','D','E','F','G'};

// Convert node letter → index (0..6)
int get_index(char node) {
    for (int i = 0; i < MAX_NODES; i++) {
        if (nodes[i] == node) return i;
    }
    return -1;
}

void find_direct_peers_and_highest_risk(char start_node) {
    int start = get_index(start_node);
    if (start == -1) {
        printf("Invalid workstation: %c\n", start_node);
        return;
    }

    // BFS setup
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Enqueue starting node
    queue[rear++] = start;
    visited[start] = 1;

    int max_time = -1;
    char max_peer = ' ';
    int found_neighbor = 0;

    printf("\nSuspected compromised workstation: %c\n", start_node);
    printf("Directly connected workstations (1-hop neighbors via BFS):\n");
    printf("------------------------------------------------------------\n");

    // We only need level 1 → process only the starting node
    int u = queue[front++];   // dequeue start

    // Visit all direct neighbors (this is level 1)
    for (int v = 0; v < MAX_NODES; v++) {
        if (adj[u][v] > 0 && adj[u][v] != INF && !visited[v]) {
            // We found a direct neighbor
            visited[v] = 1;
            // We could enqueue(v) here if we wanted deeper levels — but we don't

            printf(" → %c   data transfer time: %d minutes\n", nodes[v], adj[u][v]);
            found_neighbor = 1;

            // Track highest risk direct connection
            if (adj[u][v] > max_time) {
                max_time = adj[u][v];
                max_peer = nodes[v];
            }
        }
    }

    if (!found_neighbor) {
        printf("No direct connections found from %c.\n", start_node);
    } else {
        printf("\nHighest risk direct peer: %c (transfer time = %d minutes)\n", 
               max_peer, max_time);
        printf("This workstation has the highest volume of data transferred with the suspected node.\n");
    }
}

int main() {
    char suspected;

    printf("Enterprise Network - Insider Threat Investigation\n");
    printf("Workstations: A, B, C, D, E, F, G\n\n");

    printf("Enter suspected compromised workstation (A-G): ");
    scanf(" %c", &suspected);
    suspected = toupper(suspected);

    find_direct_peers_and_highest_risk(suspected);

    printf("\nNote: BFS was used to discover direct (1-hop) neighbors as requested.\n");
    return 0;
}