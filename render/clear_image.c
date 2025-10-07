#include "render.h"
#include "colors.h"
#include "stdlib.h"

// Clear image to black
void clear_image(t_render *render)
{
    int x;
    int y;
    y= 0;
    while(y < render->window_height)
    {
        x = 0;
        while (x < render->window_width)
        {
            put_pixel(render,x,y,COLOR_BLACK);
            x++;
        }
        y++;
    }
}

//TODO BUNLAR PARÇALANIP AYARLANACAK




