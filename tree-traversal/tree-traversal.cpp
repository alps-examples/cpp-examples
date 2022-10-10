#include <functional>
#include <memory>
#include <stack>

#include <gtest/gtest.h>

struct Node {
    Node(char value)
        : value(value)
    {
    }
    ~Node()
    {
        delete left;
        delete right;
    }
    int value = 0;
    Node* left = nullptr;
    Node* right = nullptr;
};

using NodeVisitorFunction = std::function<void(Node*)>;

void preorder(Node* root, NodeVisitorFunction visit)
{
    std::string traversal;
    if (root) {
        visit(root);
        preorder(root->left, visit);
        preorder(root->right, visit);
    }
}

void inorder(Node* root, NodeVisitorFunction visit)
{
    if (root) {
        inorder(root->left, visit);
        visit(root);
        inorder(root->right, visit);
    }
}

void postorder(Node* root, NodeVisitorFunction visit)
{
    if (root) {
        postorder(root->left, visit);
        postorder(root->right, visit);
        visit(root);
    }
}

void preorder_it(Node* root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = root;

    while (cur || !s.empty()) {
        while (cur) {
            visit(cur);
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        cur = cur->right;
    }
}

void inorder_it(Node* root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = root;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        visit(cur);

        cur = cur->right;
    }
}

void postorder_it(Node* root, NodeVisitorFunction visit)
{
    std::stack<Node*> s;
    Node* cur = root;
    Node* prev = nullptr;

    while (cur || !s.empty()) {
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        if (!cur->right || cur->right == prev) {
            visit(cur);
            s.pop();
            prev = cur;
            cur = nullptr;
        } else {
            cur = cur->right;
        }
    }
}

// Fixture that serves as basis for test case
struct TreeTraversal : ::testing::Test {

    using TreeTraversalFunction = std::function<void(Node* root, NodeVisitorFunction)>;

    TreeTraversal()
        : tree('a')
    {
        tree.left = new Node('b');
        tree.right = new Node('c');
    }

    static std::string to_string(Node* node, TreeTraversalFunction traverse)
    {
        std::string output;
        traverse(node, [&output](Node* n) { output += n->value; });
        return output;
    }

    Node tree;
};

TEST_F(TreeTraversal, PreoderAbc)
{
    EXPECT_EQ(to_string(&tree, preorder), "abc");
}

TEST_F(TreeTraversal, InorderAbc)
{
    EXPECT_EQ(to_string(&tree, inorder), "bac");
}

TEST_F(TreeTraversal, PostOrderAbc)
{
    EXPECT_EQ(to_string(&tree, postorder), "bca");
}

TEST_F(TreeTraversal, PreorderItAbc)
{
    EXPECT_EQ(to_string(&tree, preorder_it), "abc");
}

TEST_F(TreeTraversal, InorderItAbc)
{
    EXPECT_EQ(to_string(&tree, inorder_it), "bac");
}

TEST_F(TreeTraversal, PostorderItAbc)
{
    EXPECT_EQ(to_string(&tree, postorder_it), "bca");
}
