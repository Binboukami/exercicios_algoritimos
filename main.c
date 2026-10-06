#include <stdio.h>

#define NAME_MAX_SIZE 127

typedef struct {
	const char name[NAME_MAX_SIZE];
	float first_score;
	float second_score;
	float third_score;
} StudentForm;

int main(void) {

		int num_entries = 5;
		StudentForm entries[num_entries];

		// printf("Quantos alunos deseja adicionar\n");
		// scanf("%d", &num_entries);
		//
		// if (num_entries < 1) {
		// 	printf("Numero de entradas deve ser ao menos '1'");
		// 	return -1;
		// }

		for (int i = 0; i < (num_entries); i++) {

			printf("Insira nome do aluno %d: \n", (i+1));
			scanf(" %s", &entries[i].name);

			printf("Insira a Primeira Nota: \n");
			scanf("%f", &entries[i].first_score);

			printf("Insira a Segunda Nota: \n");
			scanf("%f", &entries[i].second_score);

			printf("Insira a Terceira Nota: \n");
			scanf("%f", &entries[i].third_score);

			printf("\e[1;1H\e[2J");
		}

		printf("\e[1;1H\e[2J");
		printf("Alunos registrados: \n\n");

		for (int i = 0; i < num_entries; i++) {
			printf("Nome: %s \n", entries[i].name);
			printf("Notas: %.2f | %.2f | %.2f \n", entries[i].first_score, entries[i].second_score, entries[i].third_score);

			float avg_score = (entries[i].first_score + entries[i].second_score + entries[i].third_score) / 3;
			printf("Media: %.2f \n ", avg_score);


			if (avg_score >= 7)
				printf("Status: %s \n", "Aprovado");
			else
				printf("Status: %s \n", "Reprovado");

			printf("\n------------------------------------------------------------------\n");
		}
}
