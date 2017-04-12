#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <math.h>

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
	void copy(Vektor3 *vector3){
		this->x = vector3->x;
		this->y = vector3->y;
		this->z = vector3->z;
	}
};

class Shape{
protected:
	Vektor3 *position;
	
	float lado;

	float angle = 0;
	Vektor3 *rotator;
	
	Color3 *color;

	float lineWidth = 1;

	float precision = 35;
public:
	Shape(){
		position = new Vektor3(0, 0, 0);
		color = new Color3(1, 1, 1);
		rotator = new Vektor3(0, 0, 0);
	}
	Vektor3* getPosition(){
		return position;
	}
	float getAngle() { return angle; }
	void setRGB(float r, float g, float b){
		color->r = r;
		color->g = g;
		color->b = b;
	}
	void setLineWidth(float width){
		lineWidth = width;
	}
	void MoveForward(float move){
		this->position->x = this->position->x + move * sin(this->angle*DEG2RAD);
		this->position->z = this->position->z + move * cos(this->angle*DEG2RAD);
	}
	void turnRight(float rot){
		this->angle += rot;
	}
};

class Circulo : public Shape{
public:
	Circulo(float x, float y, float z, float radio){
		this->position->x = x;
		this->position->y = y;
		this->position->z = z;
		this->lado = radio;
	}
	void Draw(){
		glLineWidth(lineWidth);
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glRotatef(angle, rotator->x, rotator->y, rotator->z);
			glBegin(GL_LINE_LOOP);
				glColor3f(color->r, color->g, color->b);
				for (int i = 0; i < precision; i++) {
					float theta = 2.0f * 3.1415926f * float(i) / precision;
					float x = lado * cosf(theta);
					float y = lado * sinf(theta);
					glVertex2f(x, y);
				}
			glEnd();
		glPopMatrix();
	}
};

class Triangulo : public Shape{
	float altura;
public:
	Triangulo(float x, float y, float z, float lado){
		this->position->x = x;
		this->position->y = y;
		this->position->z = z;
		this->lado = lado;
		altura = (sqrt(3)*lado) / 2;
	}
	void Draw(){
		glLineWidth(lineWidth);
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);
			glColor3f(color->r, color->g, color->b);
			glBegin(GL_LINE_LOOP);
				glVertex2f(-lado / 2, -altura / 2);
				glVertex2f(lado / 2, -altura / 2);
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
			glTranslatef(position->x, position->y, position->z);
			glRotatef(angle, 0, 1, 0);
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
	Camera(float px, float py, float pz){
		this->position = new Vektor3(px, py, pz);
		this->lookAt = new Vektor3(0, 0, 0);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	Camera(float px, float py, float pz, float lx, float ly, float lz) {
		this->position = new Vektor3(px, py, pz);
		this->lookAt = new Vektor3(lx, ly, lz);
		this->up = new Vektor3(0, 1, 0);
		this->angleY = 0;
		this->angleZ = 0;
	}
	void update(){
		gluLookAt(position->x, position->y, position->z, lookAt->x, lookAt->y, lookAt->z, up->x, up->y, up->z);
	}
	void setObjective(Vektor3 *pos, float distance, float angle){
		lookAt->copy(pos);
		position->copy(pos);
		position->y += 20;
		position->x = position->x + distance * sin(angle*DEG2RAD);
		position->z = position->z + distance * cos(angle*DEG2RAD);
	}
};