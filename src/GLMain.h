#ifndef SAMPLE002_GLMAIN_H
#define SAMPLE002_GLMAIN_H

#include "pch.h"

class GLMain {
public:
    GLMain();

    ~GLMain();

    void Load();

    GLint makeShader();

    void Loop();

private:

    int width;
    int height;
    float fps;
    //OpenGL
    GLFWwindow *window;
    GLuint texID;

    GLfloat points[24] = { 0.5f, 0.5f, 0.0f, //四角形一つ目
                         0.5f, -0.5f, 0.0f,
                         -0.5f, 0.5f,  0.0f,
                         -0.5f, -0.5f, 0.0f,

                         0.3f, 0.8f, 0.0f,//四角形2つ目
                         0.5f, -0.3f, 0.0f,
                         -0.7f, 0.5f, 0.0f,
                         -0.2f, -0.2f, 0.0f};
    GLfloat vertex_uv[8] = {1.0f, 0.0f,
                            0.0f, 0.0f,
                            0.0f, 1.0f,
                            1.0f, 1.0f};
    GLfloat colors[24] = { 0.5f, 0.0f, 0.3f,//四角形一つ目
                         0.5f, 0.8f, 0.0f,
                         1.0f, 0.0f, 1.0f,
                         1.0f, 0.8f, 1.0f,

                         0.5f, 0.0f, 1.0f,//四角形2つ目
                         0.5f, 0.3f, 0.5f,
                         1.0f, 0.0f, 1.0f,
                         0.2f, 0.1f, 1.0f };

    GLdouble vertex[8][3] = {{0.0, 0.0, 0.0}, /* A */
                             {1.0, 0.0, 0.0}, /* B */
                             {1.0, 1.0, 0.0}, /* C */
                             {0.0, 1.0, 0.0}, /* D */
                             {0.0, 0.0, 1.0}, /* E */
                             {1.0, 0.0, 1.0}, /* F */
                             {1.0, 1.0, 1.0}, /* G */
                             {0.0, 1.0, 1.0}  /* H */};
    int edge[12][2] = {{0, 1}, /* ア(A-B) */
                     {1, 2}, /* イ(B-C) */
                     {2, 3}, /* ウ(C-D) */
                     {3, 0}, /* エ(D-A) */
                     {4, 5}, /* オ(E-F) */
                     {5, 6}, /* カ(F-G) */
                     {6, 7}, /* キ(G-H) */
                     {7, 4}, /* ク(H-E) */
                     {0, 4}, /* ケ(A-E) */
                     {1, 5}, /* コ(B-F) */
                     {2, 6}, /* サ(C-G) */
                     {3, 7}  /* シ(D-H) */};

    GLuint vao, vertex_vbo, uv_vbo, color_vbo;
    GLint shader, programHandle;

};


#endif //SAMPLE002_GLMAIN_H
