#include <stdio.h>
#include <string.h>

#define MAX 100

struct Node {
    int set;
} nodes[MAX];

struct Edge {
    int u, v, weight;
    int selected;
} edges[MAX];

int edge_count = 0;

// Function to get the distance between nodes
void getEdges(int total) {
    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            printf("Enter distance between Vertex %c and %c: ", i + 'A', j + 'A');
            scanf("%d", &edges[edge_count].weight);
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].selected = 0;
            edge_count++;
        }
    }
}

// Function to initialize nodes and edges
void initialize(int total) {
    for (int i = 0; i < total; i++) {
        nodes[i].set = i;
    }
}

// Function to sort edges based on their weights (using Bubble Sort)
void sortEdges() {
    struct Edge temp;
    for (int i = 0; i < edge_count - 1; i++) {
        for (int j = 0; j < edge_count - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's algorithm
void kruskal(int total) {
    int edges_selected = 0;

    for (int i = 0; i < edge_count && edges_selected < total - 1; i++) {
        int u_set = nodes[edges[i].u].set;
        int v_set = nodes[edges[i].v].set;

        if (u_set != v_set) {
            edges[i].selected = 1;
            edges_selected++;

            // Union of two sets
            for (int j = 0; j < total; j++) {
                if (nodes[j].set == v_set) {
                    nodes[j].set = u_set;
                }
            }
        }
    }

    // Print the result
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < edge_count; i++) {
        if (edges[i].selected) {
            printf("%c <--> %c Distance: %d\n", edges[i].u + 'A', edges[i].v + 'A', edges[i].weight);
        }
    }
}

int main() {
    int total;

    printf("Enter the number of vertices: ");
    scanf("%d", &total);

    getEdges(total);
    initialize(total);
    sortEdges();
    kruskal(total);

    return 0;
}
