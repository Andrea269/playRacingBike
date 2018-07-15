//
// Created by andrea on 14/07/18.
//

#ifndef PLAYRACINGBIKE_TRACK_H
#define PLAYRACINGBIKE_TRACK_H
#endif //PLAYRACINGBIKE_TRACK_H

#include <vector>
#include "../Mesh/point3.h"
#include "../Mesh/mesh.h"

class Track{
public:
    void InitTrack(float x, float z);
    void Render();
    Track(){
        positionOnY=0;
        positionOnX, positionOnZ=0;
    }
    float positionOnX, positionOnY, positionOnZ;
//    vector pieceTrack;
private:
    void SetupRoadTexture(Point3 min, Point3 max, int numbertexture);
};