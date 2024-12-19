#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


//compile shader, you input type and source code, as a assistant for function createShader
unsigned int compileShader(unsigned int typeShader,const std::string sourceCode)
{

    //create shader
    unsigned int idShader = glCreateShader(typeShader);
    const char* soucreCodePoinetr = sourceCode.c_str();
    glShaderSource(idShader, 1, &soucreCodePoinetr, NULL);
    glCompileShader(idShader);

    //check the result of compilation
     int result; glGetShaderiv(idShader, GL_COMPILE_STATUS, &result);
     if (result == GL_FALSE)
     {
         //get length and message
         int length; glGetShaderiv(idShader, GL_INFO_LOG_LENGTH, &length);
         char* messageError = (char*)alloca(sizeof(char) * length);
         glGetShaderInfoLog(idShader, length, &length, messageError);

         //output
         std::cout << (typeShader == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
             << " shader compile fails" << std::endl;
         std::cout << messageError << std::endl;
     }


    return idShader;
}

//input two shader source code and return the program of vertex and fragment shaders
unsigned int createShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    //create shader
    unsigned int idVertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int idFragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    //create program and link, validate
    unsigned int programShader = glCreateProgram();
    glAttachShader(programShader, idVertexShader);   glAttachShader(programShader, idFragmentShader);
    glLinkProgram(programShader);   glValidateProgram(programShader);

    //delete the two shaders
    glDeleteShader(idVertexShader); glDeleteShader(idFragmentShader);


    return programShader;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //init glew
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR: FAIL TO INITATE GLEW" << std::endl;

    //put out version of glew and your openg
    std::cout << "The versoin of glew is : " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "The versoin of OpenGL is : " << glGetString(GL_VERSION) << std::endl;

    //original coordinates
    float verticesArrf[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    //write source code of shader
    std::string vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{gl_Position=position;}";

    std::string fragmentShaderSource =
        "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "void main()\n"
        "{color=vec4(0.4f,0.9f,0.8f,1.0);}";

    //generate the coordinates arr buffer----vertex buffer
    unsigned int  vertex_buffer; glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, verticesArrf, GL_STATIC_DRAW);
    //the last parameter is usage, divided into two part, including modification and usage freqency
    //and which device can access, like GL draw function

    //set vertex attributes
    unsigned int VerAttri_positoin = 0; 
    glEnableVertexAttribArray(VerAttri_positoin);//you need enable vertex attribute
    glVertexAttribPointer(VerAttri_positoin, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    //shader program
    unsigned int programShader = createShader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(programShader);




    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        ////we use the legacy to draw a triangle as simple as it can
        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f( 0.0f,  0.5f);
        //glVertex2f( 0.5f, -0.5f);
        //glEnd();


        glDrawArrays(GL_TRIANGLES, 0, 3);





        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //clear
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteProgram(programShader);


    glfwTerminate();
    return 0;
}