#include <stdio.h>
#define INFINITY 999

// Function to find the Minimum Spanning Tree using Prim's algorithm
int prim(int cost[10][10], int source, int n) {
    int visited[10] = {0}, cmp[10], vertex[10];
    int sum = 0, min, u;

    // Initialize arrays
    for (int i = 1; i <= n; i++) {
        vertex[i] = source;
        cmp[i] = cost[source][i];
    }
    visited[source] = 1;

    // Prim's algorithm
    for (int i = 1; i < n; i++) {
        min = INFINITY;
        u = -1;

        // Find the minimum edge
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && cmp[j] < min) {
                min = cmp[j];
                u = j;
            }
        }

        if (u == -1) break;  // No more vertices to process

        visited[u] = 1;
        sum += cmp[u];
        printf("\n %d -> %d, Edge Cost = %d", vertex[u], u, cmp[u]);

        // Update cmp array for the next iteration
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && cost[u][v] < cmp[v]) {
                cmp[v] = cost[u][v];
                vertex[v] = u;
            }
        }
    }

    return sum;
}

int main() {
    int a[10][10], n, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (0 for self-loop, 999 for no edge):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Validate the cost matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] != a[j][i] || a[i][i] != 0) {
                printf("Invalid entry: cost matrix should be symmetrical and the diagonal elements should be zero.\n");
                return 1;
            }
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    int total_cost = prim(a, source, n);
    printf("\n\nTotal Cost of Minimum Spanning Tree: %d\n", total_cost);

    return 0;
}
