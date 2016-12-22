/*
Nombre: David Rolando Neyra Gutierrez
Curso: Computacion Grafica
Escuela: Ciencia de la Computacion
*/
#include "punto.h"

vector<Punto> puntos;
Punto * centro = NULL;

void raton(int boton,int estado,int x,int y)
{
  if(boton == GLUT_LEFT_BUTTON)
  {
    if(estado == GLUT_UP)
    { 
      band = false;
      punto.x = x;
      punto.y = ALTO-y;
      puntos.push_back(punto);

      glBegin(GL_POINTS);
        glVertex2d(punto.x,punto.y);
      glEnd();
      cout<<punto.x<<" "<<punto.y<<endl;
    }
  }
  glutPostRedisplay();
}


Punto * PuntoCentral()
{
  int tam = puntos.size();
  int xMin = puntos[0].x,xMax=puntos[0].x,yMin = puntos[0].y,yMax = puntos[0].y;

  for(int i=1;i<tam;i++){
    if(puntos[i].x <= xMin) xMin = puntos[i].x;
    else if(puntos[i].x >= xMax) xMax = puntos[i].x; 

    if(puntos[i].y <= yMin) yMin = puntos[i].y;
    else if(puntos[i].y >= yMax) yMax = puntos[i].y; 
  }

  cout<<endl;

  Punto * res =new Punto;
  
  (*res).x = (xMax + xMin)/2;
  (*res).y = (yMax + yMin)/2;

  return res ;

}

void edgedetect(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)    // if second point is below first point interchange them
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)      // if denominator is zero we can't find slope
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;    // y2-y1=0 implies line is horizontal
            x=x1;
            for(i=y1;i<y2;i++)        // starting from x1,y1 add slope mx to x
            {                                  // and round it to find the next point on the
                                                // line. For that particular scan line i
                        if(x<le[i])         // insert the x value into either le or re.
                                    le[i]=x; 
