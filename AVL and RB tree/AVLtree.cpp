#include <bits/stdc++.h>
using namespace std;
template <typename K, typename V>
class AVLNode
{
public:
    K key;
    V value;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode(K k, V v) : key(k), value(v), left(NULL), right(NULL), height(1) {}
};
template <typename K, typename V>
class AVLTree
{
private:
    AVLNode<K, V> *root;
    int getHeight(AVLNode<K, V> *Node)
    {
        return Node ? Node->height : 0;
    }
    int getBalanceFactor(AVLNode<K, V> *Node)
    {
        return Node ? getHeight(Node->left) - getHeight(Node->right) : 0;
    }
    void updateHeight(AVLNode<K, V> *Node)
    {
        if (Node)
        {
            Node->height = 1 + max(getHeight(Node->left), getHeight(Node->right));
        }
    }
    AVLNode<K, V> *rotateRight(AVLNode<K, V> *y)
    {
        AVLNode<K, V> *x = y->left;
        AVLNode<K, V> *temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }
    AVLNode<K, V> *rotateLeft(AVLNode<K, V> *x)
    {
        AVLNode<K, V> *y = x->right;
        AVLNode<K, V> *temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }
    AVLNode<K, V> *balance(AVLNode<K, V> *Node)
    {
        updateHeight(Node);
        int balanceFactor = getBalanceFactor(Node);

        if (balanceFactor > 1 && getBalanceFactor(Node->left) >= 0)
        {
            return rotateRight(Node);
        }
        if (balanceFactor > 1 && getBalanceFactor(Node->left) < 0)
        {
            Node->left = rotateLeft(Node->left);
            return rotateRight(Node);
        }
        if (balanceFactor < -1 && getBalanceFactor(Node->right) <= 0)
        {
            return rotateLeft(Node);
        }
        if (balanceFactor < -1 && getBalanceFactor(Node->right) > 0)
        {
            Node->right = rotateRight(Node->right);
            return rotateLeft(Node);
        }
        return Node;
    }
    AVLNode<K, V> *insertNode(AVLNode<K, V> *Node, K key, V value, bool &success)
    {
        if (!Node)
        {
            success = true;
            return new AVLNode<K, V>(key, value);
        }
        if (key < Node->key)
        {
            Node->left = insertNode(Node->left, key, value, success);
        }
        else if (key > Node->key)
        {
            Node->right = insertNode(Node->right, key, value, success);
        }
        else
        {
            success = false;
            return Node;
        }
        return balance(Node);
    }
    AVLNode<K, V> *findMinNode(AVLNode<K, V> *Node)
    {
        while (Node->left)
        {
            Node = Node->left;
        }
        return Node;
    }
    AVLNode<K, V> *deleteNode(AVLNode<K, V> *Node, K key, bool &success)
    {
        if (!Node)
        {
            success = false;
            return NULL;
        }
        if (key < Node->key)
        {
            Node->left = deleteNode(Node->left, key, success);
        }
        else if (key > Node->key)
        {
            Node->right = deleteNode(Node->right, key, success);
        }
        else
        {
            success = true;

            if (!Node->left || !Node->right)
            {
                AVLNode<K, V> *temp = Node->left ? Node->left : Node->right;
                delete Node;
                return temp;
            }
            else
            {
                AVLNode<K, V> *temp = findMinNode(Node->right);
                Node->key = temp->key;
                Node->value = temp->value;
                Node->right = deleteNode(Node->right, temp->key, success);
            }
        }

        if (!Node)
            return Node;
        return balance(Node);
    }
    void preOrder(AVLNode<K, V> *Node, ofstream &out)
    {
        if (Node)
        {
            out << Node->key << " ";
            preOrder(Node->left, out);
            preOrder(Node->right, out);
        }
    }
    void inOrder(AVLNode<K, V> *Node, ofstream &out)
    {
        if (Node)
        {
            inOrder(Node->left, out);
            out << Node->key << " ";
            inOrder(Node->right, out);
        }
    }
    void postOrder(AVLNode<K, V> *Node, ofstream &out)
    {
        if (Node)
        {
            postOrder(Node->left, out);
            postOrder(Node->right, out);
            out << Node->key << " ";
        }
    }
    void levelOrder(AVLNode<K, V> *Node, ofstream &out)
    {
        if (!Node)
            return;

        queue<AVLNode<K, V> *> q;
        q.push(Node);
        while (!q.empty())
        {
            AVLNode<K, V> *current = q.front();
            q.pop();

            out << current->key << " ";
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }
    void destroyTree(AVLNode<K, V> *Node)
    {
        if (Node)
        {
            destroyTree(Node->left);
            destroyTree(Node->right);
            delete Node;
        }
    }

public:
    AVLTree() : root(NULL) {}
    ~AVLTree()
    {
        destroyTree(root);
    }
    bool insert(K key, V value)
    {
        bool success = false;
        root = insertNode(root, key, value, success);
        return success;
    }
    bool remove(K key)
    {
        bool success = false;
        root = deleteNode(root, key, success);
        return success;
    }
    void traverse(int type, ofstream &out)
    {
        switch (type)
        {
        case 1:
            preOrder(root, out);
            break;
        case 2:
            inOrder(root, out);
            break;
        case 3:
            postOrder(root, out);
            break;
        case 4:
            levelOrder(root, out);
            break;
        }
    }
};
int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    int n;
    infile >> n;

    outfile << n << endl;

    AVLTree<int, int> tree;

    for (int i = 0; i < n; i++)
    {
        int e, x;
        infile >> e >> x;

        if (e == 0)
        {
            bool result = tree.remove(x);
            outfile << e << " " << x << " " << (result ? 1 : 0) << endl;
        }
        else if (e == 1)
        {
            bool result = tree.insert(x, x);
            outfile << e << " " << x << " " << (result ? 1 : 0) << endl;
        }
        else if (e == 2)
        {
            tree.traverse(x, outfile);
            outfile << "\n";
        }
    }

    infile.close();
    outfile.close();

    return 0;
}