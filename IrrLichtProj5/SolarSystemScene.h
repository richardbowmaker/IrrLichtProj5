#pragma once

#include <irrlicht.h>
#include <Windows.h>

#include "General.h"

class CSolarSystemScene : public IScene
{
public:

    CSolarSystemScene();
    ~CSolarSystemScene();

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
    CTimer timer_;
    irr::scene::ISceneNode *centre_;
    irr::scene::ISceneNode *sun_;
    irr::scene::ISceneNode *earth_orbit_centre_;
    irr::scene::ISceneNode *earth_centre_;
    irr::scene::ISceneNode *earth_;
    irr::scene::ISceneNode *moon_centre_;
    irr::scene::ISceneNode *moon_;
    EventReceiver receiver_;
    irr::scene::ICameraSceneNode *camera_;
};




