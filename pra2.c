/*
Graficos por Computadora

Nombre: Práctica 02
Nombre del archivo: pra2.c
Fecha:  06-12-2022
Programador: Morales Flores Gael Alexis

Objetivo: Iniciar con 10 círculos ubicados 
          de forma aleatoria dentro de un plano 
          cuadrado, moverlos los círculos en 
          direcciones aleatorias y a diferentes velocidades, 
          cuando dos círculos colisionen entre sí, 
          estos deben de desaparecer, el programa debe 
          terminar hasta que no quede ningún círculo activo.

Compilar:
gcc -c pra2.c
Enlazar:
gcc pra2.o -o run  -l glut32 -l opengl32
*/

#include<gl\glut.h>
#include<math.h>
#include<stdio.h>
#include<windows.h>
#define tamVentana 600
#define nCirculos 10

typedef struct{ 
    float x;
    float y;
}PUNTO;

typedef struct{ 
    PUNTO c;
    float r;
    char activo;
}CIRCULO;

void display(void);

void Animar(void);
void dibujarTexto(char *Texto, float x, float y);

void Circulo(CIRCULO ci);
void inicializarCirculos();

const float pi=3.14159;
const float radio = 0.5;

CIRCULO circulos[nCirculos];
float deltaX[nCirculos];
float deltaY[nCirculos];

char cadena[25] = "[Circulos activos: ]";
char circulosActivos = nCirculos;
char inicio = 0;
unsigned int time = 0;

int main(int argc, char **argv){
    inicializarCirculos();
    glutInit(&argc,argv);
    glutInitWindowSize(tamVentana, tamVentana);
    glutCreateWindow("Proyecto 02: Demostracion de colision de figuras");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0,10.0,-10.0,10.0,1.0,-1.0); 
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(display);
    glutIdleFunc(Animar);
    glutMainLoop();
    return 0;
}
  
void display(void){
    unsigned int i;
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    sprintf(cadena,"[Circulos activos: %i]",circulosActivos);
    dibujarTexto(cadena, -3, -9.8);
    // DIBUJAR LOS CÍRCULOS ACTIVOS
    for(i=0; i < nCirculos; i++)
        if(circulos[i].activo == 1)
            Circulo(circulos[i]);
    glFlush();
    if(inicio == 0){
        sleep(3);
        inicio = 1;
    }
}

void Animar(void){    
    unsigned int i, j;    
    if(circulosActivos<2){
        sleep(2);
        exit(0);
    } 
    if((time%150)==0){
        for(i=0; i<nCirculos/2; i++){
            circulos[i].c.x += deltaX[i];
            circulos[i].c.y += deltaY[i];
            if(circulos[i].c.x + radio > 9.5)
                deltaX[i]*= -1;
            else if(circulos[i].c.x + radio < - 9.5)
                deltaX[i]*= -1;
            if(circulos[i].c.y + radio > 9.5)
                deltaY[i]*= -1;
            else if(circulos[i].c.y + radio < - 9.5)
                deltaY[i]*= -1;
            for(j=0; j<nCirculos; j++){
                if(j!=i)
                    if(circulos[j].activo == 1 && circulos[i].activo == 1)
                        if((circulos[i].c.x < circulos[j].c.x + radio) && (circulos[i].c.x > circulos[j].c.x - radio)){
                            if((circulos[i].c.y < circulos[j].c.y + radio) && (circulos[i].c.y > circulos[j].c.y - radio)){
                                // if(circulosActivos == 2)
                                //     circulos[i].activo = 0;
                                circulos[i].activo = 0;
                                circulos[j].activo = 0;
                                circulosActivos -=2;                            
                            }
                }                  
            }            
        }                
    }
    if((time%300)==0){
        for(i=nCirculos/2; i<nCirculos; i++){            
            circulos[i].c.x += deltaX[i];
            circulos[i].c.y += deltaY[i];
            if(circulos[i].c.x + radio > 9.5)
                deltaX[i]*= -1;
            else if(circulos[i].c.x + radio < - 9.5)
                deltaX[i]*= -1;
            if(circulos[i].c.y + radio > 9.5)
                deltaY[i]*= -1;
            else if(circulos[i].c.y + radio < - 9.5)
                deltaY[i]*= -1;
            for(j=0; j<nCirculos; j++){
                if(j!=i)
                    if(circulos[j].activo == 1 && circulos[i].activo == 1)
                        if((circulos[i].c.x < circulos[j].c.x + radio) && (circulos[i].c.x > circulos[j].c.x - radio)){
                            if((circulos[i].c.y < circulos[j].c.y + radio) && (circulos[i].c.y > circulos[j].c.y - radio)){
                                if(circulosActivos == 2)
                                    circulos[i].activo = 0;
                                circulos[i].activo = 0;
                                circulos[j].activo = 0;
                                circulosActivos -=2;                            
                            }
                }                  
            }            
        }                
    }
    time++;
    if(time>1000000000)
        time=0;
    glutPostRedisplay();    
}

void Circulo(CIRCULO ci){
    float x,y,theta;
    glBegin(GL_LINE_LOOP);
    for(theta=0; theta<6.28; theta+=0.1){
        x=ci.c.x+ci.r*cos(theta);
        y=ci.c.y+ci.r*sin(theta);
        glVertex2f(x,y);
    }
  glEnd(); 
}

void inicializarCirculos(){
    unsigned int i;    
    float numsX[nCirculos], numsY[nCirculos];
    // CREACIÓN DE DELTAS ALEATORIAS
    for(i=0; i<nCirculos; i++){
        numsX[i] = (rand() % 101)*0.01;
        numsY[i] = (rand() % 101)*0.01;        
    }
    // INICIALIZACIÓN DE TODOS LOS CIRCULOS CON SU RADIO,
    // COORDENADAS DEL CENTRO Y DELTAS CORRESPONDIENTES 
    // A CADA CUADRANTE DEL PLANO 
    for(i=0; i<nCirculos; i++){
        circulos[i].activo = 1;                
        circulos[i].r = radio;        
        // PRIMER CUADRANTE
        if(i<nCirculos/4){
            circulos[i].c.x = (rand() % 10);
            circulos[i].c.y = (rand() % 10);
            deltaX[i] = numsX[i];
            deltaY[i] = numsY[i];
        }
        // SEGUNDO CUADRANTE
        else if(i<nCirculos/2){
            circulos[i].c.x = (rand() % 10)*-1;
            circulos[i].c.y = (rand() % 10);
            deltaX[i] = numsX[i]*-1;
            deltaY[i] = numsY[i];
        }
        // TERCER CUADRANTE
        else if(i<(nCirculos*3/4)){
            circulos[i].c.x = (rand() % 10)*-1;
            circulos[i].c.y = (rand() % 10)*-1;
            deltaX[i] = numsX[i]*-1;
            deltaY[i] = numsY[i]*-1;
        }
        // CUARTO CUADRANTE
        else{
            circulos[i].c.x = (rand() % 10);
            circulos[i].c.y = (rand() % 10)*-1;
            deltaX[i] = numsX[i]*1;
            deltaY[i] = numsY[i]*-1;
        }
    }
}

void dibujarTexto(char *Texto, float x, float y){
  int k=0;
  glRasterPos2f(x,y);
  while(Texto[k]!='\0'){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Texto[k]);
    k++;
  }
}