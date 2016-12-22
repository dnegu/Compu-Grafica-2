/*
 * (c) Copyright 1993, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED 
 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
/*  bezmesh.c
 *  This program renders a wireframe Bezier surface,
 *  using two-dimensional evaluators.
 */

/*
Nombre: David Rolando Neyra Gutierrez
Curso: Computacion Grafica
Escuela: Ciencia de la Computacion
*/
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
using namespace std;

float xClick,yClick;

GLfloat ctrlpoints[4][4][3] = {
    {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}}, 
    {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},{0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}}, 
    {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},{0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}}, 
    {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},{0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

struct MyPos
{
		int posx;
		int posy;

		MyPos(int posx, int posy){
			this -> posx = posx;
			this -> posy = posy;
		}
};

void display(void)
{
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix ();
    glRotatef(85.0, 1.0, 1.0, 1.0);
    for (j = 0; j <= 8; j++) {
	glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 30; i++)
	    glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 30; i++)
	    glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
	glEnd();
    }
    glPopMatrix ();
    
    glFlush();
    glutSwapBuffers();
}

void myinit(void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
	    0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
	glOrtho(-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w, 
	    4.0*(GLfloat)h/(GLfloat)w, -4.0, 4.0);
    else
	glOrtho(-4.0*(GLfloat)w/(GLfloat)h, 
	    4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle()
{
	display();
}

void keyboard(unsigned char key, int x, int y)
{
   cout<<key;
	switch(key)
	{
	   case 'W':
		case 'w':
		   ctrlpoints[0][0][0]+=0.1;
		   ctrlpoints[0][0][1]+=0.1;
		   ctrlpoints[0][0][2]+=0.1;
			myinit();
			break;
		case 'S':
		case 's':
			ctrlpoints[0][0][0]-=0.1;
		   ctrlpoints[0][0][1]-=0.1;
		   ctrlpoints[0][0][2]-=0.1;
			myinit();
			break;
		case 'A':
		case 'a':
			ctrlpoints[3][3][0]+=0.1;
		   ctrlpoints[3][3][1]+=0.1;
		   ctrlpoints[3][3][2]+=0.1;
			myinit();
			break;
		case 'D':
		case 'd':
			ctrlpoints[3][3][0]-=0.1;
		   ctrlpoints[3][3][1]-=0.1;
		   ctrlpoints[3][3][2]-=0.1;
			myinit();
			break;
		case 'Z':
		case 'z':
			ctrlpoints[3][0][0]+=0.1;
		   ctrlpoints[3][0][1]+=0.1;
		   ctrlpoints[3][0][2]+=0.1;
			myinit();
			break;
		case 'X':
		case 'x':
			ctrlpoints[3][0][0]-=0.1;
		   ctrlpoints[3][0][1]-=0.1;
		   ctrlpoints[3][0][2]-=0.1;
			myinit();
			break;
		case 'C':
		case 'c':
			ctrlpoints[0][3][0]+=0.1;
		   ctrlpoints[0][3][1]+=0.1;
		   ctrlpoints[0][3][2]+=0.1;
			myinit();
			break;
		case 'V':
		case 'v':
			ctrlpoints[0][3][0]-=0.1;
		   ctrlpoints[0][3][1]-=0.1;
		   ctrlpoints[0][3][2]-=0.1;
			myinit();
			break;
		
		case 27:	// escape
			exit(0);
			break;
	}
	glutSwapBuffers();
}

MyPos distancia(){

	float leng=0,dist;
	int posx,posy;
	dist=abs(sqrt(pow(ctrlpoints[0][0][0]+xClick,2) + pow(ctrlpoints[0][0][1]+yClick,2)));
	leng = dist;
	posx = 0;
	posy = 0;

	for (int i=0; i<4;i++){
		for (int j=0 ; j<4; j++){
			dist=abs(sqrt(pow(ctrlpoints[i][j][0]+xClick,2) + pow(ctrlpoints[i][j][1]+yClick,2)));
			if(dist<=leng){
				leng = dist;
				posx = i;
				posy = j;
			}
		}
	}

	MyPos pos(posx,posy);
	return pos;
}

void raton(int button, int state, int x, int y)
{
    	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){ 
			xClick = (x-250.0)/62.0;
			yClick = (250.0-y)/62.0;
			MyPos pos = distancia();
			ctrlpoints[pos.posx][pos.posy][0]=xClick;
			ctrlpoints[pos.posx][pos.posy][1]=yClick;
			myinit();
		}


	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Malla movible");  
    myinit();     
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(raton);
    glutMainLoop();
    return 0;
}
