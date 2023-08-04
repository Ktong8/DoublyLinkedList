#include "doubly_linked_list.h"
#include <stdexcept>

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
    
    template <typename T>
    T DoublyLinkedList<T>::front() const {
        if (!size_) {
            throw std::out_of_range("Cannot get front of empty linked list");
        }
        return head_->val;
    }

    template <typename T>
    T& DoublyLinkedList<T>::front() {
        if (!size_) {
            throw std::out_of_range("Cannot get front of empty linked list");
        }
        return head_->val;
    }

    template <typename T>
    T DoublyLinkedList<T>::back() const {
        if (!size_) {
            throw std::out_of_range("Cannot get back of empty linked list");
        }
        return tail_->prev->val;
    }

    template <typename T>
    T& DoublyLinkedList<T>::back() {
        if (!size_) {
            throw std::out_of_range("Cannot get back of empty linked list");
        }
        return tail_->prev->val;
    }

    template <typename T>
    unsigned int DoublyLinkedList<T>::size() const {
        return size_;
    }

    template <typename T>
    bool DoublyLinkedList<T>::empty() const {
        return !size_;
    }

    template <typename T>
    void DoublyLinkedList<T>::swap(DoublyLinkedList& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
    }

    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator& DoublyLinkedList<T>::DoublyLinkedListIterator::operator++() {
        node = node->next.get();
        return *this;
    }

    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator& DoublyLinkedList<T>::DoublyLinkedListIterator::operator--() {
        node = node->prev;
        return *this;
    }

    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator DoublyLinkedList<T>::DoublyLinkedListIterator::operator++(int) {
        DoublyLinkedListIterator tmp = *this;
        node = node->next.get();
        return tmp;
    }

    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator DoublyLinkedList<T>::DoublyLinkedListIterator::operator--(int) {
        DoublyLinkedListIterator tmp = *this;
        node = node->prev;
        return tmp;
    }
    
    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator DoublyLinkedList<T>::begin() const {
        DoublyLinkedListIterator tmp{head_.get()};
        return tmp;
    }

    template <typename T>
    typename DoublyLinkedList<T>::DoublyLinkedListIterator DoublyLinkedList<T>::end() const {
        DoublyLinkedListIterator tmp{tail_};
        return tmp;
    }
}


int main() {
    return 0;
}
