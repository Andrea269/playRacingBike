//
// Created by andrea on 14/07/18.
//

#ifndef PLAYRACINGBIKE_TRACK_H
#define PLAYRACINGBIKE_TRACK_H
#endif //PLAYRACINGBIKE_TRACK_H


class Track{
public:
    void InitTrack(float x, float z);
    void Render();
    bool OnTrack(float x, float z);
    Track(){
        positionOnY=0;
        positionOnX, positionOnZ=0;
    }
    float positionOnX, positionOnY, positionOnZ;
//    vector pieceTrack;
private:
    void SetupRoadTexture(float minX, float maxX, float minZ, float maxZ, int numbertexture);
};