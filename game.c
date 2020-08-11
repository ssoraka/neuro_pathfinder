//
// Created by ssoraka on 11.08.2020.
//

#include "header.h"

typedef struct		s_pos
{
	double			*input;
	int				x;
	int				y;
}					t_pos;


char map[HEIGHT][100] = {
		"                                                           ",
		"                                                           ",
		"            X            X_X           X_XXX_XX_X          ",
		"           XXX          XXXXX_X   X_X_XXXXXXXXXXXX_X    e  ",
		"XXXXXXX_XXXXXXXX_X_X_XXXXXXXXXXX_XXXXXXXXXXXXXXXXXXXX_X____",
};

void	print_map(){
	int i;

	i = 0;
	while (i < HEIGHT) {
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n");
}

void	signal_recognition(double *input, char signal) {
	input[EMPTY] = 0.0;
	input[EARTH] = 0.0;
	input[TRAP] = 0.0;
	input[EXIT] = 0.0;
	if (signal == 'X')
		input[EARTH] = 1.0;
	else if (signal == '_')
		input[TRAP] = 1.0;
	else if (signal == 'e')
		input[EXIT] = 1.0;
	else
		input[EMPTY] = 1.0;
}

void get_environment(t_pos *pos) {

	signal_recognition(pos->input, map[pos->y + 1][pos->x + 1]);
	signal_recognition(pos->input + 1 * SIGNAL_COUNT, map[pos->y + 0][pos->x + 1]);
	signal_recognition(pos->input + 2 * SIGNAL_COUNT, map[pos->y - 1][pos->x + 1]);
	signal_recognition(pos->input + 3 * SIGNAL_COUNT, map[pos->y + 0][pos->x + 2]);
}

void	print_arr_double(double *d, int size) {
	int i;

	i = 0;
	while (i < size) {
		printf("%.2lf ", d[i]);
		i++;
	}
	printf("\n");
}

void calculate_layer(double const *f_prev, t_layer *layer) {
	int i;
	int j;
	double sum;

	j = 0;
	while (j < layer->j_count) {
		sum = 0.0;
		i = 0;
		while (i < layer->i_count) {
			sum += layer->w_ij[i][j] * f_prev[i];
			i++;
		}
		layer->f[j] = layer->func(sum);
		j++;
	}
}

void use_brain(t_brain *brain) {
	int i;
	double *f_prev;

	f_prev = brain->input;
	i = 0;
	while (i < brain->count) {
		printf("Layer %d: ", i);
		calculate_layer(f_prev, brain->l + i);
		print_arr_double(brain->l[i].f, brain->l[i].j_count);
		f_prev = brain->l[i].f;
		i++;
	}
}

void make_step(t_brain brain, t_pos *pos) {
	double *ptr;
	int i;
	int i_max;

	ptr = brain.l[brain.count - 1].f;
	i_max = 0;
	i = 1;
	while (i < N_OUTPUT) {
		if (ptr[i] > ptr[i_max])
			i_max = i;
		i++;
	}


	pos->x++;
	if (i_max == 0) {
		pos->y++;
		printf("GO DOWN\n");
	} else if (i_max == 3) {
		pos->x++;
		printf("JUMP RIGHT\n");
	} else if (i_max == 2) {
		pos->y--;
		printf("GO UP\n");
	} else
		printf("GO\n");
}

t_bool start_game_with_brain(t_brain brain) {
	t_pos p;
	int len;
	int i;
	char tmp;

	if (brain.l[brain.count - 1].j_count != N_OUTPUT) {
		printf("last layer must contain %d neurons", N_OUTPUT);
		exit(0);
	}

	p.x = 1;
	p.y = 3;
	p.input = brain.input;

	len = (int)strlen(map[0]);
	i = 0;
	while (i < len){
		get_environment(&p);
		use_brain(&brain);
		make_step(brain, &p);

		tmp = map[p.y][p.x];
		map[p.y][p.x] = 's';
		print_map();

		if (tmp == 'e')
			return (TRUE);
		if (tmp != ' ' || map[p.y + 1][p.x] != 'X')
			return (FALSE);
		else
			map[p.y][p.x] = tmp;
		i++;
	}
	printf("CONGRATULATIONS!!!\n");
	return (TRUE);
}