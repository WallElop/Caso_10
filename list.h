#ifndef MATROIDINT_H
#define MATROIDINT_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define define_list(type) \
\
    struct _list_##type; \
    \
    typedef struct \
    { \
        int (*is_empty)(const struct _list_##type*); \
        size_t (*size)(const struct _list_##type*); \
        const type (*get)(const struct _list_##type*, size_t pos); \
        void (*insert)(struct _list_##type*, type); \
    } _list_functions_##type; \
    \
    typedef struct _list_elem_##type \
    { \
        type _data; \
        struct _list_elem_##type* _next; \
    } list_elem_##type; \
    \
    typedef struct _list_##type \
    { \
        size_t _size; \
        list_elem_##type* _first; \
        list_elem_##type* _last; \
        _list_functions_##type* _functions; \
    } List_##type; \
    \
    List_##type* new_list_##type(); \
    bool list_is_empty_##type(const List_##type* list); \
    size_t list_size_##type(const List_##type* list); \
    const type list_get_##type(const List_##type* list, size_t pos); \
    void list_insert_##type(List_##type* list, type elem); \
    \
    bool list_is_empty_##type(const List_##type* list) \
    { \
        return list->_size == 0; \
    } \
    \
    size_t list_size_##type(const List_##type* list) \
    { \
        return list->_size; \
    } \
    \
    const type list_get_##type(const List_##type* list, size_t pos) \
    { \
        size_t cont = 0; \
        list_elem_##type* auxiliarNode = list->_first; \
        if(pos <= list->_size){\
            while(cont<=list->_size){\
                if(cont == pos){\
                    return auxiliarNode->_data;\
                }\
                auxiliarNode = auxiliarNode->_next;\
                cont++;\
            }\
            return -1;\
        }\
        return -1; \
    } \
    \
    void list_insert_##type(List_##type* list, type elem) \
    { \
        list_elem_##type* new_node = (list_elem_##type*)malloc(sizeof(list_elem_##type)); \
        new_node->_data = elem;\
        new_node->_next = NULL;\
        if(list->_size != 0){\
            list_elem_##type* auxiliarNode = list->_first; \
            while(auxiliarNode->_next != NULL){\
                auxiliarNode = auxiliarNode->_next;\
            }\
            auxiliarNode->_next = new_node;\
            list->_size +=1;\
        }\
        else{\
            list->_first = new_node;\
            list->_size +=1;\
        } \
    } \
    \
    _list_functions_##type _list_funcs_##type = { \
        &list_is_empty_##type, \
        &list_size_##type, \
        &list_get_##type, \
        &list_insert_##type, \
    }; \
    \
    List_##type* new_list_##type() \
    { \
        List_##type* res = (List_##type*) malloc(sizeof(List_##type)); \
        res->_size = 0; \
        res->_first = NULL; \
        res->_functions = &_list_funcs_##type; \
        return res; \
    }

#define List(type) \
    List_##type

#define new_list(type) \
    new_list_##type()

#define is_empty(collection) \
    collection->_functions->is_empty(collection)

#define size(collection) \
    collection->_functions->size(collection)

#define get(collection, pos) \
    collection->_functions->get(collection, pos)

#define insert(collection, elem) \
    collection->_functions->insert(collection, elem)

#endif // MATROIDINT_H
