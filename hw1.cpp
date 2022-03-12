#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

float shift = 0;                        // variable used to move the house right and left
float shift2 = 0;                       // variable to move the house up and down
float a = 0.5, b = 0.5, c = 0.5;        // variable that used in scaling 
float speed = 0.5;
int x = -1, y = -1, z = -1;
float rotationArray[3] = { 0,0,0 };
int axis = -1;
int flag = 1;                           // used to disable rotation
float _angle = 45.0f;


/// <summary>
/// Method that handles keypress to take user input to make scaling,rotating and translation actions
/// esc exits program
/// l, r, u, d buttons moves house left,right,up and down
/// b and s buttons makes house bigger and smaller
/// p key stops housee's rotation and continues if pressed again
/// </summary>
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case 27:            //exits program when user prints esc
        exit(0);

    case 'p':   case 'P':        // pause and continue
        flag *= -1;
        break;

    case 'l':  case 'L':         //move left
        shift -= 0.1;
        glutPostRedisplay();
        break;

    case 'r':  case 'R':         //move right
        shift += 0.1;
        glutPostRedisplay();
        break;

    case 'u': case 'U':           //move up
        shift2 += 0.1;
        glutPostRedisplay();
        break;

    case 'd':  case 'D':          //move down
        shift2 -= 0.1;
        glutPostRedisplay();
        break;

    case 'b':  case 'B':         //bigger
        if (a < 1.25) {
            a += 0.01;
            b += 0.01;
            c += 0.01;
        }
        break;

    case 's':   case 'S':        //smaller
        if (a >= 0.4) {
            a -= 0.01;
            b -= 0.01;
            c -= 0.01;
        }
        break;
    }
}

/// <summary>
/// Method to control house rotation with buttons on the keyboard (left,right,up,down arrow keys)
/// </summary>
void handleKeyboardButtons(int button, int x, int y)
{
    switch (button)
    {
    case GLUT_KEY_LEFT:     //rotate to left
       
        axis = 0;
        x *= -1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:    //rotate to right
        axis = 1;
        y *= -1;
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:       //rotate to up
        axis = 2;
        z *= -1;
        
        glutPostRedisplay();
        break;
    }
    glutPostRedisplay();
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);          //Automatically normalize normals
    glShadeModel(GL_SMOOTH);         //Enable smooth shading
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

/// <summary>
/// Method to rotate the house
/// </summary>
void rotateHouse() {
    if (flag == 1) {
        switch (axis)
        {
        case 0: rotationArray[0] += (speed * x);
            break;
        case 1: rotationArray[1] += (speed * y);
            break;
        case 2: rotationArray[2] += (speed * z);
            break;
        }
    }
    glRotatef(rotationArray[0], 1.0, 0.0, 0.0);
    glRotatef(rotationArray[1], 0.0, 1.0, 0.0);
    glRotatef(rotationArray[2], 0.0, 0.0, 1.0);
}



/// <summary>
/// This methods draws house to the screen with simply drawing rectangles and triangles
/// Rotating,scaling and translation function calls are also done in this method
/// </summary>
void drawHouse() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     //clear color buffer bits
    glClearColor(0.196078, 0.6, 0.8, 0.0);                  //set background color
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, -1.5f, -2.0f);
    glPushMatrix();
    glTranslatef(1.0f, 1.0f, 0.0f);
    rotateHouse();          //rotate house
    glScalef(a, b, c);      // scale the house with parameters
   
  
    //front rectangle
    glColor3f(0.91, 0.76, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.1+shift2, 0.0);
    glVertex3f(0.9 + shift, 1.1+shift2, 0.0);
    glVertex3f(0.9 + shift, 1.575+shift2, 0.0);
    glVertex3f(0.2 + shift, 1.575+shift2, 0.0);
    glEnd();

    //back rectange
    glColor3f(0.91, 0.76, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.5);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.5);
    glEnd();

    //left rectangle
    glColor3f(0.91, 0.76, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.2 + shift, 1.1 + shift2, 0.0);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.5);
    glEnd();

    //right rectangle
    glColor3f(0.91, 0.76, 0.65);
    glBegin(GL_POLYGON);
    glVertex3f(0.9 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.1 + shift2, 0.0);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.5);
    glEnd();


    //base of the house
    glColor3f(0.647059, 0.164706, 0.164706);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.1 + shift2, 0.0);
    glVertex3f(0.2 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.1 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.1 + shift2, 0.0);
    glEnd();

    //left triangle for roof
    glColor3f( 0.647059 ,0.164706, 0.164706);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.8 + shift2, 0.25);
    glEnd();

    //right triangle for roof
    glColor3f(0.647059, 0.164706, 0.164706);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.5);
    glVertex3f(0.2 + shift, 1.8 + shift2, 0.25);
    glEnd();

    // roof 
    glColor3f(0.647059, 0.164706, 0.164706);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.0);
    glVertex3f(0.9 + shift, 1.8 + shift2, 0.25);
    glVertex3f(0.2 + shift, 1.8 + shift2, 0.25);
    glEnd();

    //back roof
    glColor3f(0.647059, 0.164706, 0.164706);
    glBegin(GL_POLYGON);
    glVertex3f(0.2 + shift, 1.575 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.575 + shift2, 0.5);
    glVertex3f(0.9 + shift, 1.8 + shift2, 0.25);
    glVertex3f(0.2 + shift, 1.8 + shift2, 0.25);
    glEnd();

    
    // door of the house
    glColor3f(.15, 0.3, .3);
    glBegin(GL_POLYGON);
    glVertex3f(0.47 + shift, 1.105 + shift2, 0.51);
    glVertex3f(0.65 + shift, 1.105 + shift2, 0.51);
    glVertex3f(0.65 + shift, 1.46 + shift2, 0.51);
    glVertex3f(0.47 + shift, 1.46 + shift2, 0.51);
    glEnd();

   
    // window
    glColor3f(0.372549, 0.623529, 0.623529);
    glBegin(GL_POLYGON);
    glVertex3f(0.72 + shift, 1.25 + shift2, 0.51);
    glVertex3f(0.83 + shift, 1.25 + shift2, 0.51);
    glVertex3f(0.83 + shift, 1.4 + shift2, 0.51);
    glVertex3f(0.72 + shift, 1.4 + shift2, 0.51);
    glEnd();

    //window
    glColor3f(0.372549 , 0.623529 , 0.623529);
    glBegin(GL_POLYGON);
    glVertex3f(0.27 + shift, 1.25 + shift2, 0.51);
    glVertex3f(0.38 + shift, 1.25 + shift2, 0.51);
    glVertex3f(0.38 + shift, 1.4 + shift2, 0.51);
    glVertex3f(0.27 + shift, 1.4 + shift2, 0.51);
    glEnd();


    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    _angle += 0.1f;
    if (_angle > 360) {
        _angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("3D House with Rotating,Scaling and Translation -Esra Nur Arıcan-");
    initRendering();
    glutDisplayFunc(drawHouse);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleKeyboardButtons);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
