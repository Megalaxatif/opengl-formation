#include <renderer.h>
#include <vertex-buffer.h>
#include <texture.h>
#include <thread>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "programme opengl de pro", NULL, NULL);
    glfwMakeContextCurrent(window);

    // debuging glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // I don't know what it is
    std::cout << glGetString(GL_VERSION) << std::endl; // opengl version

    // position array
    float positions[]{
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f,// 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };
    unsigned int indices[]{
        0, 1, 2, // first triangle
        1, 2, 3 // second triangle
    };

    // abstracting opengl into classes
    ASSERT(VertexBuffer vertex_buffer(positions, 8 * 2 * sizeof(float)));
    ASSERT(VertexArray vertex_array(2, 4));
    ASSERT(IndexBuffer index_buffer(indices, 6));
    ASSERT(Shader shader1("../src/shader/basic-shader.shader"));
    ASSERT(Texture texture("ressource/PP discord.jpg"));
    texture.bind(0); // bind the texture on the first location
    shader1.bind();
    ASSERT(shader1.setUniform1i("u_texture", 0)); // we set the uniform on 0 because it's the position of the texture in opengl
    ASSERT(Renderer renderer); // we create the renderer

    float r = 0.0f;
    float increment = 0.05f;

    while(!glfwWindowShouldClose(window)){

        renderer.clear(); // clear the window
        //shader1.setUniform4f("u_color", r, 0.4f, 0.8f, 1.0f); // modify the uniform at each loop
        renderer.draw(vertex_array, index_buffer, shader1);

        if (r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        r += increment;

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // little delay
    }
    glfwTerminate();
    return 0;
}