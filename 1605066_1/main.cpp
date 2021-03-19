#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <cstdlib>   // rand and srand
#include <ctime>

#define pi (2*acos(0.0))

using namespace std;

struct point
{
	double x,y,z;
};

class Point3D{
public:
    float x,y,z;
    Point3D(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Point3D(float x,float y,float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float getDotProduct(Point3D B){
        return (x*B.x + y*B.y + z*B.z);
    }
};

const int axisLength = 100;
const int windowHeight = 600;
const int windowWidth = 600;
const float scaling = 1.3;
const float angleScaling = 0.08;

float cameraAngle=10.0;
int drawaxes;
float value = (1/sqrt(2));

const float fullBodyCutOffAngle = 45.0;
float fullBodyAngle = 0.0;
float gunRotateAngle = 0;
float gunUpDownAngle = 0;
float HalfBodyUpDownAngle = 0;

Point3D pos = Point3D(100.0,100.0,0.0);
Point3D u = Point3D(0,0,1);
Point3D r = Point3D(-value,value,0);
Point3D l = Point3D(-value,-value,0);
Point3D center(0,0,0);
Point3D target(0,38,0);
//float moveX = 100, moveY = 100.0, moveZ = 0.0;

void drawAxes()
{
    if(drawaxes==1){
        glBegin(GL_LINES);
        {
		    glColor3f(1.0, 0, 0); //x axis red
			glVertex3f( axisLength,0,0);
			glVertex3f(-axisLength,0,0);

			glColor3f(0, 0, 1);  //y axis blue
			glVertex3f(0,axisLength,0);
			glVertex3f(0,-axisLength,0);

			glColor3f(1,1 , 1);  //z axis white
			glVertex3f(0,0, axisLength);
			glVertex3f(0,0,-axisLength);
		}
		glEnd();
    }

}

void drawPlaneSheet(){
    //glColor3f(0.35, 0.28, 0.38);
    //glColor3f(0.224, 0.216, 0.216);
    glColor3f(0.72, 0.749, 0.8);

    int x = 37;
    int y = 38.5;
    int z = 42;
    //glPointSize(5);
    glBegin(GL_QUADS);{
        glVertex3f(x,y,-z);
        glVertex3f(-x,y,-z);
        glVertex3f(-x,-y,-z);
        glVertex3f(x,-y,-z);

    }
    glEnd();
}

void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        if(i%2==0){
            glColor3f(1,1,1);
        }else{
            glColor3f(0,0,0);
        }
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere

				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere

                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void drawOuterSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		r = 2*radius - r;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
		    if(j%2==0){
                glColor3f(1,1,1);
            }else{
                glColor3f(0,0,0);
            }

			glBegin(GL_QUADS);{

                //lower hemisphere

                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                /*
                //upper hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

                */

			}glEnd();
		}
	}
}


void drawUpperHemiSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        /*
        if(i%2==0){
            glColor3f(1,1,1);
        }else{
            glColor3f(0,0,0);
        }
        */

		for(j=0;j<slices;j++)
		{
		    if(j%2==0){
                glColor3f(1,1,1);
            }else{
                glColor3f(0,0,0);
            }
			glBegin(GL_QUADS);{
			    //upper hemisphere

				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                ///lower hemisphere
                /*
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                */

			}glEnd();
		}
	}
}

void drawLowerHemiSphere(double radius,int slices,int stacks){
struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);

		for(j=0;j<slices;j++)
		{
		    if(j%2==0){
                glColor3f(1,1,1);
            }else{
                glColor3f(0,0,0);
            }
			glBegin(GL_QUADS);{
			    ///upper hemisphere
			    /*
			    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
			    */

                ///lower hemisphere

                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}


void drawCylinder(double radius,int slices,int stacks){
struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=3*radius*sin(((double)i/(double)stacks)*(pi/2));
		//r=radius*cos(((double)i/(double)stacks)*(pi/2));

		r=radius;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);

		for(j=0;j<slices;j++)
		{
		    if(j%2==0){
                glColor3f(1,1,1);
            }else{
                glColor3f(0,0,0);
            }
			glBegin(GL_QUADS);{
			    ///upper hemisphere

			    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);


                ///lower hemisphere

                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void getNexPoistionVector(Point3D *v,int option){

    if(option==1){
        pos.x = pos.x + scaling*v->x;
        pos.y = pos.y + scaling*v->y;
        pos.z = pos.z + scaling*v->z;
    }else if(option==2){
        pos.x = pos.x - scaling*v->x;
        pos.y = pos.y - scaling*v->y;
        pos.z = pos.z - scaling*v->z;
    }

}

void rotateVector(Point3D *L, Point3D *U, float angle){
    Point3D L_prime = Point3D();

    L_prime.x = L->x*cos(pi*angle/180) + U->x*sin(pi*angle/180);
    L_prime.y = L->y*cos(pi*angle/180) + U->y*sin(pi*angle/180);
    L_prime.z = L->z*cos(pi*angle/180) + U->z*sin(pi*angle/180);

    U->x = U->x*cos(pi*angle/180) - L->x*sin(pi*angle/180);
    U->y = U->y*cos(pi*angle/180) - L->y*sin(pi*angle/180);
    U->z = U->z*cos(pi*angle/180) - L->z*sin(pi*angle/180);

    L->x = L_prime.x;   L->y = L_prime.y;   L->z = L_prime.z;
    //cout<<"----------------x: "<<L->x<<" y: "<<L->y<< " z: "<<L->z<<endl;
    //cout<<"------DOT PRODUCT--: "<<l.getDotProduct(u)<<endl;

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1':
			///rotate/LookLeft--->U fixed
			//cameraAngle +=angleScaling;
			rotateVector(&r,&l,cameraAngle);
			cout<<"---rotate/LookLeft\n---DOT PRODUCT--: "<<l.getDotProduct(r)<<endl;
			break;
        case '2':
			///rotate/LookRight --->U fixed
			//cameraAngle -=angleScaling;
			rotateVector(&r,&l,-cameraAngle);
			cout<<"---rotate/LookRight\n---DOT PRODUCT--: "<<l.getDotProduct(r)<<endl;
			break;
        case '3':
            ///--->R fixed
			//cameraAngle +=angleScaling;
			rotateVector(&l,&u,cameraAngle);
			break;
		case '4':
		    ///--->R fixed
			//cameraAngle -=angleScaling;
			rotateVector(&l,&u,-cameraAngle);
			break;
        case '5':
            ///tilt Clockwise--->L fixed
            //cameraAngle +=angleScaling;
			rotateVector(&u,&r,cameraAngle);
			cout<<"---tilt Clockwise\n---DOT PRODUCT--: "<<u.getDotProduct(r)<<endl;
			break;
        case '6':
            ///tilt AntiClockwise--->L fixed
            //cameraAngle -=angleScaling;
			rotateVector(&u,&r,-cameraAngle);
			cout<<"---tilt AntiClockwise\n---DOT PRODUCT--: "<<u.getDotProduct(r)<<endl;
			break;

        case 'q':
            fullBodyAngle += 0.8;
            //cout<<"fullBodyAngle\t:"<<fullBodyAngle<<endl;
            if(fullBodyAngle>fullBodyCutOffAngle){
                fullBodyAngle = fullBodyCutOffAngle;
            }
            break;
        case 'w':
            fullBodyAngle -= 0.8;
            cout<<"fullBodyAngle\t:"<<fullBodyAngle<<endl;
            if(fullBodyAngle<-fullBodyCutOffAngle){
                fullBodyAngle = -fullBodyCutOffAngle;
            }
            break;
        case 'e':
            HalfBodyUpDownAngle += 0.8;
            if(HalfBodyUpDownAngle>fullBodyCutOffAngle){
                HalfBodyUpDownAngle = fullBodyCutOffAngle;
            }
            break;
        case 'r':
            HalfBodyUpDownAngle -= 0.8;
            if(HalfBodyUpDownAngle<-(fullBodyCutOffAngle)){
                HalfBodyUpDownAngle = -(fullBodyCutOffAngle);
            }//
            break;
        case 'a':

            gunUpDownAngle += 0.8;
            if(gunUpDownAngle>fullBodyCutOffAngle){
                gunUpDownAngle = fullBodyCutOffAngle;
            }
            break;
        case 's':
            gunUpDownAngle -= 0.8;
            if(gunUpDownAngle<-(fullBodyCutOffAngle)){
                gunUpDownAngle = -(fullBodyCutOffAngle);
            }
            break;
        case 'd':
            //cout<<"d:"<<gunRotateAngle<<endl;
            gunRotateAngle += 0.8;
            if(gunRotateAngle>fullBodyCutOffAngle){
                gunRotateAngle = fullBodyCutOffAngle;
            }
            break;
        case 'f':
            //cout<<"f:"<<gunRotateAngle<<endl;
            gunRotateAngle -= 0.8;
            if(gunRotateAngle<-fullBodyCutOffAngle){
                gunRotateAngle = -fullBodyCutOffAngle;
            }
            break;



		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
			//pos.y += 2;
			getNexPoistionVector(&l,2);
			break;
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			//pos.y -= 2;
			getNexPoistionVector(&l,1);
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			//pos.x -= 2;
			getNexPoistionVector(&r,1);
			break;
		case GLUT_KEY_LEFT:
			//cameraAngle -= 0.03;
			//pos.x += 2;
			getNexPoistionVector(&r,2);
			break;

		case GLUT_KEY_PAGE_UP:
			//pos.z += 2;
			getNexPoistionVector(&u,1);
			break;
		case GLUT_KEY_PAGE_DOWN:
			//pos.z -= 2;
			getNexPoistionVector(&u,2);
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

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}




void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(pos.x,pos.y,pos.z,    pos.x+l.x,pos.y+l.y,pos.z+l.z,      u.x,u.y,u.z);

    //cout<<"x: "<<pos.x<<" y: "<<pos.y<< " z: "<<pos.z<<endl;
	//cout<<"x: "<<u.x<<" y: "<<u.y<< " z: "<<u.z<<endl;

	drawAxes();

    glPushMatrix();
    {

        glRotatef(90,1,0,0);
        glRotatef(fullBodyAngle,0,1,0);
        //cout<<"fullBodyAngle\t:"<<fullBodyAngle<<endl;
        glPushMatrix();
        {
            if(fullBodyAngle>0.7 || fullBodyAngle<-0.7){
                glRotatef(HalfBodyUpDownAngle*0.8,0,0,1);
            }else if(fullBodyAngle<-0.7){
                glRotatef(-HalfBodyUpDownAngle*0.8,0,0,1);
            }

            drawUpperHemiSphere(15,80,80);
        }
        glPopMatrix();

        glRotatef(HalfBodyUpDownAngle,1,0,0); ///it will work for e/r rotate WRT x axis
        drawLowerHemiSphere(15,80,80);

        glTranslatef(0,0,-20);
        //glRotatef(90,1,0,0);
        glRotatef(gunUpDownAngle,1,0,0); ///it will work for a/s rotate WRT x axis
        glRotatef(gunRotateAngle,0,0,1); ///it will work for d/f rotate WRT own axis
        drawUpperHemiSphere(5,80,80);

        glTranslatef(0,0,-15);
        drawCylinder(5,80,80);

        glTranslatef(0,0,-15);
        drawOuterSphere(5,80,80);

        glRotatef(-90,1,0,0);
        glTranslatef(0,50,0);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
        {
            glVertex3f(center.x,center.y,center.z);
            glVertex3f(target.x,target.y,target.z);
        }
        glEnd();

    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0,100,0);

        glRotatef(90,1,0,0);
        drawPlaneSheet();
    }
    glPopMatrix();
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){

	/*
	drawgrid=0;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	*/
    drawaxes=1;
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	///give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
    //glFrustum(-1,1,-1,1,2,10);
    glMatrixMode(GL_MODELVIEW);

}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowHeight, windowWidth);
	glutInitWindowPosition(600, 150);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Camera-1");

    init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);


    glutMainLoop();
    return 0;
}
