# BinarySearchTree
/**
Terminologies used in Trees:
Root - The top node in a tree.
Parent - The converse notion of a child.
Siblings - Nodes with the same parent.
Descendant - A node reachable by repeated proceeding from parent to child.
Ancestor - A node reachable by repeated proceeding from child to parent.
Leaf - A node with no children.
Internal node - A node with at least one child.
External node - A node with no children.
Degree - Number of sub trees of a node.
Edge - Connection between one node to another.
Path - A sequence of nodes and edges connecting a node with a descendant.
Level - The level of a node is defined by 1 + (the number of connections between the node and the root).
Height of node - The height of a node is the number of edges on the longest downward path between that node and a leaf.
Height of tree - The height of a tree is the height of its root node.
Depth - The depth of a node is the number of edges from the node to the tree's root node.
Forest - A forest is a set of n >= 0 disjoint trees.
**/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <assert.h>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node( int d = 0, Node* l = NULL, Node* r = NULL )
    {
        data = d;
        left = l;
        right = r;
    }
};

class BST
{
    Node* root;
    int size;

public:
    BST();
	BST(const BST& other);
     ~BST();
    int getMin() const;
    int getMax() const;
    int getSize() const;
    bool isEmpty() const;

    void push( int x );
    void popMin();
    void popMax();

    int getLevel( int x );
    int getHeightOfNode( int x );
    int getHeightOfTree();
    int getDepth( int x );
    void getElementsInRow( vector<int>& v, int k );

    bool contains( int x );
    void clear();
    Node*& search( int x );

    void preorder();
    void inorder();

	BST leftTree() const;
	BST rightTree() const;

private:
    void destroy(Node*& node);
    Node*& findNode( int x );
    int calcHeightOfNode( Node*& node );
    void print_preorder( Node*& node );
    void print_inorder( Node*& node );
    void getElementsInRowFromRoot(vector<int>& v, Node*& node, int k);

	void copy(Node*& p, Node* const& r,int& size) const;
	void copyTree(const BST& other);
};

void BST::copy(Node*& p, Node* const& r,int& size) const
{
	p = NULL;
	if (r) 
	{
		p = new Node;
		assert(p != NULL);
		p->data = r->data;
		size++;
		copy(p->left, r->left,size);
		copy(p->right, r->right,size);
	}
}

BST BST::leftTree() const
{
	BST tree;
	int size = 0;
	copy(tree.root, root->left, size);
	tree.size = size;
	return tree;
}

BST BST::rightTree() const
{
	BST tree;
	int size = 0;
	copy(tree.root, root->right,size);
	tree.size = size;
	return tree;
}

void BST::copyTree(const BST& other)
{
	int size = 0;
	copy(root, other.root,size);
	this->size = size;
}

BST::BST()
{
    root = NULL;
    size = 0;
}

BST::BST(const BST& other)
{
	copyTree(other);
}

BST::~BST()
{
    destroy(root);
}

void BST::clear()
{
    destroy(root);
}

void BST::destroy( Node*& node )
{
    if( node == NULL )
        return;
    destroy(node->left);
    destroy(node->right);

    delete node;
    node = NULL;
    size--;
}

int BST::getSize() const
{
    return size;
}

bool BST::isEmpty() const
{
    return size == 0;
}

int BST::getMin() const
{
    Node* tmp = root;
    while( tmp->left )
    {
        tmp = tmp->left;
    }
    return tmp->data;
}

int BST::getMax() const
{
    Node* tmp = root;
    while( tmp->right )
    {
        tmp = tmp->right;
    }
    return tmp->data;
}

void BST::push( int x )
{
    if( contains(x) )
       return;
    Node* tmp = root;
    Node* parent_tmp = NULL;
    while( tmp )
    {
        parent_tmp = tmp;
        if( x < tmp->data )
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }

    tmp = new Node(x);
    if( size == 0 )
        root = tmp;
    else
    {
        if( x <= parent_tmp->data )
            parent_tmp->left = tmp;
        else
            parent_tmp->right = tmp;
    }
    size++;
}

Node*& BST::findNode( int x )
{
    Node* tmp = root;
    while( tmp && tmp->data != x )
    {
        if( x < tmp->data )
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    return tmp;
}

bool BST::contains( int x )
{
    Node*& node = findNode(x);
    if( node == NULL )
        return 0;
    return 1;
}

Node*& BST::search( int x )
{
    return findNode(x);
}

void BST::popMin()
{
    if(root == NULL)
        return;
    if(size == 1)
    {
        destroy(root);
        return;
    }
    Node* parent = NULL;
    Node* tmp = root;
    while(tmp->left)
    {
        parent = tmp;
        tmp = tmp->left;
    }
    if(parent)
        parent->left = tmp->right;
    else /// in case when root has no left subtree, i.e. root is the minimum element in the tree
        root = tmp->right;

    delete tmp;
    size--;
}

void BST::popMax()
{
    if(root == NULL)
        return;
    if(size == 1)
    {
        destroy(root);
        return;
    }
    Node* parent = NULL;
    Node* tmp = root;
    while(tmp->right)
    {
        parent = tmp;
        tmp = tmp->right;
    }
    if(parent)
        parent->right = tmp->left;
    else /// in case when root has no right subtree, i.e. root is the maximum element in the tree
        root = tmp->left;

    delete tmp;
    size--;
}

int BST::calcHeightOfNode(Node*& node)
{
    if(node==NULL)
    {
        return 0;
    }

    return 1 + max( calcHeightOfNode(node->left),
                calcHeightOfNode(node->right));
}

int BST::getHeightOfNode(int x)
{
    Node* tmp = findNode(x);

    return calcHeightOfNode(tmp)-1;
}

int BST::getHeightOfTree()
{
    if( root == NULL )
        return -1;
    return getHeightOfNode(root->data);
}


int BST::getLevel( int x )
{
    Node* tmp = root;
    int level = 1;
    while( tmp )
    {
        if( x < tmp->data )
            tmp = tmp->left;
        else if( x > tmp->data )
            tmp = tmp->right;
        else
            return level;
        level++;
    }

    return 0;
}

int BST::getDepth( int x )
{
    return getLevel(x)-1;
}

void BST::preorder()
{
    print_preorder(root);
    cout << endl;
}

void BST::print_preorder( Node*& node )
{
    if( node == NULL )
        return;

    cout << node->data << " ";
    print_preorder(node->left);
    print_preorder(node->right);
}

void BST::inorder()
{
    print_inorder(root);
    cout << endl;
}

void BST::print_inorder( Node*& node )
{
    if( node == NULL )
        return;

    print_inorder(node->left);
    cout << node->data << " ";
    print_inorder(node->right);
}

void BST::getElementsInRow( vector<int>& v, int k )
{
    getElementsInRowFromRoot(v, root, k);
}

void BST::getElementsInRowFromRoot(vector<int>& v, Node*& node, int k)
{
    if( node == NULL )
        return;
    if( k == 0 )
    {
        v.push_back(node->data);
        return;
    }

    getElementsInRowFromRoot(v, node->left, k-1);
    getElementsInRowFromRoot(v, node->right, k-1);
}


//int main()
//{
//    BST T;
//    T.push(7);
//    T.push(4);
//    T.push(1);
//    T.push(2);
//    T.push(3);
//    T.push(5);
//    T.push(9);
//    T.push(8);
//    T.push(13);
//    T.push(10);
//    T.push(14);
//    cout << "Size of tree: " << T.getSize() << endl;
//
//    for( int i = 1; i <= 6; i++ )
//    {
//        cout << "For node: " << i << endl;
//        cout << "Level:  " << T.getLevel(i) << endl;
//        cout << "Depth:  " << T.getDepth(i) << endl;
//        cout << "Height: " << T.getHeightOfNode(i) << endl << endl;;
//    }
//
//    T.preorder();
//
//    T.clear();
//    /*T.push(5);
//    T.push(1);
//    T.push(10);
//    T.push(2);
//    T.push(11);
//    T.push(0);
//    T.push(7);*/
//    T.push(10);
//    T.push(5);
//    T.push(20);
//    T.push(1);
//    T.push(7);
//    T.push(11);
//    T.push(25);
//    T.push(0);
//    T.push(6);
//    T.push(17);
//
//    vector <int> v;
//    int k = 3;
//    T.getElementsInRow(v, k);
//    for( int i = 0; i < v.size(); i++ )
//        cout << v[i] << " ";
//    cout << endl;
//
//    return 0;
//}
//
