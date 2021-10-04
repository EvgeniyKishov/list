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
* list.dll - библиотека для работы с двусвязными списками общего вида
* 
* Пользователь должен предоставить следующие функции:
* 
* free_data() - освобождение памяти для данных
* @data: данные 
* 
* find() - поиск элемента в списке
* @head: вершина списка
* @data: данные для поиска
* Возвращаемое значение: указатель на найденный элемент списка или NULL
* 
* v1.04, 02.09.2021 
*/

/**
* for_each() - функция-макрос для итерирования по списку
* @item: итератор
* @list_: список
*/
#define for_each(item, list_) \
	for (struct list *item = list_; item; item = item->next) 

/**
* struct list - двусвязный список общего вида
* @data: указатель на данные
* @is_data_alloc: флаг динамического выделения памяти под данные
* @prev: предыдущий элемент
* @next: следующий элемент
*/
struct list {
	void *data;
	bool is_data_alloc;
	struct list *prev;
	struct list *next;
};

/**
* push_list() - добавить ("протолкнуть") элемент в список
* @head: вершина списка
* @data: данные
*/
int DLL push_list(struct list **head, void *data, bool is_data_alloc);

/**
* delete_list_item() - удаление элемента списка
* @head: начало списка
* @find_data: данные для поиска элемента
* @find(): функция поиска
* @free_data(): функция освобождения памяти для данных
*/
int DLL delete_list_item(struct list **head, void *find_data,
			 struct list *(*find)(struct list *head, void *data),
			 void (*free_data)(void *data));

/**
* pop_list() - удаление вершины (начального элемента) списка
* @head: начало списка
* @free_data(): функция освобождения памяти для данных
*/
void DLL pop_list(struct list **head, void (*free_data)(void *data));

/**
* delete_list() - удаление списка
* @head: начало списка
* @free_data(): функция освобождения памяти для данных
*/
void DLL delete_list(struct list **head, void (*free_data)(void *data));

/**
* list_ver() - получение версии dll
* @void
*/
double DLL list_ver();