#include "doubly_linked_list.h"

namespace linked_list {
    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList() : size_(0), head_(nullptr), tail_(nullptr) {}

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : size_(0) {
        for (T val : other) {
            push_back(val);
        }
    }

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept : size_(other.size_), head_(std::move(other.head)), tail_(other.tail_) {}

    template <typename T>
    DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> il) : size_(il.size()) {
        for (T val : il) {
            push_back(val);
        }
    }

    template <typename T>
    DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
        size_ = 0;
        head_.release();
        tail_ = nullptr;
        for (T val : other) {
            push_back(val);
        }
        return *this;
    }

    template <typename T>
    DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& other) {
        size_ = other.size_;
        head_ = std::move(other.head_);
        tail_ = other.tail_;
    }


}


int main() {
    return 0;
}
