#include "list_tests.h"

void TestPushBack() {
    linked_list::DoublyLinkedList<int> ls;
    for (int i = -1000; i < 1000; ++i) {
        ls.push_back(i);
    }
    int i = -1000;
    for (int j : ls) {
        assert(j == i++);
    }
}

void TestPushFront() {
    linked_list::DoublyLinkedList<int> ls;
    for (int i = -1000; i < 1000; ++i) {
        ls.push_front(i);
    }
    int i = 999;
    for (int j : ls) {
        assert (j == i--);
    }
}

void TestPushAndPop() {
    linked_list::DoublyLinkedList<int> ls;
    for (int i = 0; i < 5; ++i) {
        ls.push_back(i);
    }
    for (int i = -1; i >= -5; --i) {
        ls.push_front(i);
    }
    int i = -5;
    for (int j : ls) {
        assert (j == i++);
    }
    ls.pop_front();
    i = -4;
    for (int j : ls) {
        assert (j == i++);
    }
    ls.pop_back();
    ls.pop_back();
    i = -4;
    for (int j : ls) {
        assert (j == i++);
    }
    assert (i == 3);
    int sz = 0;
    while (!ls.empty()) {
        ls.pop_back();
        sz++;
    }
    assert (sz = 7);
}

void TestInitializers() {
    linked_list::DoublyLinkedList<int> ls{1,2,3,4,5};
    int i = 1;
    for (int j : ls) {
        assert(j == i++);
    }
    auto ls2 = ls;
    i = 1;
    for (int j : ls2) {
        assert (j == i++);
    }
    auto ls3 = std::move(ls2);
    i = 1;
    for (int j : ls3) {
        assert (j == i++);
    }
    int len = 0;
    for (int j : ls2) {
        len++;
    }
    assert (len == 0);
}

void TestBeginAndEnd() {
    linked_list::DoublyLinkedList<int> ls{1,2,3,4,5};
    int i = 1;
    for (auto it = ls.begin(); it != ls.end(); ++it) {
        assert (*it == i++);
    }
    assert (i == 6);
    i = 1;
    auto it = ls.begin();
    for (; it != ls.end(); it++) {
        assert (*it == i++);
    }
    assert (i == 6);
    it--;
    --it;
    assert (*it == 4);
}

void TestSizeAndEmpty() {
    linked_list::DoublyLinkedList<int> ls{1,2,3};
    assert (ls.size() == 3);
    assert (!ls.empty());
    linked_list::DoublyLinkedList<int> ls2;
    assert (ls2.size() == 0);
    assert (ls2.empty());
    ls2.push_front(7123);
    assert (ls2.size() == 1);
    assert (!ls2.empty());
    ls2.pop_back();
    assert (ls2.size() == 0);
    assert (ls2.empty());
    ls2.push_back(161236);
    assert (ls2.size() == 1);
    for (int i = 0; i < 5; ++i) {
        ls2.push_back(i);
    }
    assert (ls2.size() == 6);
    ls.pop_back();
    assert (ls.size() == 2);
}
