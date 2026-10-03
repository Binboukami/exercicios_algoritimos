//
// Created by luisa on 24/09/2026.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>
#include <stdbool.h>

#define PASSING_SCORE 7
#define NAME_MAX_SIZE 50
#define MAX_SCORES 3

typedef enum status_t {
	UNSET,
	REPROVED,
	APPROVED
} StudentStatus;

typedef struct Student {
	unsigned int id;
	const char name[NAME_MAX_SIZE];
	float scores[MAX_SCORES];
	float average;
	StudentStatus status; // < Defined by saving the student id into an array
} StudentData;

void getStudentsList();
StudentData* getStudentById(const unsigned int id);
StudentData* createStudent(const char* name, float firstScore, float secondScore, float thirdScore);
bool updateStudentName(StudentData *student, const char* name);
bool updateStudentScore(StudentData *student, size_t scoreNum, const float score);
bool updateStudentAverage(StudentData *student);
bool deleteStudentById(const unsigned int id);

#endif //STUDENT_H