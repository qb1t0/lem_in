//
// Created by Yaroslav Salata on 8/16/17.
//
#include "lem_in.h"
#define SETMAX(a, b) (*a < b ? *a = b : 0)
char *g_s;
int g_file;
int   g_is;
int g_ymax;
int g_ant;
int g_x;
int g_key;
t_r *g_w;
t_r *g_sort;

int lb_drawpic(int fd, int type)
{

    if (fd == -1)
    {
        get_next_line(g_file, &g_s);

    }
    if (type != 2)
        fd = type ? open("../fail", O_RDONLY) : open("../isactive", O_RDONLY);
    else
        while (get_next_line(fd, &g_s))
            printf(COL_GREEN"%s\n"COL_EOC, g_s) ? ft_strclr(g_s) : 0;
        while (get_next_line(fd, &g_s))
            printf(COL_RED"%s\n"COL_EOC, g_s) ? ft_strclr(g_s) : 0;
    return (0);
}

int createyway(int y, int key, int check)
{
    t_r *buf;
    t_r *sort;

    buf = g_w;
    g_sort = NULL;
    while (buf && (g_x = 200))
    {
        if (buf->y_cord == y)
        {
            g_key = ++key;
            sort = (t_r *)malloc(sizeof(t_r));
            sort->name = buf->name;     //copying name
            sort->i = 0;                //set DEFAULT VALUE(0)
            //i - sort index of mass with same Y c [+Xi...Xn], where (default)0<=i<=N(n - max X-element)
            sort->y_cord = buf->y_cord; //copy Y-coord
            sort->x_cord = buf->x_cord; //copy X-coord
            sort->dali = g_sort;        //add node to the beginning of g_sort
            g_sort = sort;              //g_sort - our buffering global structure
        }
        buf = buf->dali;                //list to the next node
    }
    while (g_x > 0 && check <= key && (buf = g_sort))
        while (buf)
            if (buf->x_cord == g_x)
                buf->i = check++;
            else
                buf = buf->dali;
    return (!key ? 0 : 1);
}

int drawmap(int x, int y, int i,char *s)
{
    t_r *buf;

    while (y <= g_ymax)
    {
        if (!createyway(y, 0, -1) && ft_printf("\n") && y++)
            continue;
        while ((buf = g_sort) && g_key > 0)
            while (buf)
                if (buf->i == i && g_key--)
                    lb_drawpic(-1, 0);
                else
                    buf = buf->dali;
    }
}

int lb_write(int way, unsigned int i, size_t j)                      //i == 2, cause skip "[ " in string
{
    t_r *e;

    if (get_next_line(g_file, &g_s) && !g_s[0])                     //ways read
        return (0);
    while (g_s[i] && (e = (t_r *)malloc(sizeof(t_r))))
    {
        while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
            i++;
        e->name = ft_strsub(g_s, (unsigned int)j, i - j);
        j = (size_t)++i;
        while(ft_isdigit(g_s[i]) || g_s[i] == '-')
            i++;
        e->x_cord = ft_atoi(g_s + j) * g_ant;
        j = (size_t)++i;
        while(ft_isdigit(g_s[i]) || g_s[i] == '-')
            i++;
        SETMAX(&g_ymax, (e->y_cord = ft_atoi(g_s + j)));
        e->stend = way;
        e->dali = g_w;
        g_w = e;
        i += 7;
        j = i;
    }
    return (1);
}

int main(void)
{
    int fd;
    t_r *r;
    int found;

    found = 1;
    g_file = open("../test", O_RDONLY);
    g_is = 0;
    g_w = NULL;
    g_ymax = 0;
    fd = open("../head", O_RDONLY);
    while (get_next_line(fd, &g_s))                               //head printing
        printf(COL_LCYAN"%s\n"COL_EOC, g_s) ? ft_strclr(g_s) : 0;
    while (get_next_line(g_file, &g_s))
        if (!strncmp(g_s,"ERROR", 5))                            //error printing
            exit(lb_drawpic(fd, 1));
        else if (!(found = strcmp(g_s, "BONUS WAYS:")))
            break;
        else if (ft_isaldigit(g_s))
            g_ant = ft_strlen(g_s) + 1 ? ft_strclr(g_s) : 0;     //len of ant number
        else
            ft_strclr(g_s);
    found ? exit(lb_drawpic(fd, 0)) : ft_strclr(g_s);            //no-bonus print
    ft_printf("\e[5mYOUR WAYS : \n") ;
    while (lb_write(g_is, 2, 2))
        ++g_is;
    while (get_next_line(g_file, &g_s))
        drawmap(0, 0, 0, g_s);
}