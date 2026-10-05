#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <windows.h>

#include "include/application.h"
#include "include/student_manager.h"

#define KEY_ESC VK_ESCAPE
#define KEY_1 0X31
#define KEY_2 0X32

Application app = { };

bool is_running = false;

/*Crie um programa em linguagem C ou C++ que permita cadastrar os nomes e as três notas de até 5 alunos.
 *Em seguida, o programa deve:
	▪ Calcular a média das três notas para cada aluno.
	▪ Exibir uma tabela com nome, notas, média e situação (Aprovado
	se média ≥ 7, Reprovado caso contrário).
	▪ Informar qual foi o aluno com a maior média da turma.
	o Requisitos técnicos:
	▪ Use vetores para armazenar os dados dos alunos.
	▪ Use pelo menos uma função para calcular a média.
	▪ Use estrutura de repetição (for ou while) para entrada e exibição
	de dados.
	▪ Utilize uma estrutura condicional (if/else) para determinar a
	situação.
*/
#include "ui.h"

void main_menu(UI* ui_state) {
	if (GetAsyncKeyState(VK_ESCAPE) < 0)
		is_running = false;

	ui_print(ui_state, 1, 0, "1) See registered students");
	ui_print(ui_state, 2, 0, "2) Add new student information");
	ui_print(ui_state, 3, 0, "___________________________________________________");
	ui_print(ui_state, 5, 0, "ESC ) Exit program");

	if (GetAsyncKeyState(KEY_1) < 0) {
		app.current_menu = STUDENT_LIST;
		clear_ui(ui_state);
	}

	if (GetAsyncKeyState(KEY_2) < 0) {
		app.current_menu = ADD_STUDENT;
		clear_ui(ui_state);
	}
}

void student_list_view(UI* ui_state) {

	int info_offset = 5;

	ui_print(ui_state, 1, 0, "Press 'ESC' to return to Main Menu");
	ui_print(ui_state, 2, 0, "________________________________________________");

	for (size_t i = 0; i < app.students_count; i++)
	{
		if (app.students_list[i] != nullptr)
		{
			const StudentData* student = &app.students_list[i]->data;

			ui_print(ui_state, 3 + (info_offset * i), 0, "Student Name: %s", student->name);

			// Scores
			ui_print(ui_state, 4 + (info_offset * i), 0, "Student Score One: %.2f | Student Score Two: %.2f | Student Score Three: %.2f", student->scores[0], student->scores[1], student->scores[2]);

			ui_print(ui_state, 5 + (info_offset * i), 0, "Average Score: %.2f", student->average);
			switch (student->status)
			{
				case APPROVED:
					ui_print(ui_state, 6 + (info_offset * i), 0, "Status: Approved");
					break;
				case REPROVED:
					ui_print(ui_state, 6 + (info_offset * i), 0, "Status: Reproved");
					break;
			}

			ui_print(ui_state, 7 + (info_offset * i), 0, "________________________________________________");
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) < 0)
	{
		app.current_menu = MAIN_MENU;
		clear_ui(ui_state);
	}
}

void add_student_view(UI* ui_state) {

	ui_print(ui_state, 1, 0, "Insira os dados de um aluno");

	char name[NAME_MAX_SIZE - 1] = {0};
	float first_score = 0.0f;
	float second_score = 0.0f;
	float third_score = 0.0f;

	ui_print(ui_state, 2, 0, "Insira o nome do aluno\n");
	fgets(name, sizeof(name), stdin);

	// ui_print(ui_state, 3, 0, "Insira a primeira nota do aluno\n");
	// scanf("%f", first_score);
	//
	// ui_print(ui_state, 4, 0, "Insira a segunda nota do aluno\n");
	// scanf("%f", second_score);
	//
	// ui_print(ui_state, 5, 0, "Insira a terceira nota do aluno\n");
	// scanf("%f", third_score);

	if (name[0] != 0) {
		StudentData* data = createStudent(name, first_score, second_score, third_score);
	}

	app.current_menu = MAIN_MENU;
	clear_ui(ui_state);

	if (GetAsyncKeyState(VK_ESCAPE) < 0) {
		app.current_menu = MAIN_MENU;
		clear_ui(ui_state);
	}
}

void clean_up_routine() {
	goto_xy(0, 0);
	// Clear screen
	printf("\e[1;1H\e[2J");

	// Restore caret
	printf("\033[?25h");
	fflush(stdout);
}

int main(void) {

	UI ui_state = { 0 };
	init_ui(&ui_state);

	is_running = true;
	clock_t last_time = clock();
	const float interval = 0.000016f;

	initStudentPool(&app.pool);
	createStudent("Zezinho", 7.0f, 8.0f, 7.0f);
	createStudent("Pedrin", 3.0f, 8.0f, 7.0f);

	app.current_menu =	STUDENT_LIST;

	while (is_running)
	{
		clock_t current_time = clock();
		double elapsed_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;

		switch (app.current_menu) {
			case MAIN_MENU:
				main_menu(&ui_state);
				break;
			case STUDENT_LIST:
				student_list_view(&ui_state);
				break;
			case ADD_STUDENT:
				add_student_view(&ui_state);
				break;
		}

		/* DEBUG */
		// if (GetAsyncKeyState(KEY_2) < 0)
		// 	flush(&ui_state);

		if (elapsed_time > interval)
		{
			last_time = current_time;
			flush(&ui_state);
		}
	}

	// Restore caret
	clean_up_routine();
	caret_enable();
	fflush(stdout);
}
