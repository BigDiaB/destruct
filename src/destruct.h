#ifndef DESTRUCT_H
#define DESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Destruct
Destruct is a small ECS "addon" for the construct library!
*/

#include <construct/construct.h>

typedef unsigned int entity;
typedef int (*system_function)(buffer*);

/* Returns the number of entities in the given entity buffer */
unsigned int get_num_entities(entity** entities);
/* Returns a boolean value corresponding to the given entity having the specified component (Populates idx with the index of the corresponding element in specified buffer if idx is not NULL) */
int has_component(entity target, buffer component, unsigned int* idx);
/* Adds the specified component to the given entity (Returns 0 on failure and 1 on success) */
int add_component(entity target, buffer component);
/* Removes the specified component from a given entity (Returns 0 on failure and 1 on success) */
int remove_component(entity target, buffer component);
/* Returns a unique entity (Unique to the specified entity buffer) */
entity create_entity(entity** entities);
/* Removes the given entity from the specified entity buffer */
void destroy_entity(entity target, entity** entities);

#ifdef __cplusplus
}
#endif

#endif /* DESTRUCT_H */