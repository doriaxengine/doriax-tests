canvasWidth = 1000
canvasHeight = 600
markerRadius = 9.0

scene = Scene()
camera = Camera(scene)

background = Sprite(scene)
blocks = {}
blockOccluders = {}

mouseLight = Light2D(scene)
fillLight = Light2D(scene)
mouseLightMarker = Polygon(scene)

draggingLight = false

blockData = {
    {x = 145, y = 130, size = 90,  color = {0.90, 0.64, 0.42}},
    {x = 325, y = 95,  size = 72,  color = {0.48, 0.70, 0.90}},
    {x = 560, y = 125, size = 116, color = {0.74, 0.55, 0.90}},
    {x = 825, y = 105, size = 84,  color = {0.88, 0.74, 0.38}},
    {x = 225, y = 305, size = 124, color = {0.62, 0.84, 0.55}},
    {x = 455, y = 285, size = 78,  color = {0.88, 0.50, 0.50}},
    {x = 695, y = 315, size = 112, color = {0.50, 0.80, 0.82}},
    {x = 895, y = 365, size = 70,  color = {0.83, 0.58, 0.78}},
    {x = 335, y = 505, size = 102, color = {0.92, 0.76, 0.52}},
    {x = 640, y = 500, size = 94,  color = {0.56, 0.65, 0.92}}
}

function addBlock(index, data)
    local block = Sprite(scene)
    blocks[#blocks + 1] = block

    block.name = "occluder block " .. tostring(index)
    block:setTexture("crate.png")
    block:setPosition(data.x, data.y, 0)
    block:setSize(data.size, data.size)
    block.pivotPreset = PivotPreset.CENTER
    block:setColor(data.color[1], data.color[2], data.color[3], 1.0)
    block.autoTransparency = false

    local occluder = block:getOccluder2D()
    blockOccluders[#blockOccluders + 1] = occluder

    occluder.shape = Occluder2DShape.AUTO_QUAD
    occluder.enabled = true
end

function moveMouseLight(x, y)
    mouseLight:setPosition(x, y, 0)
    mouseLightMarker:setPosition(x - markerRadius, y - markerRadius, 2)
end

function pointerYToSceneY(y)
    return canvasHeight - y
end

function moveMouseLightFromPointer(x, y)
    moveMouseLight(x, pointerYToSceneY(y))
end

function createLightMarker()
    local segments = 20
    local diameter = markerRadius * 2.0

    mouseLightMarker.name = "mouse light marker"
    for i = 0, segments do
        local x = (diameter * i) / segments
        local dx = x - markerRadius
        local y = math.sqrt(math.max(0.0, markerRadius * markerRadius - dx * dx))
        mouseLightMarker:addVertex(x, markerRadius + y)
        mouseLightMarker:addVertex(x, markerRadius - y)
    end
    mouseLightMarker:setColor(1.0, 0.9, 0.18, 1.0)
    mouseLightMarker:moveToTop()
end

function onTouchStart(pointer, x, y)
    draggingLight = true
    moveMouseLightFromPointer(x, y)
end

function onTouchMove(pointer, x, y)
    if draggingLight or Input.isMousePressed(Input.MOUSE_BUTTON_1) then
        moveMouseLightFromPointer(x, y)
    end
end

function onTouchEnd(pointer, x, y)
    draggingLight = false
end

function onMouseDown(button, x, y, mods)
    if button == Input.MOUSE_BUTTON_1 then
        draggingLight = true
        moveMouseLightFromPointer(x, y)
    end
end

function onMouseMove(x, y, mods)
    if draggingLight or Input.isMousePressed(Input.MOUSE_BUTTON_1) then
        moveMouseLightFromPointer(x, y)
    end
end

function onMouseUp(button, x, y, mods)
    if button == Input.MOUSE_BUTTON_1 then
        draggingLight = false
    end
end

camera.type = CameraType.CAMERA_ORTHO
camera.transparentSort = false
scene.camera = camera.entity
scene:setBackgroundColor(0.015, 0.017, 0.025)
scene:setAmbientLight2D(0.12, Vector3(0.45, 0.48, 0.56))
scene.shadow2DQuality = ShadowQuality.MEDIUM

background.name = "background"
background:setTexture("ground.png")
background:setPosition(canvasWidth * 0.5, canvasHeight * 0.5, -2)
background:setSize(canvasWidth, canvasHeight)
background.pivotPreset = PivotPreset.CENTER
background.textureScaleFactor = 1.0
background:setColor(0.62, 0.66, 0.72, 1.0)
background.autoTransparency = false

for i, data in ipairs(blockData) do
    addBlock(i - 1, data)
end

fillLight.name = "cool fill light"
fillLight:setPosition(860, 500, 0)
fillLight:setColor(0.35, 0.55, 1.0)
fillLight.intensity = 0.75
fillLight.range = 340
fillLight.falloff = 1.8
fillLight.height = 18
fillLight.shadows = true
fillLight.shadowSoftness = 3.0
fillLight.mapResolution = 512

mouseLight.name = "mouse light"
mouseLight:setColor(1.0, 0.82, 0.45)
mouseLight.intensity = 1.65
mouseLight.range = 330
mouseLight.falloff = 1.35
mouseLight.height = 22
mouseLight.shadows = true
mouseLight.shadowBias = 0.008
mouseLight.shadowSoftness = 2.0
mouseLight.mapResolution = 768

createLightMarker()

moveMouseLight(505, 235)

Engine.setCanvasSize(canvasWidth, canvasHeight)
Engine.scalingMode = Scaling.FITWIDTH
Engine.setScene(scene)
Engine.setCallTouchInMouseEvent(true)
Engine.callMouseInTouchEvent = true

Engine.onTouchStart = onTouchStart
Engine.onTouchMove = onTouchMove
Engine.onTouchEnd = onTouchEnd
Engine.onMouseDown = onMouseDown
Engine.onMouseMove = onMouseMove
Engine.onMouseUp = onMouseUp
