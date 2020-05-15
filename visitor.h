#ifndef TREES_VISITOR_H
#define TREES_VISITOR_H

#include "node.h"
#include <memory>
#include <unordered_map>
#include <list>
#include <vector>

namespace nilo {
    template<typename NodeValueType>
    class BFSVisitor {
        typedef std::shared_ptr<Node < NodeValueType>> node_ptr;
        std::unordered_map<node_ptr, std::list<node_ptr>> paths;

    public:
        const std::unordered_map<node_ptr, std::list<node_ptr>> &get_paths() const {
            return paths;
        }

        void visit(const node_ptr &node, const node_ptr &parent) {
            if (parent == nullptr) {
                std::list<node_ptr> nodePath({node});
                paths.insert({node, nodePath});
                return;
            }

            try {
                auto parentPath = paths.at(parent);
                create_node_path_from_parent_path(node, parentPath);
            } catch (std::out_of_range &e) {
                std::cout << e.what() << std::endl;
                std::cout << "Are you trying to visit a node before visiting it's parent?" << std::endl;
            }
        }

        template<typename T>
        friend std::ostream &operator<<(std::ostream &stream, const BFSVisitor<T> &visitor);

    private:
        void create_node_path_from_parent_path(const node_ptr &node, const std::list<node_ptr> &parentPath) {
            auto nodePath = parentPath; //copy
            nodePath.push_back(node);
            paths.insert({node, nodePath});
        }
    };


    template<typename NodeValueType>
    std::ostream &operator<<(std::ostream &stream, const BFSVisitor<NodeValueType> &visitor) {

        for (const auto &path : visitor.get_paths()) {
            stream << "Node " << path.first->value() << " shortest path: ";
            for (const auto &node : path.second)
                stream << node->value() << "-";

            stream << "\b" << std::endl;
        }

        return stream;
    }

    template<typename NodeValueType>
    class BFSVisitorVector {
        typedef std::shared_ptr<Node < NodeValueType>> node_ptr;
        std::unordered_map<node_ptr, std::vector<node_ptr>> paths;

    public:
        const std::unordered_map<node_ptr, std::vector<node_ptr>> &get_paths() const {
            return paths;
        }

        void visit(const node_ptr &node, const node_ptr &parent) {
            if (parent == nullptr) {
                std::vector<node_ptr> nodePath({node});
                paths.insert({node, nodePath});
                return;
            }

            try {
                auto parentPath = paths.at(parent);
                create_node_path_from_parent_path(node, parentPath);
            } catch (std::out_of_range &e) {
                std::cout << e.what() << std::endl;
                std::cout << "Are you trying to visit a node before visiting it's parent?" << std::endl;
            }
        }

        template<typename T>
        friend std::ostream &operator<<(std::ostream &stream, const BFSVisitor<T> &visitor);

    private:
        void create_node_path_from_parent_path(const node_ptr &node, const std::vector<node_ptr> &parentPath) {
            auto nodePath = parentPath; //copy
            nodePath.push_back(node);
            paths.insert({node, nodePath});
        }
    };


}
#endif //TREES_VISITOR_H
