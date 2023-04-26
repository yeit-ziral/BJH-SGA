#include "BST.h"
#include <iostream>

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);

	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}

	Node* node = _root;
	Node* parent = nullptr;
	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;

		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;
	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* root)
{
	// ������ȸ : ��Ʈ - ���� - ������
	// ������ȸ : ���� - ��Ʈ - ������
	// ������ȸ : ���� - ������ - ��Ʈ

	if (root == nullptr)
		return;

	//// ����
	//std::cout << root->key << std::endl;
	//PrintTree(root->left);
	//PrintTree(root->right);

	// ����
	PrintTree(root->left);
	std::cout << root->key << std::endl;
	PrintTree(root->right);

	//// ����
	//PrintTree(root->left);
	//PrintTree(root->right);
	//std::cout << root->key << std::endl;
}

Node* BinarySearchTree::Search(Node* root, int key)
{
	/*Node* newNode = new Node(key);

	Node* parent = nullptr;

	while (true)
	{
		if (root == nullptr)
			break;

		if (key == root->key)
			break;

		parent = root;

		if (key < root->key)
		{
			root = root->left;
		}
		else
		{
			root = root->right;
		}
	}

	newNode = root;
	if (newNode == nullptr)
		std::cout << "Can't find" << std::endl;*/

	// 1. �������� ó��
	if (root == nullptr)
		return root;

	// 2. ���ϱ�
	if (root->key == key)
		return root;

	if (key < root->key)
		return Search(root->left, key);
	else
		return Search(root->right, key);

	return nullptr;
}

Node* BinarySearchTree::Min(Node* root)
{
	/*Node* minNode = new Node;

	Node* parent = nullptr;

	while (true)
	{
		if (minNode->left == nullptr)
			break;

		minNode = minNode->left;
	}

	return minNode;*/

	// ����Լ� ���
	if (root == nullptr)
		return nullptr;

	if (root->left != nullptr)
		return Min(root->left);

	return root;
}

Node* BinarySearchTree::Max(Node* root)
{
	/*Node* newNode = new Node;

	Node* parent = nullptr;

	while (true)
	{
		if (root == nullptr)
			break;

		parent = root;

		root = root->right;
	}

	newNode->parent = parent->parent;
	newNode = parent;*/

	// ����Լ� ���
	if (root == nullptr)
		return nullptr;

	if (root->right != nullptr)
		return Max(root->right);

	return root;
}

Node* BinarySearchTree::Previous(Node* root)
{
	if (root->left == nullptr)
		return nullptr;
	else
		root = root->left;

	if (root->right == nullptr)
		return root;
	else
		return Max(root);
}

Node* BinarySearchTree::Next(Node* root)
{
	if (root->right == nullptr)
		return nullptr;
	else
		root = root->right;

	if (root->left == nullptr)
		return root;
	else
		return Min(root);
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	// node1�� ��Ʈ��忴��
	if (node1->parent == nullptr)
		_root = node2;

	// node1�� �θ��ʿ��� ���ʿ� �ִ� ����� ��
	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	// node1�� �θ��ʿ��� �����ʿ� �ִ� ����� ��
	else
	{
		node1->parent->right = node2;
	}

	if (node2 != nullptr)
	{
		node2->parent = node1->parent;
	}

	delete node1;
}

void BinarySearchTree::Delete(Node* Node)
{
}
