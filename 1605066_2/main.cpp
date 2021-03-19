#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>   // rand and srand
#include <ctime>
#include <time.h>

#define pi (2*acos(0.0))
//#include <bits/stdc++.h>
using namespace std;

const int windowHeight = 600;
const int windowWidth = 600;
const double squireSize = 80;
const int bigCircleRadius = 50;
const int bigCircleCx = 0;
const int bigCircleCy = 0;

const int circleNo = 5;
double speed = 0.0055; ///0.01---0.1
double tempSpeed = 0.0;
const double cutOffLowerSpeed = 0.005;
const double cutOffUpperSpeed = 0.1;
const int bubbleCreationtime = 2500;
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
int circleCreationControl;
int circleIndexNo;
double angle;
float Px,Py;

struct point
{
	double x,y,z;
};


int randGen()
{
    //srand(time(NULL));
    int r = rand();
    //cout<<r<<endl;
    return r;
}
class Circle{
    double centerX;
    double centerY;
    double radius;
    double unitDir_x; ///direction vector
    double unitDir_y; ///direction vector
    bool inSideBigCircle;

public:
    Circle(){}

    Circle(double centerX,double centerY,double radius,double ux,double uy)
    {
        this->inSideBigCircle = false;
        this->centerX = centerX;
        this->centerY = centerY;
        this->radius = radius;

        //double unitVectorX =  (double) ( randGen() % 85 + 1);
        //double unitVectorY =  (double) ( randGen() % 78 + 1);
        double unitVectorX =  ux;
        double unitVectorY =  uy;
        //double unitVectorX =  (double) (90);
        //double unitVectorY =  (double) (40);
        this->unitDir_x = unitVectorX/sqrt(pow(unitVectorX,2)+pow(unitVectorY,2));
        this->unitDir_y = unitVectorY/sqrt(pow(unitVectorX,2)+pow(unitVectorY,2));
        cout<<unitVectorX<<"\t"<<unitVectorY<<endl;
    }

    void setCenter(double centerX,double centerY){
        this->centerX = centerX;
        this->centerY = centerY;
    }

    void setRadius(double radius){
        this->radius = radius;
    }

    double getRadius(){
        return radius;
    }

    double getCenterX(){
        return centerX;
    }

    double getCenterY(){
        return centerY;
    }

    double getunitDir_x(){
        return unitDir_x;
    }

    double getunitDir_y(){
        return unitDir_y;
    }

    void setunitDir_x(double x){
        this->unitDir_x = x;
    }

    void setunitDir_y(double y){
        this->unitDir_y = y;
    }

    void setInSideBigCircle(bool state){
        this->inSideBigCircle = state;
    }

    bool getInSideBigCircle(){
        return this->inSideBigCircle;
    }
};

//Circle smallCircles[circleNo] = Circle(-74.0,-74.0,6.0);
static Circle smallCircles[circleNo];
/// Circle smallCircle = Circle(-74.0,-74.0,6.0);

void drawContact(float x,float y)
{
    glColor3f(1.0,1.0,1.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    {
        glVertex2f(x,y);
    }
    glEnd();
}
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}

void drawSquare(){
    glColor3f(0, 1.0, 0);
    glBegin(GL_LINES);
    {
        glVertex3f(squireSize,squireSize,0);
        glVertex3f(-squireSize,squireSize,0);

        glVertex3f(-squireSize,squireSize,0);
        glVertex3f(-squireSize,-squireSize,0);

        glVertex3f(-squireSize,-squireSize,0);
        glVertex3f(squireSize,-squireSize,0);

        glVertex3f(squireSize,-squireSize,0);
        glVertex3f(squireSize,squireSize,0);
    }
    glEnd();

}

void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100]; ///array of 2D point
    glColor3f(1,1,1);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
    //glColor3f(1,1,1);
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * pi;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}


void collisionInSquare(Circle *cir){
    double Cx = cir->getCenterX();
    double Cy = cir->getCenterY();
    double Ux = cir->getunitDir_x();
    double Uy = cir->getunitDir_y();
    double r = cir->getRadius();

    //cout<<"Unit:"<<abs(Cx)+r<<" "<<squireSize<<endl;

    if(abs(Cx)+r>=squireSize){
        //printf("I AM IN--\n");
        cir->setunitDir_x(-Ux);
    }
    else if(abs(Cy)+r>=squireSize){
        cir->setunitDir_y(-Uy);
    }
}



void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


///ami nicher line gula kete dibo
void drawLine(float x1,float y1,float x2,float y2)
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINES);
    {
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
    }
    //delay(10);
    glEnd();

}

double* getNormal_unit_Vector(double x1,double y1,double touchCx,double touchCy){
    static double arr[2];
    double Nx = x1 - touchCx; ///.final-initial point  /// touch---->(x1,y1)
    double Ny = y1 - touchCy;
    //double magnitude = sqrt(pow(Nx,2)+pow(Ny,2));
    double magnitude = sqrt(Nx*Nx+Ny*Ny);
    Nx = Nx/magnitude; ///unit Normal Vector
    Ny = Ny/magnitude; ///unit Normal Vector
    arr[0] = Nx;
    arr[1] = Ny;
    return arr;
}

double* getReflectionVector(double ax,double ay,double Nx,double Ny){
    static double arr[2];
    double Rx = ax - 2*Nx*(ax*Nx+ay*Ny);
    double Ry = ay - 2*Ny*(ax*Nx+ay*Ny);

    //double r_magnitude = sqrt(pow(Rx,2)+pow(Ry,2));
    double r_magnitude = sqrt(Rx*Rx+Ry*Ry);
    Rx = Rx/r_magnitude;
    Ry = Ry/r_magnitude;
    arr[0] = Rx;
    arr[1] = Ry;
    return arr;

}

void findPointofConduct(Circle *s_cir){

    double s_Cx = s_cir->getCenterX();
    double s_Cy = s_cir->getCenterY();
    double s_r = s_cir->getRadius();

    float r1_r2 = abs(s_r - bigCircleRadius);
    float centerDistance = sqrt(pow(abs(s_Cx-bigCircleCx),2) + pow(abs(s_Cy-bigCircleCy),2));

    float theta = atan(s_Cy/s_Cx);
    //cout<<"theta:"<<theta<<endl;

    if(s_cir->getInSideBigCircle() && centerDistance>=r1_r2){
        //cout<<"-----TOUCHed BIG CIRCLE-----"<<endl;
        float touchCx = bigCircleRadius * cos(theta);
        float touchCy = bigCircleRadius * sin(theta);

        ///------NORMAL VECTOR------//
        double * NormalVector = getNormal_unit_Vector(bigCircleCx,bigCircleCy,touchCx,touchCy);
        double Nx = NormalVector[0];
        double Ny = NormalVector[1];
        /*
        double Nx = bigCircleCx - touchCx; ///.final-initial point
        double Ny = bigCircleCy - touchCy;
        double magnitude = sqrt(pow(Nx,2)+pow(Ny,2));
        Nx = Nx/magnitude; ///unit Normal Vector
        Ny = Ny/magnitude; ///unit Normal Vector
        */

        ///--------Reflection Vector-------
        double ax = s_cir->getunitDir_x();
        double ay = s_cir->getunitDir_y();

        double * reflectionVector = getReflectionVector(ax,ay,Nx,Ny);
        double Rx = reflectionVector[0];
        double Ry = reflectionVector[1];
        /*
        double Rx = ax - 2*Nx*(ax*Nx+ay*Ny);
        double Ry = ay - 2*Ny*(ax*Nx+ay*Ny);

        double r_magnitude = sqrt(pow(Rx,2)+pow(Ry,2));
        Rx = Rx/r_magnitude;
        Ry = Ry/r_magnitude;
        */
        s_cir->setunitDir_x(Rx);
        s_cir->setunitDir_y(Ry);
    }

}

void smallCircleInBigCircle(Circle *s_cir){
    double s_Cx = s_cir->getCenterX();
    double s_Cy = s_cir->getCenterY();
    double s_r = s_cir->getRadius();

    float r1_r2 = abs(s_r - bigCircleRadius);

    float centerDistance = sqrt(pow(abs(s_Cx-bigCircleCx),2) + pow(abs(s_Cy-bigCircleCy),2));

    if(centerDistance<r1_r2){
        //cout<<"INSIDE BIG CIRCLE"<<endl;
        s_cir->setInSideBigCircle(true);
        //cout<<s_cir->getInSideBigCircle()<<endl;
    }
}


void collisionInBigCircle(Circle *cir){

    double Cx = cir->getCenterX();
    double Cy = cir->getCenterY();
    double Ux = cir->getunitDir_x();
    double Uy = cir->getunitDir_y();
    double r = cir->getRadius();

    for(int i=0;i<circleNo;i++){
        Circle circle2 = smallCircles[i];
        double Cx2 = circle2.getCenterX();
        double Cy2 = circle2.getCenterY();
        double Ux2 = circle2.getunitDir_x();
        double Uy2 = circle2.getunitDir_y();
        double r2 = circle2.getRadius();

        if(cir->getInSideBigCircle() && circle2.getInSideBigCircle()){

            if(Cx==Cx2 && Cy==Cy2 && Ux==Ux2 && Uy==Uy2){
                break;
            }
            else{
                float centerDistance = sqrt((Cx-Cx2)*(Cx-Cx2) + (Cy-Cy2)*(Cy-Cy2));
                //cout<<i<<"-->centerDistance:"<<" "<<centerDistance<<endl;
                float r1_r2 = abs(r + r2);
                //cout<<"CC: "<<centerDistance<<endl;
                if(centerDistance<=r1_r2+1.0){
                    Px = (Cx+Cx2)/2;
                    Py = (Cy+Cy2)/2;

                    double * NormalVector  = getNormal_unit_Vector(Cx2,Cy2,Px,Py);
                    double Nx = NormalVector[0];
                    double Ny = NormalVector[1];
                    ///----collision-----///
                    //cout<<"collision"<<endl;
                    ///--------Reflection Vector-------
                    double ax = circle2.getunitDir_x();
                    double ay = circle2.getunitDir_y();

                    double * reflectionVector = getReflectionVector(ax,ay,Nx,Ny);
                    double Rx = reflectionVector[0];
                    double Ry = reflectionVector[1];

                    //cout<<Rx<<endl;
                    smallCircles[i].setunitDir_x(Rx);
                    //cout<<circle2.getunitDir_x()<<endl;
                    smallCircles[i].setunitDir_y(Ry);


                    ///----------------------
                    double ax2 = cir->getunitDir_x();
                    double ay2 = cir->getunitDir_y();

                    double * reflectionVector2 = getReflectionVector(ax2,ay2,-Nx,-Ny);
                    double Rx2 = reflectionVector2[0];
                    double Ry2 = reflectionVector2[1];
                    cir->setunitDir_x(Rx2);
                    cir->setunitDir_y(Ry2);
                }
            }
        }

    }
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case 'p':
			if(speed>0){
                tempSpeed = speed;
                speed = 0;
                cout<<"PAUSED"<<endl;
			}
            else{
                speed = tempSpeed;
                cout<<"RESUMED"<<endl;
            }
			break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:
            //down arrow key
			speed -= 0.001;
			if(speed<cutOffLowerSpeed)
                speed = cutOffLowerSpeed;
            cout<<"Speed Down:"<<speed<<endl;
			break;
		case GLUT_KEY_UP:		// up arrow key
			speed += 0.001;
			if(speed>cutOffUpperSpeed)
                speed=cutOffUpperSpeed;
            cout<<"Speed Up:"<<speed<<endl;
			break;

		case GLUT_KEY_RIGHT:
			cameraAngle += 0.03;
			break;
		case GLUT_KEY_LEFT:
			cameraAngle -= 0.03;
			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}





void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15,0.05,0.15,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);\
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	//initialize the matrix
	glLoadIdentity();

    drawSquare();

    //drawCircle(45,70);
    glColor3f(1,1,0);
    drawHollowCircle(bigCircleCx,bigCircleCy,bigCircleRadius);

   // drawHollowCircle(smallCircle.getCenterX(),smallCircle.getCenterY(),smallCircle.getRadius());
    glColor3f(1,0.40,.20);

    if(circleCreationControl%bubbleCreationtime==0 && circleIndexNo<circleNo){
        //cout<<"circleIndexNo"<<circleIndexNo<<endl;
        circleIndexNo++;
    }


        for(int i=0; i<circleIndexNo;i++){
            //cout<<"i:"<<i<<endl;

             drawHollowCircle(smallCircles[i].getCenterX(),smallCircles[i].getCenterY(),
                         smallCircles[i].getRadius());
            //collisionInSquare(smallCircles[i]);
            float angle = atan2(smallCircles[i].getunitDir_y(),smallCircles[i].getunitDir_x());
            float newPoint_x = smallCircles[i].getCenterX()+6*cos(angle);
            float newPoint_y = smallCircles[i].getCenterY()+6*sin(angle);

            drawLine(smallCircles[i].getCenterX(),smallCircles[i].getCenterY(),newPoint_x,newPoint_y);
            drawContact(Px,Py);
        }
        circleCreationControl++;


    /*
    for(int i=0;i<circleNo;i++){
        drawHollowCircle(smallCircles[i].getCenterX(),smallCircles[i].getCenterY(),smallCircles[i].getRadius());
        //collisionInSquare(smallCircles[i]);
        float angle = atan2(smallCircles[i].getunitDir_y(),smallCircles[i].getunitDir_x());
        float newPoint_x = smallCircles[i].getCenterX()+6*cos(angle);
        float newPoint_y = smallCircles[i].getCenterY()+6*sin(angle);

        drawLine(smallCircles[i].getCenterX(),smallCircles[i].getCenterY(),newPoint_x,newPoint_y);

    }

    drawContact(Px,Py);
    */

	glutSwapBuffers();
}



void animate(){
	/*
	double newCx = smallCircle.getCenterX() + speed*smallCircle.getunitDir_x();
	double newCy = smallCircle.getCenterY() + speed*smallCircle.getunitDir_y();

	smallCircle.setCenter(newCx,newCy);
	//codes for any changes in Models, Camera
	*/
	for(int i=0;i<circleIndexNo;i++){
        double newCx = smallCircles[i].getCenterX() + speed*smallCircles[i].getunitDir_x();
        double newCy = smallCircles[i].getCenterY() + speed*smallCircles[i].getunitDir_y();
        //cout<<"Unitx: "<<smallCircles[i].getunitDir_x()<<endl;
        smallCircles[i].setCenter(newCx,newCy);
        collisionInSquare(&smallCircles[i]);
        smallCircleInBigCircle(&smallCircles[i]);
        findPointofConduct(&smallCircles[i]);
        collisionInBigCircle(&smallCircles[i]);
        //cout<<"HURRA:"<<smallCircles[i].getunitDir_x()<<endl;
	}
	glutPostRedisplay();
}

void init(){
    circleIndexNo = 0;
    circleCreationControl = 0;
    //clear the screen
	glClearColor(0,0,0,0);
	//initialize the matrix
	glLoadIdentity();

	gluOrtho2D(-100, 100, -100, 100);

    srand(time(0));

    for(int i=0;i<circleNo;i++)
    {
        double ux = (double) ( randGen() % 85 + 1);
        double uy =  (double) ( randGen() % 78 + 1);
        smallCircles[i]=Circle(-74.0,-74.0,6.0,ux,uy);
    }
}


int main(int argc, char **argv){

    glutInit(&argc,argv);
	glutInitWindowSize(windowHeight, windowWidth);
	glutInitWindowPosition(700, 200);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("Bubble Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
