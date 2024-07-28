#ifndef TREE_HPP
#define TREE_HPP

#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include "node.hpp"

template <typename T, int K = 2>
class Tree {
private:
    std::shared_ptr<Node<T>> root;

    void print_tree(std::shared_ptr<Node<T>> node, int depth) const {
        if (!node) return;
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << node->value << std::endl;
        for (const auto& child : node->children) {
            print_tree(child, depth + 2);
        }
    }

public:
    Tree() : root(nullptr) {}
      
    std::shared_ptr<Node<T>> getRoot() const {
        return root;
    }

    void add_root(const Node<T>& node) {
        root = std::make_shared<Node<T>>(node);
    }

    void add_sub_node(const Node<T>& parent, const Node<T>& child) {
        if (!root) return;
        std::queue<std::shared_ptr<Node<T>>> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            auto current = nodes.front();
            nodes.pop();
            if (current->value == parent.value) {
                if (current->children.size() < K) {
                    current->children.push_back(std::make_shared<Node<T>>(child));
                }
                return;
            }
            for (const auto& child : current->children) {
                nodes.push(child);
            }
        }
    }

    // Method to get nodes in BFS order
    std::vector<std::shared_ptr<Node<T>>> getNodesBFS() const {
        std::vector<std::shared_ptr<Node<T>>> result;
        if (!root) return result;

        std::queue<std::shared_ptr<Node<T>>> queue;
        queue.push(root);
        while (!queue.empty()) {
            auto node = queue.front();
            queue.pop();
            result.push_back(node);
            for (const auto& child : node->children) {
                queue.push(child);
            }
        }
        return result;
    }

    // Pre-order iterator
    class PreOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
    public:
        PreOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack.push(root);
            }
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator& other) const {
            return stack == other.stack;
        }

        Node<T>& operator*() {
            return *stack.top();
        }

        PreOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }
    };

    PreOrderIterator begin_pre_order() {
        if (K>2)
        {
            DFSIterator dfs(root);
        }
        
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Post-order iterator
    class PostOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack1, stack2;
    public:
        PostOrderIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack1.push(root);
                while (!stack1.empty()) {
                    auto node = stack1.top();
                    stack1.pop();
                    stack2.push(node);
                    for (auto& child : node->children) {
                        stack1.push(child);
                    }
                }
            }
        }

        bool operator!=(const PostOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PostOrderIterator& other) const {
            return stack2 == other.stack2;
        }

        Node<T>& operator*() {
            return *stack2.top();
        }

        PostOrderIterator& operator++() {
            stack2.pop();
            return *this;
        }
    };

    PostOrderIterator begin_post_order() {
        if(K>2){
            DFSIterator dfs(root);
        }
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // In-order iterator
    class InOrderIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
        std::shared_ptr<Node<T>> current;

        void push_left(std::shared_ptr<Node<T>> node) {
            while (node) {
                stack.push(node);
                node = node->children.empty() ? nullptr : node->children[0];
            }
        }

    public:
        InOrderIterator(std::shared_ptr<Node<T>> root) {
            push_left(root);
        }

        bool operator!=(const InOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const InOrderIterator& other) const {
            return stack == other.stack;
        }

        Node<T>& operator*() {
            return *stack.top();
        }

        InOrderIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            if (node->children.size() > 1) {
                push_left(node->children[1]);
            }
            return *this;
        }
    };

    InOrderIterator begin_in_order() {
        if(K>2){
            DFSIterator dfs(root);
        }
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    // BFS iterator
    class BFSIterator {
    private:
        std::queue<std::shared_ptr<Node<T>>> queue;
    public:
        BFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                queue.push(root);
            }
        }

        bool operator!=(const BFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const BFSIterator& other) const {
            return queue == other.queue;
        }

        Node<T>& operator*() {
            return *queue.front();
        }

        BFSIterator& operator++() {
            auto node = queue.front();
            queue.pop();
            for (const auto& child : node->children) {
                queue.push(child);
            }
            return *this;
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // DFS iterator
    class DFSIterator {
    private:
        std::stack<std::shared_ptr<Node<T>>> stack;
    public:
        DFSIterator(std::shared_ptr<Node<T>> root) {
            if (root) {
                stack.push(root);
            }
        }

        bool operator!=(const DFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const DFSIterator& other) const {
            return stack == other.stack;
        }

        Node<T>& operator*() {
            return *stack.top();
        }

        DFSIterator& operator++() {
            auto node = stack.top();
            stack.pop();
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
            }
            return *this;
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

    // Heap iterator
    class HeapIterator {
    private:
        std::vector<std::shared_ptr<Node<T>>> heap;
        size_t index;

        void heapify() {
            for (size_t i = heap.size() / 2; i-- > 0;) {
                sift_down(i);
            }
        }

        void sift_down(size_t i) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;

            if (left < heap.size() && heap[left]->value < heap[smallest]->value) {
                smallest = left;
            }
            if (right < heap.size() && heap[right]->value < heap[smallest]->value) {
                smallest = right;
            }
            if (smallest != i) {
                std::swap(heap[i], heap[smallest]);
                sift_down(smallest);
            }
        }

    public:
        HeapIterator(std::shared_ptr<Node<T>> root) : index(0) {
            if (root) {
                std::queue<std::shared_ptr<Node<T>>> q;
                q.push(root);
                while (!q.empty()) {
                    auto node = q.front();
                    q.pop();
                    heap.push_back(node);
                    for (const auto& child : node->children) {
                        q.push(child);
                    }
                }
                heapify();
            }
        }

        bool operator!=(const HeapIterator& other) const {
            return index != other.index;
        }

        bool operator==(const HeapIterator& other) const {
            return index == other.index;
        }

        Node<T>& operator*() {
            return *heap[index];
        }

        HeapIterator& operator++() {
            if (index < heap.size()) {
                ++index;
            }
            return *this;
        }
    };

    HeapIterator begin_heap() {
        return HeapIterator(root);
    }

    HeapIterator end_heap() {
        return HeapIterator(nullptr);
    }

    // Convert tree to heap
    void myHeap() {
        if (!root) return;
        std::vector<std::shared_ptr<Node<T>>> nodes = getNodesBFS();
        std::make_heap(nodes.begin(), nodes.end(), [](const std::shared_ptr<Node<T>>& a, const std::shared_ptr<Node<T>>& b) {
            return a->value > b->value;
        });
        root = nodes.front();
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i]->children.clear();
            if (2 * i + 1 < nodes.size()) {
                nodes[i]->children.push_back(nodes[2 * i + 1]);
            }
            if (2 * i + 2 < nodes.size()) {
                nodes[i]->children.push_back(nodes[2 * i + 2]);
            }
        }
    }

    // Destructor to delete the entire tree
    ~Tree() {
        root.reset();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tree<T, K>& tree) {
        tree.print_tree(tree.root, 0);
        return os;
    }
};

#endif // TREE_HPP
