#include <iostream>
#include "BinarySearchTree.cpp"


int height(BST tree)
{
    if (tree == NULL)
        return 0;

    return 1 + max(height(tree->left), height(tree->right));
}

int diameter(BST tree)
{
    if (tree == NULL)
        return 0;

    int leftHeight = height(tree->left);
    int rightHeight = height(tree->right);

    int leftDiameter = diameter(tree->left);
    int rightDiameter = diameter(tree->right);

    return max(leftHeight + rightHeight + 1, max(leftDiamter, rightDiameter));
}

int main()
{


    return 0;
}
