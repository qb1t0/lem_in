#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

//room
typedef struct			s_room
{
	char				*name;
	int 				stend;
    int                 i;
    int                 alg;
	int 				x_cord;
	int					y_cord;
	struct s_room		*next;
	struct s_room		*dali;
}						t_r;

//head of room lists
typedef struct 		s_listarr
{
	t_r					*room;
}						t_l;

//main struct
typedef struct	s_info
{
	int				start;
	int				end;
	int				ant;
	int 			v;
	t_l				*arr;
}					t_info;

#endif