ChunkGenerator = {}

ChunkGenerator.bilinearInterpolation = function(this,
                                                bottomLeft, topLeft, bottomRight, topRight,
                                                xMin, xMax,
                                                zMin, zMax,
                                                x, z)
    local width               = xMax - xMin
    local height              = zMax - zMin

    local xDistanceToMaxValue = xMax - x
    local zDistanceToMaxValue = zMax - z

    local xDistanceToMinValue = x - xMin
    local zDistanceToMinValue = z - zMin

    return 1.0 / (width * height) *
           (
               bottomLeft      *   xDistanceToMaxValue * zDistanceToMaxValue +
               bottomRight     *   xDistanceToMinValue * zDistanceToMaxValue +
               topLeft         *   xDistanceToMaxValue * zDistanceToMinValue +
               topRight        *   xDistanceToMinValue * zDistanceToMinValue
           )
end

ChunkGenerator.generateHeightMap = function(this, chunkX, chunkZ)
    local normalChunkX = chunkX * 16
    local normalChunkZ = chunkZ * 16
    local maxX = normalChunkX + 16
    local maxZ = normalChunkZ + 16
    local topLeft = Engine.getNoise(normalChunkX, normalChunkZ)
    local topRight = Engine.getNoise(maxX, normalChunkZ)
    local bottomLeft = Engine.getNoise(normalChunkX, maxZ)
    local bottomRight = Engine.getNoise(maxX, maxZ)

    local returnHeightMap = {}

    for X = 0, CHUNK_SIZE - 1 do
        returnHeightMap[X] = {}
        for Z = 0, CHUNK_SIZE - 1 do
            returnHeightMap[X][Z] = this:bilinearInterpolation(
                bottomLeft, topLeft,
                bottomRight, topRight,
                normalChunkX, maxX,
                normalChunkZ, maxZ,
                X, Z
            ) + 20
            returnHeightMap[X][Z] = math.abs(returnHeightMap[X][Z])
            returnHeightMap[X][Z] = math.floor(returnHeightMap[X][Z])
        end
    end

    return returnHeightMap
end
