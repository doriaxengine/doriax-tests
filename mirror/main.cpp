#include "Doriax.h"

using namespace doriax;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;

Scene scene;

Model model(&scene);
Camera camera(&scene);
Shape terrain(&scene);
SkyBox sky(&scene);
Light sun(&scene);

Shape mirror(&scene);


DORIAX_INIT void init(){
    scene.setCamera(camera.getEntity());
    scene.setGlobalIllumination(0.5);

    camera.setPosition(0, 7, 40);
    camera.setName("camera");

    sun.setType(LightType::DIRECTIONAL);
    sun.setDirection(0, -0.4, -0.6);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");
    terrain.setName("terrain");

    // A planar mirror in a single call: an upright wall surface turned into a
    // mirror. The engine creates and drives the reflection camera internally and
    // feeds it back to the surface — no manual camera or per-frame aiming needed.
    mirror.createWall(10, 10);          // vertical quad, +Z normal (faces the camera)
    mirror.setPosition(0, 5, 0);
    mirror.setAsMirror();               // default normal +Z matches the wall
    mirror.setReceiveLights(false);     // show the reflection directly, unshaded
    mirror.setName("mirror");

    model.loadModel("WaterBottle.glb");
    model.setScale(20);
    model.setPosition(0,3,20);

    sky.setTextureNegativeZ("ely_hills/hills_lf.tga");
    sky.setTexturePositiveZ("ely_hills/hills_rt.tga");
    sky.setTextureNegativeX("ely_hills/hills_bk.tga");
    sky.setTexturePositiveX("ely_hills/hills_ft.tga");
    sky.setTextureNegativeY("ely_hills/hills_dn.tga");
    sky.setTexturePositiveY("ely_hills/hills_up.tga");

    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onUpdate(){

    if (Input::isKeyPressed(D_KEY_UP) || Input::isKeyPressed(D_KEY_W)){
        camera.walkForward(1);
    }else if (Input::isKeyPressed(D_KEY_DOWN) || Input::isKeyPressed(D_KEY_S)){
        camera.walkForward(-1);
    }

    if (Input::isKeyPressed(D_KEY_A)){
        camera.slide(-1);
    }else if (Input::isKeyPressed(D_KEY_D)){
        camera.slide(1);
    }

    if (Input::isKeyPressed(D_KEY_LEFT)){
        camera.rotateView(2);
    }else if (Input::isKeyPressed(D_KEY_RIGHT)){
        camera.rotateView(-2);
    }
}

void onKeyDown(int key, bool repeat, int mods){

}

void onTouchMove(int pointer, float x, float y){
    float difX = lastTouchPos.x - x;
    float difY = lastTouchPos.y - y;
    lastTouchPos = Vector2(x, y);

    camera.rotateView(0.1 * difX);
    camera.elevateView(0.1 * difY);
}

void onTouchStart(int pointer, float x, float y){
    lastTouchPos = Vector2(x, y);
}
