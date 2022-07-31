#include "GLMain.h"
const char* readFromFile(const char* pathToFile)
{
    std::string content;
    std::ifstream fileStream(pathToFile, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    //std::cout << "'" << content << "'" << std::endl;
    return content.c_str();
}
GLint GLMain::makeShader() {

    const char* vertex_shader = readFromFile("./Vertex.shader");
    const char* fragment_shader =  readFromFile("./Frag.shader");

    GLuint vs, fs;
    GLuint shader_programme;

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);
    return shader_programme;
}



GLMain::GLMain() {

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(-1); //エラー発生時には強制終了させる
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    const char *title = "SampleWindow";
    int width = 1280;
    int height = 720;
    // ウィンドウの作成
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        exit(-1); //エラー発生時には強制終了させる
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Alpha要素のあるテクスチャを描画する
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



}
GLMain::~GLMain() {}

void GLMain::Loop(){
//    unsigned int buffer;
//    float positions[6] = {
//            -0.5f, -0.5f,
//            0.0f, 0.5f,
//            0.5f, -0.5f,
//    };
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();


        glUseProgram(shader);
        glUseProgram(programHandle);


        glGetAttribLocation(programHandle, "VertexPosition");
        glGetAttribLocation(programHandle, "VertexPosition");

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}

void GLMain::Load(){
    //GLuint vao, vertex_vbo, color_vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat positionData[24] = {
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,
            -1.0,  1.0, -1.0,
            1.0,  1.0, -1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0
    };
    GLfloat colorData[24] = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
    };

// 頂点座標のVBOを作成
    glGenBuffers(1, &vertex_vbo); //バッファを作成
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo); //以下よりvertex_vboでバインドされているバッファが処理される
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW); //実データを格納

    // 色のVBOを作成
    glGenBuffers(1, &color_vbo); //バッファを作成
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo); //以下よりcolor_vboでバインドされているバッファが処理される
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW); //実データを格納

    shader = GLMain::makeShader();
    int mvpLocation = glGetUniformLocation(programHandle, "MVP");
    int textureLocation = glGetUniformLocation(shader, "texture");

    float mvp;
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp);
}


