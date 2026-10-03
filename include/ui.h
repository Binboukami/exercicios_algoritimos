#ifndef UI_H
#define UI_H

#define UI_ROWS 30
#define UI_COLS 120
#define UI_WRITEABLE_X 3
#define UI_WRITEABLE_Y 2

typedef char matrix_ptr_t[UI_ROWS];

typedef struct {

	matrix_ptr_t* current_buffer;
	matrix_ptr_t* next_buffer;

	char buffer_a[UI_ROWS][UI_COLS];
	char buffer_b[UI_ROWS][UI_COLS];
} UI;

static void goto_xy(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

static void caret_enable() { printf("\033[?25h"); }
static void caret_disable() { printf("\033[?25l"); }

static void init_ui(UI* ui_state) {
	memset(ui_state->buffer_a, 32, sizeof(char) * UI_ROWS * UI_COLS);
	memset(ui_state->buffer_b, 32, sizeof(char) * UI_ROWS * UI_COLS);

	ui_state->current_buffer = ui_state->buffer_a;
	ui_state->next_buffer = ui_state->buffer_b;

	goto_xy(0, 0);
	printf("\e[1;1H\e[2J");

	caret_disable();
	fflush(stdout);
}

static void flush(UI* ui_state) {

	goto_xy(0, 0);
	/** Clear screen **/
	for (int i = 0; i < (UI_ROWS - 1); i++)
	{
		for (int j = 0; j < (UI_COLS - 1); j++)
		{
			// putchar(32);
		}
	}

	matrix_ptr_t* next_buffer = ui_state->next_buffer;

	ui_state->next_buffer = ui_state->current_buffer;
	ui_state->current_buffer = next_buffer;

	/* Clear back-buffer */
	memset(ui_state->next_buffer, 32, sizeof(ui_state->buffer_a));

	goto_xy(0, 0);
	for (int i = 0; i < (UI_ROWS - 1); i++)
	{
		for (int j = 0; j < (UI_COLS - 1); j++)
		{
			putchar(ui_state->current_buffer[i][j]);
		}
	}
}

static void ui_print(const UI* ui_state, int x, int y, const char* data, const size_t len) {
	memcpy(&ui_state->next_buffer[x][y], data, sizeof(char) * len);
}
#endif //UI_H
