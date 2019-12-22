//
// Created by Yuxf1991 on 2019/12/22.
//

#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <string>

class Shader {
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    int compile();
    void use();
    unsigned int getId() {
        return mId;
    }
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setDouble(const std::string &name, double value) const;

private:
    std::string mVertexPath;
    std::string mFragmentPath;
    unsigned int mId;
};

#endif // LEARNOPENGL_SHADER_H
