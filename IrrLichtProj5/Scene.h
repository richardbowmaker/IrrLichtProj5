#pragma once

#include <irrlicht.h>
#include <Windows.h>

#include "General.h"

class CScene : public IScene
{
public:

    CScene();
    ~CScene();

    virtual bool initialise(HWND hwnd);
    virtual void uninitialise();
    virtual bool run();

private:

    bool initialised_;
    irr::IrrlichtDevice *device_;
    irr::video::E_DRIVER_TYPE driverType_;
    irr::video::IVideoDriver *driver_;
    irr::scene::ISceneManager *smgr_;
    irr::video::SExposedVideoData videodata_;
    HWND hWnd_;

};

