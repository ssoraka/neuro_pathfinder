#include "header.h"

/*
 * правила игры:
 * Вы обучаете сеть, которой будет управляться бот, движущийся сквозь карту.
 * s - точка появления
 * е - точка выхода
 * Х - твердая почка
 * _ - смертеьная ловушка
 * остальные символы можно игнорировать
 * Алгоритмически эту задачу решить было бы слишком просто...
 */


//	"                                                           ",
//	"            X            X_X           X_XXX_XX_X          ",
//	" s         XXX          XXXXX_X   X_X_XXXXXXXXXXXX_X    e  ",
//	"XXXXXXX_XXXXXXXX_X_X_XXXXXXXXXXX_XXXXXXXXXXXXXXXXXXXX_X____",


// Функция активации
double f(double x)
{
	double e_x;
	e_x = exp(-x);
	if (-1 == e_x)
		return (0.0);
	return (1 / (1 + e_x));
}

// Производная от функции активации
double df_dx(double fx)
{
	return (fx * (1 - fx));
}

void init_layer(t_layer *layer) {
	int i;
	int j;

	// Инициализация связей между входом НС и скрытым слоем случайными значениями
	j = 0;
	while (j < layer->j_count) {
		i = 0;
		while (i < layer->i_count) {
			layer->w_ij[i][j] = ((double)rand()) / RAND_MAX;
			i++;
		}
		j++;
	}
}

int main() {
	//инициализация мозга
	t_brain brain;
	t_layer l[2];
	brain.l = l;
	brain.count = 2;

	srand(time(NULL));

	//инизиализация 1 слоя
	l[0].func = f;
	l[0].i_count = N_INPUT;
	l[0].j_count = 5; //на шару написал
	init_layer(l);

	//инизиализация 2 слоя
	l[1].func = f;
	l[1].i_count = l[0].j_count;
	l[1].j_count = N_OUTPUT;
	init_layer(l + 1);

	// тут должно быть обучение

	start_game_with_brain(brain);
	return 0;
}
