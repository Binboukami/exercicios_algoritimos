//
// Created by luisa on 24/09/2026.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "pool.h"
#include "student_manager.h"

#define MAX_STUDENT_KEYS 255
#define MAX_STUDENTS 10

typedef struct {
	unsigned int id_inc;
	StudentMemoryPool pool;

	size_t students_count;
	unsigned int student_keys[MAX_STUDENT_KEYS];
	Student* students_list[MAX_STUDENTS];
} Application;

#endif //APPLICATION_H