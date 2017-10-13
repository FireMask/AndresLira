#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>
#include <list>
#include <string.h>

#define DEG2RAD 3.14159 / 180

class Color3{
public:
	float r;
	float g;
	float b;
	Color3() {}
	Color3(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	void getHSV(){
		
	}
};

class Vektor2 {
public:
	float x;
	float y;
	Vektor2() {}
	Vektor2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vektor2(Vektor2* vektor) {
		this->x = vektor->x;
		this->y = vektor->y;
	}
	void setValues(float x, float y){
		this->x = x;
		this->y = y;
	}
	void copy(Vektor2 *vector2) {
		this->x = vector2->x;
		this->y = vector2->y;
	}
};

class Vektor3 {
public:
	float x;
	float y;
	float z;
	Vektor3(){}
	Vektor3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vektor3(Vektor3* vektor){
		this->x = vektor->x;
		this->y = vektor->y;
		this->z = vektor->z;
	}
	void setValues(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void copy(Vektor3 *vector3){
		this->x = vector3->x;
		this->y = vector3->y;
		this->z = vector3->z;
	}
};

class Shape{
protected:
	Vektor3 *position;
	Vektor3 *rotator;
	Vektor2 *angles;
	Color3 *color;
	float angle;
	float lineWidth = 1;
public:
	Shape(){
		position = new Vektor3(0, 0, 0);
		color = new Color3(1, 1, 1);
		rotator = new Vektor3(0, 0, 0);
		angles = new Vektor2(0, 0);
		angle = 0;
	}
	Vektor3* getPosition(){
		return position;
	}
	void setRGB(float r, float g, float b){
		color->r = r;
		color->g = g;
		color->b = b;
	}
	void setLineWidth(float width){
		lineWidth = width;
	}
	void setAngles(Vektor2* angles){
		this->angles = angles;
	}
};

class Circulo : public Shape{
	float radio;
	float precision;
	std::list<Vektor2*> vertexs;
public:
	Circulo(float x, float y, float z, float radio){
		this->position = new Vektor3(x, y, z);
		this->radio = radio;
		this->precision = 50;
		for (int i = 0; i < precision; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / precision;
			float x = radio * cosf(theta);
			float y = radio * sinf(theta);
			vertexs.push_back(new Vektor2(x, y));
		}

	}
	void Draw(){
		glLineWidth(lineWidth);
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glRotatef(angle, rotator->x, rotator->y, rotator->z);
			glBegin(GL_LINE_LOOP);
				glColor3f(color->r, color->g, color->b);
				for(auto item : vertexs){
					glVertex2f(item->x, item->y);
				}
			glEnd();
		glPopMatrix();
	}
};

class Triangulo : public Shape{
	float base;
	float altura;
public:
	Triangulo(float x, float y, float z, float lado){
		this->position->x = x;
		this->position->y = y;
		this->position->z = z;
		this->base = lado;
		altura = (sqrt(3)*lado) / 2;
	}
	void Draw(){
		glLineWidth(lineWidth);
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glColor3f(color->r, color->g, color->b);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-base / 2, -altura / 2);
				glVertex2f(base / 2, -altura / 2);
				glVertex2f(0, altura / 2);
			glEnd();
		glPopMatrix();
	}
};

class Cubo : public Shape{
	float alto;
	float ancho;
	float largo;
public:
	Cubo(float x, float y, float z, float alto, float ancho, float largo){
		this->position->x = x;
		this->position->y = y;
		this->position->z = z;
		this->alto = alto;
		this->ancho = ancho;
		this->largo = largo;
	}
	void Draw(){
		glLineWidth(lineWidth);
		glPushMatrix();
			glTranslatef(position->x, position->y + alto, position->z);
			glRotatef(angles->x, 0, 1, 0);
			glRotatef(angles->y, 1, 0, 0);
			glBegin(GL_QUADS);
				//Front Face
				glColor3f(1, 0, 0);
				glVertex3f(-alto, -ancho, largo);
				glVertex3f(-alto, ancho, largo);
				glVertex3f(alto, ancho, largo);
				glVertex3f(alto, -ancho, largo);

				//Back Face
				glColor3f(1, 1, 0);
				glVertex3f(-alto, -ancho, -largo);
				glVertex3f(-alto, ancho, -largo);
				glVertex3f(alto, ancho, -largo);
				glVertex3f(alto, -ancho, -largo);

				//Left Face
				glColor3f(0, 1, 1);
				glVertex3f(-alto, -ancho, largo);
				glVertex3f(-alto, ancho, largo);
				glVertex3f(-alto, ancho, -largo);
				glVertex3f(-alto, -ancho, -largo);
				
				//Right Face
				glColor3f(0, 1, 0);
				glVertex3f(alto, -ancho, largo);
				glVertex3f(alto, ancho, largo);
				glVertex3f(alto, ancho, -largo);
				glVertex3f(alto, -ancho, -largo);

				//Bottom Face
				glColor3f(0, 0, 1);
				glVertex3f(-alto, -ancho, largo);
				glVertex3f(alto, -ancho, largo);
				glVertex3f(alto, -ancho, -largo);
				glVertex3f(-alto, -ancho, -largo);

				//Top Face
				glColor3f(1, 1, 1);
				glVertex3f(-alto, ancho, largo);
				glVertex3f(alto, ancho, largo);
				glVertex3f(alto, ancho, -largo);
				glVertex3f(-alto, ancho, -largo);

			glEnd();
		glPopMatrix();
	}
};

class Plano : public Shape{
	float largo;
	float ancho;
public:
	Plano(float x, float y, float z, float largo, float ancho) {
		this->position = new Vektor3(x, y, z);
		this->largo = largo;
		this->ancho = ancho;
	}
	Plano(float largo, float ancho) {
		this->largo = largo;
		this->ancho = ancho;
	}
	void Draw(){
		glPushMatrix();
			glTranslatef(this->position->x, this->position->y, this->position->z);
			glColor3f(color->r, color->g, color->b);
			glBegin(GL_QUADS);
				glVertex3f(largo, 0, ancho);
				glVertex3f(-largo, 0, ancho);
				glVertex3f(-largo, 0, -ancho);
				glVertex3f(largo, 0, -ancho);
			glEnd();
		glPopMatrix();
	}
};

class Punto : public Shape {
public:
	Punto(float x, float y, float z) {
		this->position->x = x;
		this->position->y = y;
		this->position->z = z;
	}
	void Draw() {
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glPointSize(lineWidth);
			glBegin(GL_POINTS);
				glColor3f(color->r, color->g, color->b);
				glVertex2f(position->x, position->y);
			glEnd();
		glPopMatrix();
	}
};

class Rainbow{
	float r = 1;
	float g = 0;
	float b = 0;

	float speedC = 0.001;
public:
	Color3 getRGB(){
		return Color3(r, g, b);
	}
	
	void setSpeedColor(float speed){
		speedC = speed/100;
	}

	void update(){
		if (r >= 1 && b <= 0)
			if (g <= 1.1)
				g += speedC;
		if (g >= 1 && b <= 0)
			if (r >= 0)
				r -= speedC;
		if (g >= 1 && r <= 0)
			if (b <= 1.1)
				b += speedC;
		if (b >= 1 && r <= 0)
			if (g >= 0)
				g -= speedC;
		if (b >= 1 && g <= 0)
			if (r <= 1.1)
				r += speedC;
		if (r >= 1 && g <= 0)
			if (b >= 0)
				b -= speedC;
	}
};

class Camera{
	Vektor3 *position;
	Vektor3 *lookAt;
	Vektor3 *up;
	float angleY;
	float angleZ;
public:
	Camera(){
		this->position = new Vektor3(0, 0, 0);
		this->lookAt = new Vektor3(0, 0, 0);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	Camera(float x, float y, float z) {
		this->position = new Vektor3(x, y, z);
		this->lookAt = new Vektor3(0, 0, 0);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	Camera(Vektor3* position){
		this->position = new Vektor3(position);
		this->lookAt = new Vektor3(0, 0, 0);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	Camera(Vektor3* position, Vektor3* lookAt) {
		this->position = new Vektor3(position);
		this->lookAt = new Vektor3(lookAt);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	void update(){
		gluLookAt(position->x, position->y, position->z, lookAt->x, lookAt->y, lookAt->z, up->x, up->y, up->z);
	}
	void setObjective(Vektor3 *pos, float distance, float heigth, float angle){
		lookAt->copy(pos);
		lookAt->y += heigth;
		position->copy(pos);
		position->x = position->x - distance * sin(angle*DEG2RAD);
		position->z = position->z - distance * cos(angle*DEG2RAD);
		position->y += heigth + position->y;
	}
};

class ThirdPersonController{
	Vektor2 *angles;
	Vektor3 *objective;
	Camera *camera;
	float distance;
	float heigth;
public:
	ThirdPersonController(){
		this->distance = 150;
		this->heigth = 20;
		this->angles = new Vektor2(0, 0);
		this->camera = new Camera();
		this->objective = new Vektor3(0, 0, 0);
	}
	ThirdPersonController(Vektor3 *objective){
		this->distance = 150;
		this->heigth = 20;
		this->angles = new Vektor2(0, 0);
		this->camera = new Camera();
		this->objective = objective;
		this->angles = new Vektor2(0, 0);
	}
	void MoveForward(float move) {
		objective->x = objective->x + move * sin(this->angles->x*DEG2RAD) * cos(this->angles->y*DEG2RAD);
		objective->y = objective->y + move * sin(this->angles->x*DEG2RAD) * sin(this->angles->y*DEG2RAD);
		objective->z = objective->z + move * cos(this->angles->x*DEG2RAD);
	}
	void turnRight(float rot) {
		this->angles->x += rot;
	}
	void turnUp(float rot) {
		this->angles->y += rot;
	}
	Vektor2* getAngles() {
		return angles;
	}
	void update(Cubo* objective){
		camera->setObjective(this->objective, distance, heigth, angles->x);
		objective->setAngles(angles);
		camera->update();
	}
};

class FirstPersonCamera{
	Vektor3 *position;
	Vektor3 *lookAt;
	Vektor3 *up;
	Vektor2 *angles;
	POINT currentCursor;
	POINT lastCursor;
	float deltaX, deltaY;
	float speed;
	float lookSpeed;
public:
	bool invertedCamera;
	FirstPersonCamera(float x, float y, float z) {
		position = new Vektor3(x, y, z);
		lookAt = new Vektor3(x, y, z);
		up = new Vektor3(0, 1, 0);
		angles = new Vektor2(0, 0);
		speed = 2;
		invertedCamera = false;
		lastCursor.x = 0;
		lastCursor.y = 0;
		lookSpeed = 5;
		updateLook();
	}
	void update() {
		gluLookAt(	this->position->x,
					this->position->y,
					this->position->z,
					this->lookAt->x,
					this->lookAt->y,
					this->lookAt->z,
					this->up->x,
					this->up->y,
					this->up->z);
	}
	void moveForward(float amount) {
		this->position->x = this->position->x + amount * cos(angles->x * DEG2RAD) * sin(angles->y * DEG2RAD);
		this->position->z = this->position->z + amount * cos(angles->x * DEG2RAD) * cos(angles->y * DEG2RAD);
		this->position->y = this->position->y + amount * sin(angles->x * DEG2RAD);
		updateLook();
	}

	void moveSide(float amount){
		this->position->x = this->position->x + amount * cos(angles->x * DEG2RAD) * sin((90 + angles->y) * DEG2RAD);
		this->position->z = this->position->z + amount * cos(angles->x * DEG2RAD) * cos((90 + angles->y) * DEG2RAD);
		this->position->y = this->position->y + amount * sin(angles->x * DEG2RAD);
		updateLook();
	}

	void turnRight(float amount) {
		this->angles->y += amount;
		updateLook();
	}

	void turnUp(float amount){
		this->angles->x += amount;
		if (this->angles->x > 89) this->angles->x = 90;
		if (this->angles->x < -89) this->angles->x = -90;
		updateLook();
	}

	void updateLook(){
		this->lookAt->x = this->position->x + 1 * cos(angles->x * DEG2RAD) * sin(angles->y * DEG2RAD);
		this->lookAt->z = this->position->z + 1 * cos(angles->x * DEG2RAD) * cos(angles->y * DEG2RAD);
		this->lookAt->y = this->position->y + 1 * sin(angles->x * DEG2RAD);
	}

	void setSpeed(float speed){
		this->speed = speed;
	}


	void cursorMovement(){
		GetCursorPos(&currentCursor);
		deltaX = lastCursor.x - currentCursor.x;
		deltaY = lastCursor.y - currentCursor.y;

		if (abs(deltaX) > abs(deltaY) && deltaX > 0) { //LEFT
			turnRight(deltaX / lookSpeed);
		}
		else if (abs(deltaX) > abs(deltaY) && deltaX < 0) { //RIGHT
			turnRight(deltaX / lookSpeed);
		}
		else if (abs(deltaY) > abs(deltaX) && deltaY > 0) { //UP
			turnUp(deltaY / lookSpeed);
		}
		else if (abs(deltaY) > abs(deltaX) && deltaY < 0) { //DOWN
			turnUp(deltaY / lookSpeed);
		}

		lastCursor = currentCursor;
	}

	void leftStick(){
		if (GetKeyState('W') < 0) {
			if (GetKeyState(VK_SHIFT) < 0)
				moveForward(speed * 2);
			else
				moveForward(speed);
		}
		if (GetKeyState('S') < 0) {
			moveForward(-speed);
		}
		if (GetKeyState('A') < 0) {
			moveSide(speed);
		}
		if (GetKeyState('D') < 0) {
			moveSide(-speed);
		}
	}

	void rightStick(){
		if (GetKeyState(VK_LEFT) < 0) {
			turnRight(speed);
		}
		if (GetKeyState(VK_RIGHT) < 0) {
			turnRight(-speed);
		}
		if (GetKeyState(VK_UP) < 0) {
			if (!invertedCamera) {
				if (angles->x < 89) turnUp(speed / 2);
			}
			else {
				if (angles->x > -89) turnUp(-speed / 2);
			}
		}
		if (GetKeyState(VK_DOWN) < 0) {
			if (!invertedCamera) {
				if (angles->x > -89) turnUp(-speed / 2);
			}
			else {
				if (angles->x < 89) turnUp(speed / 2);
			}
		}
	}

	void keyboardMouse(){
		update();
		leftStick();
		cursorMovement();
	}

	void keyboard(){
		update();
		leftStick();
		rightStick();
	}
};