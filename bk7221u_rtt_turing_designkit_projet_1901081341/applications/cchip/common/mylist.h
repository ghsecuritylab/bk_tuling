
//
// list.h
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

// Library version

#define LIST_VERSION "0.0.5"

// Memory management macros

#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

/*
 * list_t iterator direction.
 */

typedef enum {
    LIST_HEAD
  , LIST_TAIL
} list_direction_t;

/*
 * list_t node struct.
 */

typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
  void *val;
} list_node_t;

/*
 * list_t struct.
 */


typedef void (*list_free_cb)(void *data);
typedef int (*list_match_cb)(void *a, void *b);

typedef struct {
  list_node_t *head;
  list_node_t *tail;
  unsigned int len;
  //void (*free)(void *val);
  list_free_cb free;
  //int (*match)(void *a, void *b);
  list_match_cb match;
} list_t;

/*
 * list_t iterator struct.
 */

typedef struct {
  list_node_t *next;
  list_direction_t direction;
} list_iterator_t;


// Node prototypes.

list_node_t *
list_node_new(void *val);

// list_t prototypes.


list_t *
list_new_free(list_free_cb callback) ;

list_t *
list_new_free_match(list_free_cb free, list_match_cb match);

list_t *
list_new();

list_node_t *
list_rpush(list_t *self, list_node_t *node);

list_node_t *
list_lpush(list_t *self, list_node_t *node);

list_node_t *
list_find(list_t *self, void *val);

list_node_t *
list_at(list_t *self, int index);

list_node_t *
list_rpop(list_t *self);

list_node_t *
list_lpop(list_t *self);

void
list_remove(list_t *self, void *val);

void
list_destroy(list_t *self);

int list_add(list_t *self, void *val);

int list_insert(list_t *self,void *src, void *dst);


// list_t iterator prototypes.

list_iterator_t *
list_iterator_new(list_t *list, list_direction_t direction);

list_iterator_t *
list_iterator_new_from_node(list_node_t *node, list_direction_t direction);

list_node_t *
list_iterator_next(list_iterator_t *self);

void
list_iterator_destroy(list_iterator_t *self);

void *
list_iterator_next_value(list_iterator_t *self) ;

int list_length(list_t *self);

void list_remove_index(list_t *self, int index);

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
