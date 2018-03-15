
#include "SceneManager.hpp"

#include "Scene_Menu.hpp"
#include "Scene_Play.hpp"

SceneManager::SceneManager()
{
    _addRequest = false;
    _replace = false;
    _popRequest = false;
    _exitRequest = false;
}

SceneManager::~SceneManager()
{
}

void SceneManager::init()
{
    addScene(Scenes::MENU);
    applySceneRequests();
}

void SceneManager::addScene(Scenes newScene, bool replace)
{
    _addRequest = true;
    _replace = replace;
    _requestName = newScene;
}

void SceneManager::pushScene(Scenes newScene) //Scene switch
{
    switch(newScene)
    {
        case MENU:
            _scenes.push(std::move(std::unique_ptr<Scene>(new Scene_Menu(*this))));
            break;
        case PLAY:
            _scenes.push(std::move(std::unique_ptr<Scene>(new Scene_Play(*this))));
            break;
        case END:
            _exitRequest = true;
            break;
        default:
            _exitRequest = true;
            break;
    }
}

void SceneManager::popScene()
{
    _popRequest = true;
}

void SceneManager::applySceneRequests()
{
    if(_addRequest)
    {
        if(!_scenes.empty())
        {
            if(_replace)
            {
                _scenes.pop();
            }
            else
            {
                _scenes.top()->pause();
            }
        }

        pushScene(_requestName);

        _scenes.top()->init();

        _addRequest = false;
    }

    if(_popRequest)
    {
        if(!_scenes.empty())
        {
            _scenes.pop();

            if(!_scenes.empty())
            {
                _scenes.top()->resume();
            }
        }

        if(_scenes.empty()) _exitRequest = true;

        _popRequest = false;
    }
}

Scene& SceneManager::activeScene()
{
    return *_scenes.top();
}

bool SceneManager::exitRequest() const
{
    return _exitRequest;
}