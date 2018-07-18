//
// Created by andrea on 7/07/18.
//

#ifndef GRAFICA_CAMERA_H
#define GRAFICA_CAMERA_H
#endif //GRAFICA_CAMERA_H
class Camera{
public:
    void InitCamera();
    void UpdateCamera(float orientation, float positionOnX, float positionOnY, float positionOnZ);
    void EventShift(bool cond);
    void UpdateIndexCamera();
    void UpdateEyeDistance(bool greater0, bool lower0);
    void UpdateView(float x, float y);
    Camera(){
        indexCamera=4;//todo 0
        oppositeView=false;
        eyeDistance=5;
        viewAlpha=20, viewBeta=40;
        InitCamera();
    }
    struct structCamera{
        double distance, height, plusAngle, plusEY;
    };
    structCamera cameras[4];
    int indexCamera;
    bool oppositeView;
    float eyeDistance; //distanza dell'occhio dall'origine
    float viewAlpha, viewBeta; // angoli che definiscono la vista
};