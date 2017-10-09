//
// Created by Yaroslav Salata on 8/16/17.
//
#include "lem_in.h"
#define SETMAX(a, b) (*a < b ? *a = b : 0)
char *g_s;
int g_file;
int   g_is;
int g_len;
int g_ymax;
int g_ant;
int g_x;
int g_key;
t_r *g_w;
t_r *g_sort;
t_r *g_mass[500];

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

int lb_xsort(int y, t_r *buf, int key, int xmax)
{
    int i;
    int max;

    i = 0;
    max = xmax;
    while(i < key && (buf = g_sort))
    {
        while(buf)
        {
            if (buf->x_cord <= xmax && buf->i < 0)
                xmax = buf->x_cord;
            buf = buf->dali;
        }
        buf = g_sort;
        while(buf)
        {
            if (buf->x_cord == xmax)
                buf->i = i;
            buf = buf->dali;
        }
        i++;
        xmax = max;
    }
    g_mass[y] = g_sort;
}

int createyway(int y, int key)
{
    t_r *buf;
    t_r *sort;

    buf = g_w;
    g_sort = NULL;
    while (buf)
    {
        if (buf->y_cord == y)
        {
            ++key;
            sort = (t_r *)malloc(sizeof(t_r));
            sort->name = buf->name;     //copying name
            sort->stend = buf->stend;   //copy waynum
            sort->ant = 0;
            sort->i = -1;                //set DEFAULT VALUE(0)
            //i - sort index of mass with same Y c [+Xi...Xn], where (default)0<=i<=N(n - max X-element)
            sort->y_cord = buf->y_cord; //copy Y-coord
            sort->x_cord = buf->x_cord; //copy X-coord
            sort->dali = g_sort;        //add node to the beginning of g_mass[]
            g_sort = sort;              //g_sort - our buffering global structure
        }
        buf = buf->dali;                //list to the next node
    }
    if (key)
        lb_xsort(y, buf, key, 500);
    return (key ? 0 : 1);
}

int lb_markant(t_r *buf, int x, int ant)
{
    t_r *craw;

    craw = buf;
    while(craw->x_cord != buf->x_cord)
            craw = craw->dali;
    craw->ant = ant;
    return(1);
}

int lb_outread(int ant, int i, int j, int len)
{
    t_r *buf;
    char *name;

    while(g_s[i] != 'L')
        i++;
    ant = ft_atoi(g_s + i + 1);
    while(g_s[i] != '-')
        i++;
    j = ++i;
    while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
        i++;
    name = ft_strsub(g_s, (unsigned int)j, (size_t) (i - j));
    //Todo: While g_w found this name && add ant to the g_mass[y] this list
    buf = g_w;
    while (buf)
    {
        if (!ft_strcmp(buf->name, name))
        {
            lb_markant(g_mass[buf->y_cord], buf->x_cord, ant);
            break;
        }
        buf = buf->dali;
    }
    return (i < len ? lb_outread(0, j, 0, len) : 1);
}

int lb_sort(int i, t_r *buf)
{
    t_r *craw;

    craw = buf;
    while (craw)
    {
        if (craw->i == i)
        {
            if (!ft_strcmp(craw->name, "start"))
                ft_printf(COL_LGREEN"[s]"COL_EOC);
            else if(!ft_strcmp(craw->name, "end"))
                ft_printf(COL_LGREEN"[e]"COL_EOC);
            else
                ft_printf("[%*.d]", g_ant ,craw->ant);
            return (1);
        }
       craw = craw->dali;
    }
    return (0);
}

int lb_drawall(int i, int j, int ant)
{
    t_r *buf;

    while(i <= g_ymax)
    {
        buf = g_mass[i];
        if (buf != NULL)
        {
            while (lb_sort(j, buf))
                j++;
        }
        j = 0;
        ft_printf("\n");
        i++;
    }
}

int map_init(int x, int y, int i, char *s)
{
    while (y <= g_ymax)
    {
        g_mass[y] = NULL;
        createyway(y, 0);
        y++;
    }
    while(get_next_line(g_file, &g_s))
    {
        lb_outread(0, 0, 0, (int) ft_strlen(g_s));
        lb_drawall(0, 0, 0); //ToDO: draw this step here
        ft_printf("________________________\n\n");
    }
}

int lb_write(int way, unsigned int i, size_t j)                      //i == 2, cause skip "[ " in string
{
    t_r *e;

    if (get_next_line(g_file, &g_s) && !g_s[0])                     //ways read
        return (0);
    g_len = (int)ft_strlen(g_s);
    while (i < g_len && (e = (t_r *)malloc(sizeof(t_r))))
    {
        while(ft_isdigit(g_s[i]) || ft_isalpha(g_s[i]))
            i++;
        e->name = ft_strsub(g_s, (unsigned int)j, i - j);
        if (way > 0  && (ft_strcmp(E+2, e->name) || ft_strcmp(S+2, e->name)))
                return(1);
        j = (size_t)++i;
        while(ft_isdigit(g_s[i]) || g_s[i] == '-')
            i++;
        e->x_cord = ft_atoi(g_s + j) * (g_ant + 3);
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
        if (!strncmp(g_s,"ERROR", 5))                             //error printing
            exit(lb_drawpic(fd, 1));
        else if (!(found = strcmp(g_s, "BONUS WAYS:")))
            break;
        else if (ft_isaldigit(g_s) && (g_ant = (int)ft_strlen(g_s))) //
            ft_strclr(g_s);      //len of ant number
        else
            ft_strclr(g_s);
    found ? exit(lb_drawpic(fd, 0)) : ft_strclr(g_s);             //no-bonus print
    ft_printf("\e[5mYOUR WAYS : \n");
    while (lb_write(g_is, 2, 2))
        ++g_is;
    map_init(0, 0, 0, g_s);
}
