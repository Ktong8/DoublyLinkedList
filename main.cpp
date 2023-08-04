#include "doubly_linked_list.h"
#include <iostream>

int main() {
    linked_list::DoublyLinkedList<int> linkedList;
    linkedList.push_back(2);
    linkedList.push_back(4);
    for (int i : linkedList) {
        std::cout << i << ", ";
    }
    std::cout << "\n";
}
