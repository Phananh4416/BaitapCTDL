#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>

struct FileNode {
    std::string fileName;
    size_t fileSize;
    std::time_t modificationTime;
    FileNode* next;

    FileNode(std::string name, size_t size, std::time_t time)
        : fileName(name), fileSize(size), modificationTime(time), next(nullptr) {}
};

struct FileLinkedList {
    FileNode* head;

    FileLinkedList() : head(nullptr) {}

    void insertFileSorted(const std::string& name, size_t size, std::time_t time) {
        FileNode* newNode = new FileNode(name, size, time);
        if (!head || difftime(head->modificationTime, time) > 0) {
            newNode->next = head;
            head = newNode;
        } else {
            FileNode* current = head;
            while (current->next && difftime(current->next->modificationTime, time) < 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    size_t getTotalSize() const {
        size_t totalSize = 0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    void trimToSize(size_t maxSize) {
        while (getTotalSize() > maxSize) {
            FileNode* minNode = head;
            FileNode* minPrev = nullptr;
            FileNode* current = head;
            FileNode* prev = nullptr;
            while (current) {
                if (current->fileSize < minNode->fileSize) {
                    minNode = current;
                    minPrev = prev;
                }
                prev = current;
                current = current->next;
            }
            if (minPrev) {
                minPrev->next = minNode->next;
            } else {
                head = minNode->next;
            }
            delete minNode;
        }
    }

    void printList() const {
        FileNode* current = head;
        while (current) {
            std::cout << "File: " << current->fileName << ", Size: " << current->fileSize 
                      << " bytes, Modified: " << std::ctime(&current->modificationTime);
            current = current->next;
        }
    }
};

void copyFileAndInsertSorted(FileLinkedList& list, const std::string& source, const std::string& destination, size_t size, std::time_t time) {
    #ifdef _WIN32
        std::system(("copy " + source + " " + destination).c_str());
    #else
        std::system(("cp " + source + " " + destination).c_str());
    #endif
    list.insertFileSorted(destination, size, time);
}

int main() {
    FileLinkedList fileList;

    fileList.insertFileSorted("file1.txt", 1000, std::time(nullptr) - 100);
    fileList.insertFileSorted("file2.txt", 2000, std::time(nullptr) - 200);
    fileList.insertFileSorted("file3.txt", 500, std::time(nullptr) - 50);

    std::cout << "Current file list:\n";
    fileList.printList();

    copyFileAndInsertSorted(fileList, "source_file.txt", "destination_file.txt", 1500, std::time(nullptr) - 150);

    std::cout << "\nFile list after copying:\n";
    fileList.printList();

    fileList.trimToSize(static_cast<size_t>(32) * 1024 * 1024 * 1024);

    std::cout << "\nFile list after trimming to 32GB:\n";
    fileList.printList();

    return 0;
}
