//
// Created by andrea on 14/07/18.
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

#include "track.h"

#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"


Mesh trackMesh((char *)"Track/track.obj");

void Track::InitTrack(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Track::Render() {
    glPushMatrix();
    glTranslatef(positionOnX+27, positionOnY, positionOnZ-30);

    glScalef(-10,10,-10);

//    glTranslate(trackMesh.Center());
//    glRotatef(, 1, 1, 1);
//    glTranslate(-trackMesh.Center());

    trackMesh.RenderNxV();//todo texture strada

    glPopMatrix();
}
