#pragma once
#include <initializer_list>
#include <memory>
#include <stdexcept>

namespace linked_list {
    template <typename T>
    class DoublyLinkedList {
    public:
        // constructors
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& other);
        DoublyLinkedList(DoublyLinkedList&& other) noexcept;
        DoublyLinkedList(std::initializer_list<T> il);

        // assignment operators
        DoublyLinkedList& operator=(const DoublyLinkedList& other);
        DoublyLinkedList& operator=(DoublyLinkedList&& other);

        // modifiers
        void push_front(T elem);
        void push_back(T elem);
        void pop_front();
        void pop_back();

        // getters
        T front() const;
        T& front();

        T back() const;
        T& back();

        unsigned int size() const;
        bool empty() const;

        // friend functions
        void swap(DoublyLinkedList& other) noexcept;
        friend class DoublyLinkedListIterator;
    private:
        struct ListNode {
            T value;
            std::unique_ptr<ListNode> next;
            ListNode* prev;

            ListNode() = default;
            ListNode(T val) : value{val}, prev{nullptr}, next{nullptr} {}
            ListNode(T val, ListNode* prev) : value{val}, prev{prev}, next{nullptr} {}
            ListNode(T val, ListNode* prev, ListNode* next)
                : value{val}
                , prev{prev}
                , next{next} {
            }
            ListNode(T val, std::unique_ptr<ListNode> next)
                : value{val}
                , prev{nullptr}
                , next{std::move(next)} {
            }
        };
        std::unique_ptr<ListNode> head_;
        ListNode* tail_;
        int size_;
    public:
        class DoublyLinkedListIterator {
        public:
            using ValueType = T;
            using Pointer = T*;
            using Reference = T&;

            friend DoublyLinkedList<ValueType>;

            Reference operator*() {
                return node->value;
            }

            Pointer operator->() {
                return &node->value;
            }

            DoublyLinkedListIterator& operator++();
            DoublyLinkedListIterator& operator--();
            DoublyLinkedListIterator operator++(int);
            DoublyLinkedListIterator operator--(int);

            bool operator==(const DoublyLinkedListIterator& other) const {
                return node == other.node;
            }
            
            bool operator!=(const DoublyLinkedListIterator& other) const {
                return node != other.node;
            }
        private:
            DoublyLinkedListIterator(ListNode* node) : node{node} {}
            ListNode* node;
        };
        DoublyLinkedListIterator begin() const;
        DoublyLinkedListIterator end() const;
    };

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
    void DoublyLinkedList<T>::pop_front() {
        head_ = std::move(head_->next);
        head_->prev = nullptr;
        size_--;
    }

    template <typename T>
    void DoublyLinkedList<T>::pop_back() {
        if (size_ == 1) {
            pop_front();
            return;
        }
        ListNode* new_end = tail_->prev->prev;
        new_end->next = std::move(tail_->prev->next);
        tail_->prev = new_end;
        size_--;
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

    template <typename T>
    typename linked_list::DoublyLinkedList<T>::DoublyLinkedListIterator& linked_list::DoublyLinkedList<T>::DoublyLinkedListIterator::operator++() {
        node = node->next.get();
        return *this;
    }
}
