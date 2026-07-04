#include "Doriax.h"
using namespace doriax;

void onUpdate();
void onCharInput(wchar_t);
void onViewLoaded();
void onKeyDown(int key, bool repeat, int mods);
void onKeyUp(int key, bool repeat, int mods);
void onMouseDown(int button, float x, float y, int mods);
void onMouseUp(int button, float x, float y, int mods);
void onMouseMove(float x, float y, int mods);
void onMouseScroll(float xoffset, float yoffset, int mods);
void onMouseEnter();
void onMouseLeave();
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);
void onTouchEnd(int pointer, float x, float y);
void onTouchCancel();

void onButtonPress();
void onButtonRelease();
void onButtonMouseMove();

Scene scene;

Text text(&scene);

DORIAX_INIT void init(){

    text.setPosition(200, 200, 0);
    text.setText("Events example: check output");
    
    Engine::setAllowEventsOutCanvas(true);
    Engine::setCallMouseInTouchEvent(true);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
    Engine::onCharInput = onCharInput;
    Engine::onViewLoaded = onViewLoaded;
    Engine::onKeyDown = onKeyDown;
    Engine::onKeyUp = onKeyUp;
    Engine::onMouseDown = onMouseDown;
    Engine::onMouseUp = onMouseUp;
    Engine::onKeyDown = onKeyDown;
    Engine::onMouseMove = onMouseMove;
    Engine::onMouseScroll = onMouseScroll;
    Engine::onMouseEnter = onMouseEnter;
    Engine::onMouseLeave = onMouseLeave;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
    Engine::onTouchEnd = onTouchEnd;
    Engine::onTouchCancel = onTouchCancel;


    Engine::setScene(&scene);
}

void onUpdate(){

}

void onButtonPress(){
    Log::verbose("Button pressed!!");
}

void onButtonRelease(){
    Log::verbose("Button released!!");
}

void onButtonMouseMove(){
    Log::verbose("Button mouse move!!");
}

void onViewLoaded(){
    Log::verbose("View loaded");
}

void onTouchStart(int pointer, float x, float y){
    Log::verbose("Touch start %i - %f %f", pointer, x, y);
}
void onTouchMove(int pointer, float x, float y){
    Log::verbose("Touch move %i - %f %f", pointer, x, y);
}
void onTouchEnd(int pointer, float x, float y){
    Log::verbose("Touch end %i - %f %f", pointer, x, y);
}
void onTouchCancel(){
    Log::verbose("Touch cancel");
}

void onMouseDown(int button, float x, float y, int mods){
    std::string modifier = "";
    if (mods & D_MODIFIER_SHIFT)
        modifier += "shift;";
    if (mods & D_MODIFIER_CONTROL)
        modifier += "control;";
    if (mods & D_MODIFIER_ALT)
        modifier += "alt;";
    if (mods & D_MODIFIER_SUPER)
        modifier += "super;";
    if (mods & D_MODIFIER_CAPS_LOCK)
        modifier += "caps;";
    if (mods & D_MODIFIER_NUM_LOCK)
        modifier += "num;";

    std::string bt = "";
    if (button == D_MOUSE_BUTTON_LEFT)
        bt = "left";
    if (button == D_MOUSE_BUTTON_RIGHT)
        bt = "right";
    if (button == D_MOUSE_BUTTON_MIDDLE)
        bt = "middle";


    Log::verbose("Mouse down - %s - %s", bt.c_str(), modifier.c_str());
}

void onMouseUp(int button, float x, float y, int mods){
    std::string modifier = "";
    if (mods & D_MODIFIER_SHIFT)
        modifier += "shift;";
    if (mods & D_MODIFIER_CONTROL)
        modifier += "control;";
    if (mods & D_MODIFIER_ALT)
        modifier += "alt;";
    if (mods & D_MODIFIER_SUPER)
        modifier += "super;";
    if (mods & D_MODIFIER_CAPS_LOCK)
        modifier += "caps;";
    if (mods & D_MODIFIER_NUM_LOCK)
        modifier += "num;";

    std::string bt = "";
    if (button == D_MOUSE_BUTTON_LEFT)
        bt = "left";
    if (button == D_MOUSE_BUTTON_RIGHT)
        bt = "right";
    if (button == D_MOUSE_BUTTON_MIDDLE)
        bt = "middle";


    Log::verbose("Mouse up - %s - %s", bt.c_str(), modifier.c_str());
}

void onMouseMove(float x, float y, int mods){
    Log::verbose("Mouse %f %f", x, y);
}

void onMouseScroll(float xoffset, float yoffset, int mods){
    if (xoffset != 0 || yoffset != 0)
        Log::verbose("Mouse scroll %f %f", xoffset, yoffset);
}

void onMouseEnter(){
    Log::verbose("Mouse enter");
}

void onMouseLeave(){
    Log::verbose("Mouse leave");
}

void onCharInput(wchar_t codepoint){
    Log::verbose("%s",StringUtils::toUTF8(codepoint).c_str());
}

void onKeyDown(int key, bool repeat, int mods){
    std::string modifier = "";
    if (mods & D_MODIFIER_SHIFT)
        modifier += "shift;";
    if (mods & D_MODIFIER_CONTROL)
        modifier += "control;";
    if (mods & D_MODIFIER_ALT)
        modifier += "alt;";
    if (mods & D_MODIFIER_SUPER)
        modifier += "super;";
    if (mods & D_MODIFIER_CAPS_LOCK)
        modifier += "caps;";
    if (mods & D_MODIFIER_NUM_LOCK)
        modifier += "num;";
    
    std::string rstr;
    if (repeat)
        rstr = "repeated";
    
    Log::verbose("KeyDown: %i - %s - %s",key, modifier.c_str(), rstr.c_str());
}

void onKeyUp(int key, bool repeat, int mods){
    std::string modifier = "";
    if (mods & D_MODIFIER_SHIFT)
        modifier += "shift;";
    if (mods & D_MODIFIER_CONTROL)
        modifier += "control;";
    if (mods & D_MODIFIER_ALT)
        modifier += "alt;";
    if (mods & D_MODIFIER_SUPER)
        modifier += "super;";
    if (mods & D_MODIFIER_CAPS_LOCK)
        modifier += "caps;";
    if (mods & D_MODIFIER_NUM_LOCK)
        modifier += "num;";
    
    std::string rstr;
    if (repeat)
        rstr = "repeated";
    
    Log::verbose("KeyUp: %i - %s - %s",key, modifier.c_str(), rstr.c_str());
}
