//
// Created by andrea on 7/07/18.
//

#ifndef GRAFICA_CAMERA_H
#define GRAFICA_CAMERA_H
#endif //GRAFICA_CAMERA_H
#include <string>
using namespace std;
class Menu{
public:
    void Init();
    void InitMenu(int width, int height);
    void DrawMenu(int width, int height, int totalPoint);
    int ButtonPress(int cordX, int cordY);
    void DrawPause(int width, int height);
    void DrawStart(int width, int height);

    Menu(){
        indentMenu=10;
        Init();
    }

    struct structMenu{
        string id;
        int x, y, w, h;
    };
    int indentMenu;
    int heightMenu;
    structMenu itemsMenu[11];
private:
    void DrawButton(int totalPoint);
};