#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// Instantiate static variables
std::string                         ResourceManager::ResourceRootDirectory;
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;


Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode = readResourceFile(vShaderFile);
    std::string fragmentCode = ResourceManager::readResourceFile(fShaderFile);
    std::string geometryCode;
    if (gShaderFile)
    {
        geometryCode = ResourceManager::readResourceFile(gShaderFile);
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

std::string ResourceManager::readResourceFile(const char* path)
{
    // Open the file from the resource root directory
    std::string fullPath = ResourceManager::ResourceRootDirectory + path;
    std::ifstream shaderFile;

    // Throw an exception if reading this file fails.
    shaderFile.exceptions(shaderFile.exceptions() | std::ios::failbit);

    try
    {
        shaderFile.open(fullPath);
    }
    catch (std::ios_base::failure& e)
    {
        std::cerr << "Failed to open file: " << fullPath << std::endl;
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

    // Read the file
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    shaderFile.close();
    return shaderStream.str();
}

Texture2D ResourceManager::loadTextureFromFile(const char* path, bool alpha)
{
    // Open the file from the resource root directory
    std::string fullPath = ResourceManager::ResourceRootDirectory + path;

    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
    
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}
