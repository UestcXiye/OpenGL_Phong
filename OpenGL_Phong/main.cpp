/***
* Task6  ���Դ (MAKE������ʱɾ��ALL_BUILD��Ҳ���Խ�Task-phong��ΪĬ����������)
* ����:
* 1-��ʼ��:   GLFW���ڣ�GLAD��
* 2-���ݴ���: �����������ݣ����ɲ���VAO&VBO(׼����GPU�н��д���)�����ö�������ָ��(�����Ͼ��Ǹ���OpenGL��δ�������)��
* 3-��Դ:     �����˶���⣬���Դ���۹��λ�ú���ɫ��
* 4-��ɫ��:   ����������͵Ƶ���ɫ����Ȼ����Shader���зֱ�����Ϊ��ɫ��������Ⱦʱʹ����ɫ������
* 5-�����:   �����ÿ֡�ļ��ʱ�䣬�Լ�������İڷ�λ�á�
* 6-��Ⱦ:     ������ʱ�䣬������ƣ���ջ��壬������Դ������������������͵ƣ�������������鴥���¼����ͷ���Դ��
* ע��        ���̿���1~8�ɿ��ƿ��صƣ�2~7�ǲ�ͬ��ɫ�ĵ��Դ��1��ƽ�й⣬8���ֵ�Ͳ�۹�
*/

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "iostream"
#include "sstream"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"

// ��Ļ����
float SCREEN_WIDTH = 1280.0f;
float SCREEN_HRIGHT = 720.0f;

float delta_time = 0.0f;  // ��ǰ֡����һ֡��ʱ���
float last_frame = 0.0f;  // ��һ֡��ʱ��

float last_x = SCREEN_WIDTH / 2.0f, last_y = SCREEN_HRIGHT / 2.0f;   // ��������ʼλ��Ϊ��Ļ����
unsigned int light_bits = 0;                                         // ���ƿ��ص�

Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));                 // �����λ��

																	 // ��������																 
float vertices[] = {
	// ---- λ�� ----       ---- ���� ----   
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// ���Դλ��
glm::vec3 point_light_positions[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.5f, 0.0f),
	glm::vec3(0.0f, 0.0f, 2.0f),
	glm::vec3(0.0f, -2.5f, 0.0f),
	glm::vec3(0.0f, 0.0f, -3.0f),
	glm::vec3(-3.5f, 0.0f, 0.0f)
};

// ��Դ��ɫ
glm::vec3 light_colors[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.5f, 0.5f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.5f, 0.5f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.0f, 0.5f)
};

void ProcessInput(GLFWwindow *window);
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void MouseCallback(GLFWwindow* window, double x_pos, double y_pos);
void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
bool IsLightOn(int index);

int main()
{
	// ---------------------��ʼ��--------------------------
	// glfw��ʼ�������õ�GL�汾Ϊ3.3���İ汾
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// ����GL����
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HRIGHT, "Phong", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ָ��������Ϊ��ǰ����
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);            // ���ع�꣬���ͣ���ڴ�����
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetKeyCallback(window, KeyCallback);

	// ��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed!" << std::endl;
		return -1;
	}

	// ������Ȳ��Բ���תy���꣬����y���������ӵײ�����������������ģ��������ת������ƫ����ʱҪ������
	glEnable(GL_DEPTH_TEST);
	camera.flip_y = true;

	// ��ɫ��(������͵�)
	Shader lamp_shader = Shader("res/shader/DrawLamp.vs", "res/shader/DrawLamp.fs");
	Shader cube_shader = Shader("res/shader/DrawCube.vs", "res/shader/DrawCube.fs");

	// ����1������⣬6�����Դ
	DirectLight dirLight = DirectLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f), glm::vec3(0.4f), glm::vec3(0.5f));
	PointLight pointLights[6];

	// ���Դ
	for (int i = 0; i < 6; i++)
	{
		pointLights[i] = PointLight(point_light_positions[i], 0.05f * light_colors[i], 0.8f * light_colors[i], light_colors[i], 1.0f, 0.09f, 0.032f);
	}

	// �۹�
	SpotLight spotLight = SpotLight(camera.position, camera.forward, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f),
		1.0f, 0.09f, 0.032f, cos(glm::radians(12.5f)), cos(glm::radians(15.0f)));

	// ---------------------�󶨶����������----------------------
	unsigned int vbo, lamp_vao, cube_vao;
	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cube_vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &lamp_vao);
	glBindVertexArray(lamp_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	last_frame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		// ��ÿһ֡�м�����µ�deltaTime
		float current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// �������
		ProcessInput(window);

		// �����ɫ����Ȼ���
		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), SCREEN_WIDTH / SCREEN_HRIGHT, 0.1f, 100.0f);

		// ��������һ����ɫ����(Cyan Plastic)�Ĳ���
		cube_shader.Use();
		cube_shader.SetVec3("viewPos", camera.position);
		cube_shader.SetFloat("material.shininess", 32.0f);
		cube_shader.SetVec3("material.diffuse", 0.0f, 0.50980392f, 0.50980392f);
		cube_shader.SetVec3("material.specular", 0.50196078f, 0.50196078f, 0.50196078f);

		// ƽ�й��Դ
		dirLight.SetOn(IsLightOn(0));
		dirLight.Draw(cube_shader, "dirLight");

		// ���Դ
		for (int i = 0; i < 6; i++)
		{
			std::stringstream name_stream;
			name_stream << "pointLights[" << i << "]";
			std::string name = name_stream.str();
			pointLights[i].SetOn(IsLightOn(i + 1));
			pointLights[i].Draw(cube_shader, name);
		}

		// �ֵ�Ͳ��Դ
		spotLight.SetOn(IsLightOn(7));
		spotLight.SetPosition(camera.position);
		spotLight.SetDirection(camera.forward);
		spotLight.Draw(cube_shader, "spotLight");

		cube_shader.SetMat4("projection", projection);
		cube_shader.SetMat4("view", view);

		// ����������
		glBindVertexArray(cube_vao);
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, current_frame, glm::vec3(1.0f, 0.3f, 0.5f));
		cube_shader.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lamp_shader.Use();
		lamp_shader.SetMat4("projection", projection);
		lamp_shader.SetMat4("view", view);

		// ���Ƶ�
		glBindVertexArray(lamp_vao);
		for (int i = 0; i < 6; i++)
		{
			if (IsLightOn(i + 1))
			{
				glm::mat4 model(1.0f);
				model = glm::translate(model, point_light_positions[i]);
				model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
				lamp_shader.SetMat4("model", model);
				lamp_shader.SetVec3("lightColor", light_colors[i]);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &lamp_vao);
	glDeleteVertexArrays(1, &cube_vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}

// ���̿���(�����λ��WSAD -> ��������)
void ProcessInput(GLFWwindow *window)
{
	float speed = camera.mouse_speed * delta_time;
	// �ƶ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.Move(camera.forward * speed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Move(-camera.forward * speed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Move(-camera.right * speed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Move(camera.right * speed);
}

// ���ڴ�С�����Ļص�����(�����ڴ�С�ı�ʱ���ӿ�ҲҪ�ı�)
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// ���̿��ƻص�(ESC -> �˳���1~8 -> ���ƿ��ص�)
void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, true); break;
		case GLFW_KEY_1: light_bits ^= 1; break;
		case GLFW_KEY_2: light_bits ^= (1 << 1); break;
		case GLFW_KEY_3: light_bits ^= (1 << 2); break;
		case GLFW_KEY_4: light_bits ^= (1 << 3); break;
		case GLFW_KEY_5: light_bits ^= (1 << 4); break;
		case GLFW_KEY_6: light_bits ^= (1 << 5); break;
		case GLFW_KEY_7: light_bits ^= (1 << 6); break;
		case GLFW_KEY_8: light_bits ^= (1 << 7); break;
		default:
			break;
		}
	}
}

// �����ƻص�
void MouseCallback(GLFWwindow* window, double x_pos, double y_pos)
{
	float x_offset = x_pos - last_x;       // ���㵱ǰ֡����һ֡�����λ��ƫ����
	float y_offset = y_pos - last_y;
	last_x = x_pos;
	last_y = y_pos;

	float sensitivity = 0.1;               // ������*ƫ��������������ƶ�̫��
	x_offset *= sensitivity;
	y_offset *= sensitivity;

	camera.Rotate(glm::vec3(x_offset, y_offset, 0));
}

// ���ֿ��ƻص�
void ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
	camera.Zoom(y_offset);
}

// ���ƿ��ص�
bool IsLightOn(int index)
{
	return (light_bits >> index) & 1;
}


