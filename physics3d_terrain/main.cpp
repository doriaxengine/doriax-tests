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

Text text(&uiscene);
Text text2(&uiscene);

Shape* cubes[25];
Shape* spheres[25];

void onViewLoaded();
void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onKeyUp(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

void startPositions(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cubes[(5*i)+j]->setPosition(10*i - 25, 15, 10*j - 25);
            cubes[(5*i)+j]->getBody3D().setLinearVelocity(Vector3(0,0,0));

            spheres[(5*i)+j]->setPosition(10*i - 20, 15, 10*j - 20);
            spheres[(5*i)+j]->getBody3D().setLinearVelocity(Vector3(0,0,0));
        }
    }
}

DORIAX_INIT void init(){

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            cubes[(5*i)+j] = new Shape(&scene);
            cubes[(5*i)+j]->createBox(1.0, 1.0, 1.0);
            cubes[(5*i)+j]->setTexture("block.png");
            cubes[(5*i)+j]->setName("cube"+std::to_string((4*i)+j));
            cubes[(5*i)+j]->getBody3D().setType(BodyType::DYNAMIC);
            cubes[(5*i)+j]->getBody3D().createBoxShape(1, 1, 1);
            cubes[(5*i)+j]->getBody3D().load();

            spheres[(5*i)+j] = new Shape(&scene);
            spheres[(5*i)+j]->createSphere(1.0);
            spheres[(5*i)+j]->setTexture("block.png");
            spheres[(5*i)+j]->setName("sphere"+std::to_string((4*i)+j));
            spheres[(5*i)+j]->getBody3D().setType(BodyType::DYNAMIC);
            spheres[(5*i)+j]->getBody3D().createSphereShape(1);
            spheres[(5*i)+j]->getBody3D().load();
        }
    }
    startPositions();

    camera.setPosition(0, 15, -50);
    scene.setCamera(camera.getEntity());

    terrain.setName("terrain");

    terrain.setHeightMap("heightmap.png");
    terrain.setTexture("ground.png");

    terrain.createTerrain();

    Body3D bodyterrain = terrain.getBody3D();
    bodyterrain.setType(BodyType::STATIC);
    bodyterrain.createHeightFieldShape();
    bodyterrain.load();

    scene.setGlobalIllumination(0.2);
    scene.setBackgroundColor(Vector4(0.5,0.5,0.5,1.0));

    sun.setType(LightType::DIRECTIONAL);
    sun.setDirection(0.0f, -0.3, -0.8);
    sun.setShadows(true);

    text.setAnchorPreset(AnchorPreset::TOP_LEFT);
    text2.setAnchorPreset(AnchorPreset::CENTER_TOP);
    text2.setText("Press space to reset");

    Engine::setCanvasSize(1000,480);
    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onViewLoaded = onViewLoaded;
    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onKeyUp = onKeyUp;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onViewLoaded(){


}

void onUpdate(){
    text.setText(std::string("FPS: ") + std::to_string(Engine::getFramerate()).c_str());

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

    if (key == D_KEY_SPACE){
        startPositions();
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