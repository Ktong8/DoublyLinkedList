#include "doubly_linked_list.h"

namespace linked_list {
    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList()
        : size_{0}
        , head_{std::make_unique<ListNode>()}
        , tail_{head_.get()} {
    }

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : size_(0) {
        for (T val : other) {
            push_back(val);
        }
    }

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept
        : size_(other.size_)
        , head_(std::move(other.head))
        , tail_(other.tail_) {
    }

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

    template <typename T>
    void DoublyLinkedList<T>::push_front(T elem) {
        head_ = std::make_unique<ListNode>(elem, nullptr, head_.release());
        if (!size_++) {
            tail_->prev = head_.get();
        } else {
            head_->next->prev = head_.get();
        }
    }

    template <typename T>
    void DoublyLinkedList<T>::push_back(T elem) {
        if (!size_) {
            push_front(elem);
            return;
        }
        tail_->prev->next.release();
        tail_->prev->next = std::make_unique<ListNode>(elem, tail_->prev, tail_);
        tail_->prev = tail_->prev->next.get();
        size_++;
    }
}


int main() {
    return 0;
}
