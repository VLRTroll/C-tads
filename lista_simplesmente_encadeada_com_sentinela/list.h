#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
typedef int* Item; /* If you need a generic list, just set this type as void* */
typedef struct _list_ List;

/* Return an empty list */
List* create(void);

/* Verify if there is any item in the list */
bool empty(List* list);

/* Return the number of itens in the list */
int length(List* list);

/* Put the item as first in the list */
void append(List* list, Item item);

/* Behavior:
 * If index < 0 or : don't insert
 * If index > lenght(list): don't insert
*/
void insertAt(List* list, Item item, int index);

/* Verify if the item is in the list */
bool contains(List* list, Item item, int (*cmpItem)(Item,Item));

/* Return the index of the item in the list. If it doesn't exist, return -1 */
int find(List* list, Item item, int (*cmpItem)(Item,Item));

/* Take the n-elemnet in the list */
Item take(List* list, int index);

/* Apply the callback function to all itens in the list */
void map(List* list, void (*func)(Item));

/* Remove the last item in the list, if it's an empty list, return NULL */
Item pop(List* list);

/* Remove a specific item from the list */
void removeItem(List* list, Item item, int (*cmpItem)(Item,Item), void (*destroyItem)(Item));

/* Remove the n-item from the list */
Item removeAt(List* list, int index);

/* Free all memory used by the list and all its itens */
void destroy(List* list, void (*destroyItem)(Item));

#endif
