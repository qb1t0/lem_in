#include "lem_in.h"
/*
** Error parsing func
** variable place:
** 0 ? ant error
** 1 ? start/end error
** 2 ? room name/coordinates error
*/

int     errorlink(int place, int dst, int src, int time)
{
    t_sr *buf;

    if (place)
    {
        if (place == -2)
            exit(ft_printf(COL_RED"ERROR (9): INVALID BONUS NUMBER"COL_EOC));
        if (place == -1)
            exit(ft_printf("%s", g_errors[0]));
        else if (place == 1 && (!ft_strcmp(S, g_s) || !ft_strcmp(E, g_s)))
            exit(ft_printf("%s", g_errors[4]));
        else if (place == 1 && !g_s)
            exit(ft_printf("EMPTY LINE: %s", g_errors[6]));
        else if (place == 2 || (place == 1 && dst == 0))
            exit(ft_printf("%s", g_errors[2]));
        else if (place == 1 && (g_start < 1 || g_end < 1))
            exit(ft_printf("%s", g_errors[3]));
        return(0);
    }
    buf = (t_sr *)malloc(sizeof(t_sr));
    buf->i = src;
    buf->wave = -1;
    buf->next = g_arr[dst].room->alg;
    g_arr[dst].room->alg = buf;
    if (time--)
        return(errorlink(0, src, dst, time));
    return(ft_printf(COL_CYAN"%s\n"COL_EOC, g_s));
}

/*
** Reads string with link
** Comparing link name with existing list
*/

int    l_link(t_r *buf, int v, int time, int i)
{
    static int src;
    static int dst;

    g_o = 0;
    while(g_s[i] && g_err && g_s[i] != '-')
        ++i ? g_o++ : 0;
    if (i == 0 || !g_s)
        return(ft_printf("%s\n", g_errors[6]) ? g_err = 0 : 0);
    i = ((time == 2) ? 0 : i + 1);
    while(g_s && time && buf != NULL)
        if (!(g_is = (ft_strncmp(buf->name, g_s + i, g_o))))
        {
            time == 2 ? src = buf->i : 0;
            time == 1 ? dst = buf->i : 0;
            return(l_link(g_head, v, --time, 0));
        }
        else
            buf = buf->dali;
    if (g_is && printf("%s", g_errors[7]))
        return (g_err = 0);

    if (dst != src)
        errorlink(0, dst, src, 1);
    src == g_isrt || dst == g_isrt ? g_start++ : 0;
    src == g_iend || dst == g_iend ? g_end++ : 0;
    return (1);
}

/*
** if (takes room(t_r))
**  Comparing names && coordinates of new room with already existing
** else if (takes 0 (src = 0))
**  Creating adjacency list array
*/

int l_compare(t_r *src, int v)
{
	t_r *temp;

	temp = g_head;
    !g_f ? g_f = 1 : 0;
    if (!src && (g_arr = (t_l *)malloc(sizeof(t_l) * v)))
        while(temp && (g_arr[temp->i].room = temp))
        {//each room 4 each g_arr[i]
            g_arr[temp->i].room->alg = NULL;
            g_arr[temp->i].room->was = 0;
            temp = temp->dali;
        }
    if (!src)
        return(l_link(g_head, v, 2, 0));
    while (temp != NULL)
        if (!ft_strcmp(src->name, temp->name) &&\
             (src->x_cord == temp->x_cord && src->y_cord == temp->y_cord))
                return(1);
        else if(!ft_strcmp(src->name, temp->name) || \
            (src->x_cord == temp->x_cord && src->y_cord == temp->y_cord))
            exit(ft_printf("%s", g_errors[8]));
        else
			    temp = temp->dali;
    src->stend == 1 ? g_isrt = v : 0;
    src->stend == 2 ? g_iend = v : 0;
    src->i = v;
    g_head = src;
	return(ft_printf(COL_GREEN"%s\n"COL_EOC, g_s));
}

/*
** Room info read && validate function
*/

t_r *l_room(int i, int j, int stend)
{
	if (g_start == 0 && !ft_strcmp(S , g_s) && ++g_start)
		return(ft_printf(COL_GREEN S"\n"COL_EOC) ? l_room(0, 2, 1) : 0);
	else if (g_end == 0 && !ft_strcmp(E, g_s) && ++g_end)
		return(ft_printf(COL_GREEN E"\n" COL_EOC) ? l_room(0, 2, 2) : 0);
    while (stend && ft_strclr(g_s) && get_next_line(g_fd, &g_s))
        if (!(IS_COM(g_s) ? ft_printf(COL_GRAY"%s\n"COL_EOC,g_s) : 0))
            break;
    while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
        i++;
    if ((g_e = (g_s[i] == ' ' && *g_s != 'L' && i != 0) ? 2 : 3) == 3)
        return(errorlink(1, i, 0, 0) ? NULL : NULL);
    g_temp = (t_r *)malloc(sizeof(t_r));
    g_temp->name = ft_strsub(g_s, 0, (size_t)i);
	while(g_e == 2 && (g_j = 1) && j--)
	{
        g_s[i + 1] == '-' ? i++ : 0;
		while (ft_isdigit(g_s[++i]) && g_err)
			g_j++;
        if ((j && g_s[i] != ' ') || (!j && g_s[i] != '\0') || g_j == 1)
            errorlink(2,0,0,0);
		j ? g_temp->x_cord = ft_atoi(g_s + i - g_j) : 0;
		!j ? g_temp->y_cord = ft_atoi(g_s + i - g_j) : 0;
	}
    g_temp->dali = (g_temp->stend = stend) ? g_head : g_head;
    return(g_temp);
}

/*
int main(void)
{
	t_info		*t;

	g_fd = open("../test1", O_RDONLY);
	t = (t_info *)malloc(sizeof(t_info));
	g_err = (int)read(g_fd, g_s, 0) >= 0 ? 1 : 0;
	DEF(&g_start, &g_end, &t->v, &g_e);
	while (ft_strclr(g_s) && get_next_line(g_fd, &g_s) && g_err)
        if (g_b == 1 && g_b++)
            ft_isaldigit(g_s) ? g_bon = ft_atoi(g_s) : errorlink(-2, 0, 0, 0);
        else if ((g_b = (ft_strcmp("##bonus", g_s) ? 0 : 1)))
            ft_printf("\e[5m""\e[91m"B);
		else if (IS_COM(g_s) && ft_strcmp(E, g_s) && ft_strcmp(S, g_s))
            ft_printf(COL_GRAY"%s\n"COL_EOC, g_s);
        else if (g_e == 1 && ++g_e)
            ft_isaldigit(g_s) && (t->ant = ft_atoi(g_s)) ? \
                A(g_s) : errorlink(-1, 0, 0, 0);
		else if (g_e == 2)
			l_compare(l_room(0, 2, 0), t->v++);
        else if (g_e == 3)
            l_link(g_head, t->v, 2, 0);
    g_h = (g_start < g_end) ? g_start - 1 : g_end - 1; //g_h - how much ways
    if ((g_ways = (t_l *)malloc(sizeof(t_l) * g_h)) && (g_f = 1)) //array for ways
        while (g_f - 1 < g_h && l_algo(-1, 0, t->v))
            g_f++;
    g_f > 1 ? l_out(-1, -1, t->ant) : exit(ft_printf("%s", g_errors[5]));
    return(1);
}*/