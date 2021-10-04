#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef DLL
	#define DLL __declspec(dllexport)
#endif

#ifndef MALLOC_ERR
	#define MALLOC_ERR -1
#endif
#ifndef SUCCESS
	#define SUCCESS 0
#endif
#ifndef ITEM_NOT_FOUND
	#define ITEM_NOT_FOUND -1
#endif
#ifndef DEALLOC
	#define DEALLOC(obj) {free(obj); obj = NULL;}
#endif

#define DATA_ALLOC true

/**
* list.dll - ���������� ��� ������ � ����������� �������� ������ ����
* 
* ������������ ������ ������������ ��������� �������:
* 
* free_data() - ������������ ������ ��� ������
* @data: ������ 
* 
* find() - ����� �������� � ������
* @head: ������� ������
* @data: ������ ��� ������
* ������������ ��������: ��������� �� ��������� ������� ������ ��� NULL
* 
* v1.04, 02.09.2021 
*/

/**
* for_each() - �������-������ ��� ������������ �� ������
* @item: ��������
* @list_: ������
*/
#define for_each(item, list_) \
	for (struct list *item = list_; item; item = item->next) 

/**
* struct list - ���������� ������ ������ ����
* @data: ��������� �� ������
* @is_data_alloc: ���� ������������� ��������� ������ ��� ������
* @prev: ���������� �������
* @next: ��������� �������
*/
struct list {
	void *data;
	bool is_data_alloc;
	struct list *prev;
	struct list *next;
};

/**
* push_list() - �������� ("�����������") ������� � ������
* @head: ������� ������
* @data: ������
*/
int DLL push_list(struct list **head, void *data, bool is_data_alloc);

/**
* delete_list_item() - �������� �������� ������
* @head: ������ ������
* @find_data: ������ ��� ������ ��������
* @find(): ������� ������
* @free_data(): ������� ������������ ������ ��� ������
*/
int DLL delete_list_item(struct list **head, void *find_data,
			 struct list *(*find)(struct list *head, void *data),
			 void (*free_data)(void *data));

/**
* pop_list() - �������� ������� (���������� ��������) ������
* @head: ������ ������
* @free_data(): ������� ������������ ������ ��� ������
*/
void DLL pop_list(struct list **head, void (*free_data)(void *data));

/**
* delete_list() - �������� ������
* @head: ������ ������
* @free_data(): ������� ������������ ������ ��� ������
*/
void DLL delete_list(struct list **head, void (*free_data)(void *data));

/**
* list_ver() - ��������� ������ dll
* @void
*/
double DLL list_ver();