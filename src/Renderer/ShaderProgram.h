#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Renderer {
    class ShaderProgram {
    public:
        ShaderProgram(const string& vertexShader, const string& fragmentShader);
        ~ShaderProgram();
        bool isCompile() const {return m_isCompiled;}
        bool use() const;

    private:
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };
}
