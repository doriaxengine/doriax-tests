
#include "Doriax.h"
using namespace doriax;

Scene scene;
Image image(&scene);
Container textcontainer(&scene);
Text text1(&scene);
Text text2(&scene);

Scene carscene;
Camera* camera;
Shape terrain(&carscene);
Model car(&carscene);
SkyBox sky(&carscene);

float curve = 0;
float speed = 0;
float rotation = 0;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);

DORIAX_INIT void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);

    camera = new Camera(&carscene);

    camera->setFramebufferFilter(TextureFilter::NEAREST);
    camera->setFramebufferSize(512, 512);
    camera->setRenderToTexture(true);
    camera->setPosition(0, 5, 20);
    carscene.setCamera(camera->getEntity());

    terrain.createPlane(200, 200);
    terrain.setTexture("road.png");

    car.loadModel("jeep/Jeep.obj");
    car.setScale(0.5);

    sky.setTextureNegativeZ("ely_hills/hills_lf.tga");
    sky.setTexturePositiveZ("ely_hills/hills_rt.tga");
    sky.setTextureNegativeX("ely_hills/hills_bk.tga");
    sky.setTexturePositiveX("ely_hills/hills_ft.tga");
    sky.setTextureNegativeY("ely_hills/hills_dn.tga");
    sky.setTexturePositiveY("ely_hills/hills_up.tga");

    image.setTexture(camera->getFramebuffer());
    image.setPosition(550,100,0);
    image.setSize(400, 300);
    image.setAnchorPreset(AnchorPreset::CENTER);

    textcontainer.setAnchorPreset(AnchorPreset::CENTER_TOP);
    textcontainer.addChild(&text1);
    textcontainer.addChild(&text2);

    text1.setText("Press F to fullscreen draw rect");
    text1.setFontSize(20);
    text1.setAnchorPreset(AnchorPreset::CENTER);
    text2.setText("Press R to change resolution");
    text2.setFontSize(20);
    text2.setAnchorPreset(AnchorPreset::CENTER);

    Engine::setScene(&scene);
    Engine::addSceneLayer(&carscene);
    Engine::setScalingMode(Scaling::NATIVE);

    Engine::onKeyDown = onKeyDown;
    Engine::onUpdate = onUpdate;

}

void onKeyDown(int key, bool repeat, int mods){
    if (key == D_KEY_F){
        if (image.getAnchorPreset() == AnchorPreset::CENTER){
            image.setAnchorPreset(AnchorPreset::FULL_LAYOUT);
        }else{
            image.setSize(400, 300);
            image.setAnchorPreset(AnchorPreset::CENTER);
        }
    }
    if (key == D_KEY_R){
        if (camera->getFramebuffer()->getWidth() == 512){
            camera->setFramebufferSize(256, 256);
        }else{
            camera->setFramebufferSize(512, 512);
        }
    }
}

void onUpdate(){
    if (Input::isKeyPressed(D_KEY_UP)){
        speed += 0.1;
    }else if (Input::isKeyPressed(D_KEY_DOWN)){
        speed -= 0.1;
    }
    speed *= 0.95;

    if (Input::isKeyPressed(D_KEY_LEFT)){
        if (curve < 3)
            curve += 0.4;
    }else if (Input::isKeyPressed(D_KEY_RIGHT)){
        if (curve > -3)
            curve -= 0.4;
    }else{
        curve = 0;
    }

    rotation += curve;
    if (rotation > 360)
        rotation = rotation - 360;
    if (rotation < 0)
        rotation = 360 + rotation;

    Vector3 vDir(cos(Angle::degToRad(rotation-90)), 0, -sin(Angle::degToRad(rotation-90)));

    car.setRotation(0,rotation,0);
    car.setPosition(car.getPosition() + (vDir*speed));

    camera->setTarget(car.getPosition());
}
