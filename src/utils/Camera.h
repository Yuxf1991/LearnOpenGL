//
// Created by Yuxf1991 on 2020/1/12.
//

#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f));
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    ~Camera() = default;
    inline glm::mat4 getViewMatrix() { return glm::lookAt(mPosition, mPosition + mFront, mUp); }
    inline float getZoom() { return mZoom; }
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void processMouseScroll(float yOffset);

private:
    void updateCameraVectors();

    // Euler Angles
    float mYaw;
    float mPitch;

    // Camera options
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;

    // Camera Attributes
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
};

#endif  // LEARNOPENGL_CAMERA_H
