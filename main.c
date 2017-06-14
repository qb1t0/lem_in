#include "lem_in.h"

int g_end;
int g_start;
int g_lem;
int g_err;
char *g_s;

static	int i_check(t_r **b_room, char *name)
{
	t_r *t_room;

	t_room = *b_room;
	while (t_room)
		if(ft_strcmp(t_room->name, name) == 0)
			return(0);
}

static int i_write(char chk, int cnt, t_info **t)
{
	/*
	if ((chk == 'e' && cnt == 1) ? get_next_line(0, &g_s) : 0)
		get_data(&(*t)->room, g_s) ? 1 : g_err = 1;
	else if  ((chk == 's' && cnt == 1) ? get_next_line(0, &g_s) : 0)
		get_data(&(*t)->room, g_s) ? 1 : g_err = 1;
	 */
	if ((chk == 'e' || chk == 's') ? get_next_line(0, &g_s) : 1)
		ft_strclr(g_s);

}

int main()
{
	t_info		*t;
	t_r			*r;

	g_start = 0;
	get_next_line(0, &g_s) ?  g_err = ft_isaldigit(g_s) : 0;
	if (g_err == 0 ? write(2, "error\n", 6) : 0)
		return (0);
	while (get_next_line(0, &g_s))
		if (*g_s == '#' && *(g_s  + 1) != '#')
			ft_strclr(g_s);
		else if (*g_s == '#' && !ft_strcmp("##start", g_s))
			g_err = (g_start == 0) ? i_write('s', ++g_start, &t) : -1;
		else if (*g_s == '#' && !ft_strcmp("##end", g_s))
			g_err = (g_end == 0) ? i_write('e', ++g_end, &t) : -1;
		else if (i_write(' ', ++g_lem, &t))
			continue ;
		else if (write(2, "error\n", 6))
			return (0);
}