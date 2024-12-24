#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node của cây AVL
typedef struct AVLNode {
    int data;  // Dữ liệu của node
    int height;  // Chiều cao của node
    struct AVLNode* left;  // Con trái
    struct AVLNode* right;  // Con phải
} AVLNode;

// Hàm tạo node mới
AVLNode* createNode(int data) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = data;
    newNode->height = 1;  // Ban đầu node có chiều cao là 1
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm lấy chiều cao của node
int height(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Hàm lấy giá trị lớn nhất trong hai số
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Xoay phải
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Trả về node mới
    return x;
}

// Xoay trái
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), y->right) + 1;

    // Trả về node mới
    return y;
}

// Hàm lấy hệ số cân bằng của node
int getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

// Chèn một node vào cây AVL
AVLNode* insertNode(AVLNode* node, int data) {
    // 1. Thực hiện chèn như cây BST
    if (node == NULL) return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else // Trùng lặp dữ liệu không cho phép
        return node;

    // 2. Cập nhật chiều cao của node tổ tiên
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Lấy hệ số cân bằng của node tổ tiên để kiểm tra xem node có bị mất cân bằng không
    int balance = getBalance(node);

    // Nếu node bị mất cân bằng, có 4 trường hợp xảy ra

    // Trường hợp Left Left
    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    // Trường hợp Right Right
    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    // Trường hợp Left Right
    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Hàm duyệt cây theo thứ tự giữa (Inorder)
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Hàm duyệt cây theo thứ tự trước (Preorder)
void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Hàm duyệt cây theo thứ tự sau (Postorder)
void postorderTraversal(AVLNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    AVLNode* root = NULL;

    // Mảng đầu vào
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Chèn từng phần tử và in cây AVL theo các phép duyệt sau mỗi lần chèn
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
        printf("Inorder sau khi chen %d: ", arr[i]);
        inorderTraversal(root);
        printf("\n");

        printf("Preorder sau khi chen %d: ", arr[i]);
        preorderTraversal(root);
        printf("\n");

        printf("Postorder sau khi chen %d: ", arr[i]);
        postorderTraversal(root);
        printf("\n\n");
    }

    return 0;
}
