#include "Doriax.h"
using namespace doriax;

float lastX;
float lastY;
float lastPressX;
float lastPressY;

Scene scene;
Scene uiscene;

Camera camera(&scene);
Terrain terrain(&scene);
Light sun(&scene);

Container textcontainer(&uiscene);
Text text(&uiscene);
Text text2(&uiscene);
Text text3(&uiscene);
Text text4(&uiscene);

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onKeyUp(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

DORIAX_INIT void init(){
    camera.setPosition(0, 15, -60);

    terrain.setName("terrain");

    terrain.setHeightMap("heightmap.png");
    terrain.setTexture("ground.png");
    terrain.setBlendMap("blendmap.png");

    terrain.setTextureDetailRed("block.png");
    terrain.setTextureDetailGreen("block.png");
    terrain.setTextureDetailBlue("block.png");

    scene.setCamera(camera.getEntity());

    scene.setGlobalIllumination(0.1);

    sun.setType(LightType::DIRECTIONAL);
    sun.setDirection(0.0f, -0.3, -0.8);
    sun.setShadows(true);

    textcontainer.setAnchorPreset(AnchorPreset::TOP_LEFT);
    textcontainer.addChild(&text);
    textcontainer.addChild(&text2);
    textcontainer.addChild(&text3);
    textcontainer.addChild(&text4);

    Engine::setCanvasSize(1000,480);
    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onKeyUp = onKeyUp;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onUpdate(){
    text.setText(std::string("FPS: ") + std::to_string(Engine::getFramerate()).c_str());
    text2.setText(std::string("Camera X: ") + std::to_string(camera.getWorldPosition().x));
    text3.setText(std::string("Camera Y: ") + std::to_string(camera.getWorldPosition().y));
    text4.setText(std::string("Camera Z: ") + std::to_string(camera.getWorldPosition().z));

    if (Input::isKeyPressed(D_KEY_UP) || Input::isKeyPressed(D_KEY_W)){
        camera.walkForward(1);
    }
    if (Input::isKeyPressed(D_KEY_DOWN) || Input::isKeyPressed(D_KEY_S)){
        camera.walkForward(-1);
    }
    if (Input::isKeyPressed(D_KEY_LEFT)){
        camera.rotateView(1);
    }
    if (Input::isKeyPressed(D_KEY_RIGHT)){
        camera.rotateView(-1);
    }
    if (Input::isKeyPressed(D_KEY_A)){
        camera.slide(-1);
    }
    if (Input::isKeyPressed(D_KEY_D)){
        camera.slide(1);
    }

}

void onKeyDown(int key, bool repeat, int mods){
    if (key == D_KEY_X){
        camera.setPosition(camera.getPosition().x, camera.getPosition().y+10, camera.getPosition().z);
        camera.setTarget(camera.getTarget().x, camera.getTarget().y+10, camera.getTarget().z);
    }

    if (key == D_KEY_Z){
        camera.setPosition(camera.getPosition().x, camera.getPosition().y-10, camera.getPosition().z);
        camera.setTarget(camera.getTarget().x, camera.getTarget().y-10, camera.getTarget().z);
    }
}

void onKeyUp(int key, bool repeat, int mods){
    if (key == D_KEY_F){
        if (!System::instance().isFullscreen()) {
            System::instance().requestFullscreen();
        }else{
            System::instance().exitFullscreen();
        }
    }
}

void onTouchStart(int pointer, float x, float y) {
    lastX = x;
    lastY = y;
    lastPressX = x;
    lastPressY = y;
}

void onTouchMove(int pointer, float x, float y) {
    float difX = lastX - x;
    lastX = x;
    camera.rotateView(0.1 * difX);

    float difY = lastY - y;
    lastY = y;
    camera.elevateView(-0.1 * difY);
}