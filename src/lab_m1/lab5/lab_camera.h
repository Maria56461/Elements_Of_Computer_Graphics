#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implemented
{
    class Camera
    {
     public:
        Camera() {
            position    = glm::vec3(0, 2, 5);
            forward     = glm::vec3(0, 0, -1);
            up          = glm::vec3(0, 1, 0);
            right       = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            Set(position, center, up);
        }

        ~Camera()
        { }

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
        {
            this->position = position;
            forward     = glm::normalize(center - position);
            right       = glm::cross(forward, up);
            this->up    = glm::cross(right, forward);
        }

        void MoveForward(float distance) {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance) {
          
            position += forward * distance;
        }

        void TranslateUpward(float distance) {
            
            position += up * distance;
        }

        void TranslateRight(float distance) {

            glm::vec3 dir = glm::normalize(glm::vec3(right.x, 0, right.z));
            position += dir * distance;
        }

        void RotateFirstPerson_OX(float angle) {
          
            glm::mat4 R = glm::rotate(glm::mat4(1), angle, right);
            forward = glm::normalize(R * glm::vec4(forward, 0));
            up = glm::cross(right, forward);

        }

        void RotateFirstPerson_OY(float angle) {
           
            glm::mat4 R = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
            forward = glm::normalize(R * glm::vec4(forward, 0));
            right = glm::normalize(R * glm::vec4(right, 0));
            up = glm::cross(right, forward);
        }

        void RotateFirstPerson_OZ(float angle) {

            // TODO(student): Compute the new `right` and `up`. This time,
            // `forward` stays the same. Use `glm::rotate()`. Don't forget
            // to normalize the vectors!
         //   glm::mat4 R = glm::rotate(glm::mat4(1), angle, forward);
         //   right = glm::normalize(R * glm::vec4(right, 0));
         //   up = glm::cross(right, forward);
        }

        void RotateThirdPerson_OX(float angle) {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OX(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OY(float angle) {
            TranslateForward(distanceToTarget);
            RotateFirstPerson_OY(angle);
            TranslateForward(-distanceToTarget);
        }

        void RotateThirdPerson_OZ(float angle)
        {
            // TODO(student): Rotate the camera in third-person mode around
            // the OZ axis.

        }

        glm::mat4 GetViewMatrix()
        {
            // intoarce o matrice de vizualizare pe care o vom aplica asupra a tot ceea ce este in scena 
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

     public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   
