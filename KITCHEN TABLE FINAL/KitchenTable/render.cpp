#include "global.h"

void URender(Mesh &mesh, GLuint ProgramId, GLFWwindow** window, GLuint textureId, glm::vec2 UVscale)
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // 1. Scales the object by 2
    glm::mat4 scale = glm::scale(mesh.scale);

    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(mesh.position);
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * mesh.rotation * scale;

    // Transforms the camera: moves the camera back and tilts it at the approximate angle of my image
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection;

    if (!ortho)
    {
         projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    }
    else
    {
        projection = glm::ortho(-10.0f, 15.0f, -10.0f, 15.0f, -20.0f, 50.0f);
    }

    // Set the shader to be used
    glUseProgram(ProgramId);

    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(ProgramId, "model");
    GLint viewLoc = glGetUniformLocation(ProgramId, "view");
    GLint projLoc = glGetUniformLocation(ProgramId, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    //LIGHTING ----------------------------------------------------------------------
    GLint objectColorLoc = glGetUniformLocation(ProgramId, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(ProgramId, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(ProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(ProgramId, "viewPosition");

    glUniform3f(objectColorLoc, 1.0f, 1.0f, 0.5f);
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLoc, lightPos.x, lightPos.y, lightPos.z);

    glUniform3f(viewPositionLoc, cameraPos.x, cameraPos.y, cameraPos.z);


    //TEXTURE ---------------------------------------------------------------------------

    GLint UVScaleLoc = glGetUniformLocation(ProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(UVscale));

    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(mesh.vao);

    //activate texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Draws the triangles
    glDrawArrays(GL_TRIANGLES, 0, mesh.nVerts);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}