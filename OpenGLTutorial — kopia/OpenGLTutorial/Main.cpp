#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "mesh.h"

#include "Ball.h"
#include "Lamps.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// shading
bool gouraud = false;

// lighting
bool blinn = false;

// objects
auto ball = Ball();
auto lamps = Lamps();

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader program
	// ------------------------------------
	Shader phongShader("shaders/phong.vs", "shaders/phong.fs");
	Shader gouraudShader("shaders/gouraud.vs", "shaders/gouraud.fs");
	Shader shader = phongShader;

	Model stadium = Model("models/Wembley_stadion_V3_L3.123c03de6ad6-86e9-41ff-bff4-654781577365/10093_Wembley_stadion_V3_Iteration0.obj");
	Model beachBall = Model("models/Beach_Ball_v2_L3.123cdf1ec704-c7ca-4faf-8f47-647b6e5df698/13517_Beach_Ball_v2_L3.obj");
	Model lamp = Model("models/JapaneseLamp/Japanese_lamp__corona.obj");

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// per-frame object movement
		ball.Move(deltaTime); 
		lamps.Move(deltaTime);

		// check shaders
		if (gouraud && shader.ID != gouraudShader.ID)
		{
			shader = gouraudShader;
		}

		if (!gouraud && shader.ID != phongShader.ID)
		{
			shader = phongShader;
		}

		// camera modes
		switch (camera.mode)
		{
		case STILL:
			camera.Position = glm::vec3{ -32.2921f, 3.06586f, 12.1431f };
			camera.Front = glm::vec3{ 0.975157f, -0.130527f, -0.178974f };
			camera.Up = glm::vec3{ 0.128383f, 0.991445f, -0.0235625f };
			break;
		case BINDED:
			camera.Position = glm::vec3{ -1.24667f, 4.54421f, 5.54953f };
			camera.Up = glm::vec3{ 0, 1, 0 };
			break;
		case FOLLOWING:
			camera.Position = ball.FollowingPosition();
			camera.Up = glm::vec3{ 0, 1, 0 };
			break;
		default:
			break;
		}

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(
			0.12f + 0.15 * sin(currentFrame / 3),
			0.18f + 0.15 * sin(currentFrame / 3),
			0.25f + 0.2 * sin(currentFrame / 3),
			1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// be sure to activate shader when setting uniforms/drawing objects
		shader.use();

		// initial shader set up
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.mode == BINDED || camera.mode == FOLLOWING
			? glm::lookAt(camera.Position, ball.Position(), glm::vec3{ 0, 1, 0 }) 
			: camera.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		shader.setBool("blinn", blinn);

		// render the loaded model
		shader.setVec3("ViewPosition", camera.Position);

		for (int i = 0; i < 5; i++)
		{
			shader.setVec4("Lights[" + to_string(i) + "].position", glm::vec4(lamps.positions[i], 1.0f));
			shader.setVec3("Lights[" + to_string(i) + "].intensity", 1.0f, 1.0f, 1.0f);
			shader.setVec3("Lights[" + to_string(i) + "].direction", glm::normalize(ball.Position() - lamps.positions[i]));
			shader.setFloat("Lights[" + to_string(i) + "].cutoff", 7);
		}

		shader.setVec3("Lights[4].intensity", 0.5f, 0.5f, 0.5f);
		shader.setVec3("Lights[4].direction", 0.0f, 1.0f, 0.0f);

		shader.setVec3("Kd", 0.5, 0.5, 0.5);
		shader.setVec3("Ka", 
			0.18f + 0.16 * sin(currentFrame / 3), 
			0.18f + 0.17 * sin(currentFrame / 3), 
			0.19f + 0.18 * sin(currentFrame / 3));
		shader.setVec3("Ks", 1.0, 1.0, 1.0);
		shader.setFloat("Shininess", 200);

		// render the ball
		shader.setMat4("model", ball.Model());
		beachBall.Draw(shader);

		// render the stadium
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.004f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0, 0.0, 0.0));
		model = glm::translate(model, glm::vec3{ 0.0f, 0.0f, -3210.0f });
		shader.setMat4("model", model);

		stadium.Draw(shader);

		// render all the lamps
		auto models = lamps.Models();

		for (int i = 0; i < 5; i++)
		{
			shader.setMat4("model", models[i]);
			lamp.Draw(shader);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// camera movement
	if (camera.mode == FREE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		camera.mode = STILL;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		camera.mode = BINDED;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		camera.mode = FOLLOWING;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		camera.mode = FREE;

	// shading
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		gouraud = true;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		gouraud = false;

	// lighting
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		blinn = true;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		blinn = false;

	// ball tossing
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		ball.Accelerate();
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ball.Reset();

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		ball.Rotate(deltaTime, true);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		ball.Rotate(deltaTime, false);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}