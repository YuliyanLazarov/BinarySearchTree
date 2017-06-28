# BinarySearchTree
#include <iostream>
#include "BinarySearchTree.cpp"

using namespace std;


int getSumOnLevel(int k, BST& tree)
{
	vector<int> nodes;
	tree.getElementsInRow(nodes, k);
	int result = 0;
	for (int i = 0; i < nodes.size(); i++)
	{
		result += nodes[i];
	}
	return result;

}


void printLevels(BST& tree)
{
	vector<int> nodes;
	int k = tree.getHeightOfTree();
	while (k >= 0)
	{
		vector<int> nodes;
		tree.getElementsInRow(nodes, k);
		for (int i = 0; i < nodes.size(); i++)
		{
			cout << nodes[i] << " ";
		}
		cout << endl;
		k--;
	}
}



bool isPerfectlyBalanced(BST& tree)
{
	if (tree.isEmpty())
	{
		return true;
	}
	if (abs(tree.leftTree().getSize() - tree.rightTree().getSize()) <= 1)
	{
		if (isPerfectlyBalanced(tree.leftTree()) && isPerfectlyBalanced(tree.rightTree()))
		{
			return true;
		}
	}
	return false;
}

bool isBalanced(BST& tree)
{
	if (tree.isEmpty())
	{
		return true;
	}
	if (abs(tree.leftTree().getHeightOfTree() - tree.rightTree().getHeightOfTree()) <= 1)
	{
		if (isPerfectlyBalanced(tree.leftTree()) && isPerfectlyBalanced(tree.rightTree()))
		{
			return true;
		}
	}
	return false;
}

int balance(BST& tree)
{
	if (isPerfectlyBalanced(tree))
	{
		return 2;
	}

	if (isBalanced(tree))
	{
		return 1;
	}

	return 0;
}

int main()
{
	BST tree;
	tree.push(3);
	tree.push(2);
	tree.push(1);
	tree.push(4);
	tree.push(5);
	tree.push(6);
	//cout << getSumOnLevel(2, tree) << endl;
	//printLevels(tree);
	cout << balance(tree) << endl;
	return 0;
