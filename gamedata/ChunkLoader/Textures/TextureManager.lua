TextureManager = {}
TextureManager.textures = {}

TextureManager.loadTexture = function(this, fileName, textureName, isOpaque)
    local textureID = Engine.loadTexture(fileName, isOpaque)
    this.textures[textureName] = textureID
end
TextureManager.getTexture = function(this, textureName)
    return this.textures[textureName]
end
