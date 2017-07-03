#include "lem_in.h"
#define DEF(x, y, z, q) *x = -1; *y = -1; *z = 0; *q = 2;

int g_end;
int g_start;
int g_count;
int g_lem; // № Ants
int g_err; // error ? 1 : 0;
int g_e; // 3 etaps of valid: 1 - N(ants); 2 - Vertexes; 3 - Edges
t_r *g_head;
char *g_s;

static	int i_check(t_r **b_room, char *name)
{
	t_r *t_room;

	t_room = *b_room;
	while (t_room)
		if(ft_strcmp(t_room->name, name) == 0)
			return(0);
}




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

static int              read_fd(t_fdlist *file)
{
	char    *buf;
	t_list  *onread;
	t_list  *crawler;

	if (!(buf = (char *)malloc(BUFF_SIZE + 1)) || \
        !(onread = (t_list *)malloc(sizeof(t_list))))
		return (-1);
	onread->content = buf;
	onread->content_size = BUFF_SIZE;
	onread->next = NULL;
	crawler = file->list;
	if (crawler != NULL)
	{
		while (crawler->next != NULL)
			crawler = crawler->next;
		crawler->next = onread;
	}
	else
		file->list = onread;
	return (read(file->fdnum, (char *)(onread->content), BUFF_SIZE));
}




int i_write(int i, int j, int chk, int stend)
{
	t_r *temp;

	if (chk == 1 && !ft_strcmp("##start", g_s) && g_start--)
		return (i_write(0, 1, ++chk, 1));
	else if (chk == 1 && !ft_strcmp("##end", g_s) && g_end--)
		return (i_write(0, 1, ++chk, 2));
	else if (chk == 1)
		return (get_next_line(0, &g_s));
	get_next_line(0, &g_s);
	temp = (t_r *)malloc(sizeof(t_r));												//MALLOC
	while(ft_isdigit(g_s[i]) && ft_isalpha(g_s[i]))
		g_err = (g_s[i++ + 1] == ' ') ? 1: 0;
	temp->name = (char *)malloc(sizeof(char) * i + 1);                        //MALLOC
	ft_strncpy(temp->name, g_s, (size_t)i);
	while(g_count-- && g_err)
	{
		while (ft_isdigit(g_s[i++]) && g_err)
			j++;
		g_s[i] != ' ' ? g_err = 0 : 0;
		g_count ? temp->x_cord = ft_atoi(g_s - j) : 0;
		!g_count ? temp->y_cord = ft_atoi(g_s - j) : 0;
		j = 0;
	}
	temp->stend = stend;
	temp->next = NULL;
}

int main()
{
	t_info		*t;
	t_r			*r;

	(r = (t_r *)malloc(sizeof(t_r))) ? g_head = r : 0;							//MALLOC
	t = (t_info *)malloc(sizeof(t_info));												//MALLOC
	if (read(0, g_s, 0) < 1)														//TEST reading
		return ((int)write(2, "error\n", 6));
	DEF(&g_start, &g_end, &t->v, &g_count);
	if ((g_err = get_next_line(0, &g_s) ? ft_isaldigit(g_s) : 0))
		t->ant = ft_atoi(g_s) ? ft_strclr(g_s) : g_err--;
	while (get_next_line(0, &g_s) && g_err)
		if (g_e == 2 && g_s[0] == '#' && g_s[1] == '#')
			i_write(0, 1, 1, ++g_lem);
		else if ((*g_s != '#' || g_err) && write(2, "error\n", 6))
			return (0);
}