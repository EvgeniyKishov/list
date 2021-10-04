#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void lprint(struct list *list)
{
	for_each(l, list)
		printf("%4.3lf\n", *(double *)l->data);
}

struct list *find_double(struct list *list, double *val)
{
	for_each(item, list)
		if (*(double *)item->data == *val)
			return item;
	return NULL;
}

struct list *find_by_id(struct list *list, int *id)
{
	for_each(item, list)
		if (*(int *)item->data == *id)
			return item;
	return NULL;
}

struct node {
	int id;
	double x, y;
};

struct elem {
	int id;
	struct node **nodes;
};

void free_elem(struct elem *el)
{
	free(el->nodes);
}

void create_node(struct node **node, struct node *node_data)
{
	*node = calloc(1, sizeof(struct node));
	if (*node == NULL)
		return;
	(*node)->id = node_data->id;
	(*node)->x = node_data->x;
	(*node)->y = node_data->y;
}
/*
int main()
{
	struct node *node1 = NULL, *node2 = NULL,
		*node3 = NULL, *node4 = NULL;
	struct list *nodes = NULL;
	struct node node_data = { 0 };

	node_data.id = 1;
	node_data.x = 0;
	node_data.y = 0;
	create_node(&node1, &node_data);

	node_data.id = 2;
	node_data.x = 1;
	node_data.y = 0;
	create_node(&node2, &node_data);

	node_data.id = 3;
	node_data.x = 1;
	node_data.y = 1;
	create_node(&node3, &node_data);

	node_data.id = 4;
	node_data.x = 0;
	node_data.y = 1;
	create_node(&node4, &node_data);

	push_list(&nodes, node1);
	push_list(&nodes, node2);
	push_list(&nodes, node3);
	push_list(&nodes, node4);

	struct elem *elem1 = NULL, *elem2 = NULL;
	elem1 = calloc(1, sizeof(struct elem));
	elem2 = calloc(1, sizeof(struct elem));
	if ((elem1 == NULL) || (elem2 == NULL))
		return 0;
	elem1->id = 1;
	elem1->nodes = calloc(3, sizeof(struct node *));
	if (elem1->nodes == NULL)
		return 0;
	elem2->id = 2;
	elem2->nodes = calloc(3, sizeof(struct node *));
	if (elem2->nodes == NULL)
		return 0;
	struct list *enode = NULL;
	for (int i = 1; i <= 4; i++) {
		enode = find_by_id(nodes, &i);
		if (enode != NULL) {
			if (i <= 3)
				elem1->nodes[i-1] = (struct node *)enode->data;
			if (i >= 2)
				elem2->nodes[i-2] = (struct node *)enode->data;
		}
	}

	struct list *elems = NULL;
	push_list(&elems, elem1);
	push_list(&elems, elem2);

	//pop_list(&elems, free_elem);
	//pop_list(&elems, free_elem);
	int e = 1;
	delete_list_item(&elems, &e, find_by_id, free_elem);

	delete_list(&nodes, NULL);

	return 0;
}
*/

int main()
{
	struct list *doubles = NULL;
	/*
	double *a = NULL, *b = NULL, *c = NULL;
	a = calloc(1, sizeof(double));		
	*a = 2.2;	
	b = calloc(1, sizeof(double));
	*b = 4.1;
	c = calloc(1, sizeof(double));
	*c = 5.6;
	*/
	double a = 2.2, b = 4.1, c = 5.6;
	push_list(&doubles, &a, !DATA_ALLOC);
	push_list(&doubles, &b, !DATA_ALLOC);
	push_list(&doubles, &c, !DATA_ALLOC);

	printf("before del: \n");
	lprint(doubles);
	double f = 4.1;
	delete_list_item(&doubles, &f, find_double, NULL);
	printf("after del: \n");
	lprint(doubles);

	delete_list(&doubles, NULL);

	//pop_list(&doubles, NULL);
	//pop_list(&doubles, NULL);

	return 0;
}
