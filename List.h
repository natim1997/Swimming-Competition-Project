#ifndef _LIST_
#define _LIST_

typedef void* DATA;

typedef enum { False, True } BOOL;	



typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;



typedef struct
{	
	NODE head;
}LIST;



BOOL	L_init(LIST* pList);
NODE*	L_insert(NODE* pNode, DATA Value);
BOOL	L_delete(NODE* pNode, void freeFunc(void*));
const NODE* L_find(const NODE* pNode, DATA Value, int compare(const void*, const void*));
BOOL	L_free(LIST* pList, void freeFunc(void*));
int		L_print(const LIST* pList, void (*print)( void*));
#endif