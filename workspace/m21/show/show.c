#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/joystick.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_rotozoom.h"



static struct fb_fix_screeninfo finfo;
static struct fb_var_screeninfo vinfo;

void get_info(int fd){
    ioctl(fd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);
   /* fprintf(stdout, "Fixed screen informations\n"
                    "-------------------------\n"
                    "Id string: %s\n"
                    "FB start memory: %p\n"
                    "FB LineLength: %d\n",
                    finfo.id, (void *)finfo.smem_start, finfo.line_length);

    fprintf(stdout, "Variable screen informations\n"
                    "----------------------------\n"
                    "xres: %d\n"
                    "yres: %d\n"
                    "xres_virtual: %d\n"
                    "yres_virtual: %d\n"
                    "bits_per_pixel: %d\n\n"
                    "RED: L=%d, O=%d\n"
                    "GREEN: L=%d, O=%d\n"
                    "BLUE: L=%d, O=%d\n"            
                    "ALPHA: L=%d, O=%d\n",
                    vinfo.xres, vinfo.yres, vinfo.xres_virtual,
                    vinfo.yres_virtual, vinfo.bits_per_pixel,
                    vinfo.red.length, vinfo.red.offset,
                    vinfo.blue.length,vinfo.blue.offset,
                    vinfo.green.length,vinfo.green.offset,
                    vinfo.transp.length,vinfo.transp.offset);

    //fprintf(stdout, "PixelFormat is %d\n", vinfo.pixelformat);
    fflush(stdout);*/
}

void set_info(int fd){
    ioctl(fd, FBIOPUT_VSCREENINFO, &vinfo);
}

int M21_SDLFB_Flip(SDL_Surface *buffer, void * fbmmap, int linewidth) {
	//copy a surface to the screen and flip it
	//it must be the same resolution, the bpp16 is then converted to 32bpp

	if (buffer->format->BitsPerPixel == 16) {
		//ok start conversion assuming it is RGB565
		int x, y;
		for (y = 0; y < buffer->h; y++) {
			for (x = 0; x < buffer->w; x++) {
				uint16_t pixel = *((uint16_t *)buffer->pixels + x + y * buffer->w);
				*((uint32_t *)fbmmap + x + y * linewidth) = 
					0xFF000000 | ((pixel & 0xF800) << 8) | ((pixel & 0x7E0) << 5) | ((pixel & 0x1F) << 3);
			}
		}
	}
	//TODO Handle 24bpp images
/*	if (buffer->format->BitsPerPixel == 24) {
		//ok start conversion assuming it is RGB888
		int x, y;
		for (y = 0; y < buffer->h; y++) {
			for (x = 0; x < buffer->w; x++) {
				uint24_t pixel = *((uint24_t *)buffer->pixels + x + y * buffer->w);
				*((uint32_t *)_screen->pixels + x + y * _screen->w) = 
					0xFF000000 | (pixel & 0xFF0000) | (pixel & 0xFF00)  | (pixel & 0xFF) ;
			}
		}
	}*/
	if (buffer->format->BitsPerPixel == 32) {
		//ok start conversion assuming it is ABGR888
		int x, y;
		for (y = 0; y < buffer->h; y++) {
			for (x = 0; x < buffer->w; x++) {
				uint32_t pixel = *((uint32_t *)buffer->pixels + x + y * buffer->w);
				*((uint32_t *)fbmmap + x + y * linewidth) = 
					0xFF000000 | ((pixel & 0xFF0000) >> 16) | (pixel & 0xFF00)  | ((pixel & 0xFF) << 16);
			}
		}
	}
	return 0;	
}




int main(int argc , char* argv[]) {
	if (argc<2) {
		puts("Usage: show image [await_input]"); 
		return 0;
	}

	char path[256];
	strncpy(path,argv[1],256);

    int fbfd;
    fbfd = open("/dev/fb0", O_RDWR);

    get_info(fbfd);
    vinfo.xres=640;
    vinfo.yres=480;
    set_info(fbfd);
    get_info(fbfd);

    uint32_t screen_size = finfo.line_length * vinfo.yres;
    void * fbp = mmap(NULL, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    memset(fbp,0,screen_size);
    SDL_Surface *image = IMG_Load(path);
	if (image==NULL) puts(IMG_GetError());
	
	SDL_Surface *imagefit = zoomSurface(image, 1.0*vinfo.xres/image->w, 1.0*vinfo.yres/image->h,0);    
    M21_SDLFB_Flip(imagefit,fbp,finfo.line_length/(vinfo.bits_per_pixel/8));
    SDL_FreeSurface(image);
    SDL_FreeSurface(imagefit);
    munmap(fbp, 0);
    close(fbfd);
}