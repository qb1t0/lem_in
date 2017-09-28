# ifndef LEM_IN_H
#define LEM_IN_H

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

#define DEF(x, y, z, q) *x = 0; *y = 0; *z = 0; *q = 1;
#define IS_COM(a) ((*a == '#')  ? (1) : (0))
#define START(i) (ft_printf("[ start(%d,%d) ]", X(i), Y(i)))
#define END(i) (ft_printf("->[ end(%d,%d) ]\n", X(i), Y(i)))
#define ROOM(s, i) (ft_printf("->[ %s(%d,%d) ]", s, X(i), Y(i)))
#define X(i) (g_arr[i].room->x_cord)
#define Y(i) (g_arr[i].room->y_cord)
#define A(s) (ft_printf(COL_GREEN"%s\n"COL_EOC, s))
#define E "##end"
#define S "##start"
#define B "bonus activated, put number of ways\n"COL_EOC

/*
** An error char *array[]
*/

static char             *g_errors[] = {
        COL_RED"ERROR (0): Invalid ants\n"COL_EOC,
        COL_RED"ERROR (1): No rooms\n"COL_EOC,
        COL_RED"ERROR (2): Invalid room name\n"COL_EOC,
        COL_RED"ERROR (3): No start or end room\n"COL_EOC,
        COL_RED"ERROR (4): Must be just 1 start && 1 end\n"COL_EOC,
        COL_RED"ERROR (5): Cant found way \f"
                "from start to end\n"COL_EOC,
		COL_RED"ERROR (6): Where is links?\n"COL_EOC,
        COL_RED"ERROR (7): Non-existing room\f"
				"name in link\n"COL_EOC,
		COL_RED"ERROR (8): Same room name or coordinates "
                "are already exist"COL_EOC
};

/*
** Adjacency list array(g_arr)
** For more info: https://en.wikipedia.org/wiki/Adjacency_list
*/

typedef struct			s_smallroom
{
    int                 i;
    int                 wave;
    struct s_smallroom  *next;
}						t_sr;

/*
** Room structure
** x_cord, y_cord - Room x & y coordinates
** name           - Room name
** alg            - Mark's room by -1 (needed by BFS algorithm)
** i              - The depth of a node
** dali           - pointer 4 next node, while reading rooms(g_e = 2)
** next           - pointer 4 next node, in adjacency list array(g_arr)
** stend          - default room - 0, for start = 1, for end = 2
*/

typedef struct			s_room
{
	char				*name;
	int 				stend;
    int                 ant;
    int                 i;
    int                 was;
	int 				x_cord;
	int					y_cord;
    t_sr                *alg;
	struct s_room		*dali;
    struct s_room		*prev;

}						t_r;

typedef struct 		    s_listarr
{
    t_r					*room;
    int                 len;
    int                 is;
}						t_l;

typedef struct	        s_info
{
	int				    ant;
	int 			    v;
}					    t_info;

int g_j;
int g_b;
int g_f;
int g_e; // 3 etaps of valid: 1 - N(ants); 2 - Vertexes; 3 - Edges
int g_h;
int g_fd;
int g_is;
int *g_al; //uses a queue (First In First Out)
char *g_s;
int g_err; // error ? 1 : 0;
int g_bon;
int g_end;
int g_isrt;
int g_iend;
size_t g_o;
t_sr *g_sr;
t_l *g_arr;
t_r *g_temp;
t_r *g_head;
t_l *g_ways;
int g_start;


int     				errorlink(int place, int dst, int src, int time);
int    					l_link(t_r *buf, int v, int time, int i);
int 					l_compare(t_r *src, int v);
t_r						*l_room(int i, int j, int stend);
int      				l_algo(int k, int i, int v);
int  					l_wayback(int v, int k, t_l *arr);
int  					l_cleanway(int k, int i, int v, t_r *buf);
void    				l_out(int i, int j, int ant);
int     				l_crawandprint(int ant, int j, int k, t_r *buf);


#endif