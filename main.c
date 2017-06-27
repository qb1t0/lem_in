#include "lem_in.h"

int g_end;
int g_start;
int g_lem; // № Ants
int g_err; // error ? 1 : 0;
int g_e; // 3 etaps of valid: 1 - N(ants); 2 - Vertexes; 3 - Edges
t_fdlist g_;
char *g_s;

static	int i_check(t_r **b_room, char *name)
{
	t_r *t_room;

	t_room = *b_room;
	while (t_room)
		if(ft_strcmp(t_room->name, name) == 0)
			return(0);
}

 int i_write(char chk, int cnt, t_info **t)
{
	static t_list;


	/*
	if ((chk == 'e' && cnt == 1) ? get_next_line(0, &g_s) : 0)
		get_data(&(*t)->room, g_s) ? 1 : g_err = 1;
	else if  ((chk == 's' && cnt == 1) ? get_next_line(0, &g_s) : 0)
		get_data(&(*t)->room, g_s) ? 1 : g_err = 1;
	 */
	if ((chk == 'e' || chk == 's') ? get_next_line(0, &g_s) : 1)
	{
		chk == 'e' ?
	}
		ft_strclr(g_s);

}

int main()
{
	t_info		*t;
	t_r			*r;

	g_start = 1;
	g_end = 1;
	if (get_next_line(0, &g_s) ? g_err = ft_isaldigit(g_s) : 0)
		t->ant = ft_atoi(g_s) ? ft_strclr(g_s) : g_err--;
	while (get_next_line(0, &g_s) && g_err)
		if (g_e == 2 && *g_s == '#' && !ft_strcmp("##start", g_s))
			g_err = (g_start) ? i_write('s', --g_start, &t) : 0;
		else if (g_e == 2 && *g_s == '#' && !ft_strcmp("##end", g_s))
			g_err = (g_end) ? i_write('e', --g_end, &t) : 0;
		else if (g_e == 2 && i_write(' ', ++g_lem, &t))
			continue ;
		else if ((*g_s != '#' || g_err) && write(2, "error\n", 6))
			return (0);
}