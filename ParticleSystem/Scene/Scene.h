#ifndef SCENE_H
#define SCENE_H

#include "Camera/Camera.h"
#include "Entity/ParticleGenerator/ParticleGeneratorBillboard.h"

class Scene {
private:
    bool isPaused = false;

public:
    Camera camera;
    ParticleGeneratorBillboard particleGenerator;

    // private:
    //     Billboard billboard;
    //     Cube cube;

public:
    Scene(int display_w, int display_h);
    ~Scene();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();

public:
    void updateProjectionMatrix(int display_w, int display_h);
    void togglePause();
};

#endif // SCENE_H
