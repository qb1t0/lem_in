#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/ft_printf/ft_printf.h"

//room
typedef struct		s_room
{
	char				*name;
	int 				x_cord;
	int					y_cord;
	struct s_room	*next;
}						t_r;

//head of room lists
typedef struct 		s_lhead
{
	t_r					*room;
}						t_head;

//main struct
typedef struct	s_info
{
	int				start;
	int				end;
	int				ant;
	int 			v;
	t_head		*arr;
}					t_info;

# endif