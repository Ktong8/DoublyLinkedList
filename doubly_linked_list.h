#pragma once
#include <initializer_list>
#include <memory>

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

        // setters
        void push_front(T elem);
        void push_back(T elem);

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
            ListNode(T val, std::unique_ptr<ListNode> next) : value{val}, prev{nullptr}, next{std::move(next)} {}
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
                return node->val;
            }

            Pointer operator->() {
                return &node->val;
            }

            DoublyLinkedListIterator& operator++();
            DoublyLinkedListIterator& operator--();
            DoublyLinkedListIterator& operator++(int);
            DoublyLinkedListIterator& operator--(int);

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
}
