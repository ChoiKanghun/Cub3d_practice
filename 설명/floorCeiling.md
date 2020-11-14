# 설명에 앞서





<br>



해당 코드들은 [Lodev.com](http://lodev.com/) 의 'Lode's Computer Graphics Tutorial--Raycasting'의 코드를 42 스타일에 맞게 옮긴 것이며, 

코드 전체는 yohlee님의 [코드](https://github.com/l-yohai/cub3d/blob/master/mlx_example/01_untextured_raycast.c) 를, 

Lodev 사이트 해석은 mihykim님의 [해석](https://github.com/365kim/raycasting_tutorial/blob/master/1_what_is_raycasting.md)을, 

수학적 지식 이해는:

minckim님의 [레포](https://github.com/minckim0/cub3d_lect) 내 pdf 파일 그리고 

[Ii2r 전문](https://github.com/sungyongcho/ii2r)을 참고하였다.

(다섯 분 모두 감사드립니다.)



<br>



현재 여러분은 갈림길에 서 있다. 

mandatory 파트가 아닌 천장, 바닥에 texture를 줄 것인가, 

아니면 그냥 색깔 하나를 칠해버릴 것인가. 



<br>



필자는 lodev의 글로부터 천장과 바닥을 칠하는 코드가 직관적으로 무슨 코드인지 이해해보려다가, 

머리가 아파서 색깔 칠하는 것으로 변경했다. 

그래서 당연히 아래코드는 바닥과 천장에 색을 칠하는 코드이다.

이번에는 변경 사항이 calculateAndSaveToMap 밑에 이중 for문 하나 뿐이다. 

원리는 화면 가운데를 기점으로 아래위로 서로 다른 색을 버퍼에 넣어둔 뒤, 나머지를 버퍼에 덮어 씌워서 천장과 바닥을 나타내는 것이다.



<br>

# 코드



<br>



```c

int calculateAndSaveToMap(t_info *info)
{
    /* 
        나중에 화면에 올릴 buf의 위에서부터 아래로, 아래서부터 위로 다른 색상을 칠해준다.
        이렇게하면 가운데에서 다시 buf에 서로 다른 색상을 담는 비효율이 있지만,
        속도면에서 크게 장애가 되지 않는니 그냥 써주려고 한다.
    */
    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            info->buf[y][x] = 0xFFFFFF; 
            info->buf[screenHeight - y - 1][x] = 0x000000;
            // buf[screenHeight - 1 ~ screenHeight - screenHeight][x] 를 칠해줌.
        }
    }
  ...
}
```



<br>



# 코드 실행



해당 코드를 돌려보면,

(gcc -L./ -lmlx -framework OpenGL -framework Appkit main.c)



<br>



![asdfadsfa](https://github.com/ChoiKanghun/images/blob/master/1025_5.png?raw=true)



<br>



이제 화면이 깨지지 않는다.





<br>



