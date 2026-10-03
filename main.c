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

typedef enum {
	MAIN_MENU,
	STUDENT_LIST
} ui_menu_t;

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

void drawStudentList() {
	getStudentsList();
	/* Display more options on how to handle the options */
}

void student_list(UI* ui_state) {
	char printable_student_name[64] = {0};
	for (size_t i = 0; i < app.students_count; i++)
	{
		if (app.students_list[i] != nullptr)
		{
			const StudentData* student = &app.students_list[i]->data;

			snprintf(printable_student_name, (sizeof("Student Name: ") + sizeof(student->name)) * sizeof(char), "Student Name: %s", student->name);

			ui_print(ui_state, 0, 0, printable_student_name, sizeof(printable_student_name));
			// printf("Student Name: %s\n", student->name);
			// printf("#");

			// // Average Score
			// for (int i = 0; i < MAX_SCORES; i++)
			// {
			// 	printf(" Nota %i: %.2f |", (1 + i), student->scores[i]);
			// }
			// printf("\n# ");
			//
			// printf("Media: %f \n", student->average);
			// printf("# ");
			//
			// printf("Status: ");
			// switch (student->status)
			// {
			// 	case APPROVED:
			// 		printf("APROVADO \n");
			// 		break;
			// 	case REPROVED:
			// 		printf("REPROVADO \n");
			// 		break;
			// }
			// printf("# ");
		}
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
	createStudent("Zezinho", 7.0f, 7.0f, 7.0f);

	while (is_running)
	{
		clock_t current_time = clock();
		double elapsed_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;

		if (GetAsyncKeyState(VK_ESCAPE) < 0)
			is_running = false;

		student_list(&ui_state);
		// ui_print(&ui_state, 0, 0, "Hello, World", sizeof("Hello, World"));

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
