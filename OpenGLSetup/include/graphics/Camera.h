#pragma once
class Camera
{
public:
    Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
        const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
        const float yaw = -90.0f,
        const float pitch = 0.0f)
        : m_position(position), m_up(up), m_yaw(yaw), m_pitch(pitch)
    {
        UpdateVectors();
    }

    glm::mat4 GetViewMatrix() const;

    glm::mat4 GetProjectionMatrix(float screenWidth, float inverseScreenHeight) const;

    void ProcessMouseInput(const float xOffset, const float yOffset, const bool constrainPitch = true);
    ~Camera();
private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -3.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 m_worldUp;
    float m_yaw = -90.f;
    float m_pitch = 0.0f;
    float m_movementSpeed = 1.f;
    float m_mouseSensitivity = 1;
    float m_fov = 1920.f/1080.f;

    void UpdateVectors();
};