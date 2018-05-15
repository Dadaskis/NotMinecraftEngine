function Block()
    local newBlock = {}

    newBlock.blockSystem = Engine.createBlockSystem()
    Engine.setBlockSystemShader(newBlock.blockSystem, BLOCK_SHADER)
    Engine.setCameraToBlockSystem(MAIN_CAMERA, newBlock.blockSystem)

    newBlock.setTexture = function(this, direction, texture)
        Engine.setBlockTexture(direction, this.blockSystem, texture)
    end

    newBlock.clear = function(this)
        Engine.clearBlocksData(this.blockSystem)
    end

    newBlock.createBlock = function(this, X, Y, Z)
        Engine.addBlockInfo(this.blockSystem, X, Y, Z)
    end

    newBlock.draw = function(this)
        Engine.drawBlocks(this.blockSystem)
    end

    return newBlock
end
