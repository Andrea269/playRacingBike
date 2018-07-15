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


#include "track.h"

//todo esportare resto della pista da blender e renderizzarla

Mesh start((char *)"Track/TrackMesh/Crossroad/Cross4road.obj");

Mesh line1v((char *)"Track/TrackMesh/Line/Line1-V.obj");
Mesh line2v((char *)"Track/TrackMesh/Line/Line2-V.obj");
Mesh line3v((char *)"Track/TrackMesh/Line/Line3-V.obj");
Mesh line4v((char *)"Track/TrackMesh/Line/Line4-V.obj");
Mesh line5o((char *)"Track/TrackMesh/Line/Line5-O.obj");
Mesh line6o((char *)"Track/TrackMesh/Line/Line6-O.obj");
Mesh line7o((char *)"Track/TrackMesh/Line/Line7-O.obj");
Mesh line8v((char *)"Track/TrackMesh/Line/Line8-V.obj");
Mesh line9o((char *)"Track/TrackMesh/Line/Line9-O.obj");
Mesh line10o((char *)"Track/TrackMesh/Line/Line10-O.obj");
Mesh line11o((char *)"Track/TrackMesh/Line/Line11-O.obj");
Mesh line12v((char *)"Track/TrackMesh/Line/Line12-V.obj");
Mesh line13v((char *)"Track/TrackMesh/Line/Line13-V.obj");
Mesh line14v((char *)"Track/TrackMesh/Line/Line14-V.obj");
Mesh line15v((char *)"Track/TrackMesh/Line/Line15-V.obj");

Mesh curve1t4((char *)"Track/TrackMesh/Curve/Curve1-4.obj");
Mesh curve2t2((char *)"Track/TrackMesh/Curve/Curve2-2.obj");
Mesh curve3t4((char *)"Track/TrackMesh/Curve/Curve3-4.obj");
Mesh curve4t3((char *)"Track/TrackMesh/Curve/Curve4-3.obj");
Mesh curve5t1((char *)"Track/TrackMesh/Curve/Curve5-1.obj");
Mesh curve6t3((char *)"Track/TrackMesh/Curve/Curve6-3.obj");
Mesh curve7t2((char *)"Track/TrackMesh/Curve/Curve7-2.obj");
Mesh curve8t4((char *)"Track/TrackMesh/Curve/Curve8-4.obj");

void Track::InitTrack(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Track::Render() {
    glPushMatrix();
   // glTranslatef(positionOnX+27, positionOnY, positionOnZ-30);
    glTranslatef(positionOnX, positionOnY, positionOnZ);

    glScalef(-10,10,-10);


    SetupRoadTexture(start.bbmin, start.bbmax, 7);
    start.RenderNxV();

    SetupRoadTexture(line1v.bbmin, line1v.bbmax, 1);
    line1v.RenderNxV();
    line2v.RenderNxV();
    line3v.RenderNxV();
    line4v.RenderNxV();

    SetupRoadTexture(line8v.bbmin, line8v.bbmax, 1);
    line8v.RenderNxV();

    SetupRoadTexture(line12v.bbmin, line12v.bbmax, 1);
    line12v.RenderNxV();
    line13v.RenderNxV();
    line14v.RenderNxV();
    line15v.RenderNxV();

    SetupRoadTexture(line5o.bbmin, line5o.bbmax, 2);
    line5o.RenderNxV();
    line6o.RenderNxV();
    line7o.RenderNxV();
    SetupRoadTexture(line9o.bbmin, line9o.bbmax, 2);
    line9o.RenderNxV();
    line10o.RenderNxV();
    line11o.RenderNxV();



    SetupRoadTexture(curve5t1.bbmin, curve5t1.bbmax, 3);
    curve5t1.RenderNxV();

    SetupRoadTexture(curve2t2.bbmin, curve2t2.bbmax, 4);
    curve2t2.RenderNxV();
    SetupRoadTexture(curve7t2.bbmin, curve7t2.bbmax, 4);
    curve7t2.RenderNxV();

    SetupRoadTexture(curve4t3.bbmin, curve4t3.bbmax, 5);
    curve4t3.RenderNxV();
    SetupRoadTexture(curve6t3.bbmin, curve6t3.bbmax, 5);
    curve6t3.RenderNxV();

    SetupRoadTexture(curve1t4.bbmin, curve1t4.bbmax, 6);
    curve1t4.RenderNxV();
    SetupRoadTexture(curve3t4.bbmin, curve3t4.bbmax, 6);
    curve3t4.RenderNxV();
    SetupRoadTexture(curve8t4.bbmin, curve8t4.bbmax, 6);
    curve8t4.RenderNxV();

    glPopMatrix();
}

void Track::SetupRoadTexture(Point3 min, Point3 max, int numbertexture){
    glBindTexture(GL_TEXTURE_2D,numbertexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ulilizzo le coordinate OGGETTO
    // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
    // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/(max.Z() - min.Z());
    float sx=1/(max.X() - min.X());
    float s[4]={sx, 0,0, - min.X()*sx };
    float t[4]={0,0,sz,  - min.Z()*sz };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, t);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, s);
}