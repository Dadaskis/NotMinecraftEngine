ChunkManager = {}

ChunkManager.chunks = {}

ChunkManager.previousPlayerPos = {
    X = -1337,
    Z =  1337
}

ChunkManager.loadChunks = function(this)
    local cameraX = math.floor(Engine.getCurrentCameraX() / 16)
    local cameraZ = math.floor(Engine.getCurrentCameraZ() / 16)
    if cameraX ~= this.previousPlayerPos.X or cameraZ ~= this.previousPlayerPos.Z then
        this.previousPlayerPos.X = cameraX
        this.previousPlayerPos.Z = cameraZ
        BlockManager:clear()
        for XChunk = cameraX - CHUNK_RENDER_DISTANCE, cameraX + CHUNK_RENDER_DISTANCE do
            if this.chunks[XChunk] == nil then
                this.chunks[XChunk] = {}
            end
            for ZChunk = cameraZ - CHUNK_RENDER_DISTANCE, cameraZ + CHUNK_RENDER_DISTANCE do
                if this.chunks[XChunk][ZChunk] == nil then
                    this.chunks[XChunk][ZChunk] = Chunk(XChunk, ZChunk)
                    this.chunks[XChunk][ZChunk]:setHeightMap(ChunkGenerator:generateHeightMap(XChunk, ZChunk))
                end
                this.chunks[XChunk][ZChunk]:loadModels()
            end
        end
    end
    BlockManager:draw()
end
