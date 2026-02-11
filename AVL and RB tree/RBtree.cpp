#include <bits/stdc++.h>
using namespace std;

enum COLOR
{
    RED,
    BLACK
};

template <typename T>
class RBNode
{
public:
    T key;
    COLOR color;
    RBNode *left;
    RBNode *right;
    RBNode *parent;
    int size;
    
    RBNode(T k) : key(k), color(RED), left(NULL), right(NULL), parent(NULL), size(1) {}
};

template <typename T>
class RBTree
{
private:
    RBNode<T> *root;
    RBNode<T> *NIL;
    
    int getSize(RBNode<T> *Node)
    {
        return (Node == NULL || Node == NIL) ? 0 : Node->size;
    }
    
    void updateSize(RBNode<T> *Node)
    {
        if (Node != NIL)
        {
            Node->size = 1 + getSize(Node->left) + getSize(Node->right);
        }
    }
    
    void rotateLeft(RBNode<T> *x)
    {
        RBNode<T> *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NIL)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

        updateSize(x);
        updateSize(y);
    }
    
    void rotateRight(RBNode<T> *y)
    {
        RBNode<T> *x = y->left;
        y->left = x->right;

        if (x->right != NIL)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == NIL)
        {
            root = x;
        }
        else if (y == y->parent->right)
        {
            y->parent->right = x;
        }
        else
        {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
        updateSize(y);
        updateSize(x);
    }
    
    void insertWithColor(RBNode<T> *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBNode<T> *y = z->parent->parent->right;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            }
            else
            {
                RBNode<T> *y = z->parent->parent->left;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void transplant(RBNode<T> *u, RBNode<T> *v)
    {
        if (u->parent == NIL)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    
    RBNode<T> *minimum(RBNode<T> *Node)
    {
        while (Node->left != NIL)
        {
            Node = Node->left;
        }
        return Node;
    }
    
    void deleteWithColor(RBNode<T> *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                RBNode<T> *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else
            {
                RBNode<T> *w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
    RBNode<T> *searchNode(RBNode<T> *Node, T key)
    {
        if (Node == NIL || Node->key == key)
        {
            return Node;
        }
        if (key < Node->key)
        {
            return searchNode(Node->left, key);
        }
        return searchNode(Node->right, key);
    }
    
    void destroyTree(RBNode<T> *Node)
    {
        if (Node != NIL)
        {
            destroyTree(Node->left);
            destroyTree(Node->right);
            delete Node;
        }
    }

public:
    RBTree()
    {
        NIL = new RBNode<T>(T());
        NIL->color = BLACK;
        NIL->size = 0;
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }
    
    ~RBTree()
    {
        destroyTree(root);
        delete NIL;
    }
    
    bool insert(T key)
    {
        if (searchNode(root, key) != NIL)
        {
            return false;
        }
        RBNode<T> *z = new RBNode<T>(key);
        z->left = NIL;
        z->right = NIL;

        RBNode<T> *y = NIL;
        RBNode<T> *x = root;
        while (x != NIL)
        {
            y = x;
            if (z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == NIL)
        {
            root = z;
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->color = RED;
        RBNode<T> *current = z;
        while (current != NIL)
        {
            updateSize(current);
            current = current->parent;
        }
        insertWithColor(z);
        return true;
    }
    
    bool remove(T key)
    {
        RBNode<T> *z = searchNode(root, key);
        if (z == NIL)
            return false;

        RBNode<T> *y = z;
        RBNode<T> *x;
        COLOR original_y = y->color;

        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
            RBNode<T> *current = x->parent;
            while (current != NIL)
            {
                updateSize(current);
                current = current->parent;
            }
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left);
            RBNode<T> *current = x->parent;
            while (current != NIL)
            {
                updateSize(current);
                current = current->parent;
            }
        }
        else
        {
            y = minimum(z->right);
            original_y = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
                RBNode<T> *current = x->parent;
                while (current != y && current != NIL)
                {
                    updateSize(current);
                    current = current->parent;
                }
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;

            RBNode<T> *current = y;
            while (current != NIL)
            {
                updateSize(current);
                current = current->parent;
            }
        }
        delete z;

        if (original_y == BLACK)
        {
            deleteWithColor(x);
        }
        return true;
    }
    
    bool search(T key)
    {
        return searchNode(root, key) != NIL;
    }
    
    int countLess(T key)
    {
        int count = 0;
        RBNode<T> *current = root;

        while (current != NIL)
        {
            if (key <= current->key)
            {
                current = current->left;
            }
            else
            {
                count += 1 + getSize(current->left);
                current = current->right;
            }
        }
        return count;
    }
};

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    
    int n;
    infile >> n;
    
    outfile << n << endl;
    
    RBTree<int> tree;
    
    for (int i = 0; i < n; i++) {
        int e, x;
        infile >> e >> x;
        
        if (e == 0) {
            bool result = tree.remove(x);
            outfile << e << " " << x << " " << (result ? 1 : 0) << endl;
        } else if (e == 1) {
            bool result = tree.insert(x);
            outfile << e << " " << x << " " << (result ? 1 : 0) << endl;
        } else if (e == 2) {
            bool result = tree.search(x);
            outfile << e << " " << x << " " << (result ? 1 : 0) << endl;
        } else if (e == 3) {
            int count = tree.countLess(x);
            outfile << e << " " << x << " " << count << endl;
        }
    }
    
    infile.close();
    outfile.close();
    
    return 0;
}