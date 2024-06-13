#include <renderer.h>
#include <vertex-buffer.h>
#include <texture.h>
#include <thread>
#include <ctime>
#include <random>
#include <cstdlib>

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

const float WIN_WIDTH = 800.0f;
const float WIN_HEIGTH = 600.0f;
const int CIRCLES = 100;

struct circle{
    float x;
    float y;
    float r;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    srand((unsigned)time(nullptr));

    circle circle_array[CIRCLES] = { 0 };

    for(int i = 0; i < CIRCLES; i++){
        circle_array[i] = circle{(float)rand()/ (float)RAND_MAX * 1.5f, (float)rand()/ (float)RAND_MAX * 1.f, (float)rand() / (float)RAND_MAX * 0.2f};
    }

    if(!glfwInit()) {
        std::cout << "impossible d'initialiser glfw";
        return -1;
    }

    // debuging glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow((int)WIN_WIDTH, (int)WIN_HEIGTH, "programme opengl de pro", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vSync
    glViewport(0, 0, (int)WIN_WIDTH, (int)WIN_HEIGTH);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // I don't know what it is

    std::cout << glGetString(GL_VERSION) << std::endl; // opengl version
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION); // glsl version
    GLint maxVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    std::cout << "max vertex attribs: " << maxVertexAttribs;


    // position array
    float positions[]{
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f,// 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };
    
    unsigned int indices[]{
        0, 1, 2, // first triangle
        0, 2, 3 // second triangle
    };

    //glm::mat4 projection_matrix = glm::ortho(-3.0f, 3.0f, -1.0f, 1.0f, -1.0f, 1.0f); // projection matrix here
    //glm::mat4 view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.25, 0));
    //glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0));
    //glm::mat4 mvp = projection_matrix * view_matrix* model_matrix;

    // abstracting opengl into classes
    ASSERT(VertexBuffer vertex_buffer(positions, sizeof(positions)));
    ASSERT(VertexArray vertex_array(vertex_buffer.get_id()));
    vertex_array.createLayout(2, 4, 0); // position
    vertex_array.createLayout(2, 4, 2); // texture coordinates

    ASSERT(IndexBuffer index_buffer(indices, 6));
    ASSERT(Texture texture("../ressource/carte.png"));
    ASSERT(Shader shader1("../src/shader/basic-shader.shader"));
    texture.bind(0); // bind the texture on the first location
    ASSERT(shader1.setUniform1i("u_texture", 0)); // we set the uniform on 0 because it's the position of the texture in opengl
    ASSERT(shader1.setUniform2f("u_resolution", WIN_WIDTH, WIN_HEIGTH));
    ASSERT(shader1.setUniform3fv("circles", CIRCLES, &circle_array[0].x));
    //ASSERT(shader1.setUniformMat4f("u_MVP", mvp));
    ASSERT(Renderer renderer); // we create the renderer

    //imgui init
    //ImGui::CreateContext();
    //ImGui_ImplGlfwGL3_Init(window, true);
    //ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = false;
    //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float time = 0.0f;

    while(!glfwWindowShouldClose(window)){

        renderer.clear(); // clear the window

        //ImGui_ImplGlfwGL3_NewFrame(); // create a frame for imgui

        ASSERT(shader1.setUniform1f("u_time", time));
        renderer.draw(vertex_array, index_buffer, shader1);

        time += 0.01;
        // imgui
        /*{
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        */
        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // little delay
    }
    // cleanup imgui and glfw
    //ImGui_ImplGlfwGL3_Shutdown();
    //ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}