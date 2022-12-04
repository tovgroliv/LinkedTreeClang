#include <LinkedTree.h>
#include <stdlib.h>

/*****************	Структуры	*********************/

typedef struct node
{
	struct tree *	child;
	struct node *	next;
	void *			value;
}
node_t;

/**************	Статичные функции	*****************/

static	void			TreeRemoveBottom	(tree_t *);
static	void			TreeRemoveTop		(tree_t *);
static	node_t *		NodeCreate			(void *, tree_t *);
static	void			NodeRemove			(node_t *, unsigned int);

/**
 * Создать новый список.
 * Вход		:	tree_t **		-	указатель на заголовок списка
 * 				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
 * Выход	:	отсутствует
*/
void TreeCreate(tree_t ** tree_tag, unsigned int clear)
{
	tree_t * tree	= malloc(sizeof(tree_t));
	tree->first		= 0;
	tree->last		= 0;
	tree->count		= 0;
	tree->clear		= clear;
	*tree_tag		= tree;
}

/**
 * Удалить список.
 * Вход		:	tree_t **		-	указатель на заголовок списка
 * Выход	:	отсутствует
*/
void TreeRemove(tree_t ** tree_tag)
{
	tree_t *	tree	= *tree_tag;
	if (!tree)
	{
		return;
	}
	
	while (tree->count > 0)
	{
		TreeRemoveBottom(tree);
	}

	free(tree);
	*tree_tag = 0;
}

/**
 * Вставить запись в начало списка.
 * Вход		:	tree_t *		-	указатель списка
 * 				tree_t *		-	дочернее дерево
 * 				void *			-	значение для вставки
 * Выход	:	отсутствует
*/
void TreeInsertBottom(tree_t * tree, tree_t * child, void * value)
{
	if (!tree)
	{
		return;
	}

	node_t * node	= NodeCreate(value, child);
	node->next		= tree->first;
	
	if (!tree->last)
	{
		tree->last = node;
	}
	
	tree->first = node;
	tree->count++;
}

/**
 * Вставить запись в конец списка.
 * Вход		:	tree_t *		-	указатель списка
 * 				tree_t *		-	дочернее дерево
 * 				void *			-	значение для вставки
 * Выход	:	отсутствует
*/
void TreeInsertTop(tree_t * tree, tree_t * child, void * value)
{
	if (!tree)
	{
		return;
	}

	node_t *	node	= NodeCreate(value, child);
	node_t *	lt		= tree->last;
	
	if (lt)
	{
		lt->next = node;
	}
	
	if (!tree->first)
	{
		tree->first = node;
	}
	
	tree->last = node;
	tree->count++;
}

/**
 * Получить значение записи списка по индексу.
 * Вход		:	tree_t *		-	указатель списка
 * 				tree_t **		-	указатель на указатель дочернего списка
 * 				unsigned int	-	идентификатор записи
 * Выход	:	void *			-	указатель на значение записи списка
*/
void * TreeGetAt(tree_t * tree, tree_t ** child, unsigned int id)
{
	if (!tree)
	{
		return 0;
	}
	
	if (id < 0 || id >= tree->count)
	{
		return 0;
	}

	node_t *		node	= 0;
	unsigned int	i		= 0;

	if (id == 0)
	{
		node = tree->first;
	}
	else if (id == tree->count - 1)
	{
		node = tree->last;
	}
	else
	{
		node = tree->first;
		i = 0;
		while (node)
		{
			if (id == i)
			{
				break;
			}
			node = node->next;
			i++;
		}
	}

	if (!node)
	{
		return 0;
	}

	if (child)
	{
		*child = node->child;
	}

	return node->value;
}

/**
 * Удалить запись списка по индексу.
 * Вход		:	tree_t *		-	указатель списка
 * 				unsigned int	-	идентификатор записи
 * Выход	:	отсутствует
*/
void TreeRemoveAt(tree_t * tree, unsigned int id)
{
	if (!tree)
	{
		return;
	}

	if (id == 0)
	{
		TreeRemoveBottom(tree);
	}
	else if (id == tree->count - 1)
	{
		TreeRemoveTop(tree);
	}
	else
	{
		node_t *		node	= tree->first;
		node_t *		next	= 0;
		unsigned int	i		= 0;

		while (node)
		{
			if (id - 1 == i)
			{
				break;
			}
			node = node->next;
			i++;
		}
		next = node->next;
		node->next = next->next;

		NodeRemove(next, tree->clear);
		tree->count--;
	}
}

/**
 * Создать новую запись списка.
 * Вход		:	void *			-	значение для вставки
 * Выход	:	node_t *		-	указатель новой записи списка
*/
static node_t * NodeCreate(void * value, tree_t * child)
{
	node_t * node	= malloc(sizeof(node_t));
	node->value		= value;
	node->next		= 0;
	node->child		= child;
	return node;
}

/**
 * Удалить запись списка.
 * Вход		:	node_t *		-	указатель записи списка
 *				unsigned int	-	1 / 0 - освободить память значений записей / не освобождать память значений записей
 * Выход	:	отсутствует
*/
static void NodeRemove(node_t * node, unsigned int clear)
{
	if (!node)
	{
		return;
	}

	if (node->child)
	{
		TreeRemove(&node->child);
	}

	if (clear)
	{
		if (node->value)
		{
			free(node->value);
		}
	}

	free(node);
}

/**
 * Удалить запись в начале списка.
 * Вход		:	tree_t *		-	указатель списка
 * Выход	:	отсутствует
*/
static void TreeRemoveBottom(tree_t * tree)
{
	if (!tree)
	{
		return;
	}

	node_t *	first	= tree->first;

	if (!tree->count || !tree->first)
	{
		return;
	}

	if (tree->count == 1)
	{
		tree->first = 0;
		tree->last = 0;
	}
	else
	{
		tree->first = first->next;
	}

	NodeRemove(first, tree->clear);
	tree->count--;
}

/**
 * Удалить запись в конце списка.
 * Вход		:	tree_t *		-	указатель списка
 * Выход	:	отсутствует
*/
static void TreeRemoveTop(tree_t * tree)
{
	if (!tree)
	{
		return;
	}

	node_t *	last	= tree->last;

	if (!tree->count || !tree->last)
	{
		return;
	}

	if (tree->count == 1)
	{
		tree->first = 0;
		tree->last = 0;
	}
	else
	{
		node_t * pv	= tree->first;
		while (pv)
		{
			if(pv->next == last)
			{
				pv->next = 0;
				tree->last = pv;
			}
			pv = pv->next;
		}
	}

	NodeRemove(last, tree->clear);
	tree->count--;
}