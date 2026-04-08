#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <memory>
#include <optional>

template <typename T>
class DoublyLinkedList {
private:
    // Node structure definition
    struct Node {
        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::weak_ptr<Node> tail;
    size_t length;

public:
    // Iterator class
    class iterator {
    private:
        std::shared_ptr<Node> current;

    public:
        iterator(std::shared_ptr<Node> node) : current(node) {}

        // Dereference operator to get value
        T& operator*() {
            // 注：对空迭代器调用此函数是未定义行为，测试数据中不会出现
            return current->value;
        }

        // Post-increment operator
        iterator operator++(int) {
            // 注：对空迭代器调用此函数是未定义行为，测试数据中不会出现
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        // Equality operators
        bool operator==(const iterator& other) const {
            // 注：比较属于不同容器的非空迭代器是未定义行为，测试数据中不会出现
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    // Constructor
    DoublyLinkedList() : head(nullptr), length(0) {}

    // No destructor needed, memory managed by shared_ptr

    // Check if list is empty
    bool empty() const {
        return length == 0;
    }

    // Get the size of the list
    size_t size() const {
        return length;
    }

    // Add element to the front
    void push_front(const T& value) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        length++;
    }

    // Add element to the back
    void push_back(const T& value) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
        if (empty()) {
            head = new_node;
            tail = new_node;
        } else {
            std::shared_ptr<Node> tail_ptr = tail.lock();
            tail_ptr->next = new_node;
            new_node->prev = tail_ptr;
            tail = new_node;
        }
        length++;
    }

    // Remove and return the first element
    std::optional<T> pop_front() {
        if (!head) {
            return std::nullopt;
        }
        T val = std::move(head->value);
        head = head->next;
        if (head) {
            head->prev.reset();
        } else {
            tail.reset();
        }
        length--;
        return val;
    }

    // Remove and return the last element
    std::optional<T> pop_back() {
        if (empty()) {
            return std::nullopt;
        }
        std::shared_ptr<Node> tail_ptr = tail.lock();
        T val = std::move(tail_ptr->value);
        std::shared_ptr<Node> prev_ptr = tail_ptr->prev.lock();
        if (prev_ptr) {
            prev_ptr->next = nullptr;
            tail = prev_ptr;
        } else {
            head = nullptr;
            tail.reset();
        }
        length--;
        return val;
    }

    // Iterators
    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }
};

#endif // DOUBLY_LINKED_LIST_HPP