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
    void InitMenu(int width, int height);
    void DrawMenu(int width, int height, int totalPoint);
    int ButtonPress(int cordX, int cordY);

    Menu(){
        indentMenu=10;
    }

    struct structMenu{
        string id;
        int x, y, w, h;
    };
    int indentMenu;
    int heightMenu;
    structMenu itemsMenu[1];//todo inserire numero voci menu
private:
    void DrowButton();
};