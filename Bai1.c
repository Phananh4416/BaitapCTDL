#include<stdio.h>

// Dinh nghia cac mau thanh cac so 0,1,2
enum {Red = 0, 
      White = 1, 
      Blue = 2};

int nhapMau(int mau[], int n){
    printf("Nhap danh sach cac mau: \n");
    for(int i = 0; i < n; i++){
        scanf("%d", &mau[i]);
        if(mau[i] < Red || mau[i] > Blue){    //Neu mau nhap vao khong phai trong 3 mau tren
            printf("Mau khong hop le\n");
            return 0;  // Tra lai gia tri 0 de the hien loi 
        }
    }
    return 1;  // Tra lai gia tri 1 de the hien thanh cong
}

// Su dung Bubble Sort(Sap xep noi bot) de sap xep mang mau gom cac mau theo thu tu tang dan
void sapxepMau(int mau[], int n){
    int temp;
    for(int i = 0; i < n; i++){                 //So lan lap qua toan bo mang
        for(int j = 0; j < n - i - 1; j++){     // Vòng lặp này duyệt qua các phần tử còn lại chưa được sắp xếp của mảng. Sau mỗi lần lặp ngoài (ứng với giá trị i), một phần tử đã được sắp xếp và không cần so sánh nữa. Vì thế, n - i - 1 giới hạn số lần so sánh.
            if(mau[j] > mau[j+1]){
                temp = mau[j];
                mau[j] = mau[j+1];              //Nếu phần tử tại vị trí j lớn hơn phần tử tại j+1, hai phần tử này sẽ được hoán đổi. 
                mau[j+1] = temp;
            }
        }
    }
}

void hienthiMau(int arr[], int n){
    printf("Day mau da duoc sap xep: ");
    for(int i = 0; i < n; i++){     // Lap qua toan bo gia tri da duoc sap xep
        switch(arr[i]){
            case Red:
                printf("Red ");
                break;
            case White:
                printf("White ");   // In ra mau tuong ung
                break;
            case Blue:
                printf("Blue ");
                break;
        }
    }
    printf("\n");
}

int main(){
    printf("Nhap so luong mau: ");
    int n;
    scanf("%d", &n);
    
    int mau[n];
    
    if(nhapMau(mau, n)){
        sapxepMau(mau, n);
        hienthiMau(mau, n);
    }
    else{
        printf("Nhap lai cac mau cho dung!\n");  // Nhap lai gia tri
        nhapMau(mau, n);
    }

    return 0;
}
