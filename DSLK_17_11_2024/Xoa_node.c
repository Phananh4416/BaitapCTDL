#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
    /**
     * @brief là một con trỏ đến kiểu dữ liệu Node. Biến này lưu trữ địa chỉ của nút tiếp theo trong 
     * danh sách liên kết. Nếu nút này là nút cuối cùng trong danh sách thì next sẽ là NULL
     * @attention Tại sao không khai báo struct Node next:
     *           -Kiểu struct node chưa hoàn chỉnh cho đến khi gặp dấu } kết thúc 
     *           -Mỗi struct node sẽ chứa một struct node khác => Bộ nhớ vô hạn 
     *           => Sử dụng con trỏ vì nó không yếu cầu bộ nhớ và có thể trỏ tới các kiểu chưa hoàn 
     *              chỉnh 
     * @attention Tại sao lại không khai báo struct Node *next ở trong hàm main?
     *           -Thực tế câu lệnh này hoàn toàn là hợp lệ và không có lỗi khi run 
     *            Tuy nhiên, next sẽ chỉ là một con trỏ trống, không trỏ tới vùng nhớ hợp lệ 
     */
};

struct Node *taoNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    /**
     * @brief Khai báo con trỏ newNode tới vùng dữ liệu kiểu cấu trúc Node và gán nó với con trỏ cùng kiểu cấu trúc Node
     * trỏ tới vùng nhớ đủ lớn để chứa đối tượng kiểu struct Node 
     */
    newNode->data = data; 
    newNode->next = NULL;
    return newNode;
};
 //Ham xóa nút ở đầu danh sách 
void xoaNutDau(struct Node**head_reference){
    //Kiểm tra nếu danh sách rỗng (con trỏ đầu trỏ tới NULL)
    if(*head_reference == NULL){
        printf("danh sach Node rỗng\n");
        return; //Kết thúc hàm nếu danh sách là rỗng
    }
    //Tại con trỏ lưu trữ nút đầu
    struct Node *temp = *head_reference;
    *head_reference = (*head_reference)->next;// Cập nhật con trỏ đầu danh sách trỏ tới nút tiếp
    free(temp);// Giải phóng bộ nhớ nút đầu 
}
//Hàm xóa nút ở cuối của danh sách 
void xoaNutCuoi(struct Node ** tail_reference){
    if(*tail_reference == NULL){ // Kiểm tra nếu danh sách rỗng 
        printf("danh sach Node rỗng\n");
        return;
    }
    //Kiểm tra nếu danh sách được tạo chỉ có đúng 1 node
    if((*tail_reference)->next == NULL){
        free(*tail_reference); // giải phóng bộ nhớ node đó
        *tail_reference == NULL;// Cập nhật con trỏ đầu thành NULL
        return;
    }
    struct Node*temp = *tail_reference; //Tạo con trỏ tạm thời để duyệt danh sach 
    while (temp->next->next != NULL){ // Duyệt đến nút áp chót ( trong trường hợp nút sau nút tham chiếu không trỏ đến NULL)
        temp = temp->next;             // Thì tiếp tục di chuyển con trỏ đến nút tiếp 
    }
    free(temp->next);// Giải phóng bộ nhớ nút cuối 
    temp -> next = NULL;// Cập nhật con trỏ next nút áp chót thành NULL => Nút áp chót giờ là nút cuối 
}
// Hàm xóa nút có giá trị nhất định 
void xoaSauNut(struct Node **node_ref, int key){
    // Tạo con trỏ tạm thời temp trỏ đến nút đầu danh sach và con trỏ prev tham chiếu trước đó 
    struct Node *temp = *node_ref, *prev;
    // Kiểm tra nếu nút đầu danh sach giờ chứa giá trị cần tìm 
    if(temp != NULL && temp -> data == key){
        // Cập nhật con trỏ danh sachs trỏ tới nút tiếp theo 
        *node_ref = temp->next;
        //giải phóng bộ nhớ nút đầu 
        free(temp);
        return;
    }
    //Duyệt danh sach tìm nút có giá trị cần tìm 
    while(temp != NULL && temp -> data != key){
        prev = temp;// Lưu lại nút trước đó 
        temp = temp -> next; // Di chuyển đến nút tiếp theo 
    }
    if (temp == NULL){
        return; //Kết thúc hàm nếu không tìm thấy 
    }
    // Bỏ qua nút cần xóa bằng cách cập nhật con trỏ next của nút trước đó 
    prev->next = temp -> next;
    //Giải phóng bộ nhớ nút cần xóa 
    free(temp);
}
void inDanhSach(struct Node* head){
    while (head != NULL){
        printf("%d -> ",head->data );
        head = head->next;
    }
    printf(" \n");
}
int main(){
    struct Node* head = taoNode(3);
    head->next = taoNode(4);
    head->next->next = taoNode(5);

    printf("Danh sach lien ket ban dau: ");
    inDanhSach(head);

    //Xóa ban đầu danh sách
    xoaNutDau(&head);
    printf("sau khi xoa nut dau: ");
    inDanhSach(head);
    //Xóa cuối của danh sách
    xoaNutCuoi(&head);
    printf("sau khi xoa nut cuoi: ");
    inDanhSach(head);

    //Xoa sau nut
    int key = 3;
    xoaSauNUt(&head, key);
    printf("sau khi xóa sau nút %d: ", key);
    inDanhSach(head);
    return 0;
}


