#pragma once
#include "Estructuras.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <math.h>
#include <list>

class Source {
public:
	void setup();
	void draw();
	bool isKeyDown(int vkey) {
		return GetKeyState(vkey) < 0;
	}
};
