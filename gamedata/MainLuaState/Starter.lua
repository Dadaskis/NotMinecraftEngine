print(LUA_STATS.STATE_ID .. " started.")

Engine.createLuaState("gamedata\\ChunkLoader")

dofile("gamedata/MainLuaState/Prepare.lua")
print("Prepared.")

while true do
    dofile("gamedata/MainLuaState/MainLoop.lua")
end
