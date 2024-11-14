#include <iostream>
using namespace std;

#define MAX_TERMS 100 // Số lượng hạng tử tối đa  

typedef struct {  
    int coefficient; // Hệ số  
    int exponent;    // Số mũ  
} Term;  

// Hàm nhập một đa thức 
void inputPolynomial(Term poly[], int* termCount) {  
    int coefficient, exponent;  
    *termCount = 0;  
    while (1) {  
        cout << "Nhap he so(0 de dung): ";  
        cin >> coefficient;  
        if (coefficient == 0) {  
            break;  
        }  
        cout << "Nhap so mu: ";  
        cin >> exponent;  
        if (*termCount < MAX_TERMS) {  
            poly[*termCount].coefficient = coefficient;  
            poly[*termCount].exponent = exponent;  
            (*termCount)++;  
        } else {  
            cout << "Dat so luong hang tu toi da!\n";  
            break;  
        }  
    }  
}  

void printPolynomial(Term poly[], int termCount) {  
    if (termCount == 0) {  
        cout << "0\n";  
        return;  
    }  
    
    for (int i = 0; i < termCount; i++) {  
        if (i > 0) {  
            cout << " + ";  
        }  
        cout << poly[i].coefficient << "x^" << poly[i].exponent;  
    }  
    cout << ";\n";  
} 

void addPolynomials(Term poly1[], int termCount1, Term poly2[], int termCount2, Term result[], int* resultCount) {  
    *resultCount = 0;  
    int i = 0, j = 0;  
    
    while (i < termCount1 || j < termCount2) {  
        if (i < termCount1 && (j >= termCount2 || poly1[i].exponent > poly2[j].exponent)) {  
            result[*resultCount] = poly1[i];  
            (*resultCount)++;  
            i++;  
        } else if (j < termCount2 && (i >= termCount1 || poly2[j].exponent > poly1[i].exponent)) {  
            result[*resultCount] = poly2[j];  
            (*resultCount)++;  
            j++;  
        } else {  
            result[*resultCount].exponent = poly1[i].exponent;  
            result[*resultCount].coefficient = poly1[i].coefficient + poly2[j].coefficient;  
            (*resultCount)++;  
            i++;  
            j++;  
        }  
    }  
}  

int main() {  
    Term f[MAX_TERMS], g[MAX_TERMS], h[MAX_TERMS];  
    int termCountF, termCountG, termCountH;  
    cout << "Nhap da thuc f(x):\n";  
    inputPolynomial(f, &termCountF); 
    cout << "Nhap da thuc g(x):\n";  
    inputPolynomial(g, &termCountG);  
    
    cout << "f(x) = ";  
    printPolynomial(f, termCountF);   
    cout << "g(x) = ";  
    printPolynomial(g, termCountG);    
    
    addPolynomials(f, termCountF, g, termCountG, h, &termCountH);  
    
    cout << "h(x) = f(x) + g(x) = ";  
    printPolynomial(h, termCountH);  
    
    // Debug: In ra các vị trí lưu trữ các phần tử trong đa thức
    cout << "\nVi tri luu tru cac phan tu trong da thuc f(x):\n";
    for (int i = 0; i < termCountF; ++i) {
        cout << "f[" << i << "] = " << &f[i] << " (He so: " << f[i].coefficient << ", So mu: " << f[i].exponent << ")\n";
    }

    cout << "\nVi tri luu tru cac phan tu trong da thuc g(x):\n";
    for (int i = 0; i < termCountG; ++i) {
        cout << "g[" << i << "] = " << &g[i] << " (He so: " << g[i].coefficient << ", So mu: " << g[i].exponent << ")\n";
    }

    cout << "\nVi tri luu tru cac phan tu trong da thuc h(x):\n";
    for (int i = 0; i < termCountH; ++i) {
        cout << "h[" << i << "] = " << &h[i] << " (He so: " << h[i].coefficient << ", So mu: " << h[i].exponent << ")\n";
    }

    return 0;  
}  
