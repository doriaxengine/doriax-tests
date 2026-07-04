#include "Doriax.h"

using namespace doriax;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;


Scene scene;

Camera camera(&scene);
Shape terrain(&scene);
SkyBox sky(&scene);
Light* sun = NULL;

Sprite tree1(&scene);
Text text1(&scene);

Sprite tree2(&scene);
Text text2(&scene);

DORIAX_INIT void init(){
    scene.setGlobalIllumination(0.1);
    scene.setCamera(camera.getEntity());

    camera.setPosition(0, 7, -40);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");

    tree1.setTexture("tree_08_10000.png");
    tree1.setBillboard(true, false, true);
    tree1.setScale(0.1);
    tree1.setPosition(10,0,0);
    tree1.setSize(100,100);
    tree1.setPivotPreset(PivotPreset::BOTTOM_CENTER);
    tree1.addChild(&text1);
    
    text1.setText("True billboard");
    text1.setScale(0.5);
    text1.setPivotCentered(true);
    text1.setPosition(0,100,0);

    tree2.setTexture("tree_08_10000.png");
    tree2.setBillboard(true);
    tree2.setCylindricalBillboard(true);
    tree2.setScale(0.1);
    tree2.setPosition(-10,0,0);
    tree2.setSize(100,100);
    tree2.setPivotPreset(PivotPreset::BOTTOM_CENTER);
    tree2.addChild(&text2);
    
    text2.setBillboard(true);
    text2.setText("Fake billboard");
    text2.setScale(0.5);
    text2.setPivotCentered(true);
    text2.setPosition(0,100,0);

    sky.setTextureNegativeZ("ely_hills/hills_lf.tga");
    sky.setTexturePositiveZ("ely_hills/hills_rt.tga");
    sky.setTextureNegativeX("ely_hills/hills_bk.tga");
    sky.setTexturePositiveX("ely_hills/hills_ft.tga");
    sky.setTextureNegativeY("ely_hills/hills_dn.tga");
    sky.setTexturePositiveY("ely_hills/hills_up.tga");

    if (!sun)
        sun = new Light(&scene);
    sun->setType(LightType::DIRECTIONAL);
    sun->setDirection(0,-0.7, 0.8);
    sun->setIntensity(10);
    sun->setShadows(true);

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
    //model.getAnimation(0).start();
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
