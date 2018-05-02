#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const char* shadow_mapping_vertex = "#version 440 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNormal;\n"
"layout (location = 2) in vec2 aTexCoords;\n"
"out vec2 TexCoords;\n"
"out VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"    vec4 FragPosLightSpace;\n"
"} vs_out;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 lightSpaceMatrix;\n"
"void main()\n"
"{\n"
"    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));\n"
"    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;\n"
"    vs_out.TexCoords = aTexCoords;\n"
"    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);\n"
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"}\n\0";

const char* shadow_mapping_fragment = "#version 440 core\n"
"out vec4 FragColor;\n"
"in VS_OUT {\n"
"    vec3 FragPos;\n"
"    vec3 Normal;\n"
"    vec2 TexCoords;\n"
"    vec4 FragPosLightSpace;\n"
"} fs_in;\n"
"uniform sampler2D diffuseTexture;\n"
"uniform sampler2D shadowMap;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 viewPos;\n"
"float ShadowCalculation(vec4 fragPosLightSpace)\n"
"{\n"
"    // 执行透视除法\n"
"    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;\n"
"    // 变换到[0,1]的范围\n"
"    projCoords = projCoords * 0.5 + 0.5;\n"
"    // 取得最近点的深度（使用[0,1]范围下的fragPosLight当坐标）\n"
"    float closestDepth = texture(shadowMap, projCoords.xy).r; \n"
"    // 取得当前片元在光源视角下的深度\n"
"    float currentDepth = projCoords.z;\n"
"    // 阴影偏移\n"
"    vec3 normal = normalize(fs_in.Normal);\n"
"    vec3 lightDir = normalize(lightPos - fs_in.FragPos);\n"
"    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);\n"
"    // PCF\n"
"    float shadow = 0.0;\n"
"    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);\n"
"    for(int x = -1; x <= 1; ++x)\n"
"    {\n"
"        for(int y = -1; y <= 1; ++y)\n"
"        {\n"
"            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; \n"
"            // 判断是否在阴影中，是+1\n"
"            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        \n"
"        }    \n"
"    }\n"
"    shadow /= 9.0;\n"
"    // 消除超出坐标的阴影\n"
"    if(projCoords.z > 1.0)\n"
"        shadow = 0.0;\n"
"        \n"
"    return shadow;\n"
"}\n"
"void main()\n"
"{           \n"
"    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;\n"
"    vec3 normal = normalize(fs_in.Normal);\n"
"    vec3 lightColor = vec3(0.3);\n"
"    // ambient\n"
"    vec3 ambient = 0.3 * color;\n"
"    // diffuse\n"
"    vec3 lightDir = normalize(lightPos - fs_in.FragPos);\n"
"    float diff = max(dot(lightDir, normal), 0.0);\n"
"    vec3 diffuse = diff * lightColor;\n"
"    // specular\n"
"    vec3 viewDir = normalize(viewPos - fs_in.FragPos);\n"
"    vec3 reflectDir = reflect(-lightDir, normal);\n"
"    float spec = 0.0;\n"
"    vec3 halfwayDir = normalize(lightDir + viewDir);  \n"
"    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);\n"
"    vec3 specular = spec * lightColor;    \n"
"    // shadow\n"
"    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      \n"
"    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    \n"
"    FragColor = vec4(lighting, 1.0);\n"
"}\n\0";

const char* shadow_mapping_depth_vertex = "#version 440 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 lightSpaceMatrix;\n"
"uniform mat4 model;\n"
"void main()\n"
"{\n"
"    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);\n"
"}\n\0";

const char* shadow_mapping_depth_fragment = "#version 440 core\n"
"void main()\n"
"{             \n"
"    // gl_FragDepth = gl_FragCoord.z;\n"
"}\n\0";


// link vertex shader and fragment shader
int shaderprogram(const char * vertexShaderSource, const char* fragmentShaderSource) {
	// 创建并编译着色器程序
	// 1. 顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// 检查顶点着色器是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 2. 片段着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// 检查片段着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// 链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// 检查是否链接成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	// 链接完成后删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}
/*
ID: shader ID
name: uniform parameter
value：the value of parameter
*/

void setFloat(int ID, const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void setVec3(int ID, const std::string &name, const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
/*
ID: shader ID
name: uniform parameter
value：the value of parameter
*/
void setMat4(int ID, const std::string &name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}