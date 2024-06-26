#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <mi_sys.h>
#include <mi_common.h>
#include <mi_disp.h>

#define LUMONCFG_PATH "/mnt/SDCARD/.system/miyoomini/lumon.cfg"
#define LUMONLOG_PATH "/mnt/SDCARD/.system/miyoomini/lumon.log"

MI_DISP_LcdParam_t mylcdparams;
MI_DISP_ColorTemperature_t mytempparams;
int lcdparamscnt;
int tempparamscnt;

FILE *mylog;

u_int32_t  myMin(unsigned int a, unsigned int b){
	if (a<=b) {
		return (u_int32_t)(a);
	} else {
		return (u_int32_t)(b);
	}
}

int readLumonCfg(char * filecfg){
	lcdparamscnt = 0;
	tempparamscnt = 0;
	//read BOXART_CFGFILE then fill the struct woth all read data
	FILE *config = fopen(filecfg,"r");
	if (mylog) fprintf(mylog,"Opening CFG file %s\n", LUMONCFG_PATH);
    char *mysetting;
    if (config) {
		char * pch;
		char parametri[512];
        if (mylog) fprintf(mylog,"Reading CFG file %s\n", LUMONCFG_PATH );
        while (fgets(parametri, sizeof(parametri), config)) {
            char tmpstr[20];
                if (strncmp(parametri,"LUM =",5) == 0){
				lcdparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mylcdparams.stCsc.u32Luma = myMin(strtol(pch,NULL,10),100);
                if (mylog) fprintf(mylog,"LUM = %d\n", mylcdparams.stCsc.u32Luma);
                }
            if (strncmp(parametri,"HUE =",5) == 0){
				lcdparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mylcdparams.stCsc.u32Hue = myMin(strtol(pch,NULL,10) ,100);
                if (mylog) fprintf(mylog,"HUE = %d\n",  mylcdparams.stCsc.u32Hue);
                }
            if (strncmp(parametri,"SAT =",5) == 0){
				lcdparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mylcdparams.stCsc.u32Saturation = myMin(strtol(pch,NULL,10),100);
                if (mylog) fprintf(mylog,"SAT = %d\n", mylcdparams.stCsc.u32Saturation);
                }
            if (strncmp(parametri,"CON =",5) == 0){
				lcdparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mylcdparams.stCsc.u32Contrast = myMin(strtol(pch,NULL,10),100);
                if (mylog) fprintf(mylog,"CON = %d\n", mylcdparams.stCsc.u32Contrast);
                }
			if (strncmp(parametri,"SHP =",5) == 0){
				lcdparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mylcdparams.u32Sharpness = myMin(strtol(pch,NULL,10),100);
                if (mylog) fprintf(mylog,"SHP = %d\n", mylcdparams.u32Sharpness);
                }
            if (strncmp(parametri,"RED =",5) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16RedColor = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"RED = %d\n", mytempparams.u16RedColor);
                }
            if (strncmp(parametri,"GRN =",5) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16GreenColor = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"GRN = %d\n", mytempparams.u16GreenColor);
                }
            if (strncmp(parametri,"BLU =",5) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16BlueColor = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"BLU = %d\n", mytempparams.u16BlueColor);
                }
			if (strncmp(parametri,"REDOFF =",8) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16RedOffset = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"REDOFF = %d\n", mytempparams.u16RedOffset);
                }
            if (strncmp(parametri,"GRNOFF =",8) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16GreenOffset = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"GRNOFF = %d\n", mytempparams.u16GreenOffset);
                }
            if (strncmp(parametri,"BLUOFF =",8) == 0){
				tempparamscnt++;
                pch = strtok (parametri,"=");
                pch = strtok (NULL, "=");
                mytempparams.u16BlueOffset = (u_int16_t)(strtol(pch,NULL,10) & 0xff);
                if (mylog) fprintf(mylog,"BLUOFF = %d\n", mytempparams.u16BlueOffset);
                }
            
        }
        fclose(config);
		if (mylog) fprintf(mylog,"Closing CFG file %s\n", LUMONCFG_PATH);
		return 1;
    }
	return 0;
}




int main(void) {

	mylog = fopen(LUMONLOG_PATH,"w");
	if (mylog) fprintf(mylog, "Starting Lumon.elf\n");
	MI_DISP_DEV dev = 0;
	
	MI_DISP_PubAttr_t attrs;
	memset(&attrs,0,sizeof(MI_DISP_PubAttr_t));
	MI_DISP_GetPubAttr(dev,&attrs);
	
	attrs.eIntfType = E_MI_DISP_INTF_LCD;
	attrs.eIntfSync = E_MI_DISP_OUTPUT_USER;
	MI_DISP_SetPubAttr(dev,&attrs);
	
	MI_DISP_Enable(dev);
	
	MI_DISP_LcdParam_t lcdparams;
	memset(&lcdparams,0,sizeof(MI_DISP_LcdParam_t));
	MI_DISP_GetLcdParam(dev, &lcdparams);
	memset(&mylcdparams,0,sizeof(MI_DISP_LcdParam_t));
	MI_DISP_GetLcdParam(dev, &mylcdparams);

	if (mylog) fprintf(mylog,"READ LUM = %d\n", lcdparams.stCsc.u32Luma);
	if (mylog) fprintf(mylog,"READ CON = %d\n", lcdparams.stCsc.u32Contrast);
	if (mylog) fprintf(mylog,"READ SAT = %d\n", lcdparams.stCsc.u32Saturation);
	if (mylog) fprintf(mylog,"READ HUE = %d\n", lcdparams.stCsc.u32Hue);
	if (mylog) fprintf(mylog,"READ SHP = %d\n\n", lcdparams.u32Sharpness);

	lcdparams.stCsc.u32Luma = 45;
	lcdparams.stCsc.u32Contrast = 50;
	lcdparams.stCsc.u32Hue = 50;
	lcdparams.stCsc.u32Saturation = 45;
	lcdparams.u32Sharpness = 0;
	
	MI_DISP_ColorTemperature_t tempparams;
	memset(&tempparams,0,sizeof(MI_DISP_ColorTemperature_t));
	MI_DISP_DeviceGetColorTempeture(dev, &tempparams);
	memset(&mytempparams,0,sizeof(MI_DISP_ColorTemperature_t));
	MI_DISP_DeviceGetColorTempeture(dev, &mytempparams);
	
	if (mylog) fprintf(mylog,"READ RED = %d\n", tempparams.u16RedColor);
	if (mylog) fprintf(mylog,"READ BLU = %d\n", tempparams.u16BlueColor);
	if (mylog) fprintf(mylog,"READ GRN = %d\n", tempparams.u16GreenColor);
	if (mylog) fprintf(mylog,"READ REDOFF = %d\n", tempparams.u16RedOffset);
	if (mylog) fprintf(mylog,"READ BLUOFF = %d\n", tempparams.u16BlueOffset);
	if (mylog) fprintf(mylog,"READ GRNOFF = %d\n", tempparams.u16GreenOffset);

	tempparams.u16BlueColor = 0x80;
	tempparams.u16BlueOffset = 0;
	tempparams.u16RedColor = 0x80;
	tempparams.u16RedOffset = 0;
	tempparams.u16GreenColor = 0x80;
	tempparams.u16GreenOffset = 0;

	readLumonCfg(LUMONCFG_PATH);
	
	if (lcdparamscnt == 5){
		if (mylog) fprintf(mylog,"Using lcd parameters from cfg file\n");
		if (MI_DISP_SetLcdParam(dev, &mylcdparams)==0){
			if (mylog) fprintf(mylog,"Successfully loaded cfg lcd params\n");
		}
	} else {
		if (mylog) fprintf(mylog,"Using lcd parameters standard\n");
		MI_DISP_SetLcdParam(dev, &lcdparams);
	}	
	if (tempparamscnt == 6){
			if (mylog) fprintf(mylog,"Using color temp parameters from cfg file\n");
			MI_DISP_DeviceSetColorTempeture(dev, &mytempparams);
	} 
	


	if (mylog) fprintf(mylog,"NEW LUM = %d\n", mylcdparams.stCsc.u32Luma);
	if (mylog) fprintf(mylog,"NEW HUE = %d\n", mylcdparams.stCsc.u32Hue);
	if (mylog) fprintf(mylog,"NEW SAT = %d\n", mylcdparams.stCsc.u32Saturation);
	if (mylog) fprintf(mylog,"NEW CON = %d\n", mylcdparams.stCsc.u32Contrast);
	if (mylog) fprintf(mylog,"NEW SHP = %d\n", mylcdparams.u32Sharpness);

	MI_DISP_GetLcdParam(dev, &lcdparams);
	if (mylog) fprintf(mylog,"READ LUM = %d\n", lcdparams.stCsc.u32Luma);
	if (mylog) fprintf(mylog,"READ CON = %d\n", lcdparams.stCsc.u32Contrast);
	if (mylog) fprintf(mylog,"READ SAT = %d\n", lcdparams.stCsc.u32Saturation);
	if (mylog) fprintf(mylog,"READ HUE = %d\n", lcdparams.stCsc.u32Hue);
	if (mylog) fprintf(mylog,"READ SHP = %d\n\n", lcdparams.u32Sharpness);

	if (mylog) fprintf(mylog,"NEW RED = %d\n", tempparams.u16RedColor);
	if (mylog) fprintf(mylog,"NEW BLU = %d\n", tempparams.u16BlueColor);
	if (mylog) fprintf(mylog,"NEW GRN = %d\n", tempparams.u16GreenColor);
	if (mylog) fprintf(mylog,"NEW REDOFF = %d\n", tempparams.u16RedOffset);
	if (mylog) fprintf(mylog,"NEW BLUOFF = %d\n", tempparams.u16BlueOffset);
	if (mylog) fprintf(mylog,"NEW GRNOFF = %d\n", tempparams.u16GreenOffset);
	
	
	if (mylog) fclose(mylog);
	//while (1) pause();
	
	// MI_DISP_Disable(dev);
}
