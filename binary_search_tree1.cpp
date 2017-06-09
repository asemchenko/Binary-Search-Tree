// binary_search_tree1.cpp: определяет точку входа для консольного приложения.
//

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "tree_implementation.h"
using namespace std;
int main()
{
	srand(time(NULL));
	Tree<int> tree;
	int count_nodes;
	printf("How many nodes you want insert? ");
	scanf_s("%d", &count_nodes);
	printf("\n");
	
	for (int i = 0; i < count_nodes; i++)
	{
		int k;
		printf("Input node key: ");
		scanf_s("%d", &k);
		printf("\n");
		tree.insertRandom(k);
		printf("Tree: \n");
		tree.show(tree.get_root_ptr(),tree.get_high(tree.get_root_ptr()));
	}
	/*while (true)
	{
		int k;
		printf("Input node key: ");
		scanf_s("%d", &k);
		printf("\n");
		tree.add_element_to_root(k);
		printf("Tree: \n");
		tree.print_tree();
	}*/
	tree.print_tree();
	system("pause");
	return 0;
}

