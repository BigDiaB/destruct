#ifndef DESTRUCT_H
#define DESTRUCT_H

/* Destruct

Destruct is a small ECS "addon" for the construct library!
Usage example:
*/

#include <construct/construct.h>

/* Returns a boolean value corresponding to the given entity having the specified component (Populates idx with the index of the corresponding element in specified buffer if idx is not NULL)*/
int has_component(unsigned int entity, buffer component, unsigned int* idx);
/* Adds the specified component to the given entity */
void add_component(unsigned int entity, buffer component);
/* Removes the specified component from a given entity (Gets ignored if entity doesn't have the specified component) */
void remove_component(unsigned int entity, buffer component);
/* Returns a unique unsigned integer to be used as an entity (Unique to the specified entity buffer) */
unsigned int create_entity(unsigned int** entities);
/* Removes the given entity from the specified entity buffer */
void destroy_entity(unsigned int entity, unsigned int** entities);

#endif /* DESTRUCT_H */