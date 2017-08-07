#include <fcntl.h>
#include "lem_in.h"

#define DEF(x, y, z, q) *x = 0; *y = 0; *z = 0; *q = 1;
#define IS_COM(a) ((*a == '#')  ? (1) : (0))
#define A(s) (ft_printf(COL_GREEN"%s\n"COL_EOC, s))
#define E "##end"
#define S "##start"

int g_fd; //FILE DESCRIPTOR
int g_j;
int g_o;
int g_f;
int g_is;
int g_end;
int g_isrt;
int g_iend;
int g_start;
int g_stop;
int g_err; // error ? 1 : 0;
int g_e; // 3 etaps of valid: 1 - N(ants); 2 - Vertexes; 3 - Edges
int *g_al; //uses a queue (First In First Out)
int g_h;
t_r *g_head;
t_r *g_back;
t_l *g_arr;
t_l *g_ways;
char *g_s;

int		ft_strfcmp(const char *s1, const char *s2, size_t n)
{
    if (n == 0)
        return (0);
    while ((*s1 && *s2) && (n > 1) && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    return (*(unsigned char *)(s1) - *(unsigned char *)(s2));
}

void    l_out(int i, int j, int ant)
{
    t_r *buf;

    while (g_ways[0].len == 1 && ++i < ant)
        printf("L%d-%s ", i + 1, g_arr[g_iend].room->name);
    i != -1 ? exit((int)write(1, "\n", 1)) : 0;
    while (++i < ant)
    {
        //g_ways[i]
    }
    while (i < g_f)
    {
        buf = g_ways[i].room;
        while(buf)
        {

            buf = buf->dali;
        }
        i++;
    }
    return ;
}

int  l_cleanway(int i, int v, t_r *buf)
{
    while (++i < v - 1)
        if (i != g_isrt && g_arr[i].room->was != -1)
            g_arr[i].room->was = 0;
    while (buf)
    {
        if (buf->i != g_iend)
            g_arr[buf->i].room->was = -1;
        buf = buf->dali;
    }
}

int  l_wayback(int v, int k, t_l *arr)
{
    int i;
    t_r *buf;

    //buf = (t_r *)malloc(sizeof(t_r) * k);
    g_ways[g_f - 1].len = k;
    while((buf = (t_r *)malloc(sizeof(t_r))) && k > 0)
    {
        i = 0;
        while(i < v && arr[i].room->was != k)
            i++;
        if (i != g_isrt && i != g_iend)
            g_arr[i].room->was = i;
        //buf = (t_r *)malloc(sizeof(t_r));
        buf->i = arr[i].room->i;
        //buf->name = arr[i].room->name;
        buf->ant = 0;
        buf->dali = g_ways[g_f - 1].room;
        g_ways[g_f - 1].room = buf;
        k--;
    }
    buf = g_ways[g_f - 1].room;
    l_cleanway(-1, v, buf);
    return(1);
}

int     create_link(int dst, int src, int time)
{
    t_sr *buf;

    buf = (t_sr *)malloc(sizeof(t_sr));
    buf->i = src;
    buf->wave = -1;
    buf->next = g_arr[dst].room->alg;
    g_arr[dst].room->alg = buf;
    if (time--)
        return(create_link(src, dst, time));
    ft_printf(COL_CYAN"%s\n"COL_EOC, g_s);
    return (0);
}

/*
** Representing of the BFS algorithm
 * g_al - int mass for stack
 *
*/
int      l_algo(int k, int i, int v)
{
    t_sr *buf;
    t_l  *arr;

    arr = g_arr;
    g_al = (int *)malloc(sizeof(int) * v); //int mass for stack
    buf = g_arr[g_isrt].room->alg;
    while (++k < v && (buf = (k ? arr[g_al[k - 1]].room->alg : arr[g_isrt].room->alg)))
    {//loop for vertices marking
        while(buf) {
            if (g_arr[buf->i].room->was != -1 && \
                !arr[buf->i].room->was && buf->wave == -1) //mark here
                g_al[k + i++] = buf->i;
            if (arr[buf->i].room->was != -1)
                arr[buf->i].room->was = k + 1;
            if (buf->i == g_iend) //stop if end
                return (l_wayback(v, ++k, arr));
            buf = buf->next;
        }
        i ? i-- : 0;
    }
    if (arr[k].room->i != g_iend && g_f == 1)
        exit(ft_printf("%s", g_errors[5]));
    else
        return (g_err);
    //return(l_wayback(v, --k, arr));
}

/*
** Reads string with link
** Comparing link name with existing list
*/

int    l_link(t_r *buf, int v, int time, int i)
{
    static int src;
    static int dst;

    //g_f = !g_f ? 0 : g_f + 1;
    while(g_s[i] && g_err && g_s[i] != '-')
        i++;
    i == 0 || !g_s ? exit(ft_printf("%s\n", g_errors[6])) : 0;
    i = time == 2 ? 0 : i + 1;
    while(g_s && time && buf != NULL)
        if (!(g_is = (ft_strfcmp(buf->name, g_s + i, (size_t)i + 1))))
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
        create_link(dst, src, 1);
    dst == g_isrt ? g_start++ : 0;
    dst == g_iend ? g_end++ : 0;
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
	return (ft_printf(COL_GREEN"%s\n"COL_EOC, g_s));
}

/*
** Error parsing func
** variable place:
** 0 ? ant error
** 1 ? start/end error
** 2 ? room name/coordinates error
*/

int    l_error(int place)
{
    if (place == 0)
        exit(ft_printf("%s", g_errors[0]));
    else if (place == 1 && !g_s)
        exit(ft_printf("%s", g_errors[6]));
    else if (place == 1 && (g_start > 1 || g_end > 1))
        exit(ft_printf("%s", g_errors[4]));
    else if (place == 1 && (g_start < 1 || g_end < 1))
        exit(ft_printf("%s", g_errors[3]));
    else if (place == 2)
        exit(ft_printf("%s", g_errors[2]));
}

/*
** Room info read && validate function
*/

t_r *l_room(int i, int j, int stend)
{
	t_r *temp;

    //command === comments ? problem
	if (g_start == 0 && !ft_strcmp(S , g_s) && ++g_start)
		return (ft_printf(COL_GREEN S"\n"COL_EOC) ? l_room(0, 2, 1) : 0);
	else if (g_end == 0 && !ft_strcmp(E, g_s) && ++g_end)
		return (ft_printf(COL_GREEN E"\n" COL_EOC) ? l_room(0, 2, 2) : 0);
    while (stend && ft_strclr(g_s) && get_next_line(g_fd, &g_s))
        if (!(IS_COM(g_s) ? ft_printf(COL_GRAY"%s\n"COL_EOC,g_s) : 0))
            break;
    while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
        i++;
    if ((g_e = (g_s[i] == ' ' && *g_s != 'L') ? 2 : 3) == 3)
        return(l_error(1) ? 0 : 0);
    temp = (t_r *)malloc(sizeof(t_r));
    temp->name = ft_strsub(g_s, 0, (size_t)i);
	while(g_e == 2 && (g_j = 1) && j--)
	{
		while (ft_isdigit(g_s[++i]) && g_err)
			g_j++;
		(j && g_s[i] != ' ') || (!j && g_s[i] != '\0') ? l_error(2) : 0;
		j ? temp->x_cord = ft_atoi(g_s + i - 1) : 0;
		!j ? temp->y_cord = ft_atoi(g_s + i - 1) : 0;
	}
    temp->dali = (temp->stend = stend) ? g_head : g_head;
    return(temp);
}

int main(void)
{
	t_info		*t;

	g_fd = open("../test", O_RDONLY);
	t = (t_info *)malloc(sizeof(t_info));
	g_err = (int)read(g_fd, g_s, 0) >= 0 ? 1 : 0;
	DEF(&g_start, &g_end, &t->v, &g_e);
	while (ft_strclr(g_s) && get_next_line(g_fd, &g_s) && g_err)
		if (IS_COM(g_s) && ft_strcmp(E, g_s) && ft_strcmp(S, g_s))
            ft_printf(COL_GRAY"%s\n"COL_EOC,g_s);
        else if (g_e == 1 && ++g_e)
            ft_isaldigit(g_s) && (t->ant = ft_atoi(g_s)) ? A(g_s) : l_error(0);
		else if (g_e == 2)
			l_compare(l_room(0, 2, 0), t->v++);
        else if (g_e == 3)
            l_link(g_head, t->v, 2, 0);
    g_h = (g_start < g_end) ? g_start : g_end; //g_h - how much ways
    if ((g_ways = (t_l *)malloc(sizeof(t_l) * g_h)) && (g_f = 1)) //array for ways
        while (g_f - 1 < g_h && l_algo(-1, 0, t->v))
            g_f++;
    g_f > 0 ? l_out(-1, -1, t->ant) : exit(ft_printf("%s", g_errors[5]));
    return (1);
}