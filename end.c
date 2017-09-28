#include "lem_in.h"

int     l_crawandprint(int ant, int j, int k, t_r *buf)
{
    int i;

    i = 0;
    while (j && ++i <= ant && (j = -1))
        while (++j < g_h && (buf = g_ways[j].room))
            while (buf)
                if (buf->ant == i && ft_printf("L%d-%s ", buf->ant, buf->name))
                {
                    k = 1;
                    j = g_h;
                    break;
                }
                else
                    buf = buf->dali;
    if (j)
        return(k);
    while (buf->i != g_iend)
        buf = buf->dali;
    while (buf->prev)
    {
        buf->ant = buf->prev->ant;
        buf = buf->prev;
    }
    return(buf->ant = ant);
}

void    l_out(int i, int j, int ant)
{
    t_r *buf;

    if (g_bon && ft_printf("BONUS WAYS:\n"))
        while (++i < g_f - 1  && (buf = g_ways[i].room) && g_bon--)
            while (buf)
            {
                buf->prev ? 0 : START(g_isrt);
                if (!(buf->i == g_iend ? END(g_iend) : 0))
                    buf->i != g_iend && buf->i != g_isrt ? \
                    ROOM(buf->name, buf->i) : 0;
                buf = buf->dali;
            }
    i = -1;
    while (g_ways[0].len == 1 && ++i < ant)
        printf("L%d-%s ", i + 1, g_arr[g_iend].room->name);
    i != -1 ? exit((int)write(1, "\n", 1)) : i++;
    while ((i < ant || g_ways[0].is) && ft_printf("\n"))
    {
        while (++j < g_h && (buf = g_ways[j].room))
            if (i < ant && g_ways[j].len - g_ways[0].len + 1 <= ant)
                g_ways[j].is = l_crawandprint(++i, 0, 0, buf);
            else if (g_ways[j].is)
                l_crawandprint(0, 0, 0, buf);
        g_ways[0].is = l_crawandprint(i, -1, 0, buf);
        j = g_ways[0].is ? -1 : 2 - 3;
    }
}

int      l_cleanway(int k, int i, int v, t_r *buf)
{
    t_sr *lol;

    if (k == 0)
    {
        lol = g_arr[i].room->alg;
        while (v > 0 && g_arr[lol->i].room->was != v) // v is like k in wayback
            lol = lol->next;
        return (lol->i);
    }
    while (++i < v - 1)
        if (i != g_isrt && g_arr[i].room->was != -1)
            g_arr[i].room->was = 0;
    while (buf)
    {
        if (buf->i != g_iend)
            g_arr[buf->i].room->was = -1;
        buf = buf->dali;
    }
    return (1);
}

/*
** Creating list j (g_ways[j]) of key rooms
*/

int     l_wayback(int v, int k, t_l *arr)
{
    int i;
    t_r *buf;

    g_ways[g_f - 1].room = NULL;
    g_ways[g_f - 1].len = k;
    i = g_iend;
    while(k > 0 && (buf = (t_r *)malloc(sizeof(t_r))))
    {
        (k == g_ways[g_f - 1].len) ? 0 : (i = l_cleanway(0, i, k, buf));
        if (i != g_isrt && i != g_iend)
            g_arr[i].room->was = i;
        buf->i = arr[i].room->i;
        buf->name = arr[i].room->name;
        buf->ant = 0;
        g_ways[g_f - 1].room ? g_ways[g_f - 1].room->prev = buf : 0;
        buf->dali = g_ways[g_f - 1].room;
        g_ways[g_f - 1].room = buf;
        k--;
    }
    g_ways[g_f - 1].room->prev = NULL;
    buf = g_ways[g_f - 1].room;
    g_ways[g_f - 1].is = 0;
    l_cleanway(1, -1, v, buf);
    return(1);
}

/*
** Representing of the BFS algorithm
 * g_al - int mass for stack
 *
*/
int     l_algo(int k, int i, int v)
{
    t_r *buf;
    t_l *arr;

    arr = g_arr;
    g_al = (int *)malloc(sizeof(int) * v); //int mass for stack
    buf = g_arr[g_isrt].room;
    while (++k < v - 1 && (g_sr = buf->alg))
    {//loop for vertices marking
        while(g_sr)
        {
            if (g_arr[g_sr->i].room->was == 0 && g_sr->i != g_isrt) //mark here
                g_al[k + i++] = g_sr->i;
            if (arr[g_sr->i].room->was == 0 && g_sr->i != g_isrt)
                arr[g_sr->i].room->was = buf->was + 1;
            if (g_sr->i == g_iend) //stop if end
                return (l_wayback(v, g_arr[g_sr->i].room->was, arr));
            g_sr = g_sr->next;
        }
        if (i == 0 && k > 0)
            break;
        i ? i-- : 0;
        buf = arr[g_al[k]].room;
    }
    if (arr[k - 1].room->i != g_iend && g_f == 1)
        exit(ft_printf("%s", g_errors[5]));
    else
        return (g_err);
}