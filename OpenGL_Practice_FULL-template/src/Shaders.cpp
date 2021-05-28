#include "Shaders.h"
#include "Helpers.h"
#include <stdio.h>
#include <stdlib.h>

GLuint createShaderFromSources(const char* vertexShader, const char* fragmentShader){
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, 0);
    glCompileShader(vs);
    CHECK_GL_ERRORS();

    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, 0);
    glCompileShader(fs);
    CHECK_GL_ERRORS();

    GLuint shaderProgram = glCreateProgram ();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    CHECK_GL_ERRORS();

    /*int infologLength = 0;
    glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0){
        GLchar* infoLog = (GLchar*)malloc(static_cast<size_t>(infologLength));
        if (infoLog == nullptr){
            printf("ERROR: Could not allocate InfoLog buffer");
            exit(1);
        }
        int charsWritten = 0;
        glGetShaderInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
        printf("Shader InfoLog:\n%s", infoLog );
        free(infoLog);
    }
    CHECK_GL_ERRORS();*/
    
    return shaderProgram;
}

GLuint createShader(){
    // Шейдер вершин
    const char* vertexShader = STRINGIFY_SHADER(
    // vertex attribute

    attribute vec3 aPos;
    attribute vec3 aColor;
    attribute vec2 aCoord;
    attribute vec3 aNormal;
    // uniforms
    uniform mat4 uModelViewProjMat;
    // output
    varying vec3 vColor;
    varying vec2 vCoord;
    varying vec3 vNormal;
    varying vec3 vFragPos;

    void main ()
    {
        vec4 vertexVec4 = vec4(aPos, 1.0f);      // последняя компонента 1, тк это точка
        // вычисляем позицию точки в пространстве OpenGL
        gl_Position = uModelViewProjMat * vertexVec4;

        vNormal = mat3(uModelViewProjMat) * aNormal;
        vFragPos = vec3(uModelViewProjMat * vec4(aPos, 1.0));

        // цвет и текстурные координаты просто пробрасываем для интерполяции
        vColor = aColor;
        vCoord = aCoord;
    }
);

        // фрагментный шейдер
    const char* fragmentShader = STRINGIFY_SHADER(
//    varying vec3 vColor;
//    varying vec2 vCoord;
//    varying vec3 vNormal;
//    varying vec3 vFragPos;
//    uniform sampler2D newTexture0;
//    float ambient_f = 0.4f;
//    vec3 lightPos = vec3(0.5f, 0.5f, -0.9f);
//    vec3 diffuse_f = vec3(0.9f, 0.9f, 0.9f);

//    void main () {
//        //gl_FragColor = vec4(vColor, 1.0);
//        //vec3 ambient = 0.4f * vec3(texture2D(newTexture0, vCoord));
//        vec3 ambient = ambient_f * vec3(texture2D(newTexture0, vCoord));

//        //deffuse - рассеянное освещение
//        vec3 norm = normalize(vNormal);
//        vec3 lightDir = normalize(lightPos - vFragPos);
//        // изменяли последний параметр с 0.0 на др
//        float diff = max(dot(norm, lightDir), 0.0f);
//        vec3 diffuse = diff * diffuse_f * vec3(texture2D(newTexture0, vCoord));

//        float distance = length(lightPos-vFragPos);

//        vec3 result = (ambient + diffuse);
//        //gl_FragColor = texture2D(newTexture0, vCoord) * vec4(vec3(1.0f, 1.0f, 1.0f), 1.0);

//        // добавляем дыры
//        //if (result == vec3(0.0, 0.0, 0.0))
//            //discard;

//        gl_FragColor = vec4(result, 1.0f);
//    }

        varying vec3 vColor;
        varying vec2 vCoord;
        varying vec3 vNormal;
        varying vec3 vFragPos;
        uniform sampler2D newTexture0;
        float ambient_f = 0.4f;
        vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);
        vec3 diffuse_f = vec3(0.9f, 0.9f, 0.9f);

        void main () {
            //gl_FragColor = vec4(vColor, 1.0);
            //vec3 ambient = 0.4f * vec3(texture2D(newTexture0, vCoord));
            vec3 ambient = ambient_f * vec3(texture2D(newTexture0, vCoord));

            //deffuse - рассеянное освещение
            vec3 norm = normalize(vNormal);
            vec3 lightDir = normalize(lightPos - vFragPos);
            float diff = max(dot(norm, lightDir), 0.0f);
            vec3 diffuse = diff * 0.7 * vec3(1.0f, 1.0f, 1.0f);

            vec3 result = (ambient + diffuse);
            //gl_FragColor = texture2D(newTexture0, vCoord) * vec4(vec3(1.0f, 1.0f, 1.0f), 1.0);
            //if (result == vec3(0.0, 0.0, 0.0))
                //discard;
            gl_FragColor = vec4(result, 1.0f);
        }
    );

    GLuint shader = createShaderFromSources(vertexShader, fragmentShader);
    CHECK_GL_ERRORS();
    return shader;
}

