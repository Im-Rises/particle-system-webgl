#include "ParticleGeneratorBillboard.h"

#include <algorithm>
#include <glad/glad.h>
#include "ballImage.h"

const char* vertexShader = R"(#version 300 es

precision mediump float;

layout (location = 0) in vec3 a_vertex;
layout (location = 1) in vec3 a_position;
layout (location = 2) in vec2 a_scale;
layout (location = 3) in vec4 a_color;

out vec2 v_UV;
out vec4 v_color;

uniform mat4 u_mvp;
uniform vec3 u_cameraRight;
uniform vec3 u_cameraUp;

void main()
{
    vec3 billboardPos = a_position
    + u_cameraRight * a_vertex.x * a_scale.x
    + u_cameraUp * a_vertex.y * a_scale.y;
    gl_Position = u_mvp * vec4(billboardPos, 1.0);
    v_UV = a_vertex.xy + vec2(0.5, 0.5);
    v_color = a_color;
}
)";

// const char* fragmentShader = "#version 300 es\n"
//                              "\n"
//                              "precision mediump float;\n"
//                              "\n"
//                              "in vec2 v_UV;\n"
//                              "in vec4 v_color;\n"
//                              "\n"
//                              "out vec4 o_fragColor;\n"
//                              "\n"
//                              "uniform sampler2D u_texture;\n"
//                              "\n"
//                              "void main() {\n"
//                              "\to_fragColor = texture(u_texture, v_UV);\n"
//                              "\tif (o_fragColor.a < 0.1)\n"
//                              "\tdiscard;\n"
//                              "\to_fragColor = v_color;\n"
//                              "}\n\0";

const char* fragmentShader = R"(#version 300 es

precision mediump float;

in vec2 v_UV;
in vec4 v_color;

out vec4 o_fragColor;

uniform sampler2D u_texture;

void main() {
    o_fragColor = texture(u_texture, v_UV);
    if (o_fragColor.a < 0.1)
    discard;
    o_fragColor = v_color;
}
)";

ParticleGeneratorBillboard::ParticleGeneratorBillboard(int particlesCount) : Entity(vertexShader,
                                                                                 fragmentShader),
                                                                             texture(ballImage, ballImageSize),
                                                                             randomEngine(std::random_device()()) {
    // Init particles
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->particlesCount = particlesCount;
    particles.resize(particlesCount);
    resetParticles();
    // Init opengl buffers
    create();
}

void ParticleGeneratorBillboard::create() {
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), particles.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, scale));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
    glEnableVertexAttribArray(3);

    glVertexAttribDivisor(1, 1); // tell OpenGL this is an instanced vertex attribute.
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

ParticleGeneratorBillboard::~ParticleGeneratorBillboard() {
    destroy();
}

void ParticleGeneratorBillboard::destroy() {
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteBuffers(1, &instanceVBO);
}

void ParticleGeneratorBillboard::update(float deltaTime) {
    for (int i = 0; i < particlesCount; i++)
    {
        particles[i].lifeTime -= deltaTime;

        if (particles[i].lifeTime > 0)
        {
            particles[i].velocity += sumForces * deltaTime; // F = a
            particles[i].position += particles[i].velocity * deltaTime + 0.5F * sumForces * deltaTime * deltaTime;
        }
        else
        {
            resetParticle(i);
        }
    }
}

void ParticleGeneratorBillboard::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    /* Sort particles using camera distance to blend correctly*/
    //     Calculate camera distance
    glm::mat4 inv_view_matrix = glm::inverse(cameraViewMatrix);
    auto cameraPos = glm::vec3(inv_view_matrix[3]);
    for (int i = 0; i < particlesCount; i++)
    {
        particles[i].cameraDistance = glm::length_t(glm::length(cameraPos - particles[i].position));
    }
    // Sort particles
    std::sort(particles.begin(), particles.end(), [](const Particle& a, const Particle& b) {
        return a.cameraDistance > b.cameraDistance;
    });

    // Shader
    shader.use();
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);
    shader.setVec3("u_cameraRight", cameraViewMatrix[0][0], cameraViewMatrix[1][0], cameraViewMatrix[2][0]);
    shader.setVec3("u_cameraUp", cameraViewMatrix[0][1], cameraViewMatrix[1][1], cameraViewMatrix[2][1]);

    // Texture
    texture.bind();

    // Draw
    glBindVertexArray(quadVAO);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesCount);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), particles.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleGeneratorBillboard::resetParticles() {
    for (int i = 0; i < particlesCount; i++)
    {
        resetParticle(i);
    }
}

void ParticleGeneratorBillboard::resetParticle(unsigned int index) {
    if (randomizePosition)
    {
        switch (spreadType)
        {
        case SpreadType::SPREAD_TYPE_SPHERE:
            particles[index].position = randomVec3InSphere(spreadRadius);
            break;
        case SpreadType::SPREAD_TYPE_RECTANGLE:
            particles[index].position = randomVec3InRectangle(minRectangleSpread, maxRectangleSpread);
            break;
        default:
            break;
        }
    }
    else
        particles[index].position = position;

    if (randomizeInitialVelocity)
        particles[index].velocity = randomVec3(minInitialVelocity, maxInitialVelocity);
    else
        particles[index].velocity = fixedInitialVelocity;

    if (randomizeLifeTime)
        particles[index].lifeTime = randomFloat(minLifeTime, maxLifeTime);
    else
        particles[index].lifeTime = fixedLifeTime;

    if (randomizeScale)
    {
        if (keepScaleAspectRatio)
        {
            float scale = randomFloat(minScale.x, maxScale.x);
            particles[index].scale = { scale, scale };
        }
        else
            particles[index].scale = randomVec2(minScale, maxScale);
    }
    else
        particles[index].scale = fixedScale;

    if (randomizeColor)
    {
        if (randomizeColorAlpha)
        {
            glm::vec3 randomColor = { randomFloat(minColor.x, maxColor.x), randomFloat(minColor.y, maxColor.y), randomFloat(minColor.z, maxColor.z) };
            float randomAlpha = randomFloat(minColorAlpha, maxColorAlpha);
            particles[index].color = { randomColor.x, randomColor.y, randomColor.z, randomAlpha };
        }
        else
        {
            glm::vec3 randomColor = { randomFloat(minColor.x, maxColor.x), randomFloat(minColor.y, maxColor.y), randomFloat(minColor.z, maxColor.z) };
            particles[index].color = { randomColor.x, randomColor.y, randomColor.z, fixedColorAlpha };
        }
    }
    else
    {
        if (randomizeColorAlpha)
        {
            particles[index].color = { fixedColor.x, fixedColor.y, fixedColor.z, randomFloat(minColorAlpha, maxColorAlpha) };
        }
        else
        {
            particles[index].color = { fixedColor.x, fixedColor.y, fixedColor.z, fixedColorAlpha };
        }
    }
}

float ParticleGeneratorBillboard::randomFloat(float min, float max) {
    if (min > max)
        std::swap(min, max);
    std::uniform_real_distribution<float> dist(min, max);
    return dist(randomEngine);
}

glm::vec2 ParticleGeneratorBillboard::randomVec2(glm::vec2 min, glm::vec2 max) {
    return { randomFloat(min.x, max.x), randomFloat(min.y, max.y) };
}

glm::vec3 ParticleGeneratorBillboard::randomVec3(glm::vec3 min, glm::vec3 max) {
    return { randomFloat(min.x, max.x), randomFloat(min.y, max.y), randomFloat(min.z, max.z) };
}

glm::vec4 ParticleGeneratorBillboard::randomVec4(glm::vec4 min, glm::vec4 max) {
    return { randomFloat(min.x, max.x), randomFloat(min.y, max.y), randomFloat(min.z, max.z), randomFloat(min.w, max.w) };
}

glm::vec3 ParticleGeneratorBillboard::randomVec3InSphere(float radius) {
    glm::vec3 randomVec = randomVec3({ -1, -1, -1 }, { 1, 1, 1 });
    return glm::normalize(randomVec) * randomFloat(0, radius) + position;
}

glm::vec3 ParticleGeneratorBillboard::randomVec3InRectangle(glm::vec3 min, glm::vec3 max) {
    return randomVec3(min, max) + position;
}

void ParticleGeneratorBillboard::setParticlesCount(int maxParticles) {
    particlesCount = maxParticles;
    particles.resize(particlesCount);
    resetParticles();
}

int ParticleGeneratorBillboard::getParticlesCount() const {
    return particlesCount;
}
