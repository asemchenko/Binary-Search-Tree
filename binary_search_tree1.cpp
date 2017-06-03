// binary_search_tree1.cpp: ���������� ����� ����� ��� ����������� ����������.
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
Node* get_min_value()
{
	Node* n = root;
	if (n)
	{
		while (n->left_child != NULL)
		{
			n = n->left_child;
		}
		return n;
	}
	return NULL;
}
Node* get_min_value(Node* n)
{
	if (n)
	{
		while (n->left_child != NULL)
		{
			n = n->left_child;
		}
		return n;
	}
	return NULL;
}
Node* get_max_value()
{
	Node* n = root;
	if (n)
	{
		while (n->right_child)
		{
			n = n->right_child;
		}
		return n;
	}
	return NULL;
}
Node* get_max_value(Node* n)
{
	if (n)
	{
		while (n->right_child)
		{
			n = n->right_child;
		}
		return n;
	}
	return NULL;
}
Node* search(keyT key)
{
	Node* n = root;
	if (!n)
	{
		return NULL;
	}
	else
	{
		while (n)
		{
			if (n->key == key)
			{
				return n;
			}
			n = n->key < key ? n->right_child : n->left_child;
		}
	}
}
Node* get_preccessor(keyT key)
{
	Node* input_node = search(key);
	if (input_node != NULL)
	{
		if (input_node->left_child)
		{
			return get_max_value(input_node->left_child);
		}
		else
		{
			Node* prev_node = input_node->parent;
			while (prev_node && (prev_node->right_child == input_node) )
			{
				input_node = prev_node;
				prev_node = prev_node->parent;
			}
			return prev_node;
		}
	}
	else
	{
		return NULL;
	}
}
Node* get_preccessor(Node* input_node)
{
	if (input_node != NULL)
	{
		if (input_node->left_child)
		{
			return get_max_value(input_node->left_child);
		}
		else
		{
			Node* prev_node = input_node->parent;
			while (prev_node && (prev_node->left_child == input_node))
			{
				input_node = prev_node;
				prev_node = prev_node->parent;
			}
			return prev_node;
		}
	}
	else
	{
		return NULL;
	}
}
Node* get_successor(keyT key)
{
	Node* input_node = search(key);
	if (input_node)
	{
		if (input_node->right_child)
		{
			return get_min_value(input_node->right_child);
		}
		else
		{
			Node* p = input_node->parent;
			while ((p) && (p->right_child == input_node))
			{
				input_node = p;
				p = p->parent;
			}
			return p;
		}
	}
	else
	{
		return NULL;
	}
}
Node* get_successor(Node* input_node)
{
	if (input_node)
	{
		if (input_node->right_child)
		{
			return get_min_value(input_node->right_child);
		}
		else
		{
			Node* p = input_node->parent;
			while ((p) && (p->right_child == input_node))
			{
				input_node = p;
				p = p->parent;
			}
			return p;
		}
	}
	else
	{
		return NULL;
	}
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
	for (int i = 200; i >= 0; i--)
	{
		tree.add_element(i);
	}
	std::cout<<tree.get_successor(tree.search(12))->key<<std::endl;
	system("pause");
	return 0;
}

