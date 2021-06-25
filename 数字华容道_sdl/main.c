#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics.h"
#include "capp.h"
#include "base.h"

/*
  使用SDL实现手机CAPP的绘图函数
  风的影子
*/

int RINTERVALS = 1000;


Uint32 timerRun(Uint32 interval, void *A1)
{
    printf("this is timer\n");
    return RINTERVALS;
}

void drawpoly(SDL_Renderer *renderer, float x, float y, int n, float r)
{
    float i; //计步循环体(从左至右绘图)
    float
        t = tan((180 - 360 / (float)n) / 2 / 180 * 3.14);
    float rx = r, b = 0, ta, tb, tc;
    //主要实现:t为一半的顶角的正切,
    //rx为变化半径
    //b与i同步以计算rx
    int times = 0; //控制变化周期次数

    tc =
        cos((180 - 360 / (float)n) / 2 / 180 * 3.14) * r * 2 * cos((180 - 360 / (float)n) / 2 / 180 * 3.14);
    tb = tc;
    ta = r;
    for (i = -r + 1;; i++)
    {
        b = (ta + i) / tb * tc;
        rx = sqrt((t * b) * (t * b) + (r - b) * (r - b));
        //设置变化半径

        SDL_RenderDrawLine(renderer,
                           i + x, sqrt(rx * rx - i * i) + y,
                           i + x, -sqrt(rx * rx - i * i) + y);

        /*变化一个周期*/
        if (b >= tc)
        {
            b = 0;
            times += 1;
            if (times == (int)n / 2)
                break; //结束运算
            ta = cos(times * (360 / n) / 180.0 * 3.14) * r;
            tb = ta - cos((times + 1) * (360 / n) / 180.0 * 3.14) * r;
        }
    }
    return;
}
int isDown = 0;
int main(int argc, char *argv[])
{
    printf("start\n");
    //初始化所有SDL子系统
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return -1;    
    }
    SDL_Window *window = SDL_CreateWindow("SDL测试 - 风的影子", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 720, SDL_WINDOW_SHOWN);
    SDL_Surface *icon = IMG_Load("assets/ic_launcher.png");
    SDL_SetWindowIcon(window, icon);
    // SDL_Surface *surface = NULL;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    bool quit = false;
    SDL_Event e;
    SDL_Point point;
    
    //接下来是获取窗口的屏幕 这样才能绘制
    // surface = SDL_GetWindowSurface(window);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    base_init(window, renderer);
    graphics_init(window, renderer);
    init(); //调用CAPP的init函数
    _TIMER *timer = NULL;
    // while (!quit)
    // {
    //     Uint32 c_red = 0xffffffff;
    //     SDL_Rect rect = {0, 0, 20, 20};

    //     SDL_RenderFillRect(renderer, &rect); // 画圆，圆心（50，50） 半径50
    //                                          //加载图像
    //     hello = SDL_LoadBMP("ic_launcher.bmp");
    //     //使用SDL_Surface创建Texture
    //     pTexture = SDL_CreateTextureFromSurface(renderer, hello);
    //     SDL_Rect *srcRect = malloc(sizeof(SDL_Rect));
    //     SDL_Rect *dstRect = malloc(sizeof(SDL_Rect));
    //     srcRect->x = 0;
    //     srcRect->y = 0;
    //     srcRect->w = 140;
    //     srcRect->h = 140;
    //     dstRect->x = 0;
    //     dstRect->y = 0;
    //     dstRect->w = 140;
    //     dstRect->h = 140;
    //     SDL_RenderCopy(renderer, pTexture, srcRect, dstRect);
    //     SDL_Color color = {255, 0, 0, 255};
    //     drawCircle(200, 200, 50, 0xffffffff);
    //     drawLine(renderer, 0, 0, 500, 500);
    //     //将图像应用到窗口上
    //     // SDL_BlitSurface( hello, NULL, renderer, NULL );

    //     drawImgEx(renderer, "ic_launcher.bmp", 200, 0, 0, 0, 100, 100);
    //     while (SDL_PollEvent(&e))
    //     {
    //         switch (e.type)
    //         {
    //         case SDL_QUIT:
    //             quit = true;
    //             break;
    //         case SDL_MOUSEMOTION:
    //             event(MS_DOWN, e.motion.x, e.motion.y);
    //             if (isDown)
    //             {
    //                 SDL_RenderDrawLine(renderer, point.x, point.y, e.motion.x, e.motion.y);

    //                 point.x = e.motion.x;
    //                 point.y = e.motion.y;
    //             }
    //             break;
    //         case SDL_MOUSEBUTTONDOWN:
    //             event(MS_MOVE, e.motion.x, e.motion.y);
    //             point.x = e.motion.x;
    //             point.y = e.motion.y;
    //             isDown = 1;
    //             break;
    //         case SDL_MOUSEBUTTONUP:
    //             isDown = 0;
    //             event(MS_UP, e.motion.x, e.motion.y);
    //             // quit = true;
    //             SDL_AddTimer(RINTERVALS, timerRun, NULL);
    //             break;
    //         }
    //     }
    //     drawCircle(0, 300, 300, 0xff40ff30);
    //     SDL_RenderPresent(renderer);
    //     //更新窗口操作
    //     // SDL_UpdateWindowSurface(window);
    //     SDL_Delay(1000 / 60);
        
    // }



    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_USEREVENT:
                if (e.user.code == SDL_TIMER){
                    timer = (_TIMER *)(e.user.data1);
                    timer->timerCB(timer->data);
                }

                break;
            case SDL_QUIT:
                exitApp();
                quit = true;
                break;
            case SDL_MOUSEMOTION:
                if(isDown)
                event(MS_MOVE, e.motion.x, e.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                event(MS_DOWN, e.motion.x, e.motion.y);
                isDown = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                isDown = 0;
                event(MS_UP, e.motion.x, e.motion.y);
                break;
            }
        }
       
        // SDL_RenderPresent(renderer);
        //更新窗口操作
        // SDL_UpdateWindowSurface(window);
        // SDL_Delay(1000 / 60);
    }
    graphics_free();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);


return 0;
}

//绘制一张图片
void drawImg(SDL_Renderer *renderer, char *file, int x, int y, int w, int h)
{
    SDL_Surface *hello = NULL;
    SDL_Texture *pTexture = NULL;
    hello = SDL_LoadBMP(file);
    //使用SDL_Surface创建Texture
    pTexture = SDL_CreateTextureFromSurface(renderer, hello);
    SDL_Rect *srcRect = malloc(sizeof(SDL_Rect));
    SDL_Rect *dstRect = malloc(sizeof(SDL_Rect));
    srcRect->x = 0;
    srcRect->y = 0;
    srcRect->w = w;
    srcRect->h = h;
    dstRect->x = x;
    dstRect->y = y;
    dstRect->w = w;
    dstRect->h = h;
    SDL_RenderCopy(renderer, pTexture, srcRect, dstRect);
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
{
    //用于保存坐标
    SDL_Rect offset;

    //获得坐标
    offset.x = x;
    offset.y = y;

    //Blit操作
    SDL_BlitSurface(source, clip, destination, &offset);
}

//图片裁剪绘制
void drawImgEx(SDL_Renderer *renderer, char *file, int x, int y, int bx, int by, int bw, int bh)
{
    //  SDL_Surface *hello = NULL;
    //  hello = SDL_LoadBMP(file);
    //  SDL_Rect clip = {bx,by,bw,bh};
    //  apply_surface(x, y, hello, screen, &clip);
    SDL_Surface *hello = NULL;
    SDL_Texture *pTexture = NULL;
    hello = SDL_LoadBMP(file);
    //使用SDL_Surface创建Texture
    pTexture = SDL_CreateTextureFromSurface(renderer, hello);
    SDL_Rect *srcRect = malloc(sizeof(SDL_Rect));
    SDL_Rect *dstRect = malloc(sizeof(SDL_Rect));
    srcRect->x = bx;
    srcRect->y = by;
    srcRect->w = bw;
    srcRect->h = bh;
    dstRect->x = x;
    dstRect->y = y;
    dstRect->w = bw;
    dstRect->h = bh;
    SDL_RenderCopy(renderer, pTexture, srcRect, dstRect);
}

void DrawCircle(SDL_Renderer *ren, int x, int y, int radius)
{
    // using std::cout;
    // using std::clock;
    // using std::endl;
    // int st=clock();
    int i = 0;
    int tx = 0, ty = radius, d = 3 - (radius << 1);
    while (tx < ty)
    {
        for (i = x - ty; i <= x + ty; ++i)
        {
            SDL_RenderDrawPoint(ren, i, y - tx);
            if (tx)
                SDL_RenderDrawPoint(ren, i, y + tx);
        }
        if (d < 0)
            d += (tx << 2) + 6;
        else
        {
            for (i = x - tx; i <= x + tx; ++i)
            {
                SDL_RenderDrawPoint(ren, i, y - ty);
                SDL_RenderDrawPoint(ren, i, y + ty);
            }
            d += ((tx - ty) << 2) + 10, ty--;
        }
        tx++;
    }
    if (tx == ty)
        for (i = x - ty; i <= x + ty; ++i)
        {
            SDL_RenderDrawPoint(ren, i, y - tx);
            SDL_RenderDrawPoint(ren, i, y + tx);
        }
    // int en=clock();
    // cout<<"Drawing Circle(radius "<<radius<<" pixels),costs:"<<en-st<<"ms"<<endl;
}

// //画圆
// void drawCircle(SDL_Renderer *renderer, SDL_Color *color, int x0, int y0, int r)
// {
//     int x, y;
//     int d;
//     x = 0;
//     y = r;
//     d = 1 - r;
//     SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
//     while (x < y)
//     {
//         SDL_RenderDrawPoint(renderer, x + x0, y + y0);
//         SDL_RenderDrawPoint(renderer, x + x0, -y + y0);
//         SDL_RenderDrawPoint(renderer, -x + x0, y + y0);
//         SDL_RenderDrawPoint(renderer, -x + x0, -y + y0);
//         SDL_RenderDrawPoint(renderer, y + x0, x + y0);
//         SDL_RenderDrawPoint(renderer, y + x0, -x + y0);
//         SDL_RenderDrawPoint(renderer, -y + x0, x + y0);
//         SDL_RenderDrawPoint(renderer, -y + x0, -x + y0);
//         if (d > 0)
//         {
//             d += ((x - y) << 1) + 5;
//             y--;
//         }
//         else
//         {
//             d += (x << 1) + 3;
//             //d += 2;
//         }
//         x++;
//     }
// }
// //画矩形
// void drawRect(SDL_Renderer *renderer, int x, int y, int w, int h)
// {
//     SDL_Rect rect = {x, y, w, h};

//     SDL_RenderFillRect(renderer, &rect); // 画圆，圆心（50，50） 半径50
// }

//画线
// void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
// {
//     SDL_Rect rect = {x1, y1, x2, y2};

//     SDL_RenderDrawLine(renderer, x1, y1, x2, y2); // 画圆，圆心（50，50） 半径50
// }

//画点
// void drawPoint(SDL_Renderer *renderer, int x, int y)
// {
//     SDL_RenderDrawPoint(renderer, x, y);
// }
//画文字

/**
 * Name : SDLColorToColor
 *
 * Change from an "SDL_Color" to an Uint32
 * sdl_color input SDL_Color Color
 * return Uint32 Color
 */
Uint32 SDLColorToColor(SDL_Surface *screen, SDL_Color *sdl_color)
{
    return SDL_MapRGB(screen->format, sdl_color->r, sdl_color->g, sdl_color->b);
}

/*
 * Return the pixel value at (x, y) 获取像素
 * NOTE: The surface must be locked before calling this!
 */
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0; /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value 设置像素
 * NOTE: The surface must be locked before calling this!
 */
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    switch (surface->format->BytesPerPixel)
    {
    case 1: // Assuming 8-bpp
    {
        Uint8 *bufp;
        bufp = (Uint8 *)surface->pixels + y * surface->pitch + x;
        *bufp = pixel;
    }
    break;
    case 2: // Probably 15-bpp or 16-bpp
    {
        Uint16 *bufp;
        bufp = (Uint16 *)surface->pixels + y * surface->pitch / 2 + x;
        *bufp = pixel;
    }
    break;
    case 3: // Slow 24-bpp mode, usually not used
    {
        Uint8 *bufp;
        bufp = (Uint8 *)surface->pixels + y * surface->pitch + x * 3;
        if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
            bufp[0] = pixel;
            bufp[1] = pixel >> 8;
            bufp[2] = pixel >> 16;
        }
        else
        {
            bufp[2] = pixel;
            bufp[1] = pixel >> 8;
            bufp[0] = pixel >> 16;
        }
    }
    break;
    case 4: // Probably 32-bpp
    {
        Uint32 *bufp;
        bufp = (Uint32 *)surface->pixels + y * surface->pitch / 4 + x;
        *bufp = pixel;
    }
    break;
    }
}
