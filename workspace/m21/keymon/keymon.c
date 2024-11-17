#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/input.h>

#include <msettings.h>

#define VOLUME_MIN 		0
#define VOLUME_MAX 		20
#define BRIGHTNESS_MIN 	0
#define BRIGHTNESS_MAX 	10

// uses different codes from SDL
#define CODE_MENU		27
#define CODE_PLUS		12
#define CODE_MINUS		11
#define CODE_PWR		-1

//	for ev.value
#define RELEASED	0
#define PRESSED		1
#define REPEAT		2

#define INPUT_COUNT 4
#define JS_COUNT 3
static int inputs[INPUT_COUNT];
static int jsinputs[JS_COUNT];


struct js_event {
		uint32_t time;     /* event timestamp in milliseconds */
		int16_t value;    /* value */
		uint8_t type;      /* event type */
		uint8_t number;    /* axis/button number */
	};
#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

struct js_event jsev;
static struct input_event ev;
FILE *file_log;

int main (int argc, char *argv[]) {
	InitSettings();
	// TODO: will require two inputs
	// input_fd = open("/dev/input/event0", O_RDONLY | O_NONBLOCK | O_CLOEXEC);
	char path[INPUT_COUNT][32];
	char jspath[JS_COUNT][32];
	for (int i=0; i<INPUT_COUNT; i++) {
		sprintf(path[i], "/dev/input/event%i", i);
		inputs[i] = open(path[i], O_RDONLY | O_NONBLOCK | O_CLOEXEC);
	}
	
	for (int i=0; i<JS_COUNT; i++) {
		sprintf(jspath[i], "/dev/input/js%i", i);
		jsinputs[i] = open(jspath[i], O_RDONLY | O_NONBLOCK| O_CLOEXEC);
	}

	//printf("opened /dev/input/event1\n");system("sync");

	uint32_t input;
	uint32_t val;
	uint32_t menu_pressed = 0;
	
	uint32_t up_pressed = 0;
	uint32_t up_just_pressed = 0;	
	uint32_t up_repeat_at = 0;
	
	uint32_t down_pressed = 0;
	uint32_t down_just_pressed = 0;
	uint32_t down_repeat_at = 0;
	
	uint8_t ignore;
	uint32_t then;
	uint32_t now;
	struct timeval tod;
	
	gettimeofday(&tod, NULL);
	then = tod.tv_sec * 1000 + tod.tv_usec / 1000; // essential SDL_GetTicks()
	ignore = 0;
	while (1) {
		gettimeofday(&tod, NULL);
		now = tod.tv_sec * 1000 + tod.tv_usec / 1000;
		if (now-then>1000) ignore = 1; // ignore input that arrived during sleep
		

		for (int x=0; x<JS_COUNT; x++) {
		//	if (fcntl(jsinputs[x], F_GETFD) <	0) {
		//		printf("Reopening /dev/input/js%i\n", x);fflush(stdout);
		//		jsinputs[x] = open(jspath[x], O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		//	}
			while (read (jsinputs[x], &jsev, sizeof(jsev)) == sizeof(jsev)) {
				//if (jsev.type >= 0) {
					printf("/dev/input/js%i: type:%i number:%i value:%i\n", x, jsev.type, jsev.number, jsev.value); fflush(stdout);
				//}
			}			
		}





		for (int i=0; i<INPUT_COUNT; i++) {
			int input_fd = inputs[i];
			while(read(input_fd, &ev, sizeof(ev))==sizeof(ev)) {
				if (ignore) continue;
				val = ev.value;
				printf("/dev/input/event%i: type:%i code:%i value:%i\n\n", i, ev.type,ev.code,ev.value); fflush(stdout);
				if (( ev.type != EV_KEY ) || ( val > REPEAT )) continue;
	//			printf("Code: %i (%i)\n", ev.code, val); fflush(stdout);
				switch (ev.code) {
					case CODE_MENU:
						menu_pressed = val;
					break;
					case CODE_PLUS:
						up_pressed = up_just_pressed = val;
						if (val) up_repeat_at = now + 300;
					break;
					case CODE_MINUS:
						down_pressed = down_just_pressed = val;
						if (val) down_repeat_at = now + 300;
					break;
					default:
						//file_log = fopen("/mnt/SDCARD/.userdata/m21/logs/keymon.log", "a+"); 
						//fprintf(file_log, "Event BTN Code = %d\n",ev.code);
						//fclose(file_log); system("sync");
					break;
				}
			}
		}
		
		if (ignore) {
			menu_pressed = 0;
			up_pressed = up_just_pressed = 0;
			down_pressed = down_just_pressed = 0;
			up_repeat_at = 0;
			down_repeat_at = 0;
		}
		
		if (up_just_pressed || (up_pressed && now>=up_repeat_at)) {
			if (menu_pressed) {
				//printf("brightness up\n"); fflush(stdout);
				val = GetBrightness();
				if (val<BRIGHTNESS_MAX) SetBrightness(++val);
			}
			else {
				//printf("volume up\n"); fflush(stdout);
				val = GetVolume();
				if (val<VOLUME_MAX) SetVolume(++val);
			}
			
			if (up_just_pressed) up_just_pressed = 0;
			else up_repeat_at += 100;
		}
		
		if (down_just_pressed || (down_pressed && now>=down_repeat_at)) {
			if (menu_pressed) {
				//printf("brightness down\n"); fflush(stdout);
				val = GetBrightness();
				if (val>BRIGHTNESS_MIN) SetBrightness(--val);
			}
			else {
				 //printf("volume down\n"); fflush(stdout);
				val = GetVolume();
				if (val>VOLUME_MIN) SetVolume(--val);
			}
			
			if (down_just_pressed) down_just_pressed = 0;
			else down_repeat_at += 100;
		}
		
		then = now;
		ignore = 0;
		
		usleep(16667); // 60fps
	}
	
}
