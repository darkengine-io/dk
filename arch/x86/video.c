#include "arch/x86/video.h"

char *vidmem;
unsigned int pos = 0;

void video_init() {
	vidmem = (char*) _X86_VIDMEM;
}

void screen_clear() {
	char *vidptr = vidmem;
	for (int i = 0; i < _X86_SCREEN_COLS * _X86_SCREEN_ROWS * 2; i+=2) { // two-byte stride
		vidptr[i] = ' ';
		vidptr[i + 1] =	COLOR_LIGHT_GREY | COLOR_BLACK << 4;
	}
	pos = 0;
}

void putchar(char c) {
	putchar_color(c, COLOR_LIGHT_GREY, COLOR_BLACK);
}

void putchar_color(char c, x86_colors fg, x86_colors bg) {
	char *vidptr = vidmem;
	switch (c) {
		case '\n':
			pos += (_X86_SCREEN_COLS - ((pos / 2) % _X86_SCREEN_COLS)) * 2;
			break;
		case '\b':
			pos -= 2;
			putchar_color(' ', fg, bg);
			pos -= 2;
			break;
		default:
			vidptr[pos] = c;
			vidptr[pos + 1] = fg | bg << 4;
			pos += 2;
			break;
	}
}

void puts(const char *s) {
	puts_color(s, COLOR_LIGHT_GREY, COLOR_BLACK);
}

void puts_color(const char *s, x86_colors fg, x86_colors bg) {
	for (char* t = (char*) s; *t; t++) {
		putchar(*t);
	}
}
