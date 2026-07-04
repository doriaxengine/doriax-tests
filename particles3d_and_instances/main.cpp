#include "Doriax.h"

using namespace doriax;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;

enum class ParticlesType{
    MODEL,
    SPRITE
};

std::string parttext(" particles (press SPACE to change)");

Scene scene;

Camera camera(&scene);
Shape terrain(&scene);
SkyBox sky(&scene);
Light sun(&scene);

Particles particles(&scene);
Sprite sprite(&scene);
Shape cube(&scene);

Model trees(&scene);

Scene uiscene;
Text text(&uiscene);

ParticlesType type;

DORIAX_INIT void init(){
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);

    text.setText("Sprite" + parttext);
    type = ParticlesType::SPRITE;

    scene.setGlobalIllumination(0.1);
    scene.setCamera(camera.getEntity());

    camera.setPosition(0, 7, 40);
    camera.setTarget(0, 7, 0);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");

    cube.createBox(1,1,1);
    cube.setColor(0.2, 0.4, 1.0, 1.0);
    cube.setVisible(false);
    //cube.setCastShadows(false);

    //sprite.setPosition(0, 7, 0);
    sprite.setPivotPreset(PivotPreset::CENTER);
    sprite.setTexture("particle.png");
    sprite.setColor(0.2, 0.4, 1.0, 1.0);
    //sprite.setBillboard(true, true, false);
    sprite.createInstancedMesh();
    sprite.setInstancedBillboard(true);
    sprite.setCastShadows(false);
    sprite.setReceiveShadows(false);
    sprite.setSize(2,2);
    
    particles.setMaxParticles(100);
    particles.setRate(10);
    particles.setTarget(&sprite);
    particles.setLifeInitializer(5);
    particles.setSizeInitializer(4000,4000);
    particles.setVelocityInitializer(Vector3(-1,5,-1), Vector3(1,8,1));
    //particles.setVelocityInitializer(Vector3(0,5,3), Vector3(0,8,3));
    particles.setAccelerationInitializer(Vector3(0, -5, 0));
    particles.start();

    trees.loadModel("CommonTree_1.obj");
    trees.setScale(3);
    for (int i = -100; i < 100; i+=20){
        for (int j = -100; j < 100; j+=20){
            if ((i > 10 || i < -10) && (j > 10 || j < -10))
                trees.addInstance(i/3.0, 0.0, j/3.0);
        }
    }

    sky.setTextureNegativeZ("ely_hills/hills_lf.tga");
    sky.setTexturePositiveZ("ely_hills/hills_rt.tga");
    sky.setTextureNegativeX("ely_hills/hills_bk.tga");
    sky.setTexturePositiveX("ely_hills/hills_ft.tga");
    sky.setTextureNegativeY("ely_hills/hills_dn.tga");
    sky.setTexturePositiveY("ely_hills/hills_up.tga");

    sun.setType(LightType::DIRECTIONAL);
    sun.setDirection(0,-0.7, -0.8);
    sun.setIntensity(10);
    sun.setShadows(true);

    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
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
    if (key == D_KEY_SPACE){
        if (type == ParticlesType::SPRITE){
            text.setText("Model" + parttext);
            type = ParticlesType::MODEL;
            particles.setTarget(&cube);

            sprite.clearInstances();
            sprite.setVisible(false);
            cube.setVisible(true);
        }else{
            text.setText("Sprite" + parttext);
            type = ParticlesType::SPRITE;
            particles.setTarget(&sprite);

            cube.clearInstances();
            cube.setVisible(false);
            sprite.setVisible(true);
        }
    }
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
