//
// Created by Yuxf1991 on 2019/12/22.
//

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "Shader.h"

const int MAX_LOG_LENGTH = 1024;

Shader::Shader(std::string vertexPath, std::string fragmentPath)
    : mVertexPath(std::move(vertexPath)), mFragmentPath(std::move(fragmentPath)), mId(0)
{
}

int Shader::compile()
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常：
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // 打开文件
        vShaderFile.open(mVertexPath, std::ios_base::in);
        fShaderFile.open(mFragmentPath, std::ios_base::in);

        std::stringstream vShaderStream, fShaderStream;
        // 读取文件的缓冲内容到数据流中
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件处理器
        vShaderFile.close();
        fShaderFile.close();
        // 转换数据流到string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (const std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, MAX_LOG_LENGTH, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, MAX_LOG_LENGTH, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    mId = glCreateProgram();
    glAttachShader(mId, vertexShader);
    glAttachShader(mId, fragmentShader);
    glLinkProgram(mId);
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mId, MAX_LOG_LENGTH, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
}

void Shader::use()
{
    glUseProgram(mId);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
}

void Shader::setDouble(const std::string &name, double value) const
{
    glUniform1d(glGetUniformLocation(mId, name.c_str()), value);
}

void Shader::setVec3f(const std::string &name, float x, float y, float z) const
{
    glUniform3fv(glGetUniformLocation(mId, name.c_str()), 1, glm::value_ptr(glm::vec3(x, y, z)));
}

void Shader::setMat4f(const std::string &name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
