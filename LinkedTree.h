#ifndef LINKED_TREE_H
#define LINKED_TREE_H

	/*****************	Структуры	*********************/

	typedef struct tree
	{
		struct node *	first;
		struct node *	last;
		unsigned int	count;
		unsigned int	clear;
	}
	tree_t;

	/*****************	Публичные функции	*************/
	
	/**
	 * Создать новый список.
	 * Вход		:	tree_t **		-	указатель на заголовок списка
	 * 				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
	 * Выход	:	отсутствует
	*/
	void		TreeCreate			(tree_t **, unsigned int);

	/**
	 * Удалить список.
	 * Вход		:	tree_t **		-	указатель на заголовок списка
	 * Выход	:	отсутствует
	*/
	void		TreeRemove			(tree_t **);

	/**
	 * Вставить запись в начало списка.
	 * Вход		:	tree_t *		-	указатель списка
	 * 				tree_t *		-	дочернее дерево
	 * 				void *			-	значение для вставки
	 * Выход	:	отсутствует
	*/
	void		TreeInsertBottom	(tree_t *, tree_t *, void *);

	/**
	 * Вставить запись в конец списка.
	 * Вход		:	tree_t *		-	указатель списка
	 * 				tree_t *		-	дочернее дерево
	 * 				void *			-	значение для вставки
	 * Выход	:	отсутствует
	*/
	void		TreeInsertTop		(tree_t *, tree_t *, void *);

	/**
	 * Получить значение записи списка по индексу.
	 * Вход		:	tree_t *		-	указатель списка
	 * 				tree_t **		-	указатель на указатель дочернего списка
	 * 				unsigned int	-	идентификатор записи
	 * Выход	:	void *			-	указатель на значение записи списка
	*/
	void *		TreeGetAt			(tree_t *, tree_t **, unsigned int);

	/**
	 * Удалить запись списка по индексу.
	 * Вход		:	tree_t *		-	указатель списка
	 * 				unsigned int	-	идентификатор записи
	 * Выход	:	отсутствует
	*/
	void		TreeRemoveAt		(tree_t *, unsigned int);

#endif