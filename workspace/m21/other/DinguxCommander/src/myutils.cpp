#ifndef _MYPIXELFORMAT
#define _MYPIXELFORMAT

#include <SDL.h>
#include <stdio.h>

void printPixelFormat(SDL_Surface* surface, char *name){
	SDL_PixelFormat* format = surface->format;

	printf("SDL_Surface %s:\n",name);
	printf("Surface WxHxB = %dx%dx%d\n",surface->w,surface->h,surface->format->BitsPerPixel);
	if (format->palette != NULL) {
		printf("  palette: %p\n",format->palette);
	} else {
		printf("  palette: NULL\n");
	}
	printf("  BitsPerPixel: %d\n",format->BitsPerPixel);
	printf("  BytesPerPixel: %d\n",format->BytesPerPixel);
	printf("  Rloss: %d\n",format->Rloss);
	printf("  Gloss: %d\n",format->Gloss);
	printf("  Bloss: %d\n",format->Bloss);
	printf("  Aloss: %d\n",format->Aloss);
	printf("  Rshift: %d\n",format->Rshift);
	printf("  Gshift: %d\n",format->Gshift);
	printf("  Bshift: %d\n",format->Bshift);
	printf("  Ashift: %d\n",format->Ashift);
	printf("  Rmask: 0x%08x\n",format->Rmask);
	printf("  Gmask: 0x%08x\n",format->Gmask);
	printf("  Bmask: 0x%08x\n",format->Bmask);
	printf("  Amask: 0x%08x\n",format->Amask);
	printf("  colorkey: 0x%08x\n",format->colorkey);
	printf("  alpha: %d\n\n",format->alpha);
	uint8_t red,blue,green,alpha;
	SDL_GetRGBA(*((uint32_t *)surface->pixels+1000), surface->format, &red, &green, &blue, &alpha); // SDL_GetRGB(Uint32 pixel, Uint8 *g, Uint8 *b, Uint8 *a);
	printf("IMAGE %s@1000 0x%08x -> RED=%d GREEN=%d BLUE=%d ALPHA=%d\n\n",name,*((uint32_t *)surface->pixels+1000),red,green,blue,alpha);
	system("sync");	
}

uint32_t argbToABGR(uint32_t argbColor) {
    uint8_t r = (argbColor >> 16) & 0xFF;
    uint8_t b = argbColor & 0xFF;
    return (argbColor & 0x0000FF00) | (b << 16) | r | 0xFF000000;
}

uint32_t addAlpha(uint32_t argbColor) {
    return (argbColor | 0xFF000000);
}

#endif