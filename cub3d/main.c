# include "../minilibx_opengl_20191021/mlx.h"

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct	s_player
{
	int			x;
	int			y;
	int			color;
}				t_player;

typedef struct s_window 
{
    void *mlx_ptr;
    void *win_ptr;
    t_player player;


    int width;
    int height;
    int row_count;
    int column_count;
    int grid_color;
} t_window;

int draw_grid(t_window *window)
{
    int draw_position;
    int i;

    i = 1;
    while (i < window->row_count)
    {
        draw_position = 0;
        while (draw_position <= window->width)
        {
            mlx_pixel_put(window->mlx_ptr, window->win_ptr, draw_position, \
            i * (window->height / window->row_count), window->grid_color);
            draw_position++;
        }
        i++;
    }
    i = 1;
    while (i < window->column_count)
    {
        draw_position = 0;
        while (draw_position <= window->width)
        {
            mlx_pixel_put(window->mlx_ptr, window->win_ptr, i * (window->width / window->column_count), \
            draw_position, window->grid_color);
            draw_position++;
        }
        i++;
    }
    return (0);
}

void init_player(t_window *window)
{
    mlx_pixel_put(window->mlx_ptr, window->win_ptr, window->player.x, window->player.y, window->player.color);
}

void move_dot_left(t_window *window)
{
    int old_x = window->player.x;
    int old_y = window->player.y;
    int black = 0x000000;
    if ((0 < window->player.x && window->player.x < window->width) && \
        (0 < window->player.y && window->player.x < window->height))
    {
        // draw old spot wiht black first
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, old_x, old_y, black);
        // then draw new spot
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, --window->player.x, window->player.y, window->player.color);
    }
}
void move_dot_right(t_window *window)
{
    int old_x = window->player.x;
    int old_y = window->player.y;
    int black = 0x000000;
    if ((0 < window->player.x && window->player.x < window->width) && \
        (0 < window->player.y && window->player.x < window->height))
    {
        // draw old spot wiht black first
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, old_x, old_y, black);
        // then draw new spot
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, ++window->player.x, window->player.y, window->player.color);
    }
}
void move_dot_up(t_window *window)
{
    int old_x = window->player.x;
    int old_y = window->player.y;
    int black = 0x000000;
    if ((0 < window->player.x && window->player.x < window->width) \
    && (0 < window->player.y && window->player.x < window->height))
    {
        // draw old spot with black first
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, old_x, old_y, black);
        // then draw new psot
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, window->player.x, \
        --window->player.y, window->player.color);
    }
}

int move_dot_down(t_window *window)
{
    int old_x = window->player.x;
    int old_y = window->player.y;
    int black = 0x000000;
    if ((0 < window->player.x && window->player.x < window->width) && \
    (0 < window->player.y && window->player.x < window->height))
    {
        // draw old spot black first
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, old_x, old_y, black);
        // then draw new spot
        mlx_pixel_put(window->mlx_ptr, window->win_ptr, window->player.x, \
        ++window->player.y, window->player.color);
    }
}
int press_key_for_dot(int key, t_window *window)
{
    if (key == KEY_A)
        move_dot_left(window);
    if (key == KEY_D)
        move_dot_right(window);
    if (key == KEY_S)
        move_dot_down(window);
    if (key == KEY_W)
        move_dot_up(window);
}
int main()
{
    t_window window;

    /* window setting starts */
    window.width = 1080;
    window.height = 1080;
    window.row_count = 10;
    window.column_count = 10;
    window.grid_color = 0x00FFFF;
    window.mlx_ptr = mlx_init();
        /* 
            mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
            x * y 크기인 창을 띄움. 제목은 title
        */
    window.win_ptr = mlx_new_window(window.mlx_ptr, window.width, window.height, "choikanghun");
    /* window setting ends */

    /* player setting starts */
    window.player.color = 0xFF0000;
    window.player.x = 220;
    window.player.y = 220;
    /* player setting ends */

        /*
           init_player는 mlx_pixel_put을 호출.
           mlx_pixel_put 은 현재 player 의 위치(x, y)에 마지막 인자인 RGB 색상을 띄는 픽셀을 올린다. 
        */
    init_player(&window);

        /*
            mlx_loop_hook은 두 번째 인자로 커스텀 함수를 받는다.
            draw_grid 함수의 경우 격자를 그려낸다.
        */
    mlx_loop_hook(window.mlx_ptr, draw_grid, &window);    
        /*
            mlx_hook 함수는 두 번째 인자로 keyPress, 세 번재로 keyPressMask를 받는다.
            2는 keyPress, 1은 (1L << 0) 과 같은 것으로 keyPressMask를 의미한다.
            세 번째는 커스텀 함수를 받는다. 
            이 경우의 커스텀 함수는 int를 반환하는 함수로,
            press_key_for_dot은 move_dot_up/down/left/right를 호출한다.
        */
    mlx_hook(window.win_ptr, 2, 1, press_key_for_dot, &window);
    mlx_loop(window.mlx_ptr);
}
