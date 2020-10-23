# include "../minilibx_opengl_20191021/mlx.h"
# include <math.h>

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

int main(int argc, char **argv)
{
    //  x, y의 초기 위치 
    double playerPositionX = 22, playerPositionY = 12;
    // direction Vector 의 초기 방향
    double directionVectorX = -1, directionVectorY = 0;
    /* camera plane의 2d 버전.
        

        --------------------- plane
                |
                | <- direction vector
                |
        --------p--------- camera plane
            (playerPositionX, Y)
        방향벡터와 카메라 평면은 항상 수직 & 같은 길이. plane의 값이 변경되어도.
    
    */
    double cameraPlaneX = 0, cameraPlaneY = 0.66;
    
    // '현재' 프레임의 시간.
    double time = 0;
    // '이전' 프레임의 시간.
    // 현재 프레임의 시간 - 이전 프레임의 시간: 이동거리 결정 및 fps 측정
    double oldTime = 0;

    
    // screen함수는 해상도를 지정해서 화면을 생성.
    // 해상도는 너무 높으면 렌더링이 느려짐.
    screen(screenWidth, screenHeight, 0, "Ray Caseter");
    
    // 화면 생성 후 게임 루프 시작.
    // while문은 전체 프레임을 그려내고 입력을 읽는 역할을 함.
    while (!done())
    {
        /* 
            광선의 시작점은 playerPositionX, Y임.
            directionVectorX, Y는 플레이어의 초기 '방향벡터'.
            planeX와 planeY는 위에서 말했듯 카메라 평면.
            아래 for문은 ray의 위치(position) 및 방향(direction) 계산.
        */
        for (int x = 0; x < w; x++)
        { 
            // cameraX 는 for문의 x값이 카메라 평면 상에 있을 때의 x좌표.
            double cameraX = (2 * x / double(w)) - 1;
            // planeX == 0; planeY == 0.66; dirVecX = -1; dirVecY = 0;
            // 광선의 방향은 방향벡터 + 카메라평면 * 배수.
            double rayDirectionX = directionVectorX + cameraPlaneX * cameraX;
            double rayDirectionY = directionVectorY + cameraPlaneY * cameraX;
            
            /*
                DDAgorithm
            */
            // 현재 player가 위치한 맵 내 위치.(which box of the map)
            int mapX = int(playerPositionX);
            int mapY = int(playerPositionY);

            // 현재 위치에서 다음 x사이드 또는 y사이드까지의 거리.
            // 이를 이하 '첫 번째 x면 및 y면'이라고 부를 것.
            double sideDistX;
            double sideDistY;

            // 아래 두 변수가 왜 저렇게 구해지는지에 대해서는 ii2r github #6 참고. 
            // deltaDistX는 첫 번째 x면에서 그 다음 x면까지의 광선의 이동거리.
            // 이 경우 x는 1만큼 이동.
            double deltaDistX = abs(1 / rayDirectionX);
            // deltaDistY는 첫 번째 y면에서 그 다음 y면까지의 광선의 이동거리.
            // 이 경우 y는 1만큼 이동.
            double deltaDistY = abs(1 / rayDirectionY);
            
            // 광선의 이동거리를 계산할 때 사용할 변수.
            double perpWallDist;

            // DDAgorithm은 반복문을 실행할 때마다 x, y방향으로 딱 한 칸씩 점프.
            // 광선의 방향에 따라 어느 방향으로 건너뛰는지 달라짐.
            // 그 정보는 stepX, Y에 +1, -1 둘 중 하나로 저장됨.
            int stepX;
            int stepY;

            /*
                hit은 벽과 부딪혔는지 판별하기 위한 변수임.
                부딪힌다는 것은 루프를 종료하기 위한 조건이 됨.
                만약 벽에 부딪혔는데 그게 x면에 부딪힌 거라면 side = 0임.
                y면에 부딪혔다면 1이 됨.
                한편 x면, y면은 어떤 칸의 경계가 되는 선을 의미함.
            */
            int hit = 0;
            int side;

            /*
                DDAgorithm을 시작하기 전에 
                stepX, Y 그리고 sideDistX, Y에 값을 넣어주는 부분이다.
                rayDirectionX가 음수라는 말은 player기준 왼각이라는 뜻이고,
                양수라는 말은 player기준 오른각이라는 뜻이다.

                sideDistX의 값은 rayDirectionX 값이 양수인 경우
                광선의 오른쪽으로 이동하다 처음 만나는 x면까지의 거리가 된다.
                sideDistY의 값은 rayDirectionY 값이 양수인 경우
                광선의 위쪽으로 이동하다 처음 만나는 y면까지의 거리가 된다.

                rayDirectionX가 양수일 경우 sideDistX는 
                mapX + 1에서 실제 위치 playerPositionX를 빼주고 deltaDistX를 곱한 결과다.
                반대의 경우 playerPositionX에서 mapX를 빼주고 deltaDistX를 곱한 결과다.
            */
            if (rayDirectionX < 0)
            {
                stepX = -1;
                sideDistX = (playerPositionX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - playerPositionX) * deltaDistX;
            }
            if (rayDirerctionY < 0)
            {
                stepY = -1;
                sideDistY = (playerPositionY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - playerPositionY) * deltaDistY;
            }

            /*
                DDAgorithm 세팅을 완료했고, 이제 그것을 시작하는 부분.
                아래 while문은 벽에 부딪힐 때까지 매번 한 칸씩 광선 이동.
                반복할 때마다 x방향으로 한 칸 또는 y방향으로 한 칸 점프.
                만약 광선의 방향이 x축 방향과 완전히 일치한다면, x방향으로만 한 칸 점프하면 됨.
                광선이 점프할 때마다 sideDistX, Y는 deltaDistX, Y가 더해지면서 업데이트됨.
            */
            while (hit == 0)
            {
                // 다음 map 박스로 이동하거나 x, y 방향 둘 중 하나로 이동한다.
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                // ray가 벽을 만났는지 확인하는 작업
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }

            /*
                벽을 만나 DDAgorithm이 완료됨.
                이제 광선의 시작점에서 벽까지의 이동거리를 계산할 차례임.
                
            */
        }
    }
}

/*
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
*/

// int main()
// {
//     t_window window;

//     /* window setting starts */
//     window.width = 1080;
//     window.height = 1080;
//     window.row_count = 10;
//     window.column_count = 10;
//     window.grid_color = 0x00FFFF;
//     window.mlx_ptr = mlx_init();
//         /* 
//             mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
//             x * y 크기인 창을 띄움. 제목은 title
//         */
//     window.win_ptr = mlx_new_window(window.mlx_ptr, window.width, window.height, "choikanghun");
//     /* window setting ends */

//     /* player setting starts */
//     window.player.color = 0xFF0000;
//     window.player.x = 220;
//     window.player.y = 220;
//     /* player setting ends */

//         /*
//            init_player는 mlx_pixel_put을 호출.
//            mlx_pixel_put 은 현재 player 의 위치(x, y)에 마지막 인자인 RGB 색상을 띄는 픽셀을 올린다. 
//         */
//     init_player(&window);

//         /*
//             mlx_loop_hook은 두 번째 인자로 커스텀 함수를 받는다.
//             draw_grid 함수의 경우 격자를 그려낸다.
//         */
//     mlx_loop_hook(window.mlx_ptr, draw_grid, &window);    
//         /*
//             mlx_hook 함수는 두 번째 인자로 keyPress, 세 번재로 keyPressMask를 받는다.
//             2는 keyPress, 1은 (1L << 0) 과 같은 것으로 keyPressMask를 의미한다.
//             세 번째는 커스텀 함수를 받는다. 
//             이 경우의 커스텀 함수는 int를 반환하는 함수로,
//             press_key_for_dot은 move_dot_up/down/left/right를 호출한다.
//         */
//     mlx_hook(window.win_ptr, 2, 1, press_key_for_dot, &window);
//     mlx_loop(window.mlx_ptr);
// }

