#include "common.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

void RotateAround(vec3* Point, const vec3 Pivot, const float Angle)
{
    if (Angle == 0)
        return;

    float s = sin(Angle);
    float c = cos(Angle);

    Point->x -= Pivot.x;
    Point->y -= Pivot.y;

    double nx = (Point->x * c) - (Point->y * s);
    double ny = (Point->x * s) + (Point->y * c);

    Point->x = nx + Pivot.x;
    Point->y = ny + Pivot.y;
}

std::vector<float> vertices =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
std::vector<unsigned int> indices =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

std::vector<float> lightVertices =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	-0.1f, -0.1f, -0.1f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	 0.1f, -0.1f, -0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	 0.1f, -0.1f,  0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	-0.1f,  0.1f,  0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	-0.1f,  0.1f, -0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	 0.1f,  0.1f, -0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	 0.1f,  0.1f,  0.1f,    0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f
};

std::vector<unsigned int> lightIndices =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main(){

    using namespace glm;
    
    Window::innit();

    glEnable(GL_DEPTH_TEST);  

    Camera mainCamera = {{0, 0, 9}};
    Shader ShrekShader = Shader("../shaders/default.vs", "../shaders/default.fs");
    Shader LightShader = Shader("../shaders/light.vs", "../shaders/light.fs");

    Texture ShrekTex = Texture("../assets/container.jpg", GL_TEXTURE0);

    Mesh Pyramid = CreateMesh(vertices, indices, ShrekShader, {ShrekTex});

    Mesh Light = CreateMesh(lightVertices, lightIndices, LightShader, {});
    vec3 LightPos = {1.0, 1.0, 1.0};
    Light.modelMatrix = glm::translate(Light.modelMatrix, LightPos);

    while(!glfwWindowShouldClose(Window::Window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ControlCamera(&mainCamera, Window::Window);

        RotateAround(&LightPos, {0, 0, 0}, 0.01f);
        Light.modelMatrix = glm::translate(Light.modelMatrix, LightPos);

        Bind(Pyramid.shader);
        setUniform(Pyramid.shader, "projection", mainCamera.Projection);
        setUniform(Pyramid.shader, "view", mainCamera.ViewMatrix);
        setUniform(Pyramid.shader, "LightPos", LightPos);
        setUniform(Pyramid.shader, "camPos", mainCamera.position);

        Bind(Light.shader);
        setUniform(Light.shader, "projection", mainCamera.Projection);
        setUniform(Light.shader, "view", mainCamera.ViewMatrix);


        DrawMesh(&Pyramid);
        DrawMesh(&Light);

        Window::Update();
    }

    glDeleteProgram(ShrekShader.ID);
    glDeleteProgram(LightShader.ID);

    Window::Terminate();

    return 0;
}