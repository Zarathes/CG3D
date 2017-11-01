#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

static const char* vertext_shader_source =
"#version 450\n"
"\n"
"uniform mat4 MVP;"
"\n"
"layout(location = 0) in vec4 position;\n"
"layout(location = 1) in vec4 color;\n"
"\n"
"out vec4 f_color;\n"
"void main() {\n"
"  gl_Position = MVP * position;\n"
"  f_color = color; \n"
"}\n";

static const char* fragment_shader_source =
"#version 450\n"
"in  vec4 f_color; \n"
"out vec4 color; \n"
"void main() {\n"
"  color = f_color;\n"
"}\n";

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//GLint program_linked;
	//glGetProgramiv(shader_programme, GL_LINK_STATUS, &program_linked);
	//if (program_linked != GL_TRUE)
	//{
	//	GLsizei log_length = 0;
	//	GLchar message[1024];
	//	glGetProgramInfoLog(shader_programme, 1024, &log_length, message);
	//	// Write the error to a log
	//	std::cout << message << std::endl;
	//}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	window = glfwCreateWindow(mode->width, mode->height, "CG3D", monitor, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	int screen_width;
	int screen_height;
	glfwGetWindowSize(window, &screen_width, &screen_height);
	float aspect = (float)screen_width / (float)screen_height;

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float vertex_data[48] = {
		-0.5f,  0.5f, 0.5f, // Position
		 1.0f,  0.0f,  0.0f, // Color

		 -0.5f, -0.5f, 0.5f,
		 0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f, 0.5f,
		 0.0f,  0.0f,  1.0f,

		 0.5f, -0.5f,  0.5f,
		 1.0f,  1.0f,  0.0f,

		 0.5f,  0.5f, -0.5f,
		 0.0f,  1.0f,  1.0f,

		 0.5f,  -0.5f, -0.5f,
		 1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,
		 0.0f, 0.0f, 0.0f,

		 -0.5f, -0.5f, -0.5f,
		 1.0f, 1.0f, 1.0f,		
	};

	unsigned int index_data[36] = {
		0,2,3,
		0,3,1,
		2,4,5,
		2,5,3,
		4,6,7,
		4,7,5,
		6,0,1,
		6,1,7,
		6,2,0,
		6,4,2,
		7,1,3,
		7,3,5
	};

	unsigned int vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(float), vertex_data, GL_STATIC_DRAW);

	unsigned int index_buffer;
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), index_data, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));

	unsigned int shader = CreateShader(vertext_shader_source, fragment_shader_source);
	glUseProgram(shader);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotations = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scales = glm::vec3(3.0f, 3.0f, 3.0f);

	//void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
	//	const float v[4] = { x, y, w, h };
	//	glViewportArrayv(index, 1, v);
	//}

	

	
	//const float v[4] = { x, y, w, h };

	glClearColor(1.0f, 1.0f, 1.0, 1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		rotations.x++;
		rotations.y++;
		rotations.z++;

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotateYaw = glm::rotate(glm::mat4(1.0f), glm::radians(rotations.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
		glm::mat4 rotatePitch = glm::rotate(glm::mat4(1.0f), glm::radians(rotations.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Pitch
		glm::mat4 rotateRoll = glm::rotate(glm::mat4(1.0f), glm::radians(rotations.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Roll	
		glm::mat4 rotate = rotateYaw * rotatePitch * rotateRoll;
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), scales);

		glm::mat4 model = translate * rotate * scale;
		glm::mat4 proj = glm::perspective(glm::radians(60.f), aspect, 0.1f, 10.f);
		glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 MVP = proj * view * model;

		unsigned int loc = glGetUniformLocation(shader, "MVP");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &MVP[0][0]);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 4; i++)
		{
			int x = i / 2;
			int y = i % 2;
			glViewport((screen_width*0.5) * x, (screen_height*0.5) * y, screen_width*0.5, screen_height*0.5);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}