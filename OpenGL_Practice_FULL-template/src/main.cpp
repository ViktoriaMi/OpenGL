// TODO: надо ли?
// #define GLFW_INCLUDE_GLCOREARB 1 // Tell GLFW to include the OpenGL core profile header
#define GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GLEXT
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include "Sphere.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#include <glad/glad.h>
//#include "camera.h"

#include <GL/glew.h>        // для поддержки расширений, шейдеров и так далее
#include <GLFW/glfw3.h>     // Непосредственно сам GLFW
//#include <glm.h>            // библиотека графической математики
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "PngLoader.h"
#include "Helpers.h"
#include "Vertex.h"
#include "Figures.h"
#include "Shaders.h"
//#include "ObjLoader.h"

// Документация
// https://www.opengl.org/sdk/docs/man/html/

using namespace std;
using namespace glm;

#define MATH_PI 3.14159265

// Текущие переменные для модели
bool leftButtonPressed = false;
bool rightPressed = false;
double lastCursorPosX = 0.0;
double lastCursorPosY = 0.0;

Sphere sphere;

class Space
{
private:
    mat4 MVPMatrix;
    float distance;
    float rotateSpeed;
    float moveSpeed;
    float scale;
    vec3 rot;
    ImageData* image;
public:
    Space(int id, float dist, float rotate, float moveSpeed, float scale)
    {
        MVPMatrix = mat4(1.0);
        distance = dist;
        rotateSpeed = rotate;
        this->moveSpeed = moveSpeed;
        this->scale = scale;
        string path = "/home/viktoria/Downloads/MSTU/IGS/OpenGL_Practice_FULL-template/res/";
        switch (id) {
        case 0:
            path += "sun2048.png";
            break;
        case 1:
            path += "mercury2048.png";
            break;
        case 2:
            path += "venus2048.png";
            break;
        case 3:
            path += "earth2048.png";
            break;
        case 4:
            path += "mars2048.png";
            break;
        case 5:
            path += "jupiter2048.png";
            break;
        case 6:
            path += "saturn2048.png";
            break;
        case 7:
            path += "uranus2048.png";
            break;
        case 8:
            path += "neptune2048.png";
            break;
        }
        image = loadPngImage(path.c_str());
    }
    mat4 getMVP() {return MVPMatrix; }
    ImageData *getImage() {return image; }

    void translateAndRotate(double time)
    {
        MVPMatrix = mat4(1.0);
        vec3 translate = vec3(distance, 0, 0) * sin((float)time * moveSpeed);
        translate += vec3(0, distance, 0) * cos((float)time * moveSpeed);

        MVPMatrix = glm::translate(MVPMatrix, translate);

        glm::vec3 scaleVec = glm::vec3(scale);
        MVPMatrix = glm::scale(MVPMatrix, scaleVec);

        MVPMatrix = glm::rotate(MVPMatrix, glm::radians(90.f), vec3(1, 0, 0));
        MVPMatrix = glm::rotate(MVPMatrix, (float)time * glm::radians(rotateSpeed), vec3(0, 0, 1));
    }
};



unsigned int texture1;
void Starry_sky ()
{
    int weight, height, cnt;
    unsigned char *data = stbi_load("/home/viktoria/Downloads/MSTU/IGS/OpenGL_Practice_FULL-template/res/sky.png", &weight, &height, &cnt, 0);
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, weight, height,
                 0, cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

float vertex2[] = {-1,-1,0, 1,-1,0, 1,1,0, -1,1,0};
void Sky_show()
{
    glColor3f(0,1,0);
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex2);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}



void glfwErrorCallback(int error, const char* description) {
    printf("OpenGL error = %d\n description = %s\n\n", error, description);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Выходим по нажатию Escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    }
    // по пробелу включаем или выключаем вращение автоматом
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
    }
}

void glfwMouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
    // обработка левой кнопки
    if(button == GLFW_MOUSE_BUTTON_1){
        if(state == GLFW_PRESS){
            leftButtonPressed = true;
        }else{
            leftButtonPressed = false;
        }
    }
    // обработка правой кнопки
    if(button == GLFW_MOUSE_BUTTON_2){
        if(state == GLFW_PRESS){
            rightPressed = true;
        }else{
            rightPressed = false;
        }
    }
}

void glfwCursorCallback(GLFWwindow* window, double x, double y) {
    // при нажатой левой кнопки - вращаем по X и Y
    if(leftButtonPressed){
    }

    // при нажатой левой кнопки - перемещаем по X Y
    if(rightPressed){
    }

    lastCursorPosX = x;
    lastCursorPosY = y;
}

void glfwScrollCallback(GLFWwindow* window, double scrollByX, double scrollByY) {
}

int main(int argc, char *argv[]) {

    // окно
    GLFWwindow* window = 0;

    // обработчик ошибок
    glfwSetErrorCallback(glfwErrorCallback);

    // инициализация GLFW
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }

    // создание окна
#ifdef __APPLE__
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#endif
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(740, 680, "Solar system", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);        // вертикальная синхронизация
    CHECK_GL_ERRORS();

    // Обработка клавиш и прочего
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(window, glfwCursorCallback);
    glfwSetScrollCallback(window, glfwScrollCallback);

    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();

    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();

    // Инициализация отладки
    if(glDebugMessageCallback){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Коллбек ошибок OpenGL
        glDebugMessageCallback((GLDEBUGPROC)glDebugOut, 0);

        // Более высокий уровень отладки
        // GLuint unusedIds = 0;
        // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
    }
    CHECK_GL_ERRORS();

    const unsigned char* version = glGetString(GL_VERSION);
    printf("OpenGL version = %s\n", version);

    // оотношение сторон
    int width = 0;
    int height = 0;
    // Размер буффера кадра
    glfwGetFramebufferSize(window, &width, &height);
    CHECK_GL_ERRORS();

    // задаем отображение
    glViewport(0, 0, width, height);
    CHECK_GL_ERRORS();

    // Шейдеры
    GLuint shaderProgram = createShader();
    CHECK_GL_ERRORS();

    // аттрибуты вершин шейдера
    int posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    int colorAttribLocation = glGetAttribLocation(shaderProgram, "aColor");
    int texAttribLocation = glGetAttribLocation(shaderProgram, "aCoord");
    int normAttribLocation = glGetAttribLocation(shaderProgram, "aNormal");
    CHECK_GL_ERRORS();

    // юниформы шейдера
    int modelViewProjMatrixLocation = glGetUniformLocation(shaderProgram, "uModelViewProjMat");
    CHECK_GL_ERRORS();

    // VBO, данные о вершинах
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, triangleVertexCount * sizeof(Vertex), triangleVertexes, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, cubeVertexCount * sizeof(Vertex), cubeVertexes, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, SphereVertexCount * sizeof(Vertex), sphereVertixes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS();

    // отключаем отображение задней части полигонов
    //glEnable(GL_CULL_FACE);
    // отбрасываться будут задние грани
    glCullFace(GL_BACK);
    // Определяем, в каком направлении должный обходиться вершины, для передней части (против часовой стрелки?)
    // задняя часть будет отбрасываться
    glFrontFace(GL_CCW);
    CHECK_GL_ERRORS();

    // проверка глубины
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    CHECK_GL_ERRORS();

    // текущее время
    double time = glfwGetTime();


    // Загрузка текстуры
    ImageData* info = loadPngImage("/home/viktoria/Downloads/MSTU/IGS/OpenGL_Practice_FULL-template/res/test.png");
    uint textureId = 0;
    if(info->loaded){
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,              // формат внутри OpenGL
                     info->width, info->height, 0,            // ширинна, высота, границы
                     info->withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, info->data); // формат входных данных
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        CHECK_GL_ERRORS();

    // пропишем число планет
    int numPlanets = 9;
    Space *planets[numPlanets];
    planets[0] = new Space(0, 0.0, 10, 0, 0.18);
    //for (int i=1; i<numPlanets; i++)
        //planets[i] = new Space(i, 0.2*(i+1), -20*(i+1), 1-0.2*i, 0.06);

    // меркурий
    planets[1] = new Space(1, 0.3, -20*2, 0.7, 0.035);
    // венера
    planets[2] = new Space(2, 0.39, -20*3, 0.64, 0.047);
    // земля
    planets[3] = new Space(3, 0.5, -20*4, 0.6, 0.054);
    // марс
    planets[4] = new Space(4, 0.65, -20*5, 0.56, 0.047);
    // юпитер
    planets[5] = new Space(5, 0.79, -20*5.5, 0.49, 0.074);
    // сатурн
    planets[6] = new Space(6, 0.85, -20*6, 0.4, 0.064);
    // уран
    planets[7] = new Space(7, 0.95, -20*7, 0.3, 0.034);
    // нептун
    planets[8] = new Space(8, 0.98, -20*8, 0.22, 0.033);


    // загрузка текстур для планет
    GLuint planetTextures[numPlanets];
    glGenTextures(numPlanets, planetTextures);

    for (int i = 0; i < numPlanets; i++)
    {
        ImageData *im = planets[i]->getImage();
        if(im->loaded)
        {
            glBindTexture(GL_TEXTURE_2D, planetTextures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,              // формат внутри OpenGL
                         im->width, im->height, 0,              // ширина, высота, границы
                         im->withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, im->data);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            CHECK_GL_ERRORS();
        }

    }

    // Загрузка текстуры
//    ImageData* info = loadPngImage("/home/viktoria/Downloads/MSTU/IGS/OpenGL_Practice_FULL-template/res/test3.png");
//    uint textureId = 0;
//    if(info->loaded)
//    {
//        glGenTextures(1, &textureId);
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,              // формат внутри OpenGL
//                     info->width, info->height, 0,            // ширина, высота, границы
//                     info->withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, info->data); // формат входных данных
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        CHECK_GL_ERRORS();
//    }
//    float degrees = 1.0f;

    //Starry_sky();

    while (!glfwWindowShouldClose(window))
    {
        // приращение времени
        double newTime = glfwGetTime();
        //double timeDelta = newTime - time;
        time = newTime;

        // wipe the drawing surface clear
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Sky_show();
        glActiveTexture(GL_TEXTURE0);
        glUseProgram (shaderProgram);

        for (int i = 0; i < numPlanets; i++)
        {
            glBindTexture(GL_TEXTURE_2D, planetTextures[i]);

            planets[i]->translateAndRotate(time);
            // выставляем матрицу трансформации в пространство OpenGL
            glUniformMatrix4fv(modelViewProjMatrixLocation, 1, false, glm::value_ptr(planets[i]->getMVP()));

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Позиции
            glEnableVertexAttribArray(posAttribLocation);
            glVertexAttribPointer(posAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, pos));
            // Цвет вершин
            //glEnableVertexAttribArray(colorAttribLocation);
            //glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, color));
            // Текстуры
            glEnableVertexAttribArray(texAttribLocation);
            glVertexAttribPointer(texAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, texCoord));
            // Нормали
            glEnableVertexAttribArray(normAttribLocation);
            glVertexAttribPointer(normAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, normal));
            CHECK_GL_ERRORS();

            // рисуем
            //glDrawArrays(GL_TRIANGLES, 0, triangleVertexCount); // draw points 0-3 from the currently bound VAO with current in-use shader
            //glDrawArrays(GL_TRIANGLES, 0, numPlanets);
            glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, sphere.getIndices());
        }

        // матрица модель-вид-проекция
        mat4 modelViewProjMatrix = mat4(1.0);

        modelViewProjMatrix = rotate(modelViewProjMatrix, float(time), vec3(0.5f, 0.5f, 0.5f));
//        degrees += 0.1f;
//        if (degrees >= 180) degrees = 0;
//        //cout << degrees << ' ';
        // выставляем матрицу трансформации в пространство OpenGL
        //glUniformMatrix4fv(modelViewProjMatrixLocation, 1, false, glm::value_ptr(modelViewProjMatrix));

        // sizeof(Vertex) - размер блока данных о вершине
        // OFFSETOF(Vertex, color) - смещение от начала
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Позиции
        //glEnableVertexAttribArray(posAttribLocation);
        //glVertexAttribPointer(posAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, pos));
        // Цвет вершин
        //glEnableVertexAttribArray(colorAttribLocation);
        //glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, color));
        // Текстуры
        //glEnableVertexAttribArray(texAttribLocation);
        //glVertexAttribPointer(texAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, texCoord));
        // Нормали
        //glEnableVertexAttribArray(normAttribLocation);
        //glVertexAttribPointer(normAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, normal));
        //CHECK_GL_ERRORS();

        // рисуем
        //glDrawArrays(GL_TRIANGLES, 0, triangleVertexCount); // draw points 0-3 from the currently bound VAO with current in-use shader
        //glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount); // draw points 0-3 from the currently bound VAO with current in-use shader

        // VBO off
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
}
