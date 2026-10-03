#ifndef POOL_H
#define POOL_H

#include <stdio.h>
#include "utils.h"
#include "student_manager.h"


#define STUDENT_POOL_SZ 6

typedef struct student_t {
	StudentData data;
	struct student_t* next;
} Student;

typedef struct {
	Student* free;
	Student pool[STUDENT_POOL_SZ];
} StudentMemoryPool;

static void initStudentPool(StudentMemoryPool* pool)
{
	pool->free = (Student*)pool->pool;

	// First index
	Student* block = pool->free;

	// Init memory linked list
	for (int i = 0; i < (STUDENT_POOL_SZ - 1); i++)
	{
		block->next = (Student*)((unsigned char*)block + sizeof(Student));
		block = block->next;
	}

	// Last block
	block->next = NULL;
}

static Student *allocStudent(StudentMemoryPool* pool) {

	if (pool->free == NULL) {
		printf("Memory pool exhausted!\n");
		return NULL;
	}

	// Get the first free block
	Student *block = pool->free;

	// Move the free list pointer
	pool->free = block->next;

	return block;
}

static void freeStudent(StudentMemoryPool* pool, Student* block) {
	// Clean up memory
	memset(&block->data, 0, sizeof(block->data));

	// Add the block to the free list
	block->next = pool->free;
	pool->free = block;
}

#endif //POOL_H