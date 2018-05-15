print(LUA_STATS.STATE_ID .. " started.")

dofile("gamedata/ChunkLoader/Constants.lua")
print("Constants is ready.")

dofile("gamedata/ChunkLoader/Prepare.lua")
print("Prepared.")

while true do
    dofile("gamedata/ChunkLoader/MainLoop.lua")
end
