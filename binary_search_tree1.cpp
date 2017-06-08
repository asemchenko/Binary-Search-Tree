// binary_search_tree1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
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
		node->parent = NULL;

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
	void add_element_to_root(keyT element)
	{
		Node* node = new Node;
		node->key = element;
		node->right_child = NULL;
		node->left_child = NULL;
		node->parent = NULL;

		insert_to_root_subtree(root, NULL, node);
	}

	Node* get_root_ptr()
	{
		return root;
	}

	void print_sorted(Node* start)
	{
		// this func print elements of tree in sorted view
		if (start != NULL)
		{
			print_sorted(start->left_child);
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

	void right_rotation(Node* n)
	{
		// this func implement right rotation tree relatively node n
		if (n == NULL)
		{
			return;
		}

		Node* left_child_n = n->left_child;
		if (left_child_n == NULL)
		{
			return;
		}
		// if n has parent
		left_child_n->parent = n->parent;
		if (n->parent)
		{
			// making node left_child child of n->parent
			(n->parent->left_child == n ? n->parent->left_child : n->parent->right_child) = left_child_n;
		}
		else
		{
			// if n is root
			root = left_child_n;
		}
		// changing left child of n
		n->left_child = left_child_n->right_child;
		if (n->left_child)
		{
			n->left_child->parent = n;
		}
		left_child_n->right_child = n;
		n->parent = left_child_n;
	}

	void left_rotation(Node* n)
	{
		// this func implement left rotation tree relatively node n
		if (n == NULL)
		{
			return;
		}

		Node* right_child_n = n->right_child;
		if (right_child_n == NULL)
		{
			return;
		}
		// if n has parent
		right_child_n->parent = n->parent;
		if (n->parent)
		{
			// making node left_child child of n->parent
			(n->parent->right_child == n ? n->parent->right_child : n->parent->left_child) = right_child_n;
		}
		else
		{
			// if n is root
			root = right_child_n;
		}
		// changing left child of n
		n->right_child = right_child_n->left_child;
		if (n->right_child)
		{
			n->right_child->parent = n;
		}
		right_child_n->left_child = n;
		n->parent = right_child_n;
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
		if (root->right_child)
		{
			print_offset(offset);
			printf("|\n");
			print_offset(offset);
			printf("R-----");
			print_subtree(root->right_child, offset + offset_step);
		}
		if (root->left_child)
		{
			print_offset(offset);
			printf("|\n");
			print_offset(offset);
			printf("L-----");
			print_subtree(root->left_child, offset + offset_step);
		}
		printf("\n");
	}
	void insert_to_root_subtree(Node* &root_subtree, Node* root_subtree_p, Node* element)
	{
		// this func is used in function add_element_to_root
		// this func add element to root subtree with root root_subtree
		if (root_subtree == NULL)
		{
			root_subtree = element;
			element->parent = root_subtree_p;
		}
		else
		{
			if (element->key < root_subtree->key)
			{
				insert_to_root_subtree(root_subtree->left_child, root_subtree, element);
				right_rotation(root_subtree);
			}
			else
			{
				insert_to_root_subtree(root_subtree->right_child, root_subtree, element);
				left_rotation(root_subtree);
			}
		}
	}
};
int main()
{
	srand(time(NULL));
	Tree<int> tree;
	int count_nodes;
	printf("How many nodes you want insert? ");
	scanf_s("%d", &count_nodes);
	printf("\n");
	/*
	for (int i = 0; i < count_nodes; i++)
	{
		int k;
		printf("Input node key: ");
		scanf_s("%d", &k);
		printf("\n");
		tree.add_element(k);
		printf("Tree: \n");
		tree.print_tree();
	}*/
	while (true)
	{
		int k;
		printf("Input node key: ");
		scanf_s("%d", &k);
		printf("\n");
		tree.add_element_to_root(k);
		printf("Tree: \n");
		tree.print_tree();
	}
	tree.print_tree();
	system("pause");
	return 0;
}

