
#include "destruct.h"

unsigned int pseudo_random_premutation(unsigned int x)
{
    const unsigned int prime = 4294967291;
    if (x >= prime)
        return x;
    unsigned int residue = ((unsigned long long) x * x) % prime;
    return (x <= prime / 2) ? residue : prime - residue;
}

int has_component(unsigned int entity, buffer component, unsigned int* idx)
{
    unsigned int i, size = get_buffer_length(component);

    for (i = 0; i < size; i++)
    {
        if (*get_buffer_pointerui(component,i,0) == entity)
        {
            if (idx != NULL)
                *idx = i;
            return 1;
        }
    }
    return 0;
}

void add_component(unsigned int entity, buffer component)
{
    if (has_component(entity,component,NULL))
        return;
    resize_buffer(component,get_buffer_length(component)+1);
    set_buffer_fieldui(component,get_buffer_length(component)-1,0,entity);
}

void remove_component(unsigned int entity, buffer component)
{
    unsigned int index;
    
    if (!has_component(entity,component,&index))
        return;

    remove_buffer_at(component,index);
}

unsigned int create_entity(unsigned int** entities)
{
    unsigned int i, num, used = 0;

    if ((*entities) == NULL)
    {
        (*entities) = malloc(sizeof(unsigned int));
        (*entities)[0] = 0;
    }

    (*entities)[0]++;
    if ((*entities)[0] == 0)
    {
        puts("More than 2^32 entities! Internal buffer overflown!");
        exit(EXIT_FAILURE);
    }
    (*entities) = realloc((*entities),(*entities)[0]);

    do
    {
        used = 0;
        num = pseudo_random_premutation((*entities)[0]-1);
        for (i = 0; i < (*entities)[0]; i++)
            if ((*entities)[i] == num)
                used = 1;
    }
    while(used);

    return (*entities)[(*entities)[0]] = num;
}

void destroy_entity(unsigned int entity, unsigned int** entities)
{
    unsigned int i, found = 0;

    for (i = 1; i < (*entities)[0] +1; i++)
    {
        found = (*entities)[i] == entity;
        if (found)
            break;
    }

    if (found)
    {
        if (--(*entities)[0] == 0)
        {
            free((*entities));
            (*entities) = NULL;
            return;
        }

        for (; i < (*entities)[0]; i++)
        {
            (*entities)[i] = (*entities)[i + 1];
        }
    }
}