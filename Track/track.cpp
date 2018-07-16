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

#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"
#include "track.h"


Mesh start((char *)"Track/TrackMesh/Crossroad/Cross4road.obj");
Mesh cross3road1t1((char *)"Track/TrackMesh/Crossroad/Cross3road1-1.obj");
Mesh cross3road2t1((char *)"Track/TrackMesh/Crossroad/Cross3road2-1.obj");
Mesh cross3road3t1((char *)"Track/TrackMesh/Crossroad/Cross3road3-1.obj");
Mesh cross3road4t2((char *)"Track/TrackMesh/Crossroad/Cross3road4-2.obj");

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
Mesh line16o((char *)"Track/TrackMesh/Line/Line16-O.obj");
Mesh line17o((char *)"Track/TrackMesh/Line/Line17-O.obj");
Mesh line18o((char *)"Track/TrackMesh/Line/Line18-O.obj");
Mesh line19o((char *)"Track/TrackMesh/Line/Line19-O.obj");
Mesh line20o((char *)"Track/TrackMesh/Line/Line20-O.obj");
Mesh line21o((char *)"Track/TrackMesh/Line/Line21-O.obj");
Mesh line22o((char *)"Track/TrackMesh/Line/Line22-O.obj");
Mesh line23o((char *)"Track/TrackMesh/Line/Line23-O.obj");
Mesh line24o((char *)"Track/TrackMesh/Line/Line24-O.obj");
Mesh line25v((char *)"Track/TrackMesh/Line/Line25-V.obj");
Mesh line26v((char *)"Track/TrackMesh/Line/Line26-V.obj");
Mesh line27v((char *)"Track/TrackMesh/Line/Line27-V.obj");
Mesh line28v((char *)"Track/TrackMesh/Line/Line28-V.obj");
Mesh line29v((char *)"Track/TrackMesh/Line/Line29-V.obj");
Mesh line30v((char *)"Track/TrackMesh/Line/Line30-V.obj");
Mesh line31o((char *)"Track/TrackMesh/Line/Line31-O.obj");
Mesh line32v((char *)"Track/TrackMesh/Line/Line32-V.obj");
Mesh line33v((char *)"Track/TrackMesh/Line/Line33-V.obj");
Mesh line34v((char *)"Track/TrackMesh/Line/Line34-V.obj");
Mesh line35v((char *)"Track/TrackMesh/Line/Line35-V.obj");
Mesh line36v((char *)"Track/TrackMesh/Line/Line36-V.obj");
Mesh line37v((char *)"Track/TrackMesh/Line/Line37-V.obj");
Mesh line38v((char *)"Track/TrackMesh/Line/Line38-V.obj");
Mesh line39v((char *)"Track/TrackMesh/Line/Line39-V.obj");
Mesh line40v((char *)"Track/TrackMesh/Line/Line40-V.obj");
Mesh line41o((char *)"Track/TrackMesh/Line/Line41-O.obj");
Mesh line42o((char *)"Track/TrackMesh/Line/Line42-O.obj");
Mesh line43o((char *)"Track/TrackMesh/Line/Line43-O.obj");
Mesh line44o((char *)"Track/TrackMesh/Line/Line44-O.obj");
Mesh line45o((char *)"Track/TrackMesh/Line/Line45-O.obj");
Mesh line46o((char *)"Track/TrackMesh/Line/Line46-O.obj");
Mesh line47o((char *)"Track/TrackMesh/Line/Line47-O.obj");
Mesh line48o((char *)"Track/TrackMesh/Line/Line48-O.obj");
Mesh line49o((char *)"Track/TrackMesh/Line/Line49-O.obj");
Mesh line50o((char *)"Track/TrackMesh/Line/Line50-O.obj");
Mesh line51o((char *)"Track/TrackMesh/Line/Line51-O.obj");
Mesh line52o((char *)"Track/TrackMesh/Line/Line52-O.obj");
Mesh line53o((char *)"Track/TrackMesh/Line/Line53-O.obj");
Mesh line54o((char *)"Track/TrackMesh/Line/Line54-O.obj");
Mesh line55v((char *)"Track/TrackMesh/Line/Line55-V.obj");
Mesh line56v((char *)"Track/TrackMesh/Line/Line56-V.obj");
Mesh line57o((char *)"Track/TrackMesh/Line/Line57-O.obj");
Mesh line58o((char *)"Track/TrackMesh/Line/Line58-O.obj");
Mesh line59o((char *)"Track/TrackMesh/Line/Line59-O.obj");
Mesh line60o((char *)"Track/TrackMesh/Line/Line60-O.obj");
Mesh line61o((char *)"Track/TrackMesh/Line/Line61-O.obj");
Mesh line62o((char *)"Track/TrackMesh/Line/Line62-O.obj");
Mesh line63o((char *)"Track/TrackMesh/Line/Line63-O.obj");
Mesh line64o((char *)"Track/TrackMesh/Line/Line64-O.obj");
Mesh line65o((char *)"Track/TrackMesh/Line/Line65-O.obj");
Mesh line66v((char *)"Track/TrackMesh/Line/Line66-V.obj");
Mesh line67v((char *)"Track/TrackMesh/Line/Line67-V.obj");
Mesh line68v((char *)"Track/TrackMesh/Line/Line68-V.obj");

Mesh curve1t4((char *)"Track/TrackMesh/Curve/Curve1-4.obj");
Mesh curve2t2((char *)"Track/TrackMesh/Curve/Curve2-2.obj");
Mesh curve3t4((char *)"Track/TrackMesh/Curve/Curve3-4.obj");
Mesh curve4t3((char *)"Track/TrackMesh/Curve/Curve4-3.obj");
Mesh curve5t1((char *)"Track/TrackMesh/Curve/Curve5-1.obj");
Mesh curve6t3((char *)"Track/TrackMesh/Curve/Curve6-3.obj");
Mesh curve7t2((char *)"Track/TrackMesh/Curve/Curve7-2.obj");
Mesh curve8t4((char *)"Track/TrackMesh/Curve/Curve8-4.obj");
Mesh curve9t2((char *)"Track/TrackMesh/Curve/Curve9-2.obj");
Mesh curve10t4((char *)"Track/TrackMesh/Curve/Curve10-4.obj");
Mesh curve11t3((char *)"Track/TrackMesh/Curve/Curve11-3.obj");
Mesh curve12t1((char *)"Track/TrackMesh/Curve/Curve12-1.obj");
Mesh curve13t3((char *)"Track/TrackMesh/Curve/Curve13-3.obj");
Mesh curve14t4((char *)"Track/TrackMesh/Curve/Curve14-4.obj");
Mesh curve15t2((char *)"Track/TrackMesh/Curve/Curve15-2.obj");
Mesh curve16t1((char *)"Track/TrackMesh/Curve/Curve16-1.obj");
Mesh curve17t3((char *)"Track/TrackMesh/Curve/Curve17-3.obj");
Mesh curve18t4((char *)"Track/TrackMesh/Curve/Curve18-4.obj");
Mesh curve19t1((char *)"Track/TrackMesh/Curve/Curve19-1.obj");
Mesh curve20t2((char *)"Track/TrackMesh/Curve/Curve20-2.obj");
Mesh curve21t3((char *)"Track/TrackMesh/Curve/Curve21-3.obj");
Mesh curve22t1((char *)"Track/TrackMesh/Curve/Curve22-1.obj");
Mesh curve23t3((char *)"Track/TrackMesh/Curve/Curve23-3.obj");
Mesh curve24t4((char *)"Track/TrackMesh/Curve/Curve24-4.obj");
Mesh curve25t2((char *)"Track/TrackMesh/Curve/Curve25-2.obj");
Mesh curve26t4((char *)"Track/TrackMesh/Curve/Curve26-4.obj");
Mesh curve27t2((char *)"Track/TrackMesh/Curve/Curve27-2.obj");
Mesh curve28t1((char *)"Track/TrackMesh/Curve/Curve28-1.obj");
Mesh curve29t3((char *)"Track/TrackMesh/Curve/Curve29-3.obj");

void Track::InitTrack(float x, float z) {
    positionOnX=x;
    positionOnZ=z;
}

void Track::Render() {
    glPushMatrix();
    glTranslatef(positionOnX, positionOnY, positionOnZ);

    glScalef(-10,10,-10);

    SetupRoadTexture(start.bbmin.X(), start.bbmax.X(), start.bbmin.Z(), start.bbmax.Z(), 7);
    start.RenderNxV();

    SetupRoadTexture(line1v.bbmin.X(), line1v.bbmax.X(), line1v.bbmin.Z(), line1v.bbmax.Z(), 1);
    line1v.RenderNxV();
    line2v.RenderNxV();
    line3v.RenderNxV();
    line4v.RenderNxV();
    SetupRoadTexture(line8v.bbmin.X(), line8v.bbmax.X(), line8v.bbmin.Z(), line8v.bbmax.Z(), 1);
    line8v.RenderNxV();
    SetupRoadTexture(line12v.bbmin.X(), line12v.bbmax.X(), line12v.bbmin.Z(), line12v.bbmax.Z(), 1);
    line12v.RenderNxV();
    line13v.RenderNxV();
    line14v.RenderNxV();
    line15v.RenderNxV();
    SetupRoadTexture(line25v.bbmin.X(), line25v.bbmax.X(), line25v.bbmin.Z(), line25v.bbmax.Z(), 1);
    line25v.RenderNxV();
    line26v.RenderNxV();
    line27v.RenderNxV();
    SetupRoadTexture(line28v.bbmin.X(), line28v.bbmax.X(), line28v.bbmin.Z(), line28v.bbmax.Z(), 1);
    line28v.RenderNxV();
    line29v.RenderNxV();
    line30v.RenderNxV();
    SetupRoadTexture(line32v.bbmin.X(), line32v.bbmax.X(), line32v.bbmin.Z(), line32v.bbmax.Z(), 1);
    line32v.RenderNxV();
    line33v.RenderNxV();
    line34v.RenderNxV();
    line35v.RenderNxV();
    SetupRoadTexture(line36v.bbmin.X(), line36v.bbmax.X(), line36v.bbmin.Z(), line36v.bbmax.Z(), 1);
    line36v.RenderNxV();
    line37v.RenderNxV();
    line38v.RenderNxV();
    line39v.RenderNxV();
    line40v.RenderNxV();
    SetupRoadTexture(line55v.bbmin.X(), line55v.bbmax.X(), line55v.bbmin.Z(), line55v.bbmax.Z(), 1);
    line55v.RenderNxV();
    line56v.RenderNxV();
    SetupRoadTexture(line66v.bbmin.X(), line66v.bbmax.X(), line66v.bbmin.Z(), line66v.bbmax.Z(), 1);
    line66v.RenderNxV();
    line67v.RenderNxV();
    line68v.RenderNxV();

    SetupRoadTexture(line5o.bbmin.X(), line5o.bbmax.X(), line5o.bbmin.Z(), line5o.bbmax.Z(), 2);
    line5o.RenderNxV();
    line6o.RenderNxV();
    line7o.RenderNxV();
    SetupRoadTexture(line9o.bbmin.X(), line9o.bbmax.X(), line9o.bbmin.Z(), line9o.bbmax.Z(), 2);
    line9o.RenderNxV();
    line10o.RenderNxV();
    line11o.RenderNxV();
    SetupRoadTexture(line16o.bbmin.X(), line16o.bbmax.X(), line16o.bbmin.Z(), line16o.bbmax.Z(), 2);
    line16o.RenderNxV();
    line17o.RenderNxV();
    line18o.RenderNxV();
    line19o.RenderNxV();
    line20o.RenderNxV();
    line21o.RenderNxV();
    line22o.RenderNxV();
    line23o.RenderNxV();
    line24o.RenderNxV();
    SetupRoadTexture(line31o.bbmin.X(), line31o.bbmax.X(), line31o.bbmin.Z(), line31o.bbmax.Z(), 2);
    line31o.RenderNxV();
    SetupRoadTexture(line41o.bbmin.X(), line41o.bbmax.X(), line41o.bbmin.Z(), line41o.bbmax.Z(), 2);
    line41o.RenderNxV();
    line42o.RenderNxV();
    line43o.RenderNxV();
    line44o.RenderNxV();
    line45o.RenderNxV();
    line46o.RenderNxV();
    line47o.RenderNxV();
    line48o.RenderNxV();
    line49o.RenderNxV();
    line50o.RenderNxV();
    line51o.RenderNxV();
    line52o.RenderNxV();
    line53o.RenderNxV();
    line54o.RenderNxV();
    SetupRoadTexture(line57o.bbmin.X(), line57o.bbmax.X(), line57o.bbmin.Z(), line57o.bbmax.Z(), 2);
    line57o.RenderNxV();
    line58o.RenderNxV();
    line59o.RenderNxV();
    line60o.RenderNxV();
    line61o.RenderNxV();
    line62o.RenderNxV();
    line63o.RenderNxV();
    SetupRoadTexture(line64o.bbmin.X(), line64o.bbmax.X(), line64o.bbmin.Z(), line64o.bbmax.Z(), 2);
    line64o.RenderNxV();
    SetupRoadTexture(line65o.bbmin.X(), line65o.bbmax.X(), line65o.bbmin.Z(), line65o.bbmax.Z(), 2);
    line65o.RenderNxV();

    SetupRoadTexture(curve5t1.bbmin.X(), curve5t1.bbmax.X(), curve5t1.bbmin.Z(), curve5t1.bbmax.Z(), 3);
    curve5t1.RenderNxV();
    SetupRoadTexture(curve12t1.bbmin.X(), curve12t1.bbmax.X(), curve12t1.bbmin.Z(), curve12t1.bbmax.Z(), 3);
    curve12t1.RenderNxV();
    SetupRoadTexture(curve16t1.bbmin.X(), curve16t1.bbmax.X(), curve16t1.bbmin.Z(), curve16t1.bbmax.Z(), 3);
    curve16t1.RenderNxV();
    SetupRoadTexture(curve19t1.bbmin.X(), curve19t1.bbmax.X(), curve19t1.bbmin.Z(), curve19t1.bbmax.Z(), 3);
    curve19t1.RenderNxV();
    SetupRoadTexture(curve22t1.bbmin.X(), curve22t1.bbmax.X(), curve22t1.bbmin.Z(), curve22t1.bbmax.Z(), 3);
    curve22t1.RenderNxV();
    SetupRoadTexture(curve28t1.bbmin.X(), curve28t1.bbmax.X(), curve28t1.bbmin.Z(), curve28t1.bbmax.Z(), 3);
    curve28t1.RenderNxV();

    SetupRoadTexture(curve2t2.bbmin.X(), curve2t2.bbmax.X(), curve2t2.bbmin.Z(), curve2t2.bbmax.Z(), 4);
    curve2t2.RenderNxV();
    SetupRoadTexture(curve7t2.bbmin.X(), curve7t2.bbmax.X(), curve7t2.bbmin.Z(), curve7t2.bbmax.Z(), 4);
    curve7t2.RenderNxV();
    SetupRoadTexture(curve9t2.bbmin.X(), curve9t2.bbmax.X(), curve9t2.bbmin.Z(), curve9t2.bbmax.Z(), 4);
    curve9t2.RenderNxV();
    SetupRoadTexture(curve15t2.bbmin.X(), curve15t2.bbmax.X(), curve15t2.bbmin.Z(), curve15t2.bbmax.Z(), 4);
    curve15t2.RenderNxV();
    SetupRoadTexture(curve20t2.bbmin.X(), curve20t2.bbmax.X(), curve20t2.bbmin.Z(), curve20t2.bbmax.Z(), 4);
    curve20t2.RenderNxV();
    SetupRoadTexture(curve25t2.bbmin.X(), curve25t2.bbmax.X(), curve25t2.bbmin.Z(), curve25t2.bbmax.Z(), 4);
    curve25t2.RenderNxV();
    SetupRoadTexture(curve27t2.bbmin.X(), curve27t2.bbmax.X(), curve27t2.bbmin.Z(), curve27t2.bbmax.Z(), 4);
    curve27t2.RenderNxV();

    SetupRoadTexture(curve4t3.bbmin.X(), curve4t3.bbmax.X(), curve4t3.bbmin.Z(), curve4t3.bbmax.Z(), 5);
    curve4t3.RenderNxV();
    SetupRoadTexture(curve6t3.bbmin.X(), curve6t3.bbmax.X(), curve6t3.bbmin.Z(), curve6t3.bbmax.Z(), 5);
    curve6t3.RenderNxV();
    SetupRoadTexture(curve11t3.bbmin.X(), curve11t3.bbmax.X(), curve11t3.bbmin.Z(), curve11t3.bbmax.Z(), 5);
    curve11t3.RenderNxV();
    SetupRoadTexture(curve13t3.bbmin.X(), curve13t3.bbmax.X(), curve13t3.bbmin.Z(), curve13t3.bbmax.Z(), 5);
    curve13t3.RenderNxV();
    SetupRoadTexture(curve17t3.bbmin.X(), curve17t3.bbmax.X(), curve17t3.bbmin.Z(), curve17t3.bbmax.Z(), 5);
    curve17t3.RenderNxV();
    SetupRoadTexture(curve21t3.bbmin.X(), curve21t3.bbmax.X(), curve21t3.bbmin.Z(), curve21t3.bbmax.Z(), 5);
    curve21t3.RenderNxV();
    SetupRoadTexture(curve23t3.bbmin.X(), curve23t3.bbmax.X(), curve23t3.bbmin.Z(), curve23t3.bbmax.Z(), 5);
    curve23t3.RenderNxV();
    SetupRoadTexture(curve29t3.bbmin.X(), curve29t3.bbmax.X(), curve29t3.bbmin.Z(), curve29t3.bbmax.Z(), 5);
    curve29t3.RenderNxV();

    SetupRoadTexture(curve1t4.bbmin.X(), curve1t4.bbmax.X(), curve1t4.bbmin.Z(), curve1t4.bbmax.Z(), 6);
    curve1t4.RenderNxV();
    SetupRoadTexture(curve3t4.bbmin.X(), curve3t4.bbmax.X(), curve3t4.bbmin.Z(), curve3t4.bbmax.Z(), 6);
    curve3t4.RenderNxV();
    SetupRoadTexture(curve8t4.bbmin.X(), curve8t4.bbmax.X(), curve8t4.bbmin.Z(), curve8t4.bbmax.Z(), 6);
    curve8t4.RenderNxV();
    SetupRoadTexture(curve10t4.bbmin.X(), curve10t4.bbmax.X(), curve10t4.bbmin.Z(), curve10t4.bbmax.Z(), 6);
    curve10t4.RenderNxV();
    SetupRoadTexture(curve14t4.bbmin.X(), curve14t4.bbmax.X(), curve14t4.bbmin.Z(), curve14t4.bbmax.Z(), 6);
    curve14t4.RenderNxV();
    SetupRoadTexture(curve18t4.bbmin.X(), curve18t4.bbmax.X(), curve18t4.bbmin.Z(), curve18t4.bbmax.Z(), 6);
    curve18t4.RenderNxV();
    SetupRoadTexture(curve24t4.bbmin.X(), curve24t4.bbmax.X(), curve24t4.bbmin.Z(), curve24t4.bbmax.Z(), 6);
    curve24t4.RenderNxV();
    SetupRoadTexture(curve26t4.bbmin.X(), curve26t4.bbmax.X(), curve26t4.bbmin.Z(), curve26t4.bbmax.Z(), 6);
    curve26t4.RenderNxV();

    SetupRoadTexture(cross3road1t1.bbmin.X(), cross3road1t1.bbmax.X(), cross3road1t1.bbmin.Z(), cross3road1t1.bbmax.Z(), 8);
    cross3road1t1.RenderNxV();
    SetupRoadTexture(cross3road2t1.bbmin.X(), cross3road2t1.bbmax.X(), cross3road2t1.bbmin.Z(), cross3road2t1.bbmax.Z(), 8);
    cross3road2t1.RenderNxV();
    SetupRoadTexture(cross3road3t1.bbmin.X(), cross3road3t1.bbmax.X(), cross3road3t1.bbmin.Z(), cross3road3t1.bbmax.Z(), 8);
    cross3road3t1.RenderNxV();
    SetupRoadTexture(cross3road4t2.bbmin.X(), cross3road4t2.bbmax.X(), cross3road4t2.bbmin.Z(), cross3road4t2.bbmax.Z(), 9);
    cross3road4t2.RenderNxV();
    glPopMatrix();
}

void Track::SetupRoadTexture(float minX, float maxX, float minZ, float maxZ, int numbertexture){
    glBindTexture(GL_TEXTURE_2D,numbertexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // ulilizzo le coordinate OGGETTO
    // cioe' le coordnate originali, PRIMA della moltiplicazione per la ModelView
    // in modo che la texture sia "attaccata" all'oggetto, e non "proiettata" su esso

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE , GL_OBJECT_LINEAR);
    float sz=1.0/(maxZ - minZ);
    float sx=1/(maxX - minX);
    float s[4]={sx, 0,0, - minX*sx };
    float t[4]={0,0,sz,  - minZ*sz };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, t);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, s);
}