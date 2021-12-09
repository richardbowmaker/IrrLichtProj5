#pragma once

#include <irrlicht.h>
#include <Windows.h>

class CScene
{
public:

    CScene();
    ~CScene();

    bool initialise(HWND hwnd);
    void uninitialise();
    bool run();
    void setSize(int width, int height);

private:

    bool initialised_;
    irr::IrrlichtDevice *device_;
    irr::video::E_DRIVER_TYPE driverType_;
    irr::video::IVideoDriver *driver_;
    irr::scene::ISceneManager *smgr_;
    irr::video::SExposedVideoData videodata_;
    HWND hWnd_;

};

