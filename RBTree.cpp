#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct TreeNode {
    int data;
    Color color;
    struct TreeNode* left, * right, * parent;
} TreeNode;

typedef struct RedBlackTree {
    TreeNode* root;
} RedBlackTree;

// 辅助函数：寻找插入位置
TreeNode* treeMinimum(TreeNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

RedBlackTree* RBTreeNew() {
    RedBlackTree* tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    tree->root = NULL;
    return tree;
}

// 插入节点
TreeNode* RBTreeInsert(RedBlackTree* tree, int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = key;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;

    TreeNode* temp = tree->root;
    TreeNode* parent = NULL;

    // 寻找插入位置
    while (temp != NULL) {
        parent = temp;
        if (key < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    newNode->parent = parent;

    if (parent == NULL)
        tree->root = newNode;
    else if (key < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    // 插入后调整
    RBInsertFixup(tree, newNode);
    return newNode;
}

// 插入修复
void RBInsertFixup(RedBlackTree* tree, TreeNode* node) {
    while (node->parent != NULL && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            TreeNode* uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(tree, node->parent->parent);
            }
        }
        else {  // 对称情况
            TreeNode* uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// 左旋
void leftRotate(RedBlackTree* tree, TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// 右旋
void rightRotate(RedBlackTree* tree, TreeNode* y) {
    TreeNode* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}


// 辅助函数：找到树中最小的节点
TreeNode* treeMinimum(TreeNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// 删除节点
void RBTreeDelete(RedBlackTree* tree, TreeNode* z) {
    TreeNode* y = z, * x, * T2;
    Color y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        RBTransplant(tree, z, z->right);
    }
    else if (z->right == NULL) {
        x = z->left;
        RBTransplant(tree, z, z->left);
    }
    else {
        y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            RBTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (y_original_color == BLACK)
        RBDeleteFixup(tree, x);
}

// 节点替换
void RBTransplant(RedBlackTree* tree, TreeNode* u, TreeNode* v) {
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// 删除修复
void RBDeleteFixup(RedBlackTree* tree, TreeNode* x) {
    TreeNode* w;
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else {  // 对称情况
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

int main() {
    RedBlackTree* tree = RBTreeNew();

    RBTreeInsert(tree, 10);
    RBTreeInsert(tree, 20);
    RBTreeInsert(tree, 30);
    RBTreeInsert(tree, 40);
    RBTreeInsert(tree, 50);
    RBTreeInsert(tree, 25);

    // 打印函数需自行实现，以验证红黑树的正确性

    // 记得释放内存
    // ...

    return 0;
}