#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa một node trong cây biểu thức
struct ExprTree {
    char value[20];           // Giá trị node (toán hạng hoặc toán tử)
    struct ExprTree* left;    // Con trái
    struct ExprTree* right;   // Con phải
};

// Kiểu dữ liệu mới cho node cây
typedef struct ExprTree TreeNode;

// Hàm khởi tạo node mới
TreeNode* newTreeNode(const char* val) {
    TreeNode* node = malloc(sizeof(TreeNode));  // Cấp phát bộ nhớ cho node
    strcpy(node->value, val);                  // Sao chép chuỗi vào giá trị node
    node->left = NULL;                         // Ban đầu chưa có con trái
    node->right = NULL;                        // Ban đầu chưa có con phải
    return node;
}

// Hàm duyệt cây theo thứ tự trước (Pre-order)
void preOrderTraversal(TreeNode* node) {
    if (!node) return;                      // Nếu node rỗng thì dừng
    printf("%s ", node->value);             // In giá trị của node
    preOrderTraversal(node->left);          // Duyệt con trái
    preOrderTraversal(node->right);         // Duyệt con phải
}

// Hàm duyệt cây theo thứ tự giữa (In-order)
void inOrderTraversal(TreeNode* node) {
    if (!node) return;                      // Nếu node rỗng thì dừng
    inOrderTraversal(node->left);           // Duyệt con trái
    printf("%s ", node->value);             // In giá trị của node
    inOrderTraversal(node->right);          // Duyệt con phải
}

// Hàm duyệt cây theo thứ tự sau (Post-order)
void postOrderTraversal(TreeNode* node) {
    if (!node) return;                      // Nếu node rỗng thì dừng
    postOrderTraversal(node->left);         // Duyệt con trái
    postOrderTraversal(node->right);        // Duyệt con phải
    printf("%s ", node->value);             // In giá trị của node
}

// Hàm tạo cây biểu thức từ biểu thức "a + 5*b/c - c^8 + d*e^(1/2)"
TreeNode* buildTree() {
    // Tạo các node cây con
    TreeNode* d = newTreeNode("d");
    TreeNode* e = newTreeNode("e");
    TreeNode* eExp = newTreeNode("^");
    eExp->left = e;
    eExp->right = newTreeNode("1/2");

    TreeNode* deMul = newTreeNode("*");
    deMul->left = d;
    deMul->right = eExp;

    TreeNode* five = newTreeNode("5");
    TreeNode* b = newTreeNode("b");
    TreeNode* bcMul = newTreeNode("*");
    bcMul->left = five;
    bcMul->right = b;

    TreeNode* c = newTreeNode("c");
    TreeNode* divBC = newTreeNode("/");
    divBC->left = bcMul;
    divBC->right = c;

    TreeNode* c2 = newTreeNode("c");
    TreeNode* cExp = newTreeNode("^");
    cExp->left = c2;
    cExp->right = newTreeNode("8");

    TreeNode* a = newTreeNode("a");
    TreeNode* addExpr = newTreeNode("+");
    addExpr->left = a;
    addExpr->right = divBC;

    TreeNode* subExpr = newTreeNode("-");
    subExpr->left = addExpr;
    subExpr->right = cExp;

    TreeNode* finalExpr = newTreeNode("+");
    finalExpr->left = subExpr;
    finalExpr->right = deMul;

    return finalExpr; // Trả về node gốc
}

int main() {
    // Tạo cây biểu thức
    TreeNode* root = buildTree();

    // In cây theo ba kiểu duyệt
    printf("Duyệt Pre-order: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Duyệt In-order: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Duyệt Post-order: ");
    postOrderTraversal(root);
    printf("\n");

    return 0;
}
