#include "ShaderProgram.h"

namespace Renderer
{
    ShaderProgram::ShaderProgram(const string& vertexShader, const string& fragmentShader)
    {
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        //glShaderSource(vs, 1, &vertex_shader, nullptr);
        glCompileShader(vs);
    }
}
