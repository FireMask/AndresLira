#include "Definicion.h"

FirstPersonCamera *controller;

Circulo *c;

std::list<Cubo*> cubos;
std::list<Punto*> puntos;

float speed = 3;

void Source::setup(){
	controller = new FirstPersonCamera(0, 0, 0);
	controller->invertedCamera = true;
	c = new Circulo(0, 0, 0, 10);

	for (int i = 0; i < 500; i++) {
		Punto *p = new Punto(rand() % 3000 - 500, rand() % 1500 - 500, rand() % 3000 - 500);
		p->setLineWidth(5);
		puntos.push_back(p);
	}
	for (int i = 0; i < 500; i++)
		cubos.push_back(new Cubo(rand() % 3000 - 500, rand() % 1500 - 500, rand() % 3000 - 500, 10, 30, 10));
}

void Source::draw(){
	controller->keyboardMouse();

	c->Draw();

	for (auto i : puntos)
		i->Draw();
	for (auto i : cubos)
		i->Draw();

	if (isKeyDown(VK_ESCAPE))
		exit(0);
}