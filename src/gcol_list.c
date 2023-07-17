//
// Created by akaan on 16.07.2023.
//

#include <stdlib.h>
#include <setjmp.h>
#include <gcol_list.h>
#include <gcol_error.h>

jmp_buf buf_insertion;

#define malloc_m(type, count) \
(type*)malloc(sizeof(type) * (count))

typedef struct Node node_t;
typedef node_t *node_ptr;

struct Node{
    void_ptr data;
    node_ptr prev, next;
};
struct gcolList_s{
    node_ptr head, tail;
    uintmax_t size;
};

static inline node_ptr node_initialize(void_ptr data)
{
    node_ptr pnode = malloc_m(node_t, 1);
    if(!pnode) longjmp(buf_insertion, gcolError_outOfMemory_c);
    pnode->data = data;
    pnode->prev = pnode->next = NULL;
    return pnode;
}

static inline void node_destroy(node_ptr *ppnode)
{
#ifdef gcolList_destroyData_m
    free((*ppnode)->data);
#endif
    free(*ppnode);
    *ppnode = NULL;
}

gcolList_ptr gcolList_initialize()
{
    gcolList_ptr plist = malloc_m(gcolList_t, 1);
    if(!plist) gcolError_throw_m(gcolError_outOfMemory_c);
    plist->size = UINTMAX_C(0);
    plist->head = plist->tail = NULL;
    return plist;
}

void gcolList_destroy(gcolList_ptr *pplist)
{
    if(!pplist || !*pplist) gcolError_throw_m(gcolError_nullPointer_c);
    if((*pplist)->head){
        node_ptr temp = NULL;
        while ((*pplist)->head){
            temp = (*pplist)->head;
            (*pplist)->head = (*pplist)->head->next;
            node_destroy(&temp);
        }
    }
    free(*pplist);
    *pplist = NULL;
}

static inline void gcolList_head_initialize(gcolList_ptr plist, void_ptr data)
{
    plist->head = node_initialize(data);
    plist->tail = plist->head;
    plist->size++;
}

static inline void gcolList_head_destroy(gcolList_ptr plist)
{
    node_destroy(&plist->head);
    plist->tail = NULL;
    plist->size = UINTMAX_C(0);
}

void gcolList_pushBack(gcolList_ptr plist, void_ptr data)
{
    if(!plist || !data) gcolError_throw_m(gcolError_nullPointer_c);
    gcolError_t ret = setjmp(buf_insertion);
    if(!plist->head){
        if(!ret) gcolList_head_initialize(plist, data);
        else
            gcolError_throw_m(ret);
        return;
    }

    if(!ret) plist->tail->next = node_initialize(data);
    else
        gcolError_throw_m(ret);
    plist->tail->next->prev = plist->tail;
    plist->tail = plist->tail->next;
    plist->size++;
}

void gcolList_pushFront(gcolList_ptr plist, void_ptr data)
{
    if(!plist || !data) gcolError_throw_m(gcolError_nullPointer_c);
    gcolError_t ret = setjmp(buf_insertion);
    if(!plist->head){
        if(!ret) gcolList_head_initialize(plist, data);
        else
            gcolError_throw_m(ret);
        return;
    }
    if(!ret) plist->head->prev = node_initialize(data);
    else
        gcolError_throw_m(ret);
    plist->head->prev->next = plist->head;
    plist->head = plist->head->prev;
    plist->size++;
}

void gcolList_insert(gcolList_ptr plist, uintmax_t index, void_ptr data)
{
    if(!plist || !data) gcolError_throw_m(gcolError_nullPointer_c);
    if(index > plist->size || !plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);

    if(index == plist->size)
        gcolList_pushBack(plist, data);
    else if(index == UINTMAX_C(0))
        gcolList_pushFront(plist, data);
    else{
        uintmax_t i = 0;
        node_ptr iter = plist->head;
        while (iter){
            if(index == i){
                node_ptr new_node = NULL;
                gcolError_t ret = setjmp(buf_insertion);
                if(!ret) new_node = node_initialize(data);
                else
                    gcolError_throw_m(ret);
                new_node->prev = iter->prev;
                new_node->next = iter;
                new_node->prev->next = new_node;
                new_node->next->prev = new_node;
                plist->size++;
                return;
            }
            iter = iter->next, i++;
        }
    }
}

void gcolList_popBack(gcolList_ptr plist)
{
    if(!plist) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);
    if(plist->size == 1){
        gcolList_head_destroy(plist);
        return;
    }
    node_ptr temp = plist->tail;
    plist->tail = plist->tail->prev;
    plist->tail->next = NULL;
    node_destroy(&temp);
    plist->size--;
}
void gcolList_popFront(gcolList_ptr plist)
{
    if(!plist) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);

    if(plist->size == 1){
        gcolList_head_destroy(plist);
        return;
    }
    node_ptr temp = plist->head;
    plist->head = plist->head->next;
    plist->head->prev = NULL;
    node_destroy(&temp);
    plist->size--;
}
void gcolList_delete(gcolList_ptr plist, uintmax_t index)
{
    if(!plist) gcolError_throw_m(gcolError_nullPointer_c);
    if(index >= plist->size || !plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);

    if(index == plist->size - 1) gcolList_popBack(plist);
    else if(index == UINTMAX_C(0)) gcolList_popFront(plist);
    else{
        uintmax_t i = 0;
        node_ptr iter = plist->head;
        while (iter){
            if(index == i){
                iter->next->prev = iter->prev;
                iter->prev->next = iter->next;
                node_destroy(&iter);
                plist->size--;
                return;
            }
            iter = iter->next, i++;
        }
    }
}
void
gcolList_remove(gcolList_ptr plist, void_ptr data, int (*cmp)(void_ptr, void_ptr))
{
    if(!plist || !data) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);

    node_ptr iter = plist->head;
    if(cmp){
        while (iter){
            if(!cmp(data, iter->data)){
                if(iter == plist->head) gcolList_popFront(plist);
                else if(iter == plist->tail) gcolList_popBack(plist);
                else{
                    iter->next->prev = iter->prev;
                    iter->prev->next = iter->next;
                    node_destroy(&iter);
                    plist->size--;
                }
                return;
            }
            iter = iter->next;
        }
        exit(EXIT_FAILURE);
    }
    else{
        while (iter){
            if(data == iter->data){
                if(iter == plist->head) gcolList_popFront(plist);
                else if(iter == plist->tail) gcolList_popBack(plist);
                else{
                    iter->next->prev = iter->prev;
                    iter->prev->next = iter->next;
                    node_destroy(&iter);
                    plist->size--;
                }
                return;
            }
            iter = iter->next;
        }
        exit(EXIT_FAILURE);
    }
}

bool gcolList_search(gcolList_ptr plist, void_ptr data, fptrCmp cmp)
{
    if(!plist || !data) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head) gcolError_throw_m(gcolError_indexOutOfBounds);
    node_ptr iter = plist->head;
    if(cmp){
        while (iter){
            if(!cmp(data, iter->data)) return true;
            iter = iter->next;
        }
        return false;
    }else{
        while (iter){
            if(data == iter->data) return true;
            iter = iter->next;
        }
        return false;
    }
}


void_ptr gcolList_get(gcolList_ptr plist, uintmax_t index)
{
    if(!plist) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head || index >= plist->size) gcolError_throw_m(gcolError_indexOutOfBounds);

    if(index == plist->size - 1) return plist->tail->data;
    node_ptr iter = plist->head;
    uintmax_t i = 0;
    while (iter){
        if(index == i) return iter->data;
        iter = iter->next, i++;
    }
    gcolError_throw_m(gcolError_indexOutOfBounds);
}

void gcolList_print(gcolList_ptr plist, fptrPrint print)
{
    if(!plist || !print) gcolError_throw_m(gcolError_nullPointer_c);
    if(!plist->head ) gcolError_throw_m(gcolError_indexOutOfBounds);
    node_ptr iter = plist->head;
    while (iter){
        print(iter->data);
        iter = iter->next;
    }
}

uintmax_t gcolList_size(gcolList_ptr plist)
{
    if(!plist) gcolError_throw_m(gcolError_nullPointer_c);
    return plist->size;
}