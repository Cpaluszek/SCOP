#ifndef INC_INPUT_H_
#define INC_INPUT_H_


#include "./Camera.h"
#include "./Window.h"

#include "../lib/GLFW/include/glfw3.h"

class Input {
 public:
     void processInput() const;

     void setCamera(Camera* camera);
     void setWindow(GLFWwindow* window);

 private:
     Camera* camera;
     GLFWwindow* window;
     // Todo: protect ptr access
};

#endif  // INC_INPUT_H_
