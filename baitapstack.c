#include <stdio.h>
#include <stdlib.h>

// Ban đầu, định nghĩa cấu trúc của thanh gỗ với các thuộc tính
// là loại gỗ, kích thước, tuổi gỗ.
typedef struct{
    char kieugo[60];
    float kichthuoc;
    int tuoigo;
} Go;

//Định nghĩa node của ngăn xếp
typedef struct {
    Go data;
    struct Node* next;
} Node;

// Định nghĩa ngắn xếp 
typedef struct {
    Node *top; // Con trỏ duyệt đỉnh của ngăn xếp
} NganXep;
//Khởi tạo 1 ngăn xesp
void khoitao(NganXep *t){
    t ->top = NULL;
}
// Ham kiểm tra xem ngăn xếp có rỗng hay không, tách biệt với hàm khởi tạo
// để code tác biệt hơn
int kiemtraRong(NganXep *t){
    return t->top == NULL;
}
//Thêm phần tử (Gỗ) vào ngăn xếp bằng cách khởi tạo mảng động
int them(NganXep *t, Go value){
    Node *newnode = (Node *)malloc(sizeof(Node));
    //Neu không khởi tạo được phần tử tiếp theo sẽ thoát chương trình
    if(!newnode){
        return 0;
    }
    newnode->data = value; // Gán giá trị thanh gỗ cho dữ liệu mới
    newnode->next = t->top;// Liên kết node mới với phần tử đỉnh hiện tại 
    t->top = newnode; //Cập nhật đỉnh của stack để trỏ đến node mới
    return 1; // Việc cập nhật thành công
}
//Loại bỏ phần tử khỏi ngăn xếp
int xoa(NganXep *t, Go *value){
    if(kiemtraRong(t)){
        return 0; // Ngăn xếp rỗng 
    }
    Node *temp = t->top;// tạo con trỏ tạm thời gán đỉnh
    *value = temp -> data;// lấy giá trị phần tử đỉnh gán cho value
    t->top = t->top->next;// Cập nhật đỉnh ngăn xếp để trỏ tới phần tử tiếp theo
    free(temp);// Giải phóng bộ nhớ cấp phát cho phần tử mà con trỏ đỉnh đang trỏ tới cũ
    return 1;// Việc loại bỏ 1 phần tử đã thành công
}
//trong trường hợp lấy giá trị phần tử đỉnh của stack mà không bỏ
int laygiatri(NganXep *t, Go *value){
    if(kiemtraRong(t)){
        return 0;// Ngăn xếp rỗng
    }
    *value = t->top->data;
    return 1;
}
//In ngăn xếp
void inNganXep(NganXep *t){
    Node *current = t->top;
    while(current != NULL){
        printf("Loai go: %s\n", current ->data.kieugo);
        printf("Kich thuoc : %.2f\n", current ->data.kichthuoc);
        printf("Loai go: %d\n", current ->data.tuoigo);
        current = current -> next;
    }
    printf("\n");
}
//Đếm số lượng thanh gỗ có cùng tuổi gỗ 
int demcungtuoi(NganXep *t, int tuoigo){
    int count = 0;// Khởi tạo biến đếm số lượng thanh gỗ có cùng tuổi
    Node *current = t->top;// Tạo con trỏ current duyệt từ đỉnh ngăn xếp
    while (current != NULL){
        if(current ->data.tuoigo == tuoigo){// So sánh tuổi thanh gỗ hiện taị với biến tuoigo
            count++;// Nếu khớp tăng biến lên 1
        }
        current = current -> next;// Di chuyển con trỏ đến phần tử kế tiếp để duyệt 
    }
    return count;// Trả về tổng số lượng thanh gỗ cùng tuổi 
}
int main(){
    NganXep khogo;// Khái báo ngăn xếp
    khoitao(&khogo);// Khởi tạo ngăn xếp
    //Khái báo các dòng gỗ với thuộc tính được định nghĩa trên
    Go dong1 = {"thong", 3.5, 30};
    Go dong2 = {"soi", 2, 40};
    Go dong3 = {"bachduong", 5, 10};
    Go dong4 = {"thong", 2.5, 20};
    // Thêm thanh  gỗ vào ngăn xếp
    them(&khogo, dong1);
    them(&khogo, dong2);
    them(&khogo, dong3);
    them(&khogo, dong4);
    printf("Ta duoc danh sach kho go la: \n");
    inNganXep(&khogo);
    int age = 20;// khai báo tuổi gỗ cần kiểm tra 
    int count = demcungtuoi(&khogo, age);// Đếm số lượgn thanh gỗ cùng tuổi 
    printf("So luong thanh go co tuoi go %d la: %d\n", age, count);
    return 0;
}

