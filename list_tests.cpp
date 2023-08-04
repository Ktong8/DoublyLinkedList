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
