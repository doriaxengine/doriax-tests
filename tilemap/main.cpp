#include "Doriax.h"
using namespace doriax;

Scene uiscene;
Text text(&uiscene);

Scene scene;

Camera camera(&scene);

std::vector<Sprite> objects;
Sprite bg(&scene);
Object map(&scene);
Tilemap tilemap(&scene);

const int tilesize = 128;
const int numObjects = 4;

void onUpdate();


DORIAX_INIT void init(){

    camera.setType(CameraType::CAMERA_ORTHO);
    camera.setTransparentSort(false);
    scene.setCamera(camera.getEntity());
    scene.setBackgroundColor(0.867, 0.973, 1.0);

    text.setText("Use left and right arrow to move");
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);
    text.setColor(0.3, 0.3, 0.3, 1.0);

    map.setScale(0.6);
    map.addChild(&tilemap);

    objects.clear();
    objects.reserve(numObjects);
    for (int i = 0; i < numObjects; i++){
        objects.emplace_back(&scene);
        map.addChild(&objects[i]);
    }

    bg.setTexture("bg/BG.png");

    objects[0].setTexture("object/Tree_1.png");
    objects[0].setPosition(1*tilesize, 5*tilesize, 0);
    objects[0].setTextureScaleFactor(1.0);
    objects[1].setTexture("object/Tree_2.png");
    objects[1].setPosition(5*tilesize, 2*tilesize, 0);
    objects[1].setTextureScaleFactor(1.0);
    objects[2].setTexture("object/Stone.png");
    objects[2].setPosition(7*tilesize, 5*tilesize, 0);
    objects[2].setTextureScaleFactor(1.0);
    objects[3].setTexture("object/Sign_1.png");
    objects[3].setPosition(11*tilesize, 3*tilesize, 0);
    objects[3].setTextureScaleFactor(1.0);

    tilemap.setTextureScaleFactor(1.0);

    for (int i = 0; i < 2; i++){
        tilemap.addRect(i+16, "water"+std::to_string(i), "tiles/tileset2.png", TextureFilter::NEAREST, Rect(tilesize*i,0,tilesize,tilesize));
    }

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            tilemap.addRect(4*i + j, "tile"+std::to_string(i)+std::to_string(j), "tiles/tileset1.png", TextureFilter::NEAREST, Rect(tilesize*j,tilesize*i,tilesize,tilesize));
        }
    }

    tilemap.addTile(0,  Vector2(0*tilesize,4*tilesize), tilesize, tilesize);
    tilemap.addTile(1,  Vector2(1*tilesize,4*tilesize), tilesize, tilesize);
    tilemap.addTile(2,  Vector2(2*tilesize,4*tilesize), tilesize, tilesize);
    tilemap.addTile(3,  Vector2(0*tilesize,3*tilesize), tilesize, tilesize);
    tilemap.addTile(4,  Vector2(1*tilesize,3*tilesize), tilesize, tilesize);
    tilemap.addTile(5,  Vector2(2*tilesize,3*tilesize), tilesize, tilesize);
    tilemap.addTile(11, Vector2(0*tilesize,2*tilesize), tilesize, tilesize);
    tilemap.addTile(8,  Vector2(1*tilesize,2*tilesize), tilesize, tilesize);
    tilemap.addTile(15, Vector2(2*tilesize,2*tilesize), tilesize, tilesize);

    tilemap.addTile(0,  Vector2(4*tilesize,1*tilesize), tilesize, tilesize);
    tilemap.addTile(1,  Vector2(5*tilesize,1*tilesize), tilesize, tilesize);
    tilemap.addTile(2,  Vector2(6*tilesize,1*tilesize), tilesize, tilesize);
    tilemap.addTile(3,  Vector2(4*tilesize,0*tilesize), tilesize, tilesize);
    tilemap.addTile(4,  Vector2(5*tilesize,0*tilesize), tilesize, tilesize);
    tilemap.addTile(5,  Vector2(6*tilesize,0*tilesize), tilesize, tilesize);

    tilemap.addTile(12,  Vector2(6*tilesize,4*tilesize), tilesize, tilesize);
    tilemap.addTile(13,  Vector2(7*tilesize,4*tilesize), tilesize, tilesize);
    tilemap.addTile(14,  Vector2(8*tilesize,4*tilesize), tilesize, tilesize);

    tilemap.addTile(12,  Vector2(11*tilesize,2*tilesize), tilesize, tilesize);
    tilemap.addTile(14,  Vector2(12*tilesize,2*tilesize), tilesize, tilesize);

    //water
    for (int i = -10; i < 20; i++){
        tilemap.addTile(17, Vector2(i*tilesize,0*tilesize), tilesize, tilesize);
        tilemap.addTile(16, Vector2(i*tilesize,1*tilesize), tilesize, tilesize);
    }

    bg.setAutoTransparency(false);
    tilemap.setAutoTransparency(false);
    for (auto& object : objects){
        object.setAutoTransparency(false);
    }

    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
}

void onUpdate() {
    if (Input::isKeyPressed(D_KEY_LEFT)){
        Vector3 oldPos = map.getPosition();
        map.setPosition(oldPos.x+10, oldPos.y, oldPos.z);
    }else if (Input::isKeyPressed(D_KEY_RIGHT)){
        Vector3 oldPos = map.getPosition();
        map.setPosition(oldPos.x-10, oldPos.y, oldPos.z);
    }
}