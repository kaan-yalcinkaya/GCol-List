//
// Created by akaan on 16.07.2023.
//

#ifndef GCOLLIST_GCOL_LIST_H
#define GCOLLIST_GCOL_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Removes data allocated by memory allocation functions(malloc, calloc, realloc).
 */
#define gcolList_destroyData_m
//#undef gcolList_destroyData_m

/*
 * This insertion macros(pushBack, pushFront, Insert)
 * converts the given data to compound literal and passes the address of
 * this object to the insertion functions.
 * If you are going to use this macro, undef the gcolList_destroyData_m.
 * Because compound literal object's storage class will be automatic or static.
 */
#define gcolList_pushBack_m(list, type, ...) \
    gcolList_pushBack((list), &((type){__VA_ARGS__}))

#define gcolList_pushFront_m(list, type, ...) \
    gcolList_pushFront((list), &((type){__VA_ARGS__}))

#define gcolList_insert_m(list, index, type, ...) \
    gcolList_insert((list), (index), &((type){__VA_ARGS__}))

/*
 * These macros are useful when comparison functions are available.
 */
#define gcolList_remove_m(list, fun_cmp, type, ...) \
    gcolList_remove((list), &((type){__VA_ARGS__}), (fun_cmp))

#define gcolList_search_m(list, fun_cmp, type, ...) \
    gcolList_search((list), &((type){__VA_ARGS__}), (fun_cmp))

//type definitions
typedef void *void_ptr;
typedef int (*fptrCmp)(void_ptr, void_ptr);
typedef void (*fptrPrint)(void_ptr);
typedef struct gcolList_s gcolList_t;
typedef gcolList_t *gcolList_ptr;

/**
 * Required to be used to initialize a list
 * @return: Address of an initialized list
 */
gcolList_ptr gcolList_initialize();

/**
 * Clears the list and all nodes.
 * @param pplist: Address of pointer that points to be deleted list
 */
void gcolList_destroy(gcolList_ptr *pplist);

/**
 * Adds to given data to the end of the given list.
 * @param plist: Pointer to list
 * @param data: Pointer to data
 */
void gcolList_pushBack(gcolList_ptr plist, void_ptr data);

/**
 * Adds to given data to the beginning of the given list
 * @param plist: Pointer to list
 * @param data: Pointer to data
 */
void gcolList_pushFront(gcolList_ptr plist, void_ptr data);

/**
 * Adds to given data to given index of the given list
 * @param plist: Pointer to list
 * @param index: Unsigned integer value
 * @param data: Pointer to data
 */
void gcolList_insert(gcolList_ptr plist, uintmax_t index, void_ptr data);

/**
 * Deletes data at the end of the given list.
 * @param plist: Pointer to list
 */
void gcolList_popBack(gcolList_ptr plist);

/**
 * Deletes the data at the beginning of the given list.
 * @param plist: Pointer to list
 */
void gcolList_popFront(gcolList_ptr plist);

/**
 * Deletes the data at the given index of the given list.
 * @param plist: Pointer to list
 * @param index: Unsigned integer value
 */
void gcolList_delete(gcolList_ptr plist, uintmax_t index);

/**
 * Search the given data in the given list. If it finds it,
 * deletes the element. Otherwise it will throw an error
 * @param plist: Pointer to list
 * @param data: Pointer to data
 * @param cmp: Custom compare function pointer
 */
void gcolList_remove(gcolList_ptr plist, void_ptr data, fptrCmp cmp);

/**
 * Searches the given data in the given list
 * @param plist: Pointer to list
 * @param data: Pointer to data
 * @param cmp: Pointer to custom compare function
 * @return true if it finds the given data, false otherwise
 */
bool gcolList_search(gcolList_ptr plist, void_ptr data, fptrCmp cmp);

/**
 * @param plist: Pointer to list
 * @param index: Unsigned integer value
 * @return the data at the given index of the given list
 */
void_ptr gcolList_get(gcolList_ptr plist, uintmax_t index);

/**
 * Prints the data in the list
 * @param plist: Pointer to list
 * @param print: Pointer to custom print function
 */
void gcolList_print(gcolList_ptr plist, fptrPrint print);

/**
 * @param plist: Pointer to list
 * @return the number of data in the list
 */
uintmax_t gcolList_size(gcolList_ptr plist);

#endif //GCOLLIST_GCOL_LIST_H
