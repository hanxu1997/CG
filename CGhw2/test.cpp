#include <stdio.h>
#include  <imgui.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int argc,char* argv[])
{
    //设置窗口
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Void Player", NULL, NULL);
    glfwMakeContextCurrent(window);
    //绑定ImGUi
    ImGui_ImplGlfw_Init(window, true);

    ImVec4 clear_color = ImColor(114, 144, 154);

    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();       
        ImGui_ImplGlfw_NewFrame();  

        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        glfwSwapBuffers(window);

    }

    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();

    return 0;
}
