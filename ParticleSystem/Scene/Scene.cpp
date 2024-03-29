#include "Scene.h"

Scene::Scene(int display_w, int display_h) : camera(display_w, display_h), particleGenerator(10000) {
}

Scene::~Scene() {
}

void Scene::fixedUpdate(float deltaTime) {
    if (isPaused)
    {
        return;
    }
    //    cube.update(deltaTime);
    //    billboard.update(deltaTime);
    particleGenerator.update(deltaTime);
}

void Scene::update(float deltaTime) {
    camera.update(deltaTime);
}

void Scene::render() {
    //    cube.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    //    billboard.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    particleGenerator.render(camera.getViewMatrix(), camera.getProjectionMatrix());
}

void Scene::updateProjectionMatrix(int display_w, int display_h) {
    camera.updateProjectionMatrix(display_w, display_h);
}
void Scene::togglePause() {
    isPaused = !isPaused;
}
