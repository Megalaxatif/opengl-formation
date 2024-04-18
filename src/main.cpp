#include "vertex-buffer.h"
#include "index-buffer.h"

struct Shaders{
    std::string vertex_shader_source;
    std::string fragment_shader_source;
};

enum class shader_type{
    VERTEX = 0, FRAGMENT = 1
};

Shaders load_shader(std::string filepath){
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream shader_array[2];
    shader_type type = shader_type::VERTEX; // on initialise type sur vertex pour éviter les erreurs
    if (!getline(stream, line)){
        std::cout << "load_shaders error \n";
    }
    while(getline(stream, line)){
        // donc le fichier doit forcement commencer par shader sinon ça bug
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = shader_type::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos){
                type = shader_type::FRAGMENT;
            }
        }
        else{
            shader_array[(int)type] << line << "\n";
        }
    }
    return {shader_array[0].str(), shader_array[1].str()};
}


unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = &source[0]; // convertir std::string source en const char* pour qu'opengl comprenne la chaine de caractère (langage C)
    glShaderSource(id, 1, &src, nullptr); // etape de la compilation 1 : transformation en fichier objet
    glCompileShader(id); // compilation finale

    // TODO: error handling but I'm lazy so maybe later :)
    return id;
}

unsigned int Create_shader(const std::string& vertex_shader, const std::string& fragment_shader){
    unsigned int program = glCreateProgram();
    // on compile les shaders
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program); // linkage
    glValidateProgram(program);

    // effacer les fichiers objets des shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    // I don't know what it is
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    std::cout << glGetString(GL_VERSION) << std::endl; // opengl version

    // position array
    float positions[]{
        -0.5f, 0.0f, // 0
        -0.5f, 0.5f, // 1
         0.0f, 0.0f, // 2
         0.0f, 0.5f  // 3
    };
    unsigned int indices[]{
        0, 1, 2, // first triangle
        1, 2, 3 // second triangle
    };
    //class
    ASSERT(VertexBuffer vertex_buffer(positions, 8 * sizeof(float)));

    // defining how to interpret the buffer
    unsigned int vertex_array;
    ASSERT(glGenVertexArrays(1, &vertex_array));
    ASSERT(glBindVertexArray(vertex_array));
    ASSERT(glEnableVertexAttribArray(0));
    ASSERT(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));

    // class
    ASSERT(IndexBuffer index_buffer(indices, 6));
    
    // creating a shader and use it in the code
    Shaders source = load_shader("../src/shader/basic-shader.shader");
    std::cout << "FRAGMENT SHADER" << "\n";
    std::cout << source.fragment_shader_source << "\n";
    std::cout << "VERTEX SHADER" << "\n";
    std::cout << source.vertex_shader_source << "\n";
    unsigned int shader = Create_shader(source.vertex_shader_source, source.fragment_shader_source);
    glUseProgram(shader); // on bind le shader

    int location = glGetUniformLocation(shader, "u_color"); // stocker dans l'entier <location> l'adresse de l'uniform <u_color> de <shader>
    if (location == -1) std::cerr << "erreur avec l'uniform a la ligne: " << __LINE__ -1 << "\n"; // debugging, location = -1 si l'uniform est introuvable 
    glUniform4f(location, 0.2f, 0.3f, 0.5f, 1.0f); // modifier l'uniform
    float r = 0.0f;
    float increment = 0.05f;

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear la fenêtre
        glUniform4f(location, r, 0.4f, 0.8f, 1.0f); // modifier l'uniform à chaque tour de boucle
        ASSERT(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); // dessiner sur la fenêtre

        if (r > 1.0f) increment = -0.05f;
        else if (r < 0.0f) increment = 0.05f;
        r += increment;

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // petite pause pour voir le rectangle changer de couleur
    }
    glfwTerminate();
    return 0;
}