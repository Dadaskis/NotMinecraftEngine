
BlockManager = {}
BlockManager.blocks = {}

BlockManager.createBlock = function(this, ID, X, Y, Z)
    this.blocks[ID]:createBlock(X, Y, Z)
end

BlockManager.draw = function(this)
    for key, value in pairs(this.blocks) do
        value:draw()
    end
end

BlockManager.clear = function(this)
    for key, value in pairs(this.blocks) do
        value:clear()
    end
end

BlockManager.initialize = function(this)
    local stone = nil
    local dirt = nil
    local grass = nil

    TextureManager:loadTexture("Textures\\stone.png", "Stone", TRUE)
    TextureManager:loadTexture("Textures\\dirt.png", "Dirt", TRUE)
    TextureManager:loadTexture("Textures\\grassSide.png", "GrassSide", TRUE)
    TextureManager:loadTexture("Textures\\grassTop.png", "GrassTop", TRUE)

    local stoneTexture = TextureManager:getTexture("Stone")
    local dirtTexture = TextureManager:getTexture("Dirt")
    local grassTopTexture = TextureManager:getTexture("GrassTop")
    local grassSideTexture = TextureManager:getTexture("GrassSide")

    stone = Block()
    stone:setTexture(BLOCK_ALL, stoneTexture)

    dirt = Block()
    dirt:setTexture(BLOCK_ALL, dirtTexture)

    grass = Block()
    grass:setTexture(BLOCK_UP, grassTopTexture)
    grass:setTexture(BLOCK_DOWN, dirtTexture)
    grass:setTexture(BLOCK_LEFT, grassSideTexture)
    grass:setTexture(BLOCK_RIGHT, grassSideTexture)
    grass:setTexture(BLOCK_BACK, grassSideTexture)
    grass:setTexture(BLOCK_FRONT, grassSideTexture)

    this.blocks[STONE] = stone
    this.blocks[DIRT]  = dirt
    this.blocks[GRASS] = grass
end

BlockManager:initialize()
BlockManager.initialize = nil
