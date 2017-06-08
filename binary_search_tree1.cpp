// binary_search_tree1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
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
			(prev_node->key < node->key ? prev_node->right_child : prev_node->left_child) = node;
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
			//std::cout << start->key << std::endl;
			printf("%5d", start->key);
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
		while (n)
		{
			if (n->key == key)
			{
				return n;
			}
			n = (n->key < key ? n->right_child : n->left_child);
		}
		return NULL;
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
				while (prev_node && (prev_node->right_child == input_node))
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
	bool remove(keyT key)
	{
		Node* removing_node = search(key);
		if (removing_node)
		{
			Node* fact_rm_node; // node, which we will physically remove
			if ((removing_node->right_child) && (removing_node->left_child))
			{
				fact_rm_node = get_successor(removing_node);
				removing_node->key = fact_rm_node->key;
			}
			else
			{
				fact_rm_node = removing_node;
			}
			// fact_rm_node always has'nt one child
			Node* child;
			if (fact_rm_node->left_child)
			{
				child = fact_rm_node->left_child;
			}
			else
			{
				child = fact_rm_node->right_child;
			}
			if (child)
			{
				child->parent = fact_rm_node->parent;
				// if we deleting root
				if (fact_rm_node->parent == NULL)
				{
					root = child;
				}
				(fact_rm_node->parent->right_child == fact_rm_node ? fact_rm_node->parent->right_child : fact_rm_node->parent->left_child) = child;
			}
			else
			{
				(fact_rm_node->parent->right_child == fact_rm_node ? fact_rm_node->parent->right_child : fact_rm_node->parent->left_child) = NULL;
			}
			delete fact_rm_node;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool remove(Node* removing_node)
	{
		if (removing_node)
		{
			Node* fact_rm_node; // node, which we will physically remove
			if ((removing_node->right_child) && (removing_node->left_child))
			{
				fact_rm_node = get_successor(removing_node);
				removing_node->key = fact_rm_node->key;
			}
			else
			{
				fact_rm_node = removing_node;
			}
			// fact_rm_node always has'nt one child
			Node* child;
			if (fact_rm_node->left_child)
			{
				child = fact_rm_node->left_child;
			}
			else
			{
				child = fact_rm_node->right_child;
			}
			if (child)
			{
				child->parent = fact_rm_node->parent;
				// if we deleting root
				if (fact_rm_node->parent == NULL)
				{
					root = child;
				}
				(fact_rm_node->parent->right_child == fact_rm_node ? fact_rm_node->right_child : fact_rm_node->left_child) = child;
			}
			else
			{
				(fact_rm_node->parent->right_child == fact_rm_node ? fact_rm_node->right_child : fact_rm_node->left_child) = NULL;
			}
			delete fact_rm_node;
			return true;
		}
		else
		{
			return false;
		}
	}
	void print_tree()
	{
		print_subtree(root, 0);
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
	void print_offset(int ofs)
	{
		// this function used for printing tree
		for (int i = 0; i < ofs; i++)
		{
			printf(" ");
		}
	}
	void print_subtree(Node* root, int offset = 0)
	{
		const int offset_step = 6;
		std::cout << root->key << std::endl;
		if (root->left_child)
		{
			print_offset(offset);
			printf("|\n");
			print_offset(offset);
			printf("+-----");
			print_subtree(root->left_child, offset + offset_step);
		}
		if (root->right_child)
		{
			print_offset(offset);
			printf("|\n");
			print_offset(offset);
			printf("+-----");
			print_subtree(root->right_child, offset + offset_step);
		}
		printf("\n");
	}
};

inline bool cmp(int a, int b)
{
	return a < b;
}
int main()
{
	srand(time(NULL));
	Tree<int> tree;
	for (int i = 0; i< 10; i++)
	{
		int el = rand() % 30;
		tree.add_element(el);
	}
	tree.print_tree();
	system("pause");
	return 0;
}

