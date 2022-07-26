
#include "destruct.h"

#ifdef EBUG
#include <DBG/debug.h>
#endif

unsigned int pseudo_random_premutation(unsigned int x)
{
    const unsigned int prime = 4294967291;
    if (x >= prime)
        return x;
    unsigned int residue = ((unsigned long long) x * x) % prime;
    return (x <= prime / 2) ? residue : prime - residue;
}

int has_component(entity target, buffer component, unsigned int* idx)
{
    unsigned int i, size = get_buffer_length(component);

    for (i = 0; i < size; i++)
    {
        if (*get_buffer_pointerui(component,i,0) == target)
        {
            if (idx != NULL)
                *idx = i;
            return 1;
        }
    }
    return 0;
}

int add_component(entity target, buffer component)
{
    if (has_component(target,component,NULL))
        return 0;
    resize_buffer(component,get_buffer_length(component)+1);
    set_buffer_fieldui(component,get_buffer_length(component)-1,0,target);
    return 1;
}

int remove_component(entity target, buffer component)
{
    unsigned int index;

    if (!has_component(target,component,&index))
        return 0;

    remove_buffer_at(component,index);
    return 1;
}

entity create_entity(unsigned int** entities)
{
    unsigned int i, num, used, offset = 0;

    if ((*entities) == NULL)
    {
        (*entities) = malloc(sizeof(unsigned int));
        (*entities)[0] = 0;
    }

    (*entities)[0]++;
    if ((*entities)[0] == 0)
    {
        puts("More than 2^32 entities! Entity buffer overflown!");
        exit(EXIT_FAILURE);
    }
    (*entities) = realloc((*entities),(*entities)[0] * sizeof(entity));

    do
    {
        used = 0;


        const unsigned int prime = 4294967291;
        const unsigned int x = (*entities)[0] + offset -1;
        if (x >= prime)
            num = x;
        else
        {
            unsigned int residue = ((unsigned long long) x * x) % prime;
            num = (x <= prime / 2) ? residue : prime - residue;
        }

        for (i = 0; i < (*entities)[0]; i++)
        {
            if ((*entities)[i] == num)
            {
                used = 1;
                offset++;
            }
        }
    }
    while(used);

    return (*entities)[(*entities)[0]] = num;
}

void destroy_entity(entity target, unsigned int** entities)
{
    unsigned int i, found = 0;

    for (i = 1; i < (*entities)[0] +1; i++)
    {
        found = (*entities)[i] == target;
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

unsigned int get_num_entities(entity** entities)
{
    if ((*entities) == NULL)
        return 0;
    return (*entities)[0];
}