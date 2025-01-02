#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Cấu trúc đồ thị sử dụng danh sách kề
struct Graph {
    int numVertices;    // Số lượng đỉnh
    int **adjMatrix;    // Ma trận kề biểu diễn đồ thị
};

// Tạo đồ thị
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // Khởi tạo ma trận kề
    graph->adjMatrix = malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0; // Ban đầu tất cả các giá trị đều là 0
    }
    return graph;
}

// Thêm cạnh vào đồ thị
void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;  // Thêm cạnh từ src đến dest
    // Nếu là đồ thị vô hướng thì thêm dòng dưới để thêm cạnh từ dest đến src:
    // graph->adjMatrix[dest][src] = 1;
}

// In đồ thị
void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            if (graph->adjMatrix[i][j])
                printf("%d ", j);  // In các đỉnh kề với đỉnh i
        }
        printf("\n");
    }
}

// Duyệt đồ thị theo BFS
void bfs(struct Graph* graph, int startVertex) {
    int visited[MAX]; // Mảng đánh dấu các đỉnh đã được duyệt
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    int queue[MAX];  // Hàng đợi để lưu các đỉnh sẽ duyệt
    int front = -1;
    int rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    printf("BFS: ");

    while (front != rear) {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;  // Đánh dấu đỉnh đã được duyệt
            }
        }
    }
    printf("\n");
}

// Duyệt đồ thị theo DFS
void dfs(struct Graph* graph, int startVertex) {
    int visited[MAX]; // Mảng đánh dấu các đỉnh đã được duyệt
    for (int i = 0; i < MAX; i++)
        visited[i] = 0;

    int stack[MAX];  // Ngăn xếp để lưu các đỉnh sẽ duyệt
    int top = -1;

    printf("DFS: ");
    stack[++top] = startVertex;

    while (top != -1) {
        int currentVertex = stack[top--];
        if (!visited[currentVertex]) {
            printf("%d ", currentVertex);
            visited[currentVertex] = 1;  // Đánh dấu đỉnh đã được duyệt
        }

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                stack[++top] = i;  // Thêm đỉnh vào ngăn xếp
            }
        }
    }
    printf("\n");
}

// Chương trình chính
int main() {
    struct Graph* graph = createGraph(4); // Tạo đồ thị với 4 đỉnh
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);

    printGraph(graph); // In đồ thị

    bfs(graph, 2); // Thực hiện BFS từ đỉnh 2
    dfs(graph, 2); // Thực hiện DFS từ đỉnh 2

    // Giải phóng bộ nhớ
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
