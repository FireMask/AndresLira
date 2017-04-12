#include "Definicion.h"

Camera *cam;
Cubo *run;

Cubo *cubos[50];

float speed = 3;

void Source::setup(){
	cam = new Camera(150, 150, 150);
	run = new Cubo(0, 0, 0, 10, 10, 10);
	for(int i = 0; i<50; i++)
		cubos[i] = new Cubo(rand() % 3000, 0, rand() % 3000, 10, 30, 10);
}

void Source::draw(){
	cam->setObjective(run->getPosition(), -100, run->getAngle());
	cam->update();

	if(isKeyDown('W')){
		if (isKeyDown(VK_SHIFT)) 
			run->MoveForward(speed*1.5);
		run->MoveForward(speed);
	}
	if (isKeyDown('S')) {
		run->MoveForward(-speed);
	}
	if (isKeyDown('A')) {
		run->turnRight(1);
	}
	if (isKeyDown('D')) {
		run->turnRight(-1);
	}

	run->Draw();

	for (int i = 0; i < 50; i++)
		cubos[i]->Draw();
}