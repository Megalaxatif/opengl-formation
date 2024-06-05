#include <renderer.h>
#include <vertex-buffer.h>
#include <texture.h>
#include <thread>
#include <ctime>
#include <random>
#include <cstdlib>

const float WIN_WIDTH = 800.0f;
const float WIN_HEIGTH = 600.0f;
const int CIRCLES = 100;

struct circle{
    float x;
    float y;
    float r;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    srand((unsigned)time(nullptr));

    circle circle_array[CIRCLES] = { 0 };

    for(int i = 0; i < CIRCLES; i++){
        circle_array[i] = circle{(float)rand()/ (float)RAND_MAX * 1.5f, (float)rand()/ (float)RAND_MAX * 1.f, (float)rand() / (float)RAND_MAX * 0.2f};
    }

    glfwInit();

    GLFWwindow* window;
    window = glfwCreateWindow((int)WIN_WIDTH, (int)WIN_HEIGTH, "programme opengl de pro", NULL, NULL);
    glfwMakeContextCurrent(window);

    // debuging glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, (int)WIN_WIDTH, (int)WIN_HEIGTH);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // I don't know what it is
    std::cout << glGetString(GL_VERSION) << std::endl; // opengl version
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION); // glsl version
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    std::cout << "max vertex attribs: " << maxVertexAttribs;

    // position array
    float positions[]{
        -1.0f, -1.0f, 0.0f, 0.0f, // 0
         1.0f, -1.0f, 1.0f, 0.0f,// 1
         1.0f,  1.0f, 1.0f, 1.0f, // 2
        -1.0f,  1.0f, 0.0f, 1.0f  // 3
    };
    
    unsigned int indices[]{
        0, 1, 2, // first triangle
        0, 2, 3 // second triangle
    };
    // abstracting opengl into classes
    ASSERT(VertexBuffer vertex_buffer(positions, sizeof(positions)));
    //ASSERT(VertexArray vertex_array(vertex_buffer.get_id(), 2, 4));

    ASSERT(VertexArray vertex_array(vertex_buffer.get_id()));
    vertex_array.createLayout(2, 4, 0); // position
    vertex_array.createLayout(2, 4, 2); // texture coordinates

    ASSERT(IndexBuffer index_buffer(indices, 6));
    ASSERT(Texture texture("../ressource/carte.png"));
    ASSERT(Shader shader1("../src/shader/basic-shader.shader"));
    texture.bind(0); // bind the texture on the first location
    ASSERT(shader1.setUniform1i("u_texture", 0)); // we set the uniform on 0 because it's the position of the texture in opengl
    ASSERT(shader1.setUniform2f("resolution", WIN_WIDTH, WIN_HEIGTH));
    ASSERT(shader1.setUniform3fv("circles", CIRCLES, &circle_array[0].x));
    ASSERT(Renderer renderer); // we create the renderer

    float r = 0.0f;
    float increment = 0.05f;
    float time = 0.0f;

    while(!glfwWindowShouldClose(window)){

        renderer.clear(); // clear the window
        ASSERT(shader1.setUniform1f("time", time));
        renderer.draw(vertex_array, index_buffer, shader1);

        if (r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        r += increment;
        time += 0.01;

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // little delay
    }
    glfwTerminate();
    return 0;
}