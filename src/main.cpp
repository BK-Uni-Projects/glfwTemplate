#include <chrono>
#include <iostream>
#include <thread>

// GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// NOTE: include before SDL.h
#include <GL/glew.h>

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#include <GLFW/glfw3.h>

// - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// NOTE: must do before including GLM headers
// NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void glfw_error_callback(int error, const char *description) {
  printf(description);
}

int main(int argc, char *argv[]) {
  // Set GLFW error callback
  glfwSetErrorCallback(glfw_error_callback);

  // GLFW initialise
  auto glfwInitStatus = glfwInit();
  if (glfwInitStatus != GLFW_TRUE) {
    fprintf(stderr, "GLFW Init Error.\n");
    return 1;
  }
  fprintf(stderr, "GLFW initialised OK!\n");

  // Set OpenGL context parameters
  int major = 3, minor = 3;
  fprintf(stderr, "Asking for OpenGL %d.%d context\n", major, minor);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

  // Window Creation
  GLFWwindow *win = nullptr;
  win = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
  if (win == nullptr) {
    fprintf(stderr, "glfwCreateWindow error\n");
    return 1;
  }

  glfwMakeContextCurrent(win);

  // initialise GLEW - sets up the OpenGL function pointers for the version of
  // OpenGL we're using
  GLenum rev;
  glewExperimental = GL_TRUE; // GLEW isn't perfect - see
  // https://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
  rev = glewInit();
  if (GLEW_OK != rev) {
    fprintf(stderr, "glewInit error: %s\n", glewGetErrorString(rev));
    return 1;
  }
  fprintf(stderr, "glew initialised OK!\n");

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
  glfwPollEvents();

  // Clear the back buffer
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Render
  // TODO add render code

  // Present the back buffer
  glfwSwapBuffers(win);

  // Wait
  {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s); // 2 seconds
  }

  // Clean up
  fprintf(stderr, "Finished. Cleaning up and closing down\n");

  glfwTerminate();

  return 0;
}
