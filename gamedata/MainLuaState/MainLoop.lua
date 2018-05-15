if Engine.isPressed(BUTTON_W) then
    Engine.handleCurrentCamera(CAMERA_FORWARD)
end
if Engine.isPressed(BUTTON_S) then
    Engine.handleCurrentCamera(CAMERA_BACKWARD)
end
if Engine.isPressed(BUTTON_A) then
    Engine.handleCurrentCamera(CAMERA_LEFT)
end
if Engine.isPressed(BUTTON_D) then
    Engine.handleCurrentCamera(CAMERA_RIGHT)
end
if Engine.isPressed(BUTTON_SPACE) then
    Engine.handleCurrentCamera(CAMERA_UP)
end
if Engine.isPressed(BUTTON_LEFT_CONTROL) then
    Engine.handleCurrentCamera(CAMERA_DOWN)
end
