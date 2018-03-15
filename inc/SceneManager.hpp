#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <stack>

#include "Scene.hpp"

class Scene;

enum Scenes
{
    MENU = 0,
    PLAY,
    END
};

class SceneManager
{
public:

    SceneManager();
    ~SceneManager();

    void init();

    void addScene(Scenes newScene, bool replace = true);
    void popScene();

    void applySceneRequests();

    Scene& activeScene();

    bool exitRequest() const;

private:

    std::stack< std::unique_ptr<Scene> > _scenes;

    bool _addRequest;
    bool _replace;
    Scenes _requestName;
    bool _popRequest;

    bool _exitRequest;

    void pushScene(Scenes newScene);

};

#endif