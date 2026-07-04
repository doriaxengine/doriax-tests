#include "Doriax.h"
using namespace doriax;

Vector2 lastTouchPos;

Scene scene;
Camera camera(&scene);
Lines lines(&scene);

void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);
void onMouseScroll(float xoffset, float yoffset, int mods);


DORIAX_INIT void init(){
    lastTouchPos = Vector2(0, 0);

    scene.setCamera(camera.getEntity());

    int gridHeight = 0;

    for (int i = -1000; i <= 1000; i++){
        if (i == 0){
            lines.addLine(Vector3(i, gridHeight, -1000), Vector3(i, gridHeight, 1000), Vector4(1.0, 0.5, 0.5, 1.0));
        }else{
            if (i % 10 == 0){
                lines.addLine(Vector3(i, gridHeight, -1000), Vector3(i, gridHeight, 1000), Vector4(0.5, 0.5, 0.5, 1.0));
            }else{
                lines.addLine(Vector3(i, gridHeight, -1000), Vector3(i, gridHeight, 1000), Vector4(0.5, 0.5, 0.5, 0.5));
            }
        }
    }
    for (int i = -1000; i <= 1000; i++){
        if (i == 0){
            lines.addLine(Vector3(-1000, gridHeight, i), Vector3(1000, gridHeight, i), Vector4(0.5, 1.0, 0.5, 1.0));
        }else{
            if (i % 10 == 0){
                lines.addLine(Vector3(-1000, gridHeight, i), Vector3(1000, gridHeight, i), Vector4(0.5, 0.5, 0.5, 1.0));
            }else{
                lines.addLine(Vector3(-1000, gridHeight, i), Vector3(1000, gridHeight, i), Vector4(0.5, 0.5, 0.5, 0.5));
            }
        }
    }

    camera.setPosition(0, 7, 20);
    camera.setTarget(0, 2, 0);

    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
    Engine::onMouseScroll = onMouseScroll;

}

void onTouchMove(int pointer, float x, float y){
    float difX = lastTouchPos.x - x;
    float difY = lastTouchPos.y - y;
    lastTouchPos = Vector2(x, y);

    if (Input::isMousePressed(D_MOUSE_BUTTON_1)){
        camera.walkForward(-0.05 * difY);
        camera.slide(0.02 * difX);
    }else{
        camera.rotatePosition(0.1 * difX);
        camera.elevatePosition(-0.1 * difY);
    }

}

void onTouchStart(int pointer, float x, float y){
    lastTouchPos = Vector2(x, y);
}

void onMouseScroll(float xoffset, float yoffset, int mods){
    camera.zoom(1.0 * yoffset);
}