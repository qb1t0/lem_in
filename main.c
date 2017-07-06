#include <fcntl.h>
#include "lem_in.h"
#define DEF(x, y, z, q) *x = 0; *y = 0; *z = 0; *q = 2;

int g_fd; //FILE DESCRIPTOR
int g_j;
int g_end;
int g_start;
int g_lem; // № Ants
int g_err; // error ? 1 : 0;
int g_e; // 3 etaps of valid: 1 - N(ants); 2 - Vertexes; 3 - Edges
t_r *g_head;
char *g_s;


int l_cmp(t_r *src)
{
	t_r *temp;

	temp = src;
	if (temp->dali != NULL)
	while (1)
		if (!ft_strcmp(g_head->name, temp->name) || \
         	   (g_head->x_cord == temp->x_cord && \
          	      g_head->y_cord == temp->y_cord))
			return ((g_err = 0));
		else if (temp->dali == NULL)
			break;
		else
			temp = temp->dali;
	g_head = src;
	return(1);
}

t_r *i_write(int i, int chk, int j, int stend)
{
	t_r *temp;

	if (chk == 1 && !ft_strcmp("##start", g_s) && ++g_start)
		return (i_write(0, ++chk, 2, 1));
	else if (chk == 1 && !ft_strcmp("##end", g_s) && ++g_end)
		return (i_write(0, ++chk, 2, 2));
	else if (chk == 1 && get_next_line(g_fd, &g_s))                            //GNL
		return (0);
	stend ? get_next_line(g_fd, &g_s) : 0;
	temp = (t_r *)malloc(sizeof(t_r));												//MALLOC
	while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
		g_err = (g_s[++i] == ' ') ? 1: 0;
	temp->name = (char *)malloc(sizeof(char) * i + 1);                        //MALLOC
	ft_strncpy(temp->name, g_s, (size_t)i);
	while((g_j = 1) && j-- && g_err)
	{
		while (ft_isdigit(g_s[++i]) && g_err)
			g_j++;
		if ((j && g_s[i] != ' ') || (!j && g_s[i] != '\0'))
			g_err = 0;
		j ? temp->x_cord = ft_atoi(g_s + i - 1) : 0;
		!j ? temp->y_cord = ft_atoi(g_s + i - 1) : 0;
	}
	temp->dali = (temp->stend = stend) ? g_head : g_head;
	temp->next = NULL;
	return(temp);
}

int main()
{
	t_info		*t;

	g_fd = open("../test", O_RDONLY);
	t = (t_info *)malloc(sizeof(t_info));												//MALLOC
	if (read(g_fd, g_s, 0) < 0)														//TEST reading
		return ((int)write(2, "error\n", 6));
	DEF(&g_start, &g_end, &t->v, &g_e);
	if ((g_err = get_next_line(g_fd, &g_s) ? ft_isaldigit(g_s) : 0))				//GNL
		(t->ant = ft_atoi(g_s)) ? ft_strclr(g_s) : g_err--;
	while (get_next_line(g_fd, &g_s) && g_err)										//GNL
		if (g_e == 2 && g_s[0] == '#' && g_s[1] == '#')
			l_cmp(i_write(0, 1, 2, 0));
		else if (g_e == 2 && g_s[0] != '#')
			l_cmp(i_write(0, 1, 2, 0));
		else if ((*g_s != '#' || g_err) && write(2, "error\n", 6))
			return (0);
	g_err ? 0 :  write(2, "error\n", 6);
}