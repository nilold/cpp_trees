#ifndef TREES_NODE_H
#define TREES_NODE_H

#include <vector>
#include <memory>
#include <cmath>

namespace nilo {
    template<typename T>
    class Node {
    private:
        std::vector<std::shared_ptr<Node<T>>> m_children;
        T m_value;

    public:
        explicit Node(T value) : m_value(value) {};

        const std::vector<std::shared_ptr<Node<T>>> &children() const { return m_children; };

        const T &value() { return m_value; };

        void add_child(std::shared_ptr<Node<T>> child) {
            m_children.push_back(child);
        }

        bool operator==(const Node<T> &other) const{
            return value() == other.value();
        }
    };


}

template<typename T>
struct std::hash<nilo::Node<T>> {
    std::size_t operator()(const nilo::Node<T> &node) const noexcept {
        return std::hash<int>{}(node.value());
    }
};

#endif //TREES_NODE_H
