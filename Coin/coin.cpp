//
// Created by andrea on 13/07/18.
//

#include <stdio.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <vector>

#include "coin.h"

#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"


Mesh coinMesh((char *)"Coin/Coin.obj");

void Coin::InitCoin(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

//todo
void Coin::Render() {
    if(!destroy){
        glPushMatrix();
        glTranslatef(positionOnX, positionOnY, positionOnZ);

        glScalef(-0.25,0.25,-0.25);

        glTranslate(coinMesh.Center());
        glRotatef(coinRotation, 1, 1, 1);
        glTranslate(-coinMesh.Center());

        glColor3f( 255, 215, 0);
        coinMesh.RenderNxV();

        glPopMatrix();
        coinRotation+=speedRotation;
    }
}

int Coin::ChangeState(float x, float z) {
    int res=0;
    if(!destroy && positionOnX>x-rangeBike && positionOnX<x+rangeBike && positionOnZ>z-rangeBike && positionOnZ<z+rangeBike){
        destroy=true;
        res=1;
    }
    return res;
}