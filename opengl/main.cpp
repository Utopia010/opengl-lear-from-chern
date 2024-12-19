#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

    //generate the coordinates arr buffer----vertex buffer
    unsigned int  vertex_buffer; glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesArrf), verticesArrf, GL_STATIC_DRAW);
    //the last parameter is usage, divided into two part, including modification and usage freqency
    //and which device can access, like GL draw function

    //set vertex attributes
    unsigned int VerAttri_positoin = 0;
    glVertexAttribPointer(VerAttri_positoin, 2, 2 * sizeof(float), GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(VerAttri_positoin);//you need enable vertex attribute





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        //we use the legacy to draw a triangle as simple as it can
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();








        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}