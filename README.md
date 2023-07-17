# GCol-List
GCol-List is a generic linked list library for C language.
# Macros

<b>gcolList_destroyData_m: Allow dynamically allocated data to be freed when freeing a node.<b/>
if the data does not to be freed, use ```#undef gcolList_destroyData_m```<br/><br/>
gcolList_pushBack_m: Convert to given literal to a compound literal and passes the address of the resulting anonymous object to the gcolList_pushBack function.<br/><br/>
gcolList_pushFront_m: Same as pushBack_m<br/><br/>
gcolList_insert_m: Same as pushBack_m<br/><br/>
gcolList_remove_m: Same as pushBack_m<br/><br/>
gcolList_search_m: Same as pushBack_m<br/>

# Type definations
```void*: void_ptr```<br/><br/>
```struct gcolList_s: gcolList_t```<br/><br/>
```struct gcolList_s*: gcolList_ptr```<br/>

# Functions
gcolList_initialize: Allocets memory for a list and initializes the list then return the address of new list.<br/><br/>
gcolList_destroy: Frees completed list and all nodes. If gcol_destroyData_m is defined, it also frees the data in the node.<br/><br/>
gcolList_pushBack: Adds the given data to the end of the list.<br/><br/>
gcolList_pushFront: Adds the given data to the beginning of the list.<br/><br/>
gcolList_insert: Adds the given data to the given index of the list.<br/><br/>
gcolList_popBack: Deletes the data at the end of the list.<br/><br/>
gcolList_popFront: Deletes the data at the beginning of the list.<br/><br/>
gcolList_delete: Deletes the data at the given index of the list.<br/><br/>
gcolList_remove: Deletes the given data from list.<br/><br/>
gcolList_search: Searches the given data in the list.<br/><br/>
gcolList_get: Returns the data at the given index of the list.<br/><br/>
gcolList_print: Prints the datas in the list.<br/><br/>
gcolList_size: Returns the number of elements in the list.<br/><br/>

# Sample Code

```
#include <stdio.h>
#include <stdlib.h>
#include <gcol_list.h>

typedef struct {int x, y;} point_t; 

point_t *point_init(int x, int y){
    point_t *p = malloc(sizeof(point_t));
    p->x = x, p->y = y;
    return p;
}

void point_print(void_ptr pv){
    point_t *p = pv;
    printf("x: %d\ty: %d\n", p->x, p->y);
}

int point_cmp(void_ptr pv1, void_ptr pv2){
    point_t *p1 = pv1;
    point_t *p2 = pv2;
    if(p1->x == p2->x && p1->y == p2->y) return 0;
    return 1;
}

int main(){
    gcolList_ptr list = gcolList_initialize();

    point_t *point = point_init(7,11);


    gcolList_pushBack(list, point_init(1,1));
    gcolList_pushFront(list, point_init(4,0));
    gcolList_insert(list, 1, point_init(0,-1));
    gcolList_insert(list,0, point_init(9,3));
    gcolList_pushFront(list, point);

    gcolList_remove(list, point, NULL);
    gcolList_remove_m(list, point_cmp, point_t, 1, 1);


    gcolList_print(list, point_print);

    gcolList_destroy(&list);

    return 0;
}
```
