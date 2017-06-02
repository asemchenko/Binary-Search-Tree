// binary_search_tree1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
template <typename keyT>
class Tree
{
	struct Node
	{
		keyT key;
		Node* left_child;
		Node* right_child;
		Node* parent;
	};
public:
	~Tree()
	{
		erase_memory(root);
	}
	void add_element(keyT element)
	{
		Node* node = new Node;
		node->key = element;
		node->right_child = NULL;
		node->left_child = NULL;

		Node* prev_node = NULL;
		Node *current = root;
		while (current != NULL)
		{
			prev_node = current;
			if (current->key < element)
			{
				current = current->right_child;
			}
			else
			{
				current = current->left_child;
			}
		}
		if (prev_node == NULL)
		{
			root = node;
		}
		else
		{
			node->parent = prev_node;
			prev_node->key < node->key ? prev_node->right_child : prev_node->left_child = node;
		}
	}
Node* get_root_ptr()
{
	return root;
}
void print_sorted(Node* start)
{
	if (start != NULL)
	{
		print_sorted(start->left_child);
		std::cout << start->key << std::endl;
		print_sorted(start->right_child);
	}
	return;
}
private:
	Node* root = NULL;
	void erase_memory(Node* vertex_start)
	{
		if (vertex_start == NULL)
		{
			return;
		}
		erase_memory(vertex_start->left_child);
		erase_memory(vertex_start->right_child);
		delete vertex_start;
	}
};
int main()
{
	Tree<int> tree;
	for (int i = 20; i >= 0; i--)
	{
		tree.add_element(i);
	}
	tree.print_sorted(tree.get_root_ptr());
	system("pause");
	return 0;
}

