//
// Created by Christopher Gruber on 6/26/24.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::moveForward(float delta) {
    glm::vec3 forward = glm::normalize(glm::vec3(0.0f, 0.0f, 0.0f) - position);
    position += forward * delta;
}

void Camera::moveBackward(float delta) {
    glm::vec3 backward = glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f));
    position += backward * delta;
}

void Camera::zoomIn(float delta) {
    if(zoom >= 1.0f && zoom <= 45.0f)
        zoom -= delta;
    if(zoom <= 1.0f)
        zoom = 1.0f;
}

void Camera::zoomOut(float delta) {
    if(zoom <= 45.0f)
        zoom += delta;
    if(zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::reset() {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    zoom = 45.0f;
}

void Camera::rotateAroundYAxis(float angle) {
    glm::vec3 center(0.0f, 0.0f, 0.0f); // assuming the cube is at the origin
    glm::vec3 direction = glm::normalize(position - center);
    auto rotation = glm::mat4(
            cos(angle), 0, sin(angle), 0,
            0, 1, 0, 0,
            -sin(angle), 0, cos(angle), 0,
            0, 0, 0, 1
    );
    auto newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    position = center + newDirection * glm::length(position - center);
}

void Camera::rotateAroundXAxis(float angle) {
    glm::vec3 center(0.0f, 0.0f, 0.0f); // assuming the cube is at the origin
    glm::vec3 direction = glm::normalize(position - center);
    auto rotation = glm::mat4(
            1, 0, 0, 0,
            0, cos(angle), -sin(angle), 0,
            0, sin(angle), cos(angle), 0,
            0, 0, 0, 1
    );
    auto newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    position = center + newDirection * glm::length(position - center);
}

float Camera::getZoom() const {
    return zoom;
}

const glm::vec3 &Camera::getPosition() const {
    return position;
}