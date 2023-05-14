/*

	Test Square - PRX
		by pyroesp

*/

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>


PSP_MODULE_INFO("Test Square- PRX", PSP_MODULE_USER, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


int main_thread(SceSize args, void *argp){
	// wait for psp boot
	sceKernelDelayThread(10 * 1000 * 1000);
	
	unsigned int* vram32;
	int unk, bufferwidth, pixelformat, pwidth, pheight;
	sceDisplayGetMode(&unk, &pwidth, &pheight);
	sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_IMMEDIATE );
	// sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_NEXTFRAME  );
	

	while (1){
		sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_IMMEDIATE );
		// sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, PSP_DISPLAY_SETBUF_NEXTFRAME  );
		
		#define SQUARE 25
		#define X_POS 50
		#define Y_POS 50
		for (int i = 0; i < SQUARE; i++){
			for (int j = 0; j < SQUARE; j++){
				vram32[(Y_POS + i) * bufferwidth + (X_POS + j)] = 0xFFFFFFFF;
			}
		}		
		
		for (int i = 0; i < SQUARE; i++){
			for (int j = 0; j < SQUARE; j++){
				vram32[(Y_POS + i) * bufferwidth + (X_POS + j + 100)] = 0xFFFFFFFF;
			}
		}

		
		// sceKernelDelayThread(50 * 1000);
		sceDisplayWaitVblankStart();
	}

	return 0;
}



int module_start(SceSize args, void *argp){
	int thid;
	thid = sceKernelCreateThread("Test_Square", main_thread, 0x18, 4*1024, 0, NULL);
	if (thid >= 0){
		sceKernelStartThread(thid, args, argp);
	}
	
	return 0;
}

int module_stop(SceSize args, void *argp){
	return 0;
}