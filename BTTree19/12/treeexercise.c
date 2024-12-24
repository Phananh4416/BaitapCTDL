#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    char title[100]; // Tiêu đề của mục 
    int pages; // Số trang của mục
    struct Node *firstChild; // Con đầu tiên
    struct Node *nextSibling; // Anh chị em kế tiếp
} Node;

// Tạo một node mới
Node* createNode(const char* title, int pages) {
    Node* newNode = (Node*)malloc(sizeof(Node));hh
    strcpy(newNode->title, title);
    newNode->pages = pages;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Thêm một node con
void addChild(Node* parent, Node* child) {
    if (parent->firstChild == NULL) {
        parent->firstChild = child;
    } else {
        Node* current = parent->firstChild;
        while (current->nextSibling != NULL) {
            current = current->nextSibling;
        }
        current->nextSibling = child;
    }
}

// Đếm số chương của cuốn sách
int countChapters(Node* root) {
    int count = 0;
    Node* current = root->firstChild;
    while (current != NULL) {
        count++;
        current = current->nextSibling;
    }
    return count;
}

// Tìm chương dài nhất của cuốn sách
Node* findLongestChapter(Node* root) {
    Node* longest = NULL;
    Node* current = root->firstChild;
    while (current != NULL) {
        if (longest == NULL || current->pages > longest->pages) {
            longest = current;
        }
        current = current->nextSibling;
    }
    return longest;
}

// Tìm và xóa một mục khỏi sách, cập nhật lại số trang
void deleteNode(Node* root, const char* title) {
    Node* parent = NULL;
    Node* current = root->firstChild;
    Node* prev = NULL;
    while (current != NULL && strcmp(current->title, title) != 0) {
        prev = current;
        if (current->firstChild != NULL) {
            parent = current;
            current = current->firstChild;
        } else {
            current = current->nextSibling;
        }
    }
    if (current != NULL) {
        // Tìm thấy mục cần xóa
        if (prev != NULL) {
            prev->nextSibling = current->nextSibling;
        } else if (parent != NULL) {
            parent->firstChild = current->nextSibling;
        } else {
            root->firstChild = current->nextSibling;
        }
        free(current);
    }
}

// Hàm hiển thị cây để kiểm tra
void displayTree(Node* root, int level) {
    if (root == NULL) return;
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("%s (%d pages)\n", root->title, root->pages);
    displayTree(root->firstChild, level + 1);
    displayTree(root->nextSibling, level);
}

int main() {
    // Tạo root node (cuốn sách)
    Node* book = createNode("Book Title", 0);

    // Thêm các chương
    Node* chapter1 = createNode("Chapter 1", 20);
    addChild(book, chapter1);
    Node* chapter2 = createNode("Chapter 2", 15);
    addChild(book, chapter2);

    // Thêm các section cho Chapter 1
    Node* section1 = createNode("Section 1.1", 5);
    addChild(chapter1, section1);
    Node* section2 = createNode("Section 1.2", 7);
    addChild(chapter1, section2);

    // Đếm số chương
    printf("Number of chapters: %d\n", countChapters(book));

    // Tìm chương dài nhất
    Node* longestChapter = findLongestChapter(book);
    if (longestChapter != NULL) {
        printf("Longest chapter: %s with %d pages\n", longestChapter->title, longestChapter->pages);
    }

    // Hiển thị cây trước khi xóa
    printf("Tree before deletion:\n");
    displayTree(book, 0);

    // Xóa một mục
    deleteNode(book, "Section 1.2");

    // Hiển thị cây sau khi xóa
    printf("Tree after deletion:\n");
    displayTree(book, 0);

    return 0;
}
