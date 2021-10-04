#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

/**
* free_list_item() - освобождение памяти из-под элемента списка
* @item: элемент списка
* @free_data(): функция освобождения памяти для данных
* 
* Функция используется в процессе удаления элемента списка @item
*/
static void free_list_item(struct list **item, void (*free_data)(void *data))
{
	if (*item != NULL) {
		if (free_data != NULL)
			free_data((*item)->data);
		if ((*item)->is_data_alloc)
			DEALLOC((*item)->data);
	}
	DEALLOC(*item);
}

int DLL push_list(struct list **head, void *data, bool is_data_alloc)
{
	struct list *new_head = calloc(1, sizeof(struct list));
	if (new_head == NULL)
		return MALLOC_ERR;
	new_head->data = data;
	new_head->is_data_alloc = is_data_alloc;
	new_head->next = *head;
	new_head->prev = NULL;
	if (*head != NULL)
		(*head)->prev = new_head;
	*head = new_head;
	return SUCCESS;
}

/**
* shrink_list() - "схлопывание" списка
* @del_item: удаляемый элемент
* @free_data(): функция освобождения памяти для данных
* 
* Функция перекидывает связь через удаляемый элемент списка.
*/
static void shrink_list(struct list **del_item, void (*free_data)(void *data))
{
	(*del_item)->prev->next = (*del_item)->next;
	//проверка на то, что удаляется не последний элемент:
	if ((*del_item)->next != NULL)
		(*del_item)->next->prev = (*del_item)->prev;
	free_list_item(del_item, free_data);
}

int DLL delete_list_item(struct list **head, void *find_data,
			 struct list *(*find)(struct list *head, void *data),
		         void (*free_data)(void *data))
{
	struct list *del_item = NULL;

	del_item = find(*head, find_data);
	if (del_item == NULL)
		return ITEM_NOT_FOUND;
	if (del_item == *head)
		pop_list(head, free_data);
	else
		shrink_list(&del_item, free_data);

	return SUCCESS;
}

void DLL pop_list(struct list **head, void (*free_data)(void *data))
{
	struct list *tmp = NULL;

	tmp = (*head)->next;
	free_list_item(head, free_data);
	*head = tmp;
	if (*head != NULL)
		(*head)->prev = NULL;
}

void DLL delete_list(struct list **head, void (*free_data)(void *data))
{
	while (*head != NULL)
		pop_list(head, free_data);
}

double DLL list_ver()
{
	double ver = 1.04;
#ifdef _DEBUG
	return -ver;
#else
	return ver;
#endif
}