#include <iostream>
#include "cabecera.h"

using namespace std;

int main() {
    // point p;//(0,0,0)
    // vetor v,u;//(1,2,3)

    // p.printPoint();

    // double m=v*u;
    // cout<<m<<endl;

    // p=p+v;

    // p.printPoint();
    // Definir los vertices del cubo
    room r;
    r.NewPlane(6);
    for(int i=0; i<6; i++)
        r.p[i].NewPoints(4);

        // Cara frontal
        r.p[0].p[0].x = 0;
        r.p[0].p[0].y = 0;
        r.p[0].p[0].z = 0;
        r.p[0].p[1].x = 0;
        r.p[0].p[1].y = 0;
        r.p[0].p[1].z = 1;
        r.p[0].p[2].x = 1;
        r.p[0].p[2].y = 0;
        r.p[0].p[2].z = 1;
        r.p[0].p[3].x = 1;
        r.p[0].p[3].y = 0;
        r.p[0].p[3].z = 0;

        // Cara trasera

        r.p[1].p[0].x = 0;
        r.p[1].p[0].y = 1;
        r.p[1].p[0].z = 0;
        r.p[1].p[1].x = 1;
        r.p[1].p[1].y = 1;
        r.p[1].p[1].z = 0;
        r.p[1].p[2].x = 1;
        r.p[1].p[2].y = 1;
        r.p[1].p[2].z = 1;
        r.p[1].p[3].x = 0;
        r.p[1].p[3].y = 1;
        r.p[1].p[3].z = 1;

        // Cara izquierda
        r.p[2].p[0].x = 0;
        r.p[2].p[0].y = 0;
        r.p[2].p[0].z = 0;
        r.p[2].p[1].x = 0;
        r.p[2].p[1].y = 1;
        r.p[2].p[1].z = 0;
        r.p[2].p[2].x = 0;
        r.p[2].p[2].y = 1;
        r.p[2].p[2].z = 1;
        r.p[2].p[3].x = 0;
        r.p[2].p[3].y = 0;
        r.p[2].p[3].z = 1;

        // Cara derecha
        r.p[3].p[0].x = 1;
        r.p[3].p[0].y = 0;
        r.p[3].p[0].z = 0;
        r.p[3].p[1].x = 1;
        r.p[3].p[1].y = 0;
        r.p[3].p[1].z = 1;
        r.p[3].p[2].x = 1;
        r.p[3].p[2].y = 1;
        r.p[3].p[2].z = 1;
        r.p[3].p[3].x = 1;
        r.p[3].p[3].y = 1;
        r.p[3].p[3].z = 0;

        // Cara inferior
        r.p[4].p[0].x = 0;
        r.p[4].p[0].y = 0;
        r.p[4].p[0].z = 0;
        r.p[4].p[1].x = 1;
        r.p[4].p[1].y = 0;
        r.p[4].p[1].z = 0;
        r.p[4].p[2].x = 1;
        r.p[4].p[2].y = 1;
        r.p[4].p[2].z = 0;
        r.p[4].p[3].x = 0;
        r.p[4].p[3].y = 1;
        r.p[4].p[3].z = 0;

        /*vetor vt = r.p[4].p[1]-r.p[4].p[0];
        vetor vs = r.p[4].p[3]-r.p[4].p[0];
        vetor vw,vx;

        vt.printVetor();
        vs.printVetor();

        vw = vt/vs;
        vx = vs/vt;
        vw.printVetor();
        vx.printVetor();*/

        // Cara superior
        r.p[5].p[0].x = 0;
        r.p[5].p[0].y = 0;
        r.p[5].p[0].z = 1;
        r.p[5].p[1].x = 0;
        r.p[5].p[1].y = 1;
        r.p[5].p[1].z = 1;
        r.p[5].p[2].x = 1;
        r.p[5].p[2].y = 1;
        r.p[5].p[2].z = 1;
        r.p[5].p[3].x = 1;
        r.p[5].p[3].y = 0;
        r.p[5].p[3].z = 1;


        // Centro del cubo
        point centroCubo(0.5, 0.5, 0.5);

        // Iterar sobre cada cara
        for (int i = 0; i < 6; i++) {
            // Calcular dos vectores de la cara
            vetor v1,v2;
            v1=r.p[i].p[1] - r.p[i].p[0];
            v2=r.p[i].p[3] - r.p[i].p[0];

            // Calcular la normal usando el producto cruz
            vetor normal = v1/v2;
            normal.unitario();

            // Vector desde el centro del cubo al primer vertice de la cara

            vetor haciaCentro=r.p[i].p[0] - centroCubo;


            // Asegurar que la normal apunta hacia el centro
            if (normal * haciaCentro > 0) { // Si el producto punto es negativo, invertir la normal
                normal*(-1);
            }

            // Imprimir la normal de la cara
            cout << "Normal de la cara " << i + 1 << ":" ;
            normal.printVetor();
        }

    // Definimos el vector incidente
    vetor incidente(1, -1, 0); // Ejemplo

    // Calcular reflexiones para cada cara
    cout << "Reflexiones por cara:" << endl;
    for (int i = 0; i < 6; i++) {
        vetor v1 = r.p[i].p[1] - r.p[i].p[0];
        vetor v2 = r.p[i].p[3] - r.p[i].p[0];

        // Calcular la normal
        vetor normal = v1 / v2;
        normal.unitario();

        // Calcular el vector reflejado usando Reflect
        vetor reflejado;
        calcularReflexion(reflejado, incidente, normal);

        // Imprimir resultados
        cout << "Cara " << i + 1 << ": ";
        reflejado.printVetor();
    }

    //REFLEJADO
    vetor *v;
    source s;
    s.createRays(12);

    for(int i=0; i<s.NRAYS; i++)
        s.Rays[i].printVetor();


    return 0;
}
