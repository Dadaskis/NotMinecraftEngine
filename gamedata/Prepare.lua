print("Preparing...")

Engine.setCurrentCameraFOV(90)
Engine.setCurrentCameraSpeed(0.05)
Engine.setCurrentCameraPosition(0, 60, 0)

Thread = require "llthread2.ex"

local thread = Thread.new(function()
    while true do
        print("Thread!")
    end
end)
thread:start()

print("Prepare is done")
