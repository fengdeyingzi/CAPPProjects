  //加载系统头文件base.h
#include "base.h"

int main();
 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    main();
    
    return 0;
}




//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exit();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}

//应用退出函数，在应用退出时可做一些内存释放操作
int exitApp()
{
    return 0;
}

/**************************************************************************
 *
 * tPNG:
 * tPNG is part of the topaz project. 
 * 2021, Johnathan Corkery
 *
 *
 * TINFL:
 * Copyright 2013-2014 RAD Game Tools and Valve Software
 * Copyright 2010-2014 Rich Geldreich and Tenacious Software LLC
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/



// First, include tpng.h.
// This only brings in one header: the stdint.h header 
// for sized integers.
//
#include "tpng.h"


// this will be used to print the data we read in decode_png()
#include <stdio.h>
#include <stdlib.h>
void print_png(const uint8 * data, uint32 width, uint32 height) {
    uint32 x = 0, y = 0;
    printf("print_png %d %d\n",width,height);
    for(y = 0; y < (int)height; y++) {
        for(x = 0; x < (int)width; x++) {
            printf("Pixel @ X Y (%d, %d): %03d %03d %03d %03d\n",
                x+1, y+1,
                data[0],
                data[1],
                data[2],
                data[3]
            );
            data+=4;
        }
    }
}


// tPNG is for decoding raw PNG file data, so before starting
// it is up to you to read the raw bytes from the PNG source, whether its a simple
// .png file, a network location, etc. You'll also need the size in bytes!
//
int decode_png(void * pngdata, unsigned int pngSize) {

    // Then, declare a place to hold the width / height.
    //
    uint32 width;
    uint32 height;


    // Next, we use tPNG to extract the raw color values as 8bit R G B A
    // data. The width and height are also extracted.
    //
    uint8 * rgbaData = tpng_get_rgba(
        pngdata,
        pngSize,
        &width,
        &height
    );
printf("%d %d\n",width,height);
    // There could have been an error! In such a case, the pixel data will 
    // be NULL and the width/height 0. Note that in most cases tPNG will 
    // try to read as much of the file as possible. Any parts that cannot be read 
    // default to "fully transparent black" (#00000000)
    //
    if (rgbaData == NULL) {
        return 0;
    }

    // Now we can use it! Nothing fancy. It's just in RGBA, 32bit format.
    // The whole image is a single buffer, laid out in rows from left to right,
    // top to bottom.
    //
    print_png(rgbaData, width, height);
    
    // Don't forget to free the heap-allocated buffer after you're done!
    //
    free(rgbaData);
    return 1;
}


// gives a simple function to dump data from a file.
#include "helper.h"

int main() {
    printf("main\n");
    int32  pngsize;
    uint8* pngdata = dump_file_data("1.png", &pngsize);
    printf("读取png文件：%d %d\n",pngdata, pngsize);
    if (!decode_png(pngdata, pngsize)) {
        printf("An error was encountered!");
        return 1;
    }

    return 0;
}