

// #include<stdio.h>
// #include<stdlib.h>
// #include<math.h>

// #include <windows.h>
// #include <GL/glut.h>

// #define pi (2*acos(0.0))

// double cameraHeight;
// double cameraAngle;
// int drawgrid;
// int drawaxes;
// double angle;

// struct point
// {
// 	double x,y,z;
// };


// void drawAxes()
// {
// 	if(drawaxes==1)
// 	{
// 		glColor3f(1.0, 1.0, 1.0);
// 		glBegin(GL_LINES);{
// 			glVertex3f( 100,0,0);
// 			glVertex3f(-100,0,0);

// 			glVertex3f(0,-100,0);
// 			glVertex3f(0, 100,0);

// 			glVertex3f(0,0, 100);
// 			glVertex3f(0,0,-100);
// 		}glEnd();
// 	}
// }


// void drawGrid()
// {
// 	int i;
// 	if(drawgrid==1)
// 	{
// 		glColor3f(0.6, 0.6, 0.6);	//grey
// 		glBegin(GL_LINES);{
// 			for(i=-8;i<=8;i++){

// 				if(i==0)
// 					continue;	//SKIP the MAIN axes

// 				//lines parallel to Y-axis
// 				glVertex3f(i*10, -90, 0);
// 				glVertex3f(i*10,  90, 0);

// 				//lines parallel to X-axis
// 				glVertex3f(-90, i*10, 0);
// 				glVertex3f( 90, i*10, 0);
// 			}
// 		}glEnd();
// 	}
// }

// void drawSquare(double a)
// {
//     //glColor3f(1.0,0.0,0.0);
// 	glBegin(GL_QUADS);{
// 		glVertex3f( a, a,2);
// 		glVertex3f( a,-a,2);
// 		glVertex3f(-a,-a,2);
// 		glVertex3f(-a, a,2);
// 	}glEnd();
// }


// void drawCircle(double radius,int segments)
// {
//     int i;
//     struct point points[100];
//     glColor3f(0.7,0.7,0.7);
//     //generate points
//     for(i=0;i<=segments;i++)
//     {
//         points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
//         points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
//     }
//     //draw segments using generated points
//     for(i=0;i<segments;i++)
//     {
//         glBegin(GL_LINES);
//         {
// 			glVertex3f(points[i].x,points[i].y,0);
// 			glVertex3f(points[i+1].x,points[i+1].y,0);
//         }
//         glEnd();
//     }
// }

// void drawCone(double radius,double height,int segments)
// {
//     int i;
//     double shade;
//     struct point points[100];
//     //generate points
//     for(i=0;i<=segments;i++)
//     {
//         points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
//         points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
//     }
//     //draw triangles using generated points
//     for(i=0;i<segments;i++)
//     {
//         //create shading effect
//         if(i<segments/2)shade=2*(double)i/(double)segments;
//         else shade=2*(1.0-(double)i/(double)segments);
//         glColor3f(shade,shade,shade);

//         glBegin(GL_TRIANGLES);
//         {
//             glVertex3f(0,0,height);
// 			glVertex3f(points[i].x,points[i].y,0);
// 			glVertex3f(points[i+1].x,points[i+1].y,0);
//         }
//         glEnd();
//     }
// }


// void drawSphere(double radius,int slices,int stacks)
// {
// 	struct point points[100][100];
// 	int i,j;
// 	double h,r;
// 	//generate points
// 	for(i=0;i<=stacks;i++)
// 	{
// 		h=radius*sin(((double)i/(double)stacks)*(pi/2));
// 		r=radius*cos(((double)i/(double)stacks)*(pi/2));
// 		for(j=0;j<=slices;j++)
// 		{
// 			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
// 			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
// 			points[i][j].z=h;
// 		}
// 	}
// 	//draw quads using generated points
// 	for(i=0;i<stacks;i++)
// 	{
//         glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
// 		for(j=0;j<slices;j++)
// 		{
// 			glBegin(GL_QUADS);{
// 			    //upper hemisphere
// 				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
// 				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
// 				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
// 				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
//                 //lower hemisphere
//                 glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
// 				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
// 				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
// 				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
// 			}glEnd();
// 		}
// 	}
// }


// void drawSS()
// {
//     glColor3f(1,0,0);
//     drawSquare(20);

//     glRotatef(angle,0,0,1);
//     glTranslatef(110,0,0);
//     glRotatef(2*angle,0,0,1);
//     glColor3f(0,1,0);
//     drawSquare(15);

//     glPushMatrix();
//     {
//         glRotatef(angle,0,0,1);
//         glTranslatef(60,0,0);
//         glRotatef(2*angle,0,0,1);
//         glColor3f(0,0,1);
//         drawSquare(10);
//     }
//     glPopMatrix();

//     glRotatef(3*angle,0,0,1);
//     glTranslatef(40,0,0);
//     glRotatef(4*angle,0,0,1);
//     glColor3f(1,1,0);
//     drawSquare(5);
// }

// void keyboardListener(unsigned char key, int x,int y){
// 	switch(key){

// 		case '1':
// 			drawgrid=1-drawgrid;
// 			break;

// 		default:
// 			break;
// 	}
// }


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			cameraHeight -= 3.0;
			break;
		case GLUT_KEY_UP:		// up arrow key
			cameraHeight += 3.0;
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


// void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
// 	switch(button){
// 		case GLUT_LEFT_BUTTON:
// 			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
// 				drawaxes=1-drawaxes;
// 			}
// 			break;

// 		case GLUT_RIGHT_BUTTON:
// 			//........
// 			break;

// 		case GLUT_MIDDLE_BUTTON:
// 			//........
// 			break;

// 		default:
// 			break;
// 	}
// }



// void display(){

// 	//clear the display
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glClearColor(0,0,0,0);	//color black
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 	/********************
// 	/ set-up camera here
// 	********************/
// 	//load the correct matrix -- MODEL-VIEW matrix
// 	glMatrixMode(GL_MODELVIEW);

// 	//initialize the matrix
// 	glLoadIdentity();

// 	//now give three info
// 	//1. where is the camera (viewer)?
// 	//2. where is the camera looking?
// 	//3. Which direction is the camera's UP direction?

// 	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
// 	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
// 	gluLookAt(0,0,200,	0,0,0,	0,1,0);


// 	//again select MODEL-VIEW
// 	glMatrixMode(GL_MODELVIEW);


// 	/****************************
// 	/ Add your objects from here
// 	****************************/
// 	//add objects

// 	drawAxes();
// 	drawGrid();

//     //glColor3f(1,0,0);
//     //drawSquare(10);

//     drawSS();

//     //drawCircle(30,24);

//     //drawCone(20,50,24);

// 	//drawSphere(30,24,20);




// 	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
// 	glutSwapBuffers();
// }


// void animate(){
// 	angle+=0.05;
// 	//codes for any changes in Models, Camera
// 	glutPostRedisplay();
// }

// void init(){
// 	//codes for initialization
// 	drawgrid=0;
// 	drawaxes=1;
// 	cameraHeight=150.0;
// 	cameraAngle=1.0;
// 	angle=0;

// 	//clear the screen
// 	glClearColor(0,0,0,0);

// 	/************************
// 	/ set-up projection here
// 	************************/
// 	//load the PROJECTION matrix
// 	glMatrixMode(GL_PROJECTION);

// 	//initialize the matrix
// 	glLoadIdentity();

// 	//give PERSPECTIVE parameters
// 	gluPerspective(80,	1,	1,	1000.0);
// 	//field of view in the Y (vertically)
// 	//aspect ratio that determines the field of view in the X direction (horizontally)
// 	//near distance
// 	//far distance
// }

// int main(int argc, char **argv){
// 	glutInit(&argc,argv);
// 	glutInitWindowSize(500, 500);
// 	glutInitWindowPosition(0, 0);
// 	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

// 	glutCreateWindow("My OpenGL Program");

// 	init();

// 	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

// 	glutDisplayFunc(display);	//display callback function
// 	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

// 	glutKeyboardFunc(keyboardListener);
// 	glutSpecialFunc(specialKeyListener);
// 	glutMouseFunc(mouseListener);

// 	glutMainLoop();		//The main loop of OpenGL

// 	return 0;
// }


// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////////


// /*
//  * GLUT Shapes Demo
//  *
//  * Written by Nigel Stewart November 2003
//  *
//  * This program is test harness for the sphere, cone
//  * and torus shapes in GLUT.
//  *
//  * Spinning wireframe and smooth shaded shapes are
//  * displayed until the ESC or q key is pressed.  The
//  * number of geometry stacks and slices can be adjusted
//  * using the + and - keys.
//  */
// #include<windows.h>
// #ifdef __APPLE__
// #include <GLUT/glut.h>
// #else
// #include <GL/glut.h>
// #endif

// #include <stdlib.h>

// static int slices = 16;
// static int stacks = 16;

// /* GLUT callback Handlers */

// static void resize(int width, int height)
// {
//     const float ar = (float) width / (float) height;

//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

//     glMatrixMode(GL_MODELVIEW);

//     glPushMatrix();
//         glTranslated(-2.4,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidSphere(1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(0,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidCone(1,1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(2.4,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidTorus(0.2,0.8,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(-2.4,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireSphere(1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(0,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireCone(1,1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(2.4,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireTorus(0.2,0.8,slices,stacks);
//     glPopMatrix();

//     glutSwapBuffers();
// }glLoadIdentity() ;
// }

// static void display(void)
// {
//     const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
//     const double a = t*90.0;

//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glColor3d(1,0,0);

//     glPushMatrix();
//         glTranslated(-2.4,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidSphere(1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(0,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidCone(1,1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(2.4,1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutSolidTorus(0.2,0.8,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(-2.4,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireSphere(1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(0,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireCone(1,1,slices,stacks);
//     glPopMatrix();

//     glPushMatrix();
//         glTranslated(2.4,-1.2,-6);
//         glRotated(60,1,0,0);
//         glRotated(a,0,0,1);
//         glutWireTorus(0.2,0.8,slices,stacks);
//     glPopMatrix();

//     glutSwapBuffers();
// }


// static void key(unsigned char key, int x, int y)
// {
//     switch (key)
//     {
//         case 27 :
//         case 'q':
//             exit(0);
//             break;

//         case '+':
//             slices++;
//             stacks++;
//             break;

//         case '-':
//             if (slices>3 && stacks>3)
//             {
//                 slices--;
//                 stacks--;
//             }
//             break;
//     }

//     glutPostRedisplay();
// }

// static void idle(void)
// {
//     glutPostRedisplay();
// }

// const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
// const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
// const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
// const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
// const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
// const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
// const GLfloat high_shininess[] = { 100.0f };

// /* Program entry point */

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     glutInitWindowSize(640,480);
//     glutInitWindowPosition(10,10);
//     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

//     glutCreateWindow("GLUT Shapes");

//     glutReshapeFunc(resize);
//     glutDisplayFunc(display);
//     glutKeyboardFunc(key);
//     glutIdleFunc(idle);

//     glClearColor(1,1,1,1);
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);

//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LESS);

//     glEnable(GL_LIGHT0);
//     glEnable(GL_NORMALIZE);
//     glEnable(GL_COLOR_MATERIAL);
//     glEnable(GL_LIGHTING);

//     glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
//     glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
//     glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//     glLightfv(GL_LIGHT0, GL_POSITION, light_position);

//     glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
//     glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
//     glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
//     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

//     glutMainLoop();

//     return EXIT_SUCCESS;
// }


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <GL/glut.h>
#include<time.h>
#define pi (2*acos(0.0))
#include <bits/stdc++.h>
using namespace std;

const int windowHeight = 600;
const int windowWidth = 600;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;



struct point
{
	double x,y,z;
};
double speed = 0.005;

int randGen()
{
    srand(time(NULL));
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

public:
    /*
    Circle(centerX){
        centerX = centerX;
    }*/
    Circle(double centerX,double centerY,double radius)
    {
        this->centerX = centerX;
        this->centerY = centerY;
        this->radius = radius;

        double unitVectorX =  (double) ( randGen() % 100 + 1);
        double unitVectorY =  (double) ( randGen() % 100 + 1);
        this->unitDir_x = unitVectorX/sqrt(pow(unitVectorX,2)+pow(unitVectorY,2));
        this->unitDir_y = unitVectorY/sqrt(pow(unitVectorX,2)+pow(unitVectorY,2));
        //cout<<unitVectorX<<" "<<unitVectorY<<endl;
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
};

Circle smallCircle = Circle(-74.0,-74.0,6.0);


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

    double squireSize = 80;

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
    glColor3f(1,1,1);
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
    drawHollowCircle(0,0,50);
    drawHollowCircle(smallCircle.getCenterX(),smallCircle.getCenterY(),smallCircle.getRadius());
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;

	double newCx = smallCircle.getCenterX() + speed*smallCircle.getunitDir_x();
	double newCy = smallCircle.getCenterY() + speed*smallCircle.getunitDir_y();

	smallCircle.setCenter(newCx,newCy);
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//clear the screen
	glClearColor(0,0,0,0);
	//initialize the matrix
	glLoadIdentity();

	gluOrtho2D(-100, 100, -100, 100);

}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(windowHeight, windowWidth);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

