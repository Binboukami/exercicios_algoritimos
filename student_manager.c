//
// Created by luisa on 25/09/2026.
//
#include <stdio.h>
#include "include/student_manager.h"

#include <string.h>

#include "include/application.h"

extern Application app;

/* Implementation specific */

Student* getStudentPtr(const unsigned int id) {
	for (int i = 0; i < (sizeof(app.student_keys)/ sizeof(int)); i++)
	{
		if (app.student_keys[i] == id)
			return app.students_list[i];
	}

	return nullptr;
}

void getStudentsList()
{
	for (size_t i = 0; i < app.students_count; i++)
	{
		if (app.students_list[i] != nullptr)
		{
			const StudentData* student = &app.students_list[i]->data;

			printf("Student Name: %s\n", student->name);
			printf("#");

			// Average Score
			for (int i = 0; i < MAX_SCORES; i++)
			{
				printf(" Nota %i: %.2f |", (1 + i), student->scores[i]);
			}
			printf("\n# ");

			printf("Media: %f \n", student->average);
			printf("# ");

			printf("Status: ");
			switch (student->status)
			{
				case APPROVED:
						printf("APROVADO \n");
					break;
				case REPROVED:
					printf("REPROVADO \n");
					break;
			}
			printf("# ");
		}
	}
}

StudentData* getStudentById(const unsigned int id) {

	// Unused memory, not yet set
	if (id > app.students_count)
		return nullptr;

	Student* ptr = getStudentPtr(id);

	if (ptr != nullptr)
		return &ptr->data;

	return nullptr;
}

StudentData* createStudent(const char* name, float firstScore, float secondScore, float thirdScore)
{
	if ((app.students_count + 1) > MAX_STUDENTS)
		return nullptr;

	app.id_inc++;
	Student* block = allocStudent(&app.pool);

	block->data.id = app.id_inc;
	memcpy(block->data.name, name, sizeof(name));

	block->data.scores[0] = firstScore;
	block->data.scores[1] = secondScore;
	block->data.scores[2] = thirdScore;

	for (size_t i = 0; i < (sizeof(app.students_list) / sizeof(Student*)); i++)
	{
		// Linear find first available slot to fill in new data
		if (app.students_list[i] == nullptr)
		{
			app.student_keys[i] = block->data.id;
			app.students_list[i] = block;
			break;
		}
	}

	// TODO: Compute average score if all the initial scores are set
	updateStudentAverage(&block->data);

	app.students_count++;

	return &block->data;
}

bool updateStudentName(StudentData *student, const char* name)
{
	if (student == nullptr)
		return false;

	memcpy(student->name, name, sizeof(name));

	return true;
}

bool updateStudentScore(StudentData* student, const size_t scoreNum, const float score) {

	if (student == nullptr)
		return false;

	student->scores[scoreNum] = score;

	return true;
}

bool updateStudentAverage(StudentData* student) {

	// Every time a score is set, the average score is updated
	float sum_score = 0;
	for (size_t i = 0; i < MAX_SCORES; i++) {
		sum_score += student->scores[i];
	}

	student->average = sum_score / MAX_SCORES;

	if (student->average >= 7.0f)
		student->status = APPROVED;
	else
		student->status = REPROVED;

	return true;
}

bool deleteStudentById(const unsigned int id) {

	if (id > app.students_count)
		return false;

	Student* student = getStudentPtr(id);

	if (student == nullptr)
		return false;

	freeStudent(&app.pool, student);

	return true;
}