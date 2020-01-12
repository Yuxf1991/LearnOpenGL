//
// Created by Yuxf1991 on 2020/1/12.
//
#include "Camera.h"

Camera::Camera(glm::vec3 position)
    : mPosition(position),
      mWorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      mYaw(YAW),
      mPitch(PITCH),
      mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      mMovementSpeed(SPEED),
      mMouseSensitivity(SENSITIVITY),
      mZoom(ZOOM)
{
    updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : mPosition(position),
      mWorldUp(up),
      mYaw(yaw),
      mPitch(pitch),
      mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      mMovementSpeed(SPEED),
      mMouseSensitivity(SENSITIVITY),
      mZoom(ZOOM)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : mPosition(glm::vec3(posX, posY, posZ)),
      mWorldUp(glm::vec3(upX, upY, upZ)),
      mYaw(yaw),
      mPitch(pitch),
      mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
      mMovementSpeed(SPEED),
      mMouseSensitivity(SENSITIVITY),
      mZoom(ZOOM)
{
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    mRight =
        glm::normalize(glm::cross(mFront, mWorldUp));  // Normalize the vectors, because their length gets closer to 0
                                                       // the more you look up or down which results in slower movement.
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

void Camera::processMouseScroll(float yOffset)
{
    if (mZoom >= 1.0f && mZoom <= 45.0f) {
        mZoom -= yOffset;
    }
    if (mZoom < 1.0f) {
        mZoom = 1.0f;
    }
    if (mZoom > 45.0f) {
        mZoom = 45.0f;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    xOffset *= mMouseSensitivity;
    yOffset *= mMouseSensitivity;

    mYaw += xOffset;
    mPitch += yOffset;

    if (constrainPitch) {
        mPitch = (mPitch > 89.0f) ? 89.0f : mPitch;
        mPitch = (mPitch < -89.0f) ? -89.0f : mPitch;
    }
    updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;
    if (direction == FORWARD) {
        mPosition += (mFront * velocity);
    }
    if (direction == BACKWARD) {
        mPosition -= (mFront * velocity);
    }
    if (direction == LEFT) {
        mPosition -= (mRight * velocity);
    }
    if (direction == RIGHT) {
        mPosition += (mRight * velocity);
    }
}