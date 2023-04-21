#include "Pch.h"
#include "GLFW/glfw3.h"
#include "graphics/Camera.h"
#include <gtc/matrix_transform.hpp>

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix(float screenWidth, float inverseScreenHeight) const
{
    return glm::perspective(glm::radians(m_fov), screenWidth * inverseScreenHeight, 0.1f, 100.0f);
}

//void Camera::ProcessKeyboardInput(GLFWwindow*& window, const float deltaTime)
//{
//    float velocity = m_movementSpeed * deltaTime;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        m_position += m_front * velocity;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        m_position -= m_front * velocity;
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        m_position -= m_right * velocity;
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        m_position += m_right * velocity;
//}

void Camera::ProcessMouseInput(float xOffset, float yOffset, const bool constrainPitch)
{
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    if (constrainPitch) 
    {
        if (m_pitch > 89.0f) 
            m_pitch = 89.0f;

        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
        
    }

    UpdateVectors();
}

Camera::~Camera()
{
}

void Camera::UpdateVectors()
{
    glm::vec3 front{};
    front.x = cosf(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sinf(glm::radians(m_pitch));
    front.z = sinf(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
