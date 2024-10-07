#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL.h>

#include "config.h"
#include "myutils.h"

struct Screen
{
    // Logical width and height.
    decltype(SDL_Rect().w) w;
    decltype(SDL_Rect().h) h;

    // Scaling factors.
    float ppu_x;
    float ppu_y;

    // Actual width and height.
    decltype(SDL_Rect().w) actual_w;
    decltype(SDL_Rect().h) actual_h;

    // We target 25 FPS because currently the key repeat timer is tied into the
    // frame limit. :(
    int refreshRate = 25;

    SDL_Surface *surface;

#ifdef USE_SDL2
    SDL_Window *window;
#endif

    void flip() {
#ifdef USE_SDL2
		if (SDL_UpdateWindowSurface(window) <= -1) {
			SDL_Log("%s", SDL_GetError());
		}
		surface = SDL_GetWindowSurface(window);
#else
     

    uint32_t x ,y;
	//SDL_LockSurface(screen);
    uint32_t _start = SDL_GetTicks();
    //test with fast alternative blit:
    uint32_t _size = surface->h * surface->w * surface->format->BytesPerPixel;

    for (x = 3; x < _size; x+=4) {
        *((uint8_t *)surface->pixels + x) = 0xFF;
    }
    
    uint32_t last=0;
 /*   //standard method
	for (y = 0; y < surface->h; y++) {
		for (x = 0; x < surface->w; x++) {
			*((uint32_t *)surface->pixels + x + y * surface->w) |= 0xFF000000;
            last++;
	    }
    }*/
      uint32_t _middle = SDL_GetTicks();
      SDL_Flip(surface);
      uint32_t _stop = SDL_GetTicks();
      printf("SIZE= %d  - DURATION: ITERATION=%d - FLIP=%d\n",_size,_middle-_start, _stop-_middle);
      system("sync");
      surface = SDL_GetVideoSurface();
#endif
    }

    // Called once at startup.
    int init();

    // Called on every SDL_RESIZE event.
    int onResize(int w, int h);

    void setPhysicalResolution(int actual_w, int actual_h);

    void zoom(float factor);
};

extern Screen screen;

#endif // _SCREEN_H_
