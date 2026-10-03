#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#define MAX_IDX 255

typedef struct {
	unsigned int key;
	size_t value; // Indexes into an array
} item;

#endif //MAP_H
