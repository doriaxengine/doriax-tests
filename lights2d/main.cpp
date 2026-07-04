#include "Doriax.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace doriax;

const int canvasWidth = 1000;
const int canvasHeight = 600;
const int numBlocks = 10;

struct BlockData{
    float x;
    float y;
    unsigned int size;
    float r;
    float g;
    float b;
};

Scene scene;
Camera camera(&scene);

Sprite background(&scene);
std::vector<Sprite> blocks;

Light2D mouseLight(&scene);
Light2D fillLight(&scene);
Polygon mouseLightMarker(&scene);

bool draggingLight = false;

void moveMouseLight(float x, float y);
void createLightMarker();
void addBlock(int index, const BlockData& data);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);
void onTouchEnd(int pointer, float x, float y);
void onMouseDown(int button, float x, float y, int mods);
void onMouseMove(float x, float y, int mods);
void onMouseUp(int button, float x, float y, int mods);

DORIAX_INIT void init(){
    camera.setType(CameraType::CAMERA_ORTHO);
    camera.setTransparentSort(false);
    scene.setCamera(camera.getEntity());
    scene.setBackgroundColor(0.015, 0.017, 0.025);
    scene.setAmbientLight2D(0.12, Vector3(0.45, 0.48, 0.56));
    scene.setShadow2DQuality(ShadowQuality::MEDIUM);

    background.setName("background");
    background.setTexture("ground.png");
    background.setPosition(canvasWidth * 0.5, canvasHeight * 0.5, -2);
    background.setSize(canvasWidth, canvasHeight);
    background.setPivotPreset(PivotPreset::CENTER);
    background.setTextureScaleFactor(1.0);
    background.setColor(0.62, 0.66, 0.72, 1.0);
    background.setAutoTransparency(false);

    const BlockData blockData[numBlocks] = {
        {145, 130,  90, 0.90, 0.64, 0.42},
        {325,  95,  72, 0.48, 0.70, 0.90},
        {560, 125, 116, 0.74, 0.55, 0.90},
        {825, 105,  84, 0.88, 0.74, 0.38},
        {225, 305, 124, 0.62, 0.84, 0.55},
        {455, 285,  78, 0.88, 0.50, 0.50},
        {695, 315, 112, 0.50, 0.80, 0.82},
        {895, 365,  70, 0.83, 0.58, 0.78},
        {335, 505, 102, 0.92, 0.76, 0.52},
        {640, 500,  94, 0.56, 0.65, 0.92}
    };

    blocks.clear();
    blocks.reserve(numBlocks);
    for (int i = 0; i < numBlocks; i++){
        addBlock(i, blockData[i]);
    }

    fillLight.setName("cool fill light");
    fillLight.setPosition(860, 500, 0);
    fillLight.setColor(0.35, 0.55, 1.0);
    fillLight.setIntensity(0.75);
    fillLight.setRange(340);
    fillLight.setFalloff(1.8);
    fillLight.setHeight(18);
    fillLight.setShadows(true);
    fillLight.setShadowSoftness(3.0);
    fillLight.setMapResolution(512);

    mouseLight.setName("mouse light");
    mouseLight.setColor(1.0, 0.82, 0.45);
    mouseLight.setIntensity(1.65);
    mouseLight.setRange(330);
    mouseLight.setFalloff(1.35);
    mouseLight.setHeight(22);
    mouseLight.setShadows(true);
    mouseLight.setShadowBias(0.008);
    mouseLight.setShadowSoftness(2.0);
    mouseLight.setMapResolution(768);

    createLightMarker();

    moveMouseLight(505, 235);

    Engine::setCanvasSize(canvasWidth, canvasHeight);
    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);
    Engine::setCallMouseInTouchEvent(true);

    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
    Engine::onTouchEnd = onTouchEnd;
    Engine::onMouseDown = onMouseDown;
    Engine::onMouseMove = onMouseMove;
    Engine::onMouseUp = onMouseUp;
}

void addBlock(int index, const BlockData& data){
    blocks.emplace_back(&scene);

    Sprite& block = blocks.back();
    block.setName("occluder block " + std::to_string(index));
    block.setTexture("crate.png");
    block.setPosition(data.x, data.y, 0);
    block.setSize(data.size, data.size);
    block.setPivotPreset(PivotPreset::CENTER);
    block.setColor(data.r, data.g, data.b, 1.0);
    block.setAutoTransparency(false);

    Occluder2D occluder = block.getOccluder2D();
    occluder.setShape(Occluder2DShape::AUTO_QUAD);
    occluder.setEnabled(true);
}

void moveMouseLight(float x, float y){
    mouseLight.setPosition(x, y, 0);
    mouseLightMarker.setPosition(x, y, 2);
}

void createLightMarker(){
    const int segments = 20;
    const float radius = 9.0f;

    mouseLightMarker.setName("mouse light marker");
    for (int i = 0; i <= segments; i++){
        float x = -radius + (2.0f * radius * i) / segments;
        float y = std::sqrt(std::max(0.0f, radius * radius - x * x));
        mouseLightMarker.addVertex(x, y);
        mouseLightMarker.addVertex(x, -y);
    }
    mouseLightMarker.setColor(1.0, 0.9, 0.18, 1.0);
    mouseLightMarker.moveToTop();
}

void onTouchStart(int pointer, float x, float y){
    draggingLight = true;
    moveMouseLight(x, y);
}

void onTouchMove(int pointer, float x, float y){
    if (draggingLight || Input::isMousePressed(D_MOUSE_BUTTON_1)){
        moveMouseLight(x, y);
    }
}

void onTouchEnd(int pointer, float x, float y){
    draggingLight = false;
}

void onMouseDown(int button, float x, float y, int mods){
    if (button == D_MOUSE_BUTTON_1){
        draggingLight = true;
        moveMouseLight(x, y);
    }
}

void onMouseMove(float x, float y, int mods){
    if (draggingLight || Input::isMousePressed(D_MOUSE_BUTTON_1)){
        moveMouseLight(x, y);
    }
}

void onMouseUp(int button, float x, float y, int mods){
    if (button == D_MOUSE_BUTTON_1){
        draggingLight = false;
    }
}
