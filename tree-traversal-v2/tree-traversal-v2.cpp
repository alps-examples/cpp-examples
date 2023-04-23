#include <functional>
#include <memory>
#include <stack>

#include <gtest/gtest.h>

struct Node {
    Node(char value)
        : value(value)
    {
    }
    Node(char value, std::unique_ptr<Node> left, std::unique_ptr<Node> right)
        : value(value)
        , left(std::move(left))
        , right(std::move(right))
    {
    }
    int value = 0;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

using NodeVisitorFunction = std::function<void(Node&)>;

void preorder(Node& root, NodeVisitorFunction visit)
{
    std::string traversal;
    visit(root);
    if (root.left)
        preorder(*root.left, visit);
    if (root.right)
        preorder(*root.right, visit);
}

void inorder(Node& root, NodeVisitorFunction visit)
{
    if (root.left)
        inorder(*root.left, visit);
    visit(root);
    if (root.right)
        inorder(*root.right, visit);
}

void postorder(Node& root, NodeVisitorFunction visit)
{
    if (root.left) {
        postorder(*root.left, visit);
    }
    if (root.right) {
        postorder(*root.right, visit);
    }
    visit(root);
}

void preorder_it(Node& root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = &root;

    while (cur || !s.empty()) {
        while (cur) {
            visit(*cur);
            s.push(cur);
            cur = cur->left.get();
        }

        cur = s.top();
        s.pop();

        cur = cur->right.get();
    }
}

void inorder_it(Node& root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = &root;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left.get();
        }

        cur = s.top();
        s.pop();

        visit(*cur);

        cur = cur->right.get();
    }
}

void postorder_it(Node& root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = &root;
    Node* prev = nullptr;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left.get();
        }

        cur = s.top();
        if (!cur->right || cur->right.get() == prev) {
            visit(*cur);
            s.pop();
            prev = cur;
            cur = nullptr;
        } else {
            cur = cur->right.get();
        }
    }
}

// Fixture that serves as basis for test case
struct TreeTraversal : ::testing::Test {

    using TreeTraversalFunction = std::function<void(Node& root, NodeVisitorFunction)>;

    TreeTraversal()
        : tree('a', std::make_unique<Node>('b'), std::make_unique<Node>('c'))
    {
    }

    static std::string to_string(Node& node, TreeTraversalFunction traverse)
    {
        std::string output;
        traverse(node, [&output](Node& n) { output += n.value; });
        return output;
    }

    Node tree;
};

TEST_F(TreeTraversal, PreoderAbc)
{
    EXPECT_EQ(to_string(tree, preorder), "abc");
}

TEST_F(TreeTraversal, InorderAbc)
{
    EXPECT_EQ(to_string(tree, inorder), "bac");
}

TEST_F(TreeTraversal, PostOrderAbc)
{
    EXPECT_EQ(to_string(tree, postorder), "bca");
}

TEST_F(TreeTraversal, PreorderItAbc)
{
    EXPECT_EQ(to_string(tree, preorder_it), "abc");
}

TEST_F(TreeTraversal, InorderItAbc)
{
    EXPECT_EQ(to_string(tree, inorder_it), "bac");
}

TEST_F(TreeTraversal, PostorderItAbc)
{
    EXPECT_EQ(to_string(tree, postorder_it), "bca");
}
