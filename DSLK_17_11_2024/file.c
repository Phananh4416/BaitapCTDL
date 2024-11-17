#include <stdio.h>
#include <stdlib.h>

//Định nghĩa cấu trúc file
typedef struct {
    char name[50];
    int size;
    int date;// giả định dưới dạng yyyymmdd
} FileInfo;
void bubbleSort(FileInfo files[], int n) {
    int i, j;
    int swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0; 
        for (j = 0; j < n - i - 1; j++) {
            if (files[j].size > files[j + 1].size ||
               (files[j].size == files[j + 1].size && files[j].date > files[j + 1].date)) {
                // Hoán đổi 
                FileInfo temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
                swapped = 1; 
            }
        }
        if (!swapped) break;
    }
}
//Hàm so sánh để sắp xếp các tập tin theo dung lượng
int sosanh(const void *a, const void*b){
    FileInfo * fileA = (FileInfo*)a;
    FileInfo * fileB = (FileInfo*)b;
    //Nếu dung lượng bằng nhau, so sánh theo thời gian lưu trữ
    if(fileA->size == fileB->size){
        return fileA->date - fileB->date;
        //Sắp xếp tăng dần theo thời gian lưu
    }
    //Sắp xếp theo dung lượng
    return fileA->size - fileB->size;
}
//Hàm xóa các tập tin có dung lượng bé nhất và thời gian lưu lâu nhất
void DelSmallestandOldest(FileInfo files[], int* n){
    if (*n == 0){
        printf("khong co tap tin de xoa\n");
        return ;
    }
    int minSize = files[0].size;//Dung lượgn nhỏ nhất 
    int oldestDate = files[0].date; //Thời gian lưu lâu nhất
    int oldest = 0;//Vị trí tập tin cần xóa
    //Tìm tập tin có dung lượng bé nhất và thời gian lâu nhất
    for(int i = 1; i<*n;i++){
        if(files[i].size==minSize && files[i].date<oldestDate){
            oldestDate =files[i].date;//Cập nhật thời gian lưu lâu nhất
            oldest = i;//Cập nhạt vị trí cần xóa
        }
        else if(files[i].size<minSize){
            minSize = files[i].size;//Cập nhật dung lượng nhỏ nhất
            oldestDate = files[i].date;//Cập nhật thời gian lưu lâu nhất
            oldest = i; //Cập nhật vị trí cần xóa 
        }
    }
    //Xóa tập tin bằng cách dịch các phần tử còn lại lên trên
    for(int i = oldest;i<*n-1;i++){
        files[i] = files[i+1];
    }
    (*n )--; //giảm số lượng tập tin
}
//hàm in danh sách tập tin
void printList(FileInfo files[], int n){
    for(int i = 0;i<n;i++){
        printf("Name: %s, Capacity: %d, Date: %d\n", files[i].name, files[i].size, files[i].date);
    }
}

int main(){
    int n = 4;// số lượng tập tin
    FileInfo files[5] = {
        {"week1.txt" , 100, 20241711},
        {"week2.txt" , 200, 20241611},
        {"week3.txt" , 150, 20241511},
        {"week4.txt" , 50, 20241411},
    };
    //thuật toán sắp xếp
    bubbleSort(files, n);
    //In danh sách tập tin sau khi sắp xếp
    printf("Danh sach tap tin sau khi sap xep: \n");
    printList(files, n);
    //Xóa tập tin có dung lượng bé nhất và thời gian lưu lâu nhất
    DelSmallestandOldest(files, &n);
    //In danh sách tập tin sau khi xóa
    printf("\nDanh sach tap tin sau khi xoa: \n");
    printfList(files, n);
    return 0;
}