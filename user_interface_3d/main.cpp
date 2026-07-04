#include "Doriax.h"

using namespace doriax;

void onUpdate();
void onCharInput(wchar_t codepoint);
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);
void onTouchEnd(int pointer, float x, float y);

void onWindowResize(int width, int height);
void onChangeScroll(float step);
void onPress();
void onPress2();

Vector2 lastTouchPos;

Scene scene;

Camera camera(&scene);
Shape terrain(&scene);
SkyBox sky(&scene);
Light sun(&scene);

Sprite wall(&scene);


Scene uiscene;

Panel window(&uiscene);
Container windowcontainer(&uiscene);
Container iconlist(&uiscene);
Scrollbar scroll(&uiscene);

Panel window2(&uiscene);
Button button(&uiscene);
Button button2(&uiscene);
TextEdit textedit(&uiscene);
Text text(&uiscene);
Container vcontainer(&uiscene);
Container hcontainer(&uiscene);


DORIAX_INIT void init(){
    scene.setCamera(camera.getEntity());
    scene.setGlobalIllumination(0.5);

    camera.setPosition(0, 7, 40);
    camera.setTarget(0, 15, 0);
    camera.setName("camera");

    //sun.setType(LightType::DIRECTIONAL);
    //sun.setDirection(0, -0.4, -0.6);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");
    terrain.setName("terrain");

    Camera* camera2 = new Camera(&uiscene);

    camera2->setType(CameraType::CAMERA_UI);
    camera2->setFramebufferSize(1024, 1024);
    camera2->setRenderToTexture(true);
    uiscene.setEnableUIEvents(false);
    uiscene.setBackgroundColor(0.8, 0.8, 0.8, 0.2);

    uiscene.setCamera(camera2->getEntity());

    //=========================================

    wall.setTexture(camera2->getFramebuffer());
    wall.setSize(10,10);
    wall.setRotation(0, 45, 0);
    wall.setPosition(-5,5,30);
    wall.setName("wall");

    window.addChild(&windowcontainer);
    window.setSize(430, 400);
    window.setTitle("Window");
    window.setPatchMargin(10, 10, 50, 10);
    window.setPosition(100, 200); 
    window.setHeaderColor(0.5, 0.5, 0.8, 1.0);
    window.getComponent<PanelComponent>().onResize = onWindowResize;

    windowcontainer.setType(ContainerType::HORIZONTAL);
    windowcontainer.setAnchorPreset(AnchorPreset::FULL_LAYOUT);
    windowcontainer.addChild(&iconlist);
    windowcontainer.addChild(&scroll);
    windowcontainer.setName("windowcontainer");
    windowcontainer.setBoxExpand(1, false);

    iconlist.setType(ContainerType::HORIZONTAL_WRAP);
    iconlist.setAnchorPreset(AnchorPreset::TOP_WIDE);
    iconlist.setName("iconlist");

    scroll.setSize(20, 20);
    scroll.setColor(0.5, 0.5, 0.5);
    scroll.setBarSize(0.6);
    scroll.setBarColor(0.8, 0.8, 0.8, 1.0);
    scroll.setStep(0.0);
    scroll.setType(ScrollbarType::VERTICAL);
    scroll.setAnchorPreset(AnchorPreset::VERTICAL_CENTER_WIDE);
    scroll.getComponent<ScrollbarComponent>().onChange = onChangeScroll;
    scroll.setBarPatchMargin(5);

    for (int i = 0; i < 22; i++){
        Container* iconset = new Container(window.getScene());
        Image* iconimage = new Image(window.getScene());
        Text* icontext = new Text(window.getScene());

        iconlist.addChild(iconset);

        iconset->addChild(iconimage);
        iconset->addChild(icontext);
        iconset->setName("iconset");
        iconset->setAnchorPreset(AnchorPreset::CENTER);

        iconimage->setTexture("paper_icon.png");
        iconimage->setSize(30, 40);
        iconimage->setAnchorPreset(AnchorPreset::CENTER);
        iconimage->setName("iconimage");
        icontext->setText("terrain_"+std::to_string(i)+".obj");
        icontext->setColor(0, 0, 0, 1);
        icontext->setFontSize(20);
        icontext->setAnchorPreset(AnchorPreset::CENTER);
    }

    //=========================================

    window2.setSize(430, 400);
    window2.setTitle("Files");
    window2.setPatchMargin(10, 10, 50, 10);
    window2.setPosition(400, 400); 
    window2.setHeaderColor(0.5, 0.5, 0.8, 1.0);
    window2.addChild(&vcontainer);

    vcontainer.addChild(&hcontainer);
    vcontainer.addChild(&button2);
    vcontainer.addChild(&text);
    vcontainer.setBoxExpand(0, true);
    vcontainer.setBoxExpand(1, false);
    vcontainer.setBoxExpand(2, true);

    hcontainer.addChild(&textedit);
    hcontainer.addChild(&button);
    hcontainer.setBoxExpand(true);

    vcontainer.setType(ContainerType::VERTICAL);
    vcontainer.setName("vcontainer");
    vcontainer.setAnchorPreset(AnchorPreset::FULL_LAYOUT);

    hcontainer.setType(ContainerType::HORIZONTAL);
    hcontainer.setName("hcontainer");
    hcontainer.setAnchorPreset(AnchorPreset::HORIZONTAL_CENTER_WIDE);

    button.setColor(0.6, 0.6, 0.5, 1.0);
    button.setColorPressed(0.6, 0.2, 0.6, 1.0);
    button.setColorDisabled(0.2, 0.6, 0.6, 1.0);
    button.setPosition(100, 200, 0);
    button.setSize(200, 100);
    button.setPatchMargin(5);
    button.setLabel("Insert");
    button.setName("button1");
    button.setLabelFontSize(40);
    button.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button.getComponent<ButtonComponent>().onPress = onPress;
    button.setAnchorPreset(AnchorPreset::CENTER);

    button2.setColor(0.6, 0.6, 0.5, 1.0);
    button2.setColorPressed(0.6, 0.2, 0.6, 1.0);
    button2.setColorDisabled(0.2, 0.6, 0.6, 1.0);
    button2.setPosition(100, 200, 0);
    button2.setSize(200, 100);
    button2.setPatchMargin(5);
    button2.setLabel("Move position");
    button2.setName("button2");
    button2.setLabelFontSize(40);
    button2.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button2.getComponent<ButtonComponent>().onPress = onPress2;
    button2.setAnchorPreset(AnchorPreset::HORIZONTAL_CENTER_WIDE);

    textedit.setPosition(300, 50, 0);
    textedit.setTexture("textedit.png");
    //textedit.setColor(0.3, 0.3, 0.3, 1.0);
    textedit.setPatchMargin(5);
    textedit.setSize(200, 50);
    textedit.setText("");
    textedit.setName("textedit");
    textedit.setAnchorPreset(AnchorPreset::CENTER);

    text.setText("Any text");
    text.setName("textobject");
    text.setColor(Vector4(0.2, 0.2, 0.2, 1.0));
    text.setAnchorPreset(AnchorPreset::CENTER_BOTTOM);

    sky.setTextureNegativeZ("ely_hills/hills_lf.tga");
    sky.setTexturePositiveZ("ely_hills/hills_rt.tga");
    sky.setTextureNegativeX("ely_hills/hills_bk.tga");
    sky.setTexturePositiveX("ely_hills/hills_ft.tga");
    sky.setTextureNegativeY("ely_hills/hills_dn.tga");
    sky.setTexturePositiveY("ely_hills/hills_up.tga");

    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
    Engine::onCharInput = onCharInput;
    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
    Engine::onTouchEnd = onTouchEnd;
}

void onUpdate(){
    if (!uiscene.getSystem<UISystem>()->isTextEditFocused()){
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
}

void onCharInput(wchar_t codepoint){
    uiscene.getSystem<UISystem>()->eventOnCharInput(codepoint);
}

void onKeyDown(int key, bool repeat, int mods){

}

void onTouchMove(int pointer, float x, float y){
    Vector3 normal = ((wall.getModelMatrix() * Vector3(0, 0, 1)) - wall.getWorldPosition()).normalize();
    Plane plane(normal, wall.getWorldPosition());
    RayReturn rretrun = camera.screenToRay(x, y).intersects(plane);
    Vector3 point = wall.getModelMatrix().inverse() * rretrun.point;

    if (!uiscene.getSystem<UISystem>()->eventOnPointerMove(point.x * 1024 / 10, (wall.getHeight() - point.y) * 1024 / 10)){
        float difX = lastTouchPos.x - x;
        float difY = lastTouchPos.y - y;
        lastTouchPos = Vector2(x, y);

        camera.rotateView(0.1 * difX);
        camera.elevateView(0.1 * difY);
    }
}

void onTouchStart(int pointer, float x, float y){
    Vector3 normal = ((wall.getModelMatrix() * Vector3(0, 0, 1)) - wall.getWorldPosition()).normalize();
    Plane plane(normal, wall.getWorldPosition());
    RayReturn rretrun = camera.screenToRay(x, y).intersects(plane);
    Vector3 point = wall.getModelMatrix().inverse() * rretrun.point;

    if (!uiscene.getSystem<UISystem>()->eventOnPointerDown(point.x * 1024 / 10, (wall.getHeight() - point.y) * 1024 / 10)){
        lastTouchPos = Vector2(x, y);
    }
}

void onTouchEnd(int pointer, float x, float y){
    Vector3 normal = ((wall.getModelMatrix() * Vector3(0, 0, 1)) - wall.getWorldPosition()).normalize();
    Plane plane(normal, wall.getWorldPosition());
    RayReturn rretrun = camera.screenToRay(x, y).intersects(plane);
    Vector3 point = wall.getModelMatrix().inverse() * rretrun.point;

    uiscene.getSystem<UISystem>()->eventOnPointerUp(point.x * 1024 / 10, (wall.getHeight() - point.y) * 1024 / 10);
}

void onWindowResize(int width, int height){
    float contentH = static_cast<float>(iconlist.getContentHeight());
    float viewportH = static_cast<float>(windowcontainer.getHeight());

    float bar = (contentH > 0.0f) ? (viewportH / contentH) : 1.0f;
    if (bar > 1.0f) bar = 1.0f;
    scroll.setBarSize(bar);

    scroll.setVisible(bar < 1.0f);
}

void onChangeScroll(float step){
    int contentH = static_cast<int>(iconlist.getContentHeight());
    int viewportH = static_cast<int>(windowcontainer.getHeight());

    int scrollRange = std::max(0, contentH - viewportH);
    iconlist.setPositionOffset(Vector2(0, -step * scrollRange));
}

void onPress(){
    text.setText(textedit.getText());
}

void onPress2(){
    if (text.getAnchorPreset() == AnchorPreset::CENTER_BOTTOM){
        text.setAnchorPreset(AnchorPreset::CENTER_RIGHT);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_RIGHT){
        text.setAnchorPreset(AnchorPreset::CENTER_TOP);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_TOP){
        text.setAnchorPreset(AnchorPreset::CENTER_LEFT);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_LEFT){
        text.setAnchorPreset(AnchorPreset::CENTER_BOTTOM);
    }
}