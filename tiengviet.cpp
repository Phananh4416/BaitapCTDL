#include <iostream>
#include <string>

using namespace std;

// Cấu trúc Node để lưu trữ từ và số lần xuất hiện
struct WordNode {
    string word;
    int count;
    WordNode* next;

    WordNode(string w) : word(w), count(1), next(nullptr) {}
};

// Cấu trúc danh sách liên kết đơn để quản lý các từ
struct WordLinkedList {
    WordNode* head;

    WordLinkedList() : head(nullptr) {}

    // Hàm thêm từ vào danh sách
    void insertWord(const string& word) {
        WordNode* current = head;
        WordNode* prev = nullptr;
        while (current) {
            if (current->word == word) {
                current->count++;
                return;
            }
            prev = current;
            current = current->next;
        }
        WordNode* newNode = new WordNode(word);
        if (prev) {
            prev->next = newNode;
        } else {
            head = newNode;
        }
    }

    // Hàm in danh sách từ
    void printList() const {
        WordNode* current = head;
        while (current) {
            cout << "Tu: " << current->word << ", So lan xuat hien: " << current->count << endl;
            current = current->next;
        }
    }

    // Hàm tìm từ xuất hiện nhiều nhất
    string findMostFrequentWord() const {
        WordNode* current = head;
        string mostFrequentWord;
        int maxCount = 0;
        while (current) {
            if (current->count > maxCount) {
                maxCount = current->count;
                mostFrequentWord = current->word;
            }
            current = current->next;
        }
        return mostFrequentWord;
    }

    // Hàm loại bỏ từ láy
    void removeReduplicativeWords() {
        WordNode* current = head;
        WordNode* prev = nullptr;
        while (current) {
            if (current->word.length() >= 4 && current->word.substr(0, current->word.length() / 2) == current->word.substr(current->word.length() / 2)) {
                cout << "Loai bo tu lay: " << current->word << endl;
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                current = prev ? prev->next : head;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Hàm đếm số từ vựng
    int countWords() const {
        int count = 0;
        WordNode* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

int main() {
    WordLinkedList wordList;

    // Nhập câu tiếng Việt từ người dùng
    cout << "Nhap cau tieng Viet: ";
    string sentence;
    getline(cin, sentence);  // Đọc toàn bộ dòng văn bản

    // Tách các từ từ câu nhập vào và chèn vào danh sách
    size_t pos = 0;
    string delimiter = " ";

    while ((pos = sentence.find(delimiter)) != string::npos) {
        string word = sentence.substr(0, pos);
        wordList.insertWord(word);
        sentence.erase(0, pos + delimiter.length());
    }
    wordList.insertWord(sentence); // Thêm từ cuối cùng

    cout << "Danh sach tu ban dau:\n";
    wordList.printList();

    string mostFrequentWord = wordList.findMostFrequentWord();
    cout << "Tu xuat hien nhieu nhat: " << mostFrequentWord << endl;

    wordList.removeReduplicativeWords();
    cout << "Danh sach tu sau khi loai bo tu lay:\n";
    wordList.printList();

    int wordCount = wordList.countWords();
    cout << "So tu trong cau: " << wordCount << endl;

    return 0;
}
