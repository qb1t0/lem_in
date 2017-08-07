# ifndef LEM_IN_H
#define LEM_IN_H

#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

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
** ENUM for bool constants
** f - false; t - true
*/

typedef enum            e_bool
{
    f,
    t
}                       t_bool;

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

}						t_r;

typedef struct 		    s_listarr
{
    t_r					*room;
    int                 len;
}						t_l;


//** List for founded way
//*/
//typedef struct 		    s_way
//{
//    char                *name;
//    int
//}						t_way;

/*
** ant             - № of ants
** v               - № of vertices
 */

typedef struct	        s_info
{
	int				    start;
	int				    end;
	int				    ant;
	int 			    v;
	t_l				    *arr;
}					    t_info;

#endif