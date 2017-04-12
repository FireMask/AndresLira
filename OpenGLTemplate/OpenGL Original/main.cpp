/*Plantilla OpenGL 1.0 Creada por Edgar Abraham Santos Cervantes
--El 17/09/2016 para las practicas de los laboratorios de POO---
--LMAD */
#include <Windows.h> 
#include <gl\GL.h>
#include <gl\GLU.h>
#include <WinGDI.h>
#include <list>
#include "Definicion.h"
#include "resource.h"

#define Timer1 1
#define DEG2RAD 3.14159 / 180

static HGLRC hRC;
static HDC hDC;

PIXELFORMATDESCRIPTOR pfd;

HINSTANCE VentanaOpenGL;

Source mmain;

void ajustarPantalla(LPARAM &lParam)
{
	GLsizei alto;
	GLsizei ancho;
	alto = HIWORD(lParam);
	ancho= LOWORD(lParam);
	if (alto==0)
		alto=342;
	if (ancho==0)
		ancho=524;
	glViewport(0,0,ancho,alto);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)ancho/(GLfloat)alto,1.0f, 3000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

BOOL CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
		{
			hDC = GetDC(hWnd);
			ZeroMemory(&pfd,sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 16;
			int format = ChoosePixelFormat(hDC,&pfd);
			SetPixelFormat(hDC,format, &pfd);
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			SetTimer(hWnd,Timer1, 1, NULL);
			ajustarPantalla(lParam);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_COLOR_MATERIAL);
		}break;
		case WM_DESTROY:
			{
				KillTimer(hWnd,Timer1);
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hRC);
				ReleaseDC(hWnd,hDC);
				glDisable(GL_DEPTH_TEST);
			}break;
		case WM_CLOSE:
			{
				PostQuitMessage(0);
			}
		case WM_SIZE:
			{
				ajustarPantalla(lParam);
			}break;
		case WM_TIMER:
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
				glClearColor(.1,.1,.1,1);

				GLfloat color[4] = {1.0, 1.0, 1.0, 1.0};
				GLfloat position[3] = {0, 10, 10};
				GLfloat color1[4] = {1.0, 1.0, 0, 1.0};
				GLfloat position1[3] = {10, 50, 10};
				GLfloat direction[3] = {0,0,0};
				glLightfv(GL_LIGHT0, GL_SPECULAR, color);
				glLightfv(GL_LIGHT0, GL_POSITION, position);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, color1);
				glLightfv(GL_LIGHT1, GL_POSITION, position1);
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
				//gluLookAt(0, 75, 75, 0, 0, 0, 0, 1, 0);

				mmain.draw();

				SwapBuffers(hDC);
			}break;
		case WM_KEYDOWN:
			{
				switch(LOWORD(wParam))
				{
				/*case 65:
					{
						KillTimer(hWnd,Timer1);
					}break;
				case 66:
					{
						SetTimer(hWnd, Timer1,1,NULL);
					}break;*/
				}
			}break;
	}
	return false;
}

int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
{
	mmain.setup();
	DialogBox(VentanaOpenGL, MAKEINTRESOURCE(IDD_DIALOG1),NULL, WndProc);
	return 0;
}