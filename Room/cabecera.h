#ifndef CABECERA_NORMAL_H_INCLUDED
#define CABECERA_NORMAL_H_INCLUDED
#define _USE_MATH_DEFINES
#define PI (3.14159265358979323846)

#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

// Clase para un vector
class vetor {
public:
    double x, y, z;

    vetor(double a = 0.0, double b = 0.0, double c = 0.0) : x(a), y(b), z(c) {}

    vetor operator-(const vetor &v) const {
        return vetor(x - v.x, y - v.y, z - v.z);
    }

    double operator*(const vetor &v) const {
        return x * v.x + y * v.y + z * v.z; // Producto punto
    }

    void operator*(double d){
        x = x*d;
        y = y*d;
        z = z*d;
    }

    vetor operator/(const vetor &v) const {
        return vetor(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x); // Producto cruz
    }

    void operator/(double d){
        x = x/d;
        y = y/d;
        z = z/d;
    }

    void operator=(double d){
        x = d;
        y = d;
        z = d;
    }



    double magnitud(){
        double m = sqrt(x * x + y * y + z * z);
        return m;
    }

    void unitario() {
        double m = magnitud();
        if(m!=0){
            x = x/m;
            y = y/m;
            z = z/m;
        }
    }
    void printVetor(){ //Imprime el vector
        cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
};

// Clase para un punto
class point {
public:
    double x, y, z;
    point(double a = 0.0, double b = 0.0, double c = 0.0) : x(a), y(b), z(c) {}

    void iniciar(){
        x = 0;
        y = 0;
        z = 0;
    }
    point operator+ (vetor v){ //Translacion de punto
        point p;
        p.x= x + v.x;
        p.y= y + v.y;
        p.z= z + v.z;
        return p;
    }
    vetor operator-(point p){
        vetor v;
        v.x = x-p.x;
        v.y = y-p.y;
        v.z = z-p.z;
        return v;
    }

    void printPoint(){ //Imprime las coordenadas del punto
        cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
    }
};

class plane{
public:
    point *p;
    int NP;
    vetor n;

    plane(){
        p=NULL;
        NP=0;
    };

    void iniciar(){
        if (p!=NULL){
            delete p;
            p = NULL;
        }
        NP = 0;
        n = 0;
    }

    void NewPoints(int N){
        int P;
        point *tp;
        tp=new point[NP+N];
        for(P=0;P<NP;P++){
            tp[P]=p[P];
        }
        for(P=NP;P<NP+N;P++){
            tp[P].iniciar();
        }
        if(NP>0){
            delete[] p;
            p=NULL;
        }
        p=tp;
        NP+=N;
    };
};


class room{
public:
    plane *p;
    int NP;

    room(){
        p=NULL;
        NP=0;
    };

    void NewPlane(int N){
        int P;
        plane *tp;
        tp=new plane[NP+N];
        for(P=0;P<NP;P++){
            tp[P]=p[P];
        }
        for(P=NP;P<NP+N;P++){
            tp[P].iniciar();
        }
        if(NP>0){
            delete[] p;
            p=NULL;
        }
        p=tp;
        NP+=N;
    };
};

// Reflexion=VectorIncidente−2*(VectorIncidente⋅Normal)⋅Normal
// Calcular la reflexión
void calcularReflexion(vetor& salida, const vetor& incidenteVec, const vetor& normal) {
    salida = incidenteVec - normal * (2.f * (incidenteVec * normal));
}

class source{
public:
    point p;
    vetor *Rays;
    int NRAYS;

    source(){
        p=0.0;
        NRAYS=0;
        Rays=NULL;
    }
    void createRays(double NumberOfRays) {
        //matriz das Arestas {1o ponto da aresta, 2o ponto da aresta, Posição dos pontos da aresta na matriz Rays}
        int A[30][3]= {{0,1,0}, {0,2,0}, {0,3,0}, {0,4,0}, {0,5,0},
            {1,6,0}, {2,6,0}, {2,7,0}, {3,7,0}, {3,8,0},
            {4,8,0}, {4,9,0}, {5,9,0}, {5,10,0},{1,10,0},
            {6,11,0},{7,11,0},{8,11,0},{9,11,0},{10,11,0},
            {1,2,0}, {2,3,0}, {3,4,0}, {4,5,0}, {5,1,0},
            {6,7,0}, {7,8,0}, {8,9,0}, {9,10,0},{10,6,0}
        };
        //matriz dos triangulos {1a aresta, 2a aresta, [0] V em pé [-1] V de cabeça pra baixo}
        int T[20][3]= {{0,1,0},   {1,2,0},   {2,3,0},   {3,4,0},   {4,0,0},
            {5,6,-1},  {6,7,0},   {7,8,-1},  {8,9,0},   {9,10,-1},
            {10,11,0}, {11,12,-1},{12,13,0}, {13,14,-1},{14,5,0},
            {15,16,-1},{16,17,-1},{17,18,-1},{18,19,-1},{19,15,-1}
        };
        int i,j,k,n,m,RAY;
        double S,R,xB,yB,zB,xC,yC,zC,c[8];
        //create Rays matrix
        if(NRAYS>0)
            delete[] Rays;
        n=int(floor(sqrt((NumberOfRays-2)/10)+0.5));
        NRAYS=int(2+10*pow(n,2));
        Rays=new vetor[NRAYS];
        //calculating the icosaedron vertives
        S=2/sqrt(5);
        R=(5-sqrt(5))/5;
        Rays[0].x=0;
        Rays[0].y=0;
        Rays[0].z=1;
        for(i=1; i<6; i++) {
            Rays[i].x=S*cos((PI*i*72)/180);
            Rays[i].y=S*sin((PI*i*72)/180);
            Rays[i].z=1-R;
            Rays[i+5].x=S*cos((72*PI*i)/180+(36*PI)/180);
            Rays[i+5].y=S*sin((72*PI*i)/180+(36*PI)/180);
            Rays[i+5].z=R-1;
        }
        Rays[11].x=0;
        Rays[11].y=0;
        Rays[11].z=-1;
        RAY=12;
        //calculating the rays on the icosaedron edges
        for(j=0; j<30; j++) {
            A[j][2]=RAY;
            xB=Rays[A[j][0]].x;
            yB=Rays[A[j][0]].y;
            zB=Rays[A[j][0]].z;
            xC=Rays[A[j][1]].x;
            yC=Rays[A[j][1]].y;
            zC=Rays[A[j][1]].z;
            c[0]=pow(xC,2)*(pow(yB,2)+pow(zB,2))+pow(yC*zB-yB*zC,2)-2*xB*xC*(yB*yC+zB*zC)+pow(xB,2)*(pow(yC,2)+pow(zC,2));
            c[1]=acos(xB*xC+yB*yC+zB*zC);
            c[2]=-xC*(yB*yC+zB*zC)+xB*(pow(yC,2)+pow(zC,2));
            c[3]=xC*(pow(yB,2)+pow(zB,2))-xB*(yB*yC+zB*zC);
            c[4]=pow(xC,2)*yB-xB*xC*yC+zC*(-yC*zB+yB*zC);
            c[5]=-xB*xC*yB+pow(xB,2)*yC+zB*(yC*zB-yB*zC);
            c[6]=pow(xC,2)*zB-xB*xC*zC+yC*(yC*zB-yB*zC);
            c[7]=-xB*xC*zB+pow(xB,2)*zC+yB*(-yC*zB+yB*zC);
            for(i=1; i<n; i++) {
                Rays[RAY].x=(c[2]*cos(i*c[1]/n)+c[3]*cos((n-i)*c[1]/n))/c[0];
                Rays[RAY].y=(c[4]*cos(i*c[1]/n)+c[5]*cos((n-i)*c[1]/n))/c[0];
                Rays[RAY].z=(c[6]*cos(i*c[1]/n)+c[7]*cos((n-i)*c[1]/n))/c[0];
                RAY++;
            }
        }
        //calculating the rays on the icosaedron faces
        for(k=0; k<20; k++)
            for(j=1; j<n; j++) {
                xB=Rays[A[T[k][0]][2]+j-1].x;
                yB=Rays[A[T[k][0]][2]+j-1].y;
                zB=Rays[A[T[k][0]][2]+j-1].z;
                xC=Rays[A[T[k][1]][2]+j-1].x;
                yC=Rays[A[T[k][1]][2]+j-1].y;
                zC=Rays[A[T[k][1]][2]+j-1].z;
                c[0]=pow(xC,2)*(pow(yB,2)+pow(zB,2))+pow(yC*zB-yB*zC,2)-2*xB*xC*(yB*yC+zB*zC)+pow(xB,2)*(pow(yC,2)+pow(zC,2));
                c[1]=acos(xB*xC+yB*yC+zB*zC);
                c[2]=-xC*(yB*yC+zB*zC)+xB*(pow(yC,2)+pow(zC,2));
                c[3]=xC*(pow(yB,2)+pow(zB,2))-xB*(yB*yC+zB*zC);
                c[4]=pow(xC,2)*yB-xB*xC*yC+zC*(-yC*zB+yB*zC);
                c[5]=-xB*xC*yB+pow(xB,2)*yC+zB*(yC*zB-yB*zC);
                c[6]=pow(xC,2)*zB-xB*xC*zC+yC*(yC*zB-yB*zC);
                c[7]=-xB*xC*zB+pow(xB,2)*zC+yB*(-yC*zB+yB*zC);
                if(T[k][2]==0)m=j;
                else m=n-j;
                for(i=1; i<m; i++) {
                    Rays[RAY].x=(c[2]*cos(i*c[1]/m)+c[3]*cos((m-i)*c[1]/m))/c[0];
                    Rays[RAY].y=(c[4]*cos(i*c[1]/m)+c[5]*cos((m-i)*c[1]/m))/c[0];
                    Rays[RAY].z=(c[6]*cos(i*c[1]/m)+c[7]*cos((m-i)*c[1]/m))/c[0];
                    RAY++;
                }
        }
    };
};
#endif // CABECERA_NORMAL_H_INCLUDED
