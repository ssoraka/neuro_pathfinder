//
// Created by ssoraka on 11.08.2020.
//

#ifndef GAME_WITH_BRAIN_HEADER_H
#define GAME_WITH_BRAIN_HEADER_H

#include <string.h>
#include <stdio.h>
#include <time.h>
#include "math.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef int t_bool;

#define HEIGHT (5)


typedef enum	e_sig
{
	EMPTY,
	EARTH,
	TRAP,
	EXIT,
	SIGNAL_COUNT
}				t_sig;

#define N_INPUT (4 * SIGNAL_COUNT)
#define N_OUTPUT (4)

//структура слоя
typedef struct		s_layer
{
	//функция активации нейрона
	double			(*func)(double);
	//массив выходов нейронов (зарезервировал 100 на просто для удобства)
	double			f[100];
	//количество нейронов в этом слое
	int				j_count;
	// количество нейронов в предыдущем слое
	int				i_count;
	// массив связей размером i_count * j_count (зарезервировал 10000 на просто для удобства)
	double			w_ij[100][100];
}					t_layer;


//структура слоя
typedef struct		s_brain
{
	/*
	 * зрительные сенсоры
	 * просматривается 4 точки, в каждой фиксируется 1 из трех признаков t_sig:
	 * пустота, земля (по ней можно забираться), ловушка (их нужно перепрыгивать), выход(в него надо прыгать)
	 *
	 *   2
	 *  s13
	 *   0
	 *
	 * в них будут помещены сигналы датчиков t_sig в процессе движения
	 *
	 * соответственно последний слой должен иметь 4 нейрона
	 * для перемещения в соответствущие точки, минуя все опасности
	 */
	double			input[N_INPUT];
	//массив слоев нейронов
	t_layer			*l;
	//количество слоев в массиве
	int				count;
}					t_brain;




t_bool start_game_with_brain(t_brain brain);

#endif //GAME_WITH_BRAIN_HEADER_H
