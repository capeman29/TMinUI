#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#if defined(USE_SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2_rotozoom.h"
#else
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_rotozoom.h"
#endif

#include <msettings.h>

#include "defines.h"
#include "utils.h"
#include "api.h"

#define FIXED_WIDTH 640
#define FIXED_HEIGHT 480

#define CFGFILE SDCARD_PATH "/Tools/" THISPLATFORM "/Convert BoxArt.pak/boxart.cfg"
#define SRCDIR  SDCARD_PATH "/Tools/" THISPLATFORM "/Convert BoxArt.pak/srcimgdir"
#define DSTDIR SRCDIR "/outdir"

enum Aspect { ASPECT, NATIVE, FULL};
int X,Y,W,H,SW,SH;
enum Aspect aspect;



int makeBoxart(char *, char *, enum Aspect, char *);

int
filter(const struct dirent *name)
{
  return 1;
}

int main(int argc, char* argv[]) {
    PWR_setCPUSpeed(CPU_SPEED_PERFORMANCE);

    SDL_Surface* screen = GFX_init(MODE_MAIN);
    PWR_init();
    InitSettings();

    SDL_Event event;
    int quit = 0;
    int save_changes = 0;

    struct dirent **namelist;
    int n;

    char parametri[512];
    FILE *config = fopen(CFGFILE,"r");
    LOG_info("Opening CFG file %s\n", CFGFILE);
    char * pch;
    char gradient[256];
    if (config) {
        LOG_info("Reading CFG file %s\n", CFGFILE);
        while (fgets(parametri, sizeof(parametri), config)) {
            char tmpstr[20];
                if (strncmp(parametri,"BX =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                X = strtol(pch,NULL,10);
                LOG_info("BX = %d\n", X);
                }
            if (strncmp(parametri,"BY =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                Y = strtol(pch,NULL,10);
                LOG_info("BY = %d\n", Y);
                }
            if (strncmp(parametri,"BW =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                W = strtol(pch,NULL,10);
                LOG_info("BW = %d\n", W);
                }
            if (strncmp(parametri,"BH =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                H = strtol(pch,NULL,10);
                LOG_info("BH = %d\n", H);
                }
            if (strncmp(parametri,"SW =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                SW = strtol(pch,NULL,10);
                LOG_info("SW = %d\n", SW);
                }
            if (strncmp(parametri,"SH =",4) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                SH = strtol(pch,NULL,10);
                LOG_info("SH = %d\n", SH);
                }
            if (strncmp(parametri,"ASPECT =",8) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                aspect = strtol(pch,NULL,10);
                LOG_info("ASPECT = %d\n", aspect);
                }
            if (strncmp(parametri,"GRADIENT = ",11) == 0){
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                sprintf(gradient,"%s", pch);
                normalizeNewline(gradient);
                trimTrailingNewlines(gradient);
                LOG_info("GRADIENT = #%s#\n", gradient);
                }            
        }
        fclose(config);
    }
    
    //char cmd[512];
    //sprintf(cmd,"cp \"/mnt/sdcard/Tools/imgdir/PSorig.png\" " MYINPUT);
    //system(cmd);
    //sprintf(cmd,"cp \"/mnt/sdcard/Roms/NeoGeo CD (NGCD)/Imgs/mslug5.png\" \"/mnt/sdcard/Roms/NeoGeo (NG)/Imgs/mslug5.png\"");
    //system(cmd);
    LOG_info("Scanning image dir %s\n", SRCDIR);
    n = scandir(SRCDIR, &namelist, filter, alphasort);
    if (n == -1) {
     LOG_info("Failed scandir");
     return -1;
    }
    DIR* dir = opendir(DSTDIR);
    if (dir) {
    /* Directory exists. */
         closedir(dir);
    } else {
    /* Directory does not exist. */
    //create DSTDIR
        LOG_info("Creating image dest dir %s\n", DSTDIR);
        mkdir(DSTDIR, 0755);
    } 
    int total = n-1;
    char src[256];
    char dst[256];
    char progressstr[100];
    n=0;
    while (n<=total) {
        if (namelist[n]->d_type == DT_REG)
        {              
            sprintf(src,SRCDIR "/%s",namelist[n]->d_name);
            sprintf(dst,DSTDIR "/%s",namelist[n]->d_name);
            makeBoxart(src,dst, aspect, gradient);
            sprintf(progressstr,"Converted %d/%d\n%s",n,total,namelist[n]->d_name);
        } else {
            sprintf(progressstr,"Skipped %d/%d\n%s",n,total,namelist[n]->d_name);
        }        
        GFX_clear(screen);
        GFX_blitMessage(font.large, progressstr, screen, &(SDL_Rect){0,0,screen->w,screen->h});
        free(namelist[n]);
        n++;
    }
    free(namelist);
    //GFX_clear(screen);
    GFX_blitMessage(font.large, "Press A to Exit", screen, &(SDL_Rect){0,200,screen->w,screen->h-200});

    GFX_flip(screen);
    // Wait for user's input
    while (!quit) {
        PAD_poll();
        if (PAD_justPressed(BTN_A)) {
            quit = 1;
        } else {
            GFX_sync();
        }
    }

    PWR_setCPUSpeed(CPU_SPEED_MENU);
    QuitSettings();
    PWR_quit();
    GFX_quit();

    return EXIT_SUCCESS;
}

int makeBoxart(char *infilename, char *outfilename, enum Aspect _aspect, char * mygradient) {
    SDL_Surface *image = IMG_Load(infilename);
    SDL_Surface *mysurface = SDL_CreateRGBSurface(0,SW,SH,16,0,0,0,0);
    //SDL_Surface *unscaled_myimg = IMG_Load(BACKGROUND);
    if (image == NULL){
        LOG_info("error loading the image %s", infilename);
        return -1;
    }
    double xfactr, yfactr;
    double myaspect = 1.0 * image->w / image->h; 
    int localX = X;
    int localY = Y; 
    switch (_aspect) {
        case ASPECT: 
            LOG_info("ASPECT = ASPECT\n");
            //first calculate othe original aspectratio
            if (myaspect > 1.0){
                //the W is bigger than H
                    //resize to fit W
                    xfactr = 1.0 * W / image->w;
                    yfactr = xfactr; 
                    localY += (H - (image->h * yfactr))/2;
            } else { //image is higher than wider
                    //resize to fit H
                    yfactr = 1.0 * H / image->h;
                    xfactr = yfactr; 
                    localX += (W - (image->w * xfactr))/2;
            }
            break;
        case NATIVE: 
            LOG_info("ASPECT = NATIVE\n");
            if ((W > image->w) && (H > image->h)){
                //image is smaller than target box
                xfactr = 1.0;
                yfactr = 1.0; 
                //change x y to place the image in the center of the target box
                localX += (W - image->w)/2;
                localY += (H - image->h)/2;
            } else {
                //image is bigger than target box so apply ASPECT rule
                if (myaspect > 1.0){
                    //the W is bigger than H
                        //resize to fit W
                        xfactr = 1.0 * W / image->w;
                        yfactr = xfactr; 
                        localY += (H - (image->h * yfactr))/2;
                } else { //image is higher than wider
                        //resize to fit H
                        yfactr = 1.0 * H / image->h;
                        xfactr = yfactr; 
                        localX += (W - (image->w * xfactr))/2;
                }
            }            
            break;
        case FULL: 
            //fill target box by shrinking/streching the original image
            LOG_info("ASPECT = FULL\n");
            xfactr = 1.0 * W / image->w;
            yfactr = 1.0 * H / image->h; 
            break;
    }
    SDL_Surface *scaled_myimg = zoomSurface(image, xfactr , yfactr, 0);   
    SDL_BlitSurface(scaled_myimg,NULL,mysurface,&(SDL_Rect){localX,localY}); 
    if (mygradient[0]==' '){
        mygradient++;
    }
    if (strncmp(mygradient,"NONE",4) != 0){
        SDL_Surface *blackgradient = IMG_Load(mygradient);
        if (blackgradient == NULL){
            LOG_info("Failed loading Gradient: %s\n", IMG_GetError());
            return -1;  
        } 
        SDL_SetColorKey(blackgradient, SDL_TRUE, SDL_MapRGB(blackgradient->format, 0, 0, 0)); // enable color key (transparency)
        SDL_BlitSurface(blackgradient,NULL,mysurface,NULL);
        SDL_FreeSurface(blackgradient);
    }

    SDL_RWops* out = SDL_RWFromFile(outfilename, "wb");
    SDL_SaveBMP_RW(mysurface, out, 1); 
    SDL_FreeSurface(scaled_myimg); 
    SDL_FreeSurface(mysurface);
    SDL_FreeSurface(image);
    char cmd[512];
    sprintf(cmd,"bmp2png.elf -X \"%s\" && rm \"%s.bak\"", outfilename, outfilename);
    system(cmd);
    return 1;
}