/*
	test square plugin
		by pyroesp
*/

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>


PSP_MODULE_INFO("test square", PSP_MODULE_USER, 0, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define COLOR_RED 0xFF0000FF


// main thread id
int thid;
// main loop running flag
int running;


// draw rectangle at coords [x;y] of size [w:h] in [color]
void draw_rect(int x, int y, int w, int h, u32 color);


int main_thread(SceSize args, void *argp){
	// wait for psp boot
	sceKernelDelayThread(7 * 1000 * 1000);
	
	while (running){	
		#define SQUARE_SIZE 20
		// draw rect in the center of the screen
		draw_rect((SCREEN_WIDTH - SQUARE_SIZE)/2, (SCREEN_HEIGHT - SQUARE_SIZE)/2, SQUARE_SIZE, SQUARE_SIZE, COLOR_RED);

		// wait for VblankStart
		sceDisplayWaitVblankStart();
	}

	return sceKernelExitDeleteThread(0);
}


// draw rectangle
void draw_rect(int x, int y, int w, int h, u32 color){
	u32 *vram32;
	int bufferwidth, pixelformat;
	int ret = sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_IMMEDIATE);
	
	// check return value for success
	if (ret == 0 && vram32 != NULL && bufferwidth != 0){
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				vram32[(y + i) * bufferwidth + (x + j)] = color;
			}
		}
	}
	// PS: not checking return value and/or vram32 pointer will result in a crash when putting the PSP to sleep
}



int module_start(SceSize args, void *argp){
	// set main loop flag to 1
	running = 1;
	thid = sceKernelCreateThread("test_square", main_thread, 0x10, 4*1024, PSP_THREAD_ATTR_USER, NULL);
	if (thid >= 0){
		sceKernelStartThread(thid, args, argp);
	}
	
	return 0;
}

int module_stop(SceSize args, void *argp){
	// clean exit main thread
	if (running){
		running = 0;
		SceUInt time = 100*1000;
		int ret = sceKernelWaitThreadEnd(thid, &time);
		if (ret < 0)
			sceKernelTerminateDeleteThread(thid);
	}
	
	return 0;
}