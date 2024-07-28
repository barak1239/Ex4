#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"

// Helper function to create a basic tree of integers
Tree<int> createBasicIntTree() {
    Node<int> root_node(1);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    return tree;
}

// Helper function to create a basic tree of strings
Tree<std::string> createBasicStringTree() {
    Node<std::string> root_node("root");
    Tree<std::string> tree;
    tree.add_root(root_node);
    Node<std::string> n1("child1");
    Node<std::string> n2("child2");
    Node<std::string> n3("child3");
    Node<std::string> n4("child4");
    Node<std::string> n5("child5");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    return tree;
}

TEST_CASE("Complex number operations") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    SUBCASE("Addition") {
        Complex expected(4.0, 6.0);
        Complex result = c1 + c2;
        CHECK(result == expected);
    }

    SUBCASE("Multiplication") {
        Complex expected(-5.0, 10.0);
        Complex result = c1 * c2;
        CHECK(result == expected);
    }

    SUBCASE("Equality") {
        Complex c3(1.0, 2.0);
        CHECK(c1 == c3);
        CHECK(!(c1 == c2));
    }

    SUBCASE("Output Stream") {
        std::ostringstream os;
        os << c1;
        CHECK(os.str() == "1+2i");
    }
}

TEST_CASE("Tree functionality with doubles") {
    Node<double> root_node(1.1);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    SUBCASE("Pre-order traversal") {
        std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        std::vector<double> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("Post-order traversal") {
        std::vector<double> expected = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
        std::vector<double> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("In-order traversal") {
        std::vector<double> expected = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
        std::vector<double> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS traversal") {
        std::vector<double> expected = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        std::vector<double> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS traversal") {
        std::vector<double> expected = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        std::vector<double> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }
}

TEST_CASE("Basic Tree functionality with integers") {
    Tree<int> tree = createBasicIntTree();

    SUBCASE("Pre-order traversal") {
        std::vector<int> expected = {1, 2, 4, 5, 3, 6};
        std::vector<int> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("Post-order traversal") {
        std::vector<int> expected = {4, 5, 2, 6, 3, 1};
        std::vector<int> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("In-order traversal") {
        std::vector<int> expected = {4, 2, 5, 1, 6, 3};
        std::vector<int> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS traversal") {
        std::vector<int> expected = {1, 2, 3, 4, 5, 6};
        std::vector<int> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS traversal") {
        std::vector<int> expected = {1, 2, 4, 5, 3, 6};
        std::vector<int> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap traversal") {
        tree.myHeap();
        std::vector<int> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(std::is_heap(result.begin(), result.end(), std::greater<int>()));
    }
}

TEST_CASE("Basic Tree functionality with strings") {
    Tree<std::string> tree = createBasicStringTree();

    SUBCASE("Pre-order traversal") {
        std::vector<std::string> expected = {"root", "child1", "child3", "child4", "child2", "child5"};
        std::vector<std::string> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("Post-order traversal") {
        std::vector<std::string> expected = {"child3", "child4", "child1", "child5", "child2", "root"};
        std::vector<std::string> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("In-order traversal") {
        std::vector<std::string> expected = {"child3", "child1", "child4", "root", "child5", "child2"};
        std::vector<std::string> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("BFS traversal") {
        std::vector<std::string> expected = {"root", "child1", "child2", "child3", "child4", "child5"};
        std::vector<std::string> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("DFS traversal") {
        std::vector<std::string> expected = {"root", "child1", "child3", "child4", "child2", "child5"};
        std::vector<std::string> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result == expected);
    }

    SUBCASE("Heap traversal") {
        tree.myHeap();
        std::vector<std::string> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
            result.push_back((*node).get_value());
        }
        // Check if the heap property holds for strings
        CHECK(std::is_heap(result.begin(), result.end(), std::greater<std::string>()));
    }
}

TEST_CASE("Tree with Complex numbers") {
    Complex root_value(1.0, 2.0);
    Node<Complex> root_node(root_value);
    Tree<Complex> tree;
    tree.add_root(root_node);
    Complex c1(2.0, 3.0);
    Complex c2(3.0, 4.0);
    Complex c3(4.0, 5.0);
    Complex c4(5.0, 6.0);
    Complex c5(6.0, 7.0);

    tree.add_sub_node(root_node, Node<Complex>(c1));
    tree.add_sub_node(root_node, Node<Complex>(c2));
    tree.add_sub_node(Node<Complex>(c1), Node<Complex>(c3));
    tree.add_sub_node(Node<Complex>(c1), Node<Complex>(c4));
    tree.add_sub_node(Node<Complex>(c2), Node<Complex>(c5));

    SUBCASE("Pre-order traversal with Complex numbers") {
        std::vector<Complex> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result[0] == root_value);
        CHECK(result[1] == c1);
        CHECK(result[2] == c3);
        CHECK(result[3] == c4);
        CHECK(result[4] == c2);
        CHECK(result[5] == c5);
    }

    SUBCASE("Post-order traversal with Complex numbers") {
        std::vector<Complex> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result[0] == c3);
        CHECK(result[1] == c4);
        CHECK(result[2] == c1);
        CHECK(result[3] == c5);
        CHECK(result[4] == c2);
        CHECK(result[5] == root_value);
    }

    SUBCASE("In-order traversal with Complex numbers") {
        std::vector<Complex> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            result.push_back((*node).get_value());
        }
        // Provide expected values if applicable
    }

    SUBCASE("BFS traversal with Complex numbers") {
        std::vector<Complex> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result[0] == root_value);
        CHECK(result[1] == c1);
        CHECK(result[2] == c2);
        CHECK(result[3] == c3);
        CHECK(result[4] == c4);
        CHECK(result[5] == c5);
    }

    SUBCASE("DFS traversal with Complex numbers") {
        std::vector<Complex> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            result.push_back((*node).get_value());
        }
        CHECK(result[0] == root_value);
        CHECK(result[1] == c1);
        CHECK(result[2] == c3);
        CHECK(result[3] == c4);
        CHECK(result[4] == c2);
        CHECK(result[5] == c5);
    }

    SUBCASE("Heap traversal with Complex numbers") {
        tree.myHeap();
        std::vector<Complex> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
            result.push_back((*node).get_value());
        }
        // Check if the heap property holds for complex numbers (based on real part)
        CHECK(std::is_heap(result.begin(), result.end(), [](const Complex& a, const Complex& b) {
            return a.real > b.real;
        }));
    }
}
