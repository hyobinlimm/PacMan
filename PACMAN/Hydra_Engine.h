#pragma once

//»ö»ó
enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DAKR_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

void setColor(unsigned short text);
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdio.h>
#include <windows.h>
#include "new_conio.h"

BOOL Initialize();

void LHFillScreen(int ch);
void LHFillScreenEx(const char* pStr);
void LHLocateCursor(int x, int y);
void LHPutChar(int x, int y, char ch);
void LHPutAttrChar(int x, int y, char ch, WORD bg, WORD fg);
void LHPutAttrCharEx(int x, int y, const char* pStr, WORD bg, WORD fg);
void LHSetAttrChar(WORD bg, WORD fg);
void LHSetCursor(DWORD dwSize, BOOL bVisible);
void CursorView(bool show);


#endif // __CONSOLE_H__