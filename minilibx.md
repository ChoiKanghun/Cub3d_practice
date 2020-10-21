[miniLibX 라이브러리 어떻게 ](http://harm-smits.github.io/42docs/)



[harm-smits.github.io/42docs/](http://harm-smits.github.io/42docs/)

의 번역본입니다.



<br>

# Introduction



<br>



## 인트로

miniLibX는 쬐끄만 그래픽 라이브러리로서, cocoa나 x-window에 대한 지식 없이도 스크린에 기본적인 무언가를 렌더링할 수 있게 도와준다. 해당 라이브러리는 다음을 제공한다: window(창) creation, 드로잉(drawing) 툴, 이상하고 좀 부족한 이미지 기능과 이벤트 관리 시스템.



<br>



## X-WINDOW란

 X-window는 unix를 위한 네트워크 지향적인(network-oriented) 그래픽 시스템이다. 원격 데스크톱에 연결하는 데에 쓰이는 것을 하나의 예로 생각할 수 있겠다. TeamViewer가 이것을 사용하는 가장 일반적인 프로그램이다.



<br>



## MacOS란

MacOS는 화면에 대한 그래픽적인 접근(graphical access)을 관리한다. 그런데 여기에 접근하기 위해서는 우리의 application을 깔려있는(underlying) graphical 프레임워크에 등록해야한다. 



<br>



# Colors

컬러는 int 형식으로 표현된다. 그래서 ARGB 값을 담을 수 있는 int를 얻기 위해 요상한(tricky) 것들을 요구하기도 한다.





<br>



## The Color Integer Standard

우리는 TRGB format을 사용하기 위해 비트를 전환(shift)한다. 특히 색을 전환하기 위해 다음과 같이 초기화를 시도하기도 한다: `0xTTRRGGBB`. 방금의 코드는 다음을 의미한다. 



- T: 투명도
- R: Red
- G: Green
- B: Blue



<br>



RGB의 원값은 다음과 같다:



<br>



- Red: `0x00FF0000`
- Green: `0x0000FF00`
- Blue: `0x00000FF`



<br>



## 컬러 인코딩, 디코딩 하기



바이트는 2의 8승(256) 값을 가진다. 그리고 rgb 값의 범위 또한 0~255이다. 그래서 우리는 int를 완벽하게 rgba 에 갖다 꽂을 수 있다. Programmatically 하게 값들을 설정하기 위해서 우리는 `bitshifting` 이라는 개념을 활용한다. 한번 예제코드를 짜보자.



<br>



(여기서 잠깐! 아래 코드를 이해하기 위해 c언어의 `|` 그리고 `&` 가 무엇을 의미하는지 알아보자.

`|`, `&` 는 모두 비트 연산자로, 예를 들어 다음과 같은 코드가 있다고 하자.

```c
#include <stdio.h>

int main() {
  unsigned char num1 = 1; // 0000 0001
  unsigned char num2 = 3; // 0000 0011
  
  printf("%d\n", num1 & num2); // bit AND
  printf("%d\n", num1 | num2); // bit OR
}
```



<br>



여기서 num1 & num2 는 0000 0001을 의미한다.

`&` 는 비트 and 를 의미하는데, 0000 0001 과 0000 0011 둘 중에서 겹치는 자리만 남겨둔다. 

그 반대는 `|` 이다. 0000 0001 과 0000 0011 둘 중에서 하나라도 겹치는 자리가 있으면 남긴다.

이에 따라 num1 | num2 는 0000 0011이 된다.

즉, 출력값은 다음과 같이 되는 것이다. 

https://dojang.io/mod/page/view.php?id=1638 참고.



<br>



```c++
1
3
```



<br>



```c
int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
// << 이 부분이 bit 이동하는 부분임.
// | 8 | 8 | 8 | 8 | 
// 32  24  16  8       이런 구조가 있다고 생각하면
// t는 맨 앞 칸에, r은 두 번째 칸에, ...  이렇게 담김 - kchoi
}
```



<br>



int는 오른쪽에서 왼쪽으로 저장되기 때문에, bitshift해야 할 필요가 있다. 그리고 encoded TRGB int로부터 정확히 반대의 것을 할 수 있다.



<br>



```c
int get_t(int trgb)
{
  return (trgb & (0xFF << 24));
}

int get_r(int trgb)
{
  return (trgb & (0xFF << 16));
}

int get_g(int trgb)
{
  return (trgb & (0xFF << 8));
}

int get_b(int trgb)
{
  return (trgb & 0xFF);
}
```



<br>



## 얼마나 이해했는지 테스트해보자.



이제 당신은 컬러가 어떻게 초기화될 수 있다. get comfy 하시고 다음 color 조작 함수를 만들어보라:

* `add_shade` 는 double(거리) 과 int(컬러) 를 인자로 받는 함수이다. 0은 아무런 그림자도 컬러에 넣지 않지만 1은 색깔을 완전히 검은색으로 만들 것이다. 0.5는 반쯤 희미할 거고 .25는 쿼터(quarter)이다. 이 정도면 이해했으리라.
* `get_opposite` 은 int(컬러) 를 인자로 받는다. 그리고 인자로 받은 색깔을 반전(invert)시킬 것이다.



<br>



# 본격적으로 시작하기

# Getting Started





<br>



## Intro

이제 당신은 MiniLibX가 무엇을 할 수 있는지 알 것이다. 우리는 매우 기본적인 것으로 출발할 것이다. 이것만 하면 라이브러리를 가지고 제대로 동작하는 코드를 작성할 수 있을 것이다. 아래 전체를 전부 이해할 수 있도록 하자. 매우 중요하다.



<br>



## MacOS 에서 컴파일하기



MiniLibX는 Appkit과 X11을 요구하기 때문에 그들을 적절히 연결할 필요가 있다. 그런데 이것을 해내려면 조금 복잡한 과정을 거쳐야 한다. 기본적인 컴파일 과정은 이렇다:



<br>



오브젝트 파일에 다음의 규칙을 추가할 수 있다. 프로젝트의 root에 `mlx directory` 안에 `mlx source` 가 있다고 가정하고:

```c
$.o: $.c
  $(CC) -Wall -Werror -Wextra -Imlx -c $< -o $@
```



<br>



요구사항인 MacOS 내부의 API와의 연결을 위해:

```c
$(NAME): $(OBJ)
  $(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
```



<br>



같은 디렉토리 내에  `libmlx.dylib` 가 build target으로 돼 있어야 한다는 것을 잊지 말라. 왜냐하면 이것은 동적인(dynamic) 라이브러리이기 때문이다.



<br>



## 초기화하기(Init)

 

MiniLibX 라이브러리를 가지고 무언가를 하기 전에, 일단 `<mlx.h>` 헤더를 먼저 포함시켜야한다. 그래야 모든 함수에 접근할 수 있고 `mlx_init` 함수는 필수적으로 실행시켜야 하기 때문이다. 해당 init 함수는 그래픽 시스템에 connection을 만들고 `void *` 를 리턴한다. 이 `void *` 은 현재 MLX 인스턴스의 위치를 holds(가진다? 멈춰놓는다?) 한다. MiniLibX를 init 하기 위해서 이것부터 하자:



<br>



```c
#include <mlx.h>

int main(void)
{
  void *mlx;
  
  mlx = mlx_init();
}
```



<br>



----



comment by kchoi:

지금 여기서 뭘 해야 하는지 모르겠다면!

git repo를 받아놓고 거기에 minilibx 압축푼 폴더를 넣고, 해당 폴더 안에 main.c를 만들어서 

Make 한번 해주시고(오류 신경쓰지말고) 

위 블록 코드를 main.c에 입력하고 

`gcc -L[miniLibX가 있는 상대 경로] -lmlx -framework OpenGL -framework Appkit main.c` 



---



<br>



코드를 돌려보면, 아무것도 pop up 되지 않고 아무것도 render 되지 않는다. 이것은 당신이 window를 create 하지 않았기 때문이다. 이제 창을 띄워보자. 화면을 닫는 건 `ctrl + c` 로 할 수 있다. 창을 열기 위해서 `mlx_new_window` 함수를 불러오자. 이 함수는 우리가 방금 만든 창(window)을 가리키는 포인터를 리턴한다. 창에 높이와 너비 그리고 제목을 줄 수도 있다. 그리고 `mlx_loop` 를 불러야(call) 창을 렌더링시킬 수 있다. 한번 너비 * 높이가 1920 * 1080인 "Hello world!" 제목의 창을 띄워보자. 



<br>

```c
#include <mlx.h>

int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    mlx_loop(mlx);
}      
```

(gcc -L./ -lmlx -framework OpenGL -framework Appkit main.c // ./a.out)



<br>



## image에 pixel을 그려보자.

우리는 이제 기본적인 창 관리(window management) 능력을 갖추게 됐다. 이제 픽셀을 윈도우에 올려보자. 어떻게 이 픽셀들을 올릴지는 당신에게 달려있다. 그러나 올리는 방법에 대한 최적의 방법에 대해서는 다룰 필요가 있다. 첫째, `mlx_pixel_put` 함수가 아주 아주 느리다는 점을 고려해 볼 (take into account) 필요가 있다. 왜냐하면 이것이 pixel을 윈도우에 올릴 때 frame이 완전히 렌더 되기도 전에 즉시 올리기 때문이다. 단지 이 이유 하나만으로, 모든 픽셀을 버퍼에 담은 뒤에 window에 올릴 것이다. 모든 것이 복잡해보이겠지만, 너무 겁먹지 말자.



<br>



먼저 위는 `mlx` 가 요구하는 이미지의 타입이 무엇인지 이해하는 것으로부터 출발해야 한다. 만약에 우리가 이미지를 initiate하면 우리는 핵심 변수들을 그려줄 곳에 포인터를 전달해야 한다(we will have to pass a few pointers to which it will write a few important variables). 첫 번째는 `bpp` 인데, 이는 `bits per pixel` 의 줄임말이다. pixel은 기본적으로 `int` 형이기 때문에, 4바이트이다. 그러나 이것은 우리가 작은(small) [엔디안(endian)](https://genesis8.tistory.com/37) 을 다룬다면 달라질 수 있다. (즉 우리가 원격 화면에 있고 8 bit 컬러만 가지고 있다는 것이다: which means we most likely are on a remote display and only have 8 bit colors.)



<br>



이제 1920 * 1080 이미지를 다음과 같이 선언하여 초기화(init)시켜보자.



```c
#include <mlx.h>

int     main(void)
{
    void    *img;
    void    *mlx;

    mlx = mlx_init();
    img = mlx_new_image(mlx, 1920, 1080);
}
```

(아직까지는 화면에 안 뜰 것이다. mlx_loop를 코드에 넣어줘야 화면에 뭔가 뜬다. mlx_loop가 나오기 전인 지금 현재 그냥 뭐가 떴다 사라지는 건 정상이니 안심하고 넘어가자 - kchoi)



<br>



어렵지 않았을 것이다. 우리는 이제 이미지를 가지고 있지만 여기에 픽셀을 어떻게 그릴 수 있는 것일까? 이것을 위해선 우리가 메모리 주소를 가지고 올(get) 필요가 있다. 그리고 그 메모리 주소에 byte를 형성(내지는 그려낼: mutate) 할 것이다. 우리는 다음을 통해 이 주소를 얻을 수 있다:



<br>



```c
#include <mlx.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int     main(void)
{
    void    *mlx;
    t_data  img;

    mlx = mlx_init();
    img.img = mlx_new_image(mlx, 1920, 1080);

    /*
    ** After creating an image, we can call `mlx_get_data_addr`, we pass
    ** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
    ** then be set accordingly for the *current* data address.
    ** image를 만들었다면, 우리는 `mlx_get_data_addr`을 불러올 수 있다.
    ** `bits_per_pixel`, `line_length`, `endian`의 주소를 보낸다. 
    ** 그러고 나서 보내진 주소는 *현재 데이터 주소*를 위해 적절히 set 될 것이다. 
    */
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
}
```



<br>



우리가 어떻게 `bits_per_pixel`, `line_length`, `endian` 변수의 주소를 넘기는지 확인했나? 이것들은 위에서 설명했듯이 MiniLibX에 의해 적절히 set 될 것이다.(위 코드 내 주석을 말하는 듯)



<br>



이미지 주소는 있지만 아직 pixel이 없다. 우리가 이를 위한 작업을 시작하기 전에 bytes가 정렬되어 있지 않음을 이해해야 한다. 즉 `line_length`가 실제 창(window) 너비와 다를 수 있다는 것이다. 

그래서 우리는 `언제나` `mlx_get_data_addr` 을 통해 set된 line length를 가지고 메모리 주소 출발점(offset) 을 계산해야 한다.  



<br>



우리는 다음 공식을 통해 그것을 쉽게 구해낼 수 있다.

`int offset = (y * line_length + x * (bits_per_pixel / 8));` 



<br>



이제 어디에 그려야 할 지 알아냈으므로 `mlx_pixel_put` 함수를 흉내내면서도 더 빨리 동작하는 함수를 작성하는 것은 한결 쉬워졌다:

```c
typedef struct s_data {
  void	*img;
  char	*addr;
  int		bits_per_pixel;
  int		line_length;
  int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;
  
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  // 괄호 == offset
	*(unsigned int *)dst = color;
}
```



<br>



위 코드는 issue를 만든다.(<del>대충 인성</del> 문제 있다는 뜻) 

이미지는 실시간으로 윈도우에 represent 되기 때문에 동일한 이미지를 변경하는 것은 화면을 찢는듯한(screen-tearing) 현상을 나타낼 것이다. 그래서 당신은 프레임을 hold 해두기 위해 2개 또는 그 이상의 이미지를 만들어야 한다. 그런 다음에야 temporary한 이미지를 그려낼 수 있고, 그래야 현재 표시된 이미지를 (다시) 그리지 않아도 된다. 



<br>



## 이미지를 윈도우에 올리기(push)

이제 드디어 우리는 이미지를 만들었다. 이제 창에 올릴 차례다. 그래야 보일 테니까. (5, 5) 자리에 빨간색 픽셀 하나를 그려보자:



<br>



```c
#include <mlx.h>

typedef struct s_data {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_data;

int main(void)
{
  void *mlx;
  void *mlx_win;
  t_data img;
  
  mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello 42 Seoul");
  img.img = mlx_new_image(mlx, 1920, 1080);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
  mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
  mlx_loop(mlx);
}
```

0x00FF0000은 ARGB(0, 255, 0, 0)의 16진수값이다.

(위의 위 코드에서 my_mlx~ 함수도 넣어줘야 함)



<br>



---



comment by kchoi

![img34141](https://github.com/ChoiKanghun/images/blob/master/1021_1.png?raw=true)

생성된 a.out 파일을 실행하면 위와 같이 아주 tiny한 빨간색 픽셀이 찍혀 있을 것이다.



---



<br>



## 배운 것 다지기

이제 기본은 배웠으니 라이브러리와 친해지고 재밌는 것들을 해볼 차례다.

다음을 해보는 건 어떨까:



* 네모 동그라미 세모 오각형을 그려보라.
* gradient 추가, 무지개 그리기를 통해 rgb 컬러에 익숙해져보자.
* 이미지를 loop 하여 질감을 표현해보라.



<br>



# HOOKS

(리액트 훅 아님)



<br>



Hooking은 다양한 용도로 쓰인다. 디버깅이나 함수의 기능을 연장(extending)할 때와 같이. 키보드를 intercept 하거나 마우스 이벤트를 발생시키는 것, 그리고 모니터 활동을 모니터링하고 다른 애플리케이션 또는 컴포넌트의 기능을 변경하기 위해 os call을 intercept하는 것이 그 예이다. 벤치마킹 프로그램에도 많이 쓰이며, 그 예로는 hooking을 통해 output과 input을 완료하여 3D게임에서 frame rate measuring 에 쓰이는 것이 있다. (<del>뭔소리야</del>)

간단히 말해, hooking이 MiniLibX를 구성하는 뼈대라는 뜻이다. 



<br>



## key 이벤트로의 Hooking

(Hooking into key events)



<br>



Hooking이 어려운 단어처럼 들리겠지만 실제론 그렇지 않다. 한번  살펴보자.

```c
#include <mlx.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_key_hook(vars.win, close, &vars);
    mlx_loop(vars.mlx);
} 
```

(해당 코드를 실행하면 오류는 뜨지만 실행되고, 아무 키나 입력하면 다시 창이 없어진다.)



<br>



이제 우리는 아무키나 누르면 창이 꺼지는 기능을 구현했다. `mlx_key_hook` 을 통해 hook 함수를 등록했는데, 그 뒤에서(in the backgrounds) 해당 함수는 단순히 `mlx_hook` 함수를 불러낼 뿐이다. 이것에 대해서는 다음 챕터에서 자세히 알아보도록 하자. 



<br>



## 배운 것 다지기

혼자서 다음 것들을 해보자.

훅 핸들러(hook handlers)를 만들어라. 언제나: 

* 키가 눌려지면 해당 키 코드를 터미널에 출력하는

* 마우스가 움직이면 해당 마우스 포인터가 터미널에서 어느 위치에 있는지 출력하는

* a mouse is pressed, it will print the angle at which it moved over the window to the terminal.

  (무슨 뜻일까요 세 번째는?)



<br>



# Events 이벤트



<br>



## Intro

이벤트는 MiniLibX 안에서 interactive한 애프리케이션을 작성하는 foundation(기초, 초석, 뼈대 정도)이다. 그래서 이번 챕터를 완전히 이해하는 건 앞으로의 그래픽(graphical) 프로젝트에 있어 매우 중요하다. 



<br>



MiniLibX 의 모든 hooks는 이벤트가 일어날 때마다 call 되는 함수 그 이상도 그 이하도 아니다.  이 모든 이벤트를 모두 마스터 하는 것은 필수가 아니더라도, 빠르게 X11 이벤트를 훑어볼 필요는 있다.



<br>



## X11 Events



X11은 MiniLibX와 함께 사용되는 라이브러리이다. 따라서 이 header는 MiniLibX의 모든 이벤트를 찾는 데에 매우 유용하다. 여기엔 여러 종류가 있다:

- `02`: KeyPress
- `03`: KeyRelease
- `04`: ButtonPress
- `05`: ButtonRelease
- `06`: MotionNotify
- `07`: EnterNotify
- `08`: LeaveNotify
- `09`: FocusIn
- `10`: FocusOut
- `11`: KeymapNotify
- `12`: Expose
- `13`: GraphicsExpose
- `14`: NoExpose
- `15`: VisibilityNotify
- `16`: CreateNotify
- `17`: DestroyNotify
- `18`: UnmapNotify
- `19`: MapNotify
- `20`: MapRequest
- `21`: ReparentNotify
- `22`: ConfigureNotify
- `23`: ConfigureRequest
- `24`: GravityNotify
- `25`: ResizeRequest
- `26`: CirculateNotify
- `27`: CirculateRequest
- `28`: PropertyNotify
- `29`: SelectionClear
- `30`: SelectionRequest
- `31`: SelectionNotify
- `32`: ColormapNotify
- `33`: ClientMessage
- `34`: MappingNotify
- `35`: GenericEvent
- `36`: LASTEvent



<br>



만약 위 이벤트 중에서 무엇을 하는 함수인지 알 수 없는 것들이 있어도 걱정하지 말자. 왜냐하면 그것을 필요로 하는 일이 거의 없을 테니까. 만약 그런 일이 있다면 X11 function에 대한 문서를 읽어보도록 하자.



<br>



## X11 masks

X11 이벤트 각각은 mask도 가진다. 이것이 발동(trigger)될 때 한 가지 키만 등록할 수도 있고 모든 키를 등록할 수도 있다. 키 마스크는 여러분의 이벤트 목록으로부터 whitelist와 blacklist를 나눌 수 있도록 허용한다. 마스크의 종류로는 다음이 있다:

(이게 무슨 말인지는 예제 코드를 살펴보자 이번 챕터 아래 쯤에.) 



<br>



- NoEventMask `0L`
- KeyPressMask `(1L<<0)`
- KeyReleaseMask `(1L<<1)`
- ButtonPressMask `(1L<<2)`
- ButtonReleaseMask `(1L<<3)`
- EnterWindowMask `(1L<<4)`
- LeaveWindowMask `(1L<<5)`
- PointerMotionMask `(1L<<6)`
- PointerMotionHintMask `(1L<<7)`
- Button1MotionMask `(1L<<8)`
- Button2MotionMask `(1L<<9)`
- Button3MotionMask `(1L<<10)`
- Button4MotionMask `(1L<<11)`
- Button5MotionMask `(1L<<12)`
- ButtonMotionMask `(1L<<13)`
- KeymapStateMask `(1L<<14)`
- ExposureMask `(1L<<15)`
- VisibilityChangeMask `(1L<<16)`
- StructureNotifyMask `(1L<<17)`
- ResizeRedirectMask `(1L<<18)`
- SubstructureNotifyMask `(1L<<19)`
- SubstructureRedirectMask `(1L<<20)`
- FocusChangeMask `(1L<<21)`
- PropertyChangeMask `(1L<<22)`
- ColormapChangeMask `(1L<<23)`
- OwnerGrabButtonMask `(1L<<24)`



<br>



## Hooking into events

(이벤트로의 Hooking)



<br>



Hooking into events는 MiniLibX가 제공하는 가장 강력한 기능 중 하나다. 간단한 hook 등록 함수를 가지고 앞서 말한 이벤트 중 어떤 것이든 쉽게 등록할 수 있게 해준다. 예를 들어 `mlx_key_hook` 을 호출하는 것보다, `KeyPress` 나 `KeyRelease` 이벤트를 등록할 수 있는 것이다.



<br>



이를 위해, 우리는 `mlx_hook` 함수를 호출해야 한다. 한번 살펴보자:

```c
#include <mlx.h>

typedef struct  s_vars {
        void    *mlx;
        void    *win;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
}

int             main(void)
{
    t_vars    vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
  /* mlx_hook의 두 번째 인자가 x11 event(keyPress) 이고
     mlx_hook의 세 번째 인자가 x11 masks(KeyPressMask) 이다.
     - kchoi
   */
    mlx_loop(vars.mlx);
} 
```



<br>



여기서 우리는 `keyPress` 이벤트와 그에 따른 `keyPressMask` 를 등록했다. 이제 우리가 key를 입력할 때마다 window는 닫힐 것이다. 



<br>



## 배운 것 다지기

이제 당신은 이것이 어떤 원리로 동작하는지에 대해 희미하게 알아차렸을 것이다. hook handler를 만들어보는 건 어떨까?:

* `ESC` key가 눌리면 화면이 닫힘
* window 사이즈가 변경되면 터미널에 무언가를 출력
* 닫기 모양 버튼(red cross)이 클릭되면 윈도우가 닫힌다.
* 키를 x초 이상 누르고 있으면 터미널에 무언가가 출력
* 윈도우에 마우스가 들어오는 순간 터미널에 `Hello!` 가 출력되고, 윈도우 밖으로 나가는 순간 `Bye!` 가 출력



<br>



# Loops



<br>



## Intro

이제 당신은 드디어 MiniLibX 라이브러리의 기본을 모두 배웠다. 이제 윈도우에 작은 animation을 그려볼 차례다. 이를 위해 `mlx_loop`와 `mlx_loop_hook` 이라는 함수를 사용해볼 것이다. 



<br>



Loops는 MiniLibX의 기능으로, `mlx_loop_hook`에 등록해놓은 hook을 계속해서 call하여 새로운 frame에 render할 것이다. 



<br>



## Hooking into loops

loop를 초기화하기 위해서는 `mlx_loop`를 호출해야 한다. 인자는 오직 `mlx` 하나다.



<br>



예시:

```c
#include <mlx.h>

int main()
{
  void *mlx;
  
  mlx = mlx_init();
  mlx_loop(mlx);
}
```



<br>



위 코드는 당연히 아무것도 안 하고 창만 띄워 놓을 것이다. 우리는 아무 hook도 등록하지 않았기 때문이다. 

frame(여기서의 frame은 window 안의 검은 화면을 말하는 듯.)에 뭔가를 표현하고 싶다면 [Getting Started](#getting-started) 챕터에서 설명했듯이 window를 만들고 mutation(<->constant, 상수)을 사용해야 한다. 여기에 대해 적절히 인자를 넘길 줄 알고 있으리라. whiteboarded 버전의 예시는 다음과 같다:



<br>



```c
#include <mlx.h>

int     render_next_frame(void *YourStruct);

int     main(void)
{
    void    *mlx;

    mlx = mlx_init();
    mlx_loop_hook(mlx, render_next_frame, YourStruct);
    mlx_loop(mlx);
}
```

(나도 여기서 뭘 해야하는지 몰라서 그냥 아~ 내가 custom func를 render_next_frame이라는 이름으로 만들고 custom struct를 YourStruct와 같이 만들면 되는구나 하고 넘어갔다.-kchoi)



<br>



이제 각각의 프레임은 `YourStruct` 라는 인자를 받는 `render_next_frame` 함수를 호출할 것이다. 만약 그것이 포인터라면 여러번의 호출을 지속할 것이다. 이것을 장점으로 잘 살려보자.



<br>



## 학습 다지기

이제 당신만의 렌더링 함수를 등록할 수 있게 됐다. 다음을 해보자:

* 스크린 색깔이 빨강, 주황, 초록 등으로 바뀌는 moving 무지개를 렌더링해보자.
* wasd 키로 움직이는 원을 그려보라 .



<br>



# Images

## Intro

이미지는 miniLibX에서 가장 중요한 개념이다. 이에 관련된 함수들은 파일을 읽고 image object에 직접 접근할 수 있도록 해줄 것이다. 이것은 질감이다 sprite에 매우 유용하다.



<br>



# image 읽기

파일이나 이미지 객체를 읽기 위해서는, XMP나 PNG 파일이 필요하다. 읽기 위해서 `mlx_xpm_file_to_image` 그리고 `mlx_png_file_to_image` 를 호출할 수 있다. `mlx_png_file_to_image`는 현재 메모리 누수를 발생시킨다는 점은 알아두자. 두 개의 함수는 동일한 인자를 받고 그들의 사용용도 또한 같다.



<br>



image를 읽어볼까?:

```c
#include <mlx.h>

int     main(void)
{
    void    *mlx;
    void    *img;
    char    *relative_path = "./test.xpm";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}
```

(뭔가 동작하는 것 같기는 한데 화면에 표시하는 코드가 없다면 원하는 이미지가 나왔는지는 아직 모른다.)



<br>



`img`가 `NULL` 이라면 이미지 읽기가 실패한다. 그리고 이 함수는 알아서 `img_width`, `img_height`를 세팅해주기 때문에 sprite에는 이상적이다.



<br>



## 학습 다지기

파일로부터 어떻게 읽는지를 알아냈을 것이다. 좀더 graphical 한 것들을 만들어보자. 다음 프로그램을 만들어보라:

* import a cursor of your choice and allow it to roam within the window freely

  (당신이 선택한 커서?를 import하여 윈도우 안에서 자유롭게 돌아다니도록 만들어보라.)

* texture(질감)을 import 하고 당신의 윈도우에 복제하라. 



<br>



# Sync (동기화)



<br>



## Sync란 무엇인가?

전에 말했듯이 MLX를 가지고 당신 자신만의 frame buffering을 관리할 수 있다. 그런데 이것은 매우 싫증나는 일이고 시간도 많이 잡아먹는다. 게다가 더 많은 메모리를 요구하고 framedl 지속적으로 update돼야 한다는 문제가 있다. 이것은 효율적이지 못하기 때문에 이것을 최대한 피할 필요가 있다.



<br>



2020 mlx 버전부터는, 당신만의 frame을 동기화(synchronize) 할 수 있다. 이는 스크린 버퍼링이 더이상 요구되지 않게 만들어주는, `hacky한 여러 이미지들`을 만든다.

 

<br>



## Sync 사용하기

우리는 세 가지 define을 이해하는 것으로부터 출발해야 한다:

```c
#define MLX_SYNC_IMAGE_WRITABLE    1 
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

int	mlx_sync(int cmd, void *ptr);
```



<br>



Mlx Sync는 define(정의)된 명령 코드와 함께 호출되어야'만' 한다. `MLX_SYNC_IMAGE_WRITABLE` 는 후속적인(subsequential) 호출을 하나의 이미지에 buffer한다(`ptr`은 mlx image object를 가리키는 포인터이다.) 만약 당신이 변화를 전파하고 싶다면,(If you want to propagate changes,) 당신은 이미지가 나타난 화면을 flush해야 한다. 그리고 그것은 `MLX_SYNC_WIN_FLUSH_CMD`로 할 수 있으며 이 때 flush하기 원하는 window가 `ptr` 이 된다. 



<br>



## 학습 다지기

MLX sync가 무엇을 하는 지 이해했다면 전에 loop 파트에서 만들었던 circle-game에 MLX sync를 추가해보아라.



<br>



# 에필로그

이제 당신은 모든 튜토리얼을 끝마쳤다. 이제 당신은 MiniLibX true master라고 말하고 다닐 수 있을 것이다. 우리는 당신이 각각의 function이 어떤 역할을 하는지, 그리고 프로토타입은 무엇인지 빠르게 훑어볼 수 있도록 따로 [문서](https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html)를 준비해뒀다. 



<br>



빠진 게 있다고 느낀다면 언제든지 연락하라. 최대한 빨리 체크하겠다. 



<br>



당신의 모든 과제에 행운이 따르길!



<br>



---



kchoi's comment -

개인적인 소감.

이걸 다 읽었다고 해서 내가 뭘 할 수 있는 능력이 생긴 것 같지는 않다. 처음 한 번 읽어보고 `Test Your Skills(학습 다지기)` 부분을 안 해서 그런 것이라고 생각한다. 아무튼 본과정을 시작하고 한 달 정도 되었을 때 linux 환경에서  miniLibX를 어떻게 깔고 이게 당최 뭔지 헷갈려서 포기했던 때를 떠올려 보면 이러한 문서를 작성한 사람에게 굉장히 고마워진다. 



<br>



이제는 다음 과제로 넘어갈 차례이다. 

당신은 miniRT, cub3D 둘 중 어떤 것을 선택했는가?

듣기로 miniRT는 수학에 대한 이해를 많이 필요로 하지만 parsing에 대해서는 그렇게 어려움이 없다고 한다. 

반면에 cub3D는 수학에 대한 이해가 조금 덜 하지만 parsing에 대해 스트레스를 받는다고 한다. 

각자 무엇을 할지 정했다면 어서, 다음 단계로 넘어가자.



<br>



cub3D 과제 해석: [링크](https://42kchoi.tistory.com/19?category=886844)



<br>



miniRT를 잘 정리해놓은 사람들: 

* 킹갓여름님(intra: yeosong): [링크](https://yeosong1.github.io/miniRT%EA%B5%AC%ED%98%84%EA%B3%BC%EC%A0%95)
* 대천사상헌님(intra: sayi): [링크](https://velog.io/@sayi/series/miniRT)



<br>



Cub3D를 잘 정리해놓은 사람들: 

* 제너럴캡틴성용님(intra: sucho): [ii2r링크](https://github.com/sungyongcho/ii2r)

  



<br>



p.s. 잘 정리한 사이트들 언제든지 알려주세요! 추가하고 싶은데 아는 사이트가 별로 없네요 ㅠ!