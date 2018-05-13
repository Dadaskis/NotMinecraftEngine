function Chunk(chunkX, chunkZ)
    newChunk = {}
    newChunk.blocks = {}
    newChunk.chunkX = chunkX
    newChunk.chunkZ = chunkZ

    for X = 0, CHUNK_SIZE - 1 do
        newChunk.blocks[X] = {}
        for Z = 0, CHUNK_SIZE - 1 do
            newChunk.blocks[X][Z] = {}
        end
    end

    newChunk.highestPoint = 0

    newChunk.setBlock = function(this, X, Y, Z, blockID)
        this.blocks[X][Z][Y] = blockID
    end

    newChunk.getBlock = function(this, X, Y, Z)
        return this.blocks[X][Z][Y]
    end

    newChunk.setHeightMap = function(this, heightMap)
        for X = 0, CHUNK_SIZE - 1 do
            for Z = 0, CHUNK_SIZE - 1 do
                local Y = heightMap[X][Z]
                if Y > this.highestPoint then
                    this.highestPoint = Y
                end
                this:setBlock(X, Y, Z, GRASS)
                if Y - 3 > 0 then
                    for counter = 0, 2 do
                        Y = Y - 1
                        this:setBlock(X, Y, Z, DIRT)
                    end
                    if Y > 0 then
                        while Y > 0 do
                            Y = Y - 1
                            this:setBlock(X, Y, Z, STONE)
                        end
                    end
                else
                    while Y > 0 do
                        Y = Y - 1
                        this:setBlock(X, Y, Z, DIRT)
                    end
                end
            end
        end
    end

    newChunk.updateModels = function(this)
        local worldPosX = this.chunkX * 16
        local worldPosZ = this.chunkZ * 16
        for X = 0, CHUNK_SIZE - 1 do
            for Z = 0, CHUNK_SIZE - 1 do
                for Y = 0, this.highestPoint + 1 do
                    if this:getBlock(X, Y, Z) ~= AIR then
                        if X < CHUNK_SIZE - 1 then
                            if this:getBlock(X + 1, Y, Z) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                        if Y <= this.highestPoint then
                            if this:getBlock(X, Y + 1, Z) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                        if Z < CHUNK_SIZE - 1 then
                            if this:getBlock(X, Y, Z + 1) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                        if X > 0 then
                            if this:getBlock(X - 1, Y, Z) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                        if Y > 0 then
                            if this:getBlock(X, Y - 1, Z) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                        if Z > 0 then
                            if this:getBlock(X, Y, Z - 1) == AIR then
                                BlockManager:createBlock(this:getBlock(X, Y, Z), worldPosX + X, Y, worldPosZ + Z)
                                goto continue
                            end
                        end
                    end
                    ::continue::
                end
            end
        end
    end

    return newChunk
end
