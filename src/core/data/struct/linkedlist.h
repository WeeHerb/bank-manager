//
// Created by mslxl on 12/6/2022.
//


#pragma once

#include<memory>
#include<cassert>


template<typename T>
struct LinkedListNode {
    T data;
    LinkedListNode<T> *next;
    LinkedListNode<T> *prev;

    explicit LinkedListNode(T data) : data(std::move(data)), next(nullptr), prev(nullptr) {

    }
};

template<typename T>
class LinkedList;

template<typename T>
class LinkedListIter : public std::iterator<std::forward_iterator_tag, T> {

public:
    using value_tpye = T;
    using reference = T &;
    using pointer = LinkedListNode<T> *;

    explicit LinkedListIter(pointer init) : Iter(init), end(false) {
    }

    bool operator==(const LinkedListIter &rhs) const {
        return Iter == rhs.Iter && end == rhs.end;
    }

    bool operator!=(const LinkedListIter &rhs) const {
        return Iter != rhs.Iter || end != rhs.end;
    }

    LinkedListIter &operator++() {
        if (Iter->next == nullptr) {
            end = true;
            return *this;
        }
        Iter = Iter->next;
        return *this;
    }

    LinkedListIter &operator--() {
        if (end) {
            end = false;
            return *this;
        }
        Iter = Iter->prev;
        return *this;
    }

    reference operator*() {
        assert(!end);
        return Iter->data;
    }

    T *operator->() {
        assert(!end);
        return &Iter->data;
    }

private:
    pointer Iter;
    bool end;
    friend LinkedList<T>;
};

template<typename T>
class LinkedList {
private:
    LinkedListNode<T> *first;
    LinkedListNode<T> *last;
    std::size_t nodeNum;

    void freeNode(LinkedListNode<T> *node) {
        if (node == nullptr) return;
        if (node != node->next)
            freeNode(node->next);
        delete node;
    }

    void initWith(const T &data) {
        assert(first == last);
        auto node = new LinkedListNode<T>(data);
        first = node;
        last = node;
    }

public:
    LinkedList() : first(nullptr), last(nullptr), nodeNum(0) {
    }

    void clear() {
        freeNode(first);
        nodeNum = 0;
    }

    ~LinkedList() {
        freeNode(first);
    }

    void push_front(T data) {
        nodeNum++;
        if (first == nullptr && last == nullptr) {
            initWith(data);
            return;
        }
        auto node = new LinkedListNode<T>(data);
        node->next = first;
        first->prev = node;

        first = node;
    }


    void push_back(T data) {
        nodeNum++;
        if (first == nullptr && last == nullptr) {
            initWith(data);
            return;
        }

        auto node = new LinkedListNode<T>(data);
        last->next = node;
        node->prev = last;
        last = node;
    }

    LinkedListIter<T> begin() {
        if (empty()) {
            return end();
        }
        return LinkedListIter<T>(first);
    }

    LinkedListIter<T> end() {
        auto iter = LinkedListIter<T>(last);
        iter.end = true;
        return iter;
    }

    void insert(LinkedListIter<T> &iter, T data) {
        nodeNum++;
        if (empty()) {
            push_back(data);
            return;
        }
        if (iter == end()) {
            push_back(data);
            return;
        }
        if (iter == begin()) {
            push_front(data);
            return;
        }
        auto next = iter.Iter;
        auto prev = iter.Iter->prev;
        auto node = new LinkedListNode(data);
        node->next = next;
        node->prev = prev;

        prev->next = node;
        next->prev = node;
    }


    LinkedListIter<T> erase(LinkedListIter<T> &iter) {
        assert(!iter.end);
        nodeNum--;
        if (iter.Iter->next == nullptr && iter.Iter->prev == nullptr && iter.Iter == first) {
            delete first;
            first = nullptr;
            last = nullptr;
            return end();
        }
        if (iter.Iter == first) {
            auto next = iter.Iter->next;
            next->prev = nullptr;
            delete first;
            first = next;
            return begin();
        }
        if (iter.Iter == last) {
            auto prev = iter.Iter->prev;
            prev->next = nullptr;
            delete last;
            last = prev;
            return end();
        }

        auto prev = iter.Iter->prev;
        auto next = iter.Iter->next;
        next->prev = prev;
        prev->next = next;
        delete iter.Iter;
        return LinkedListIter(next);
    }

    LinkedListIter<T> erase(LinkedListIter<T> &&iter) {
        return erase(iter);
    }

    bool empty() {
        return first == nullptr && last == nullptr;
    }

    std::size_t size() {
        return nodeNum;
    }

    friend LinkedListIter<T>;
};

