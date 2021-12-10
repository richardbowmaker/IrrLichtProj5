
#include <irrlicht.h>
#include <Windows.h>

#include "General.h"
#include "SolarSystemScene.h"

CSolarSystemScene::CSolarSystemScene(CameraViewT cameraView) : 
    initialised_(false), 
    driverType_(irr::video::EDT_DIRECT3D9), 
    videodata_(0),
    cameraView_(cameraView)
{
}

CSolarSystemScene::~CSolarSystemScene()
{
}

bool CSolarSystemScene::initialise(HWND hwnd)
{
    const float earth_dist = 50.0f;
    const float earth_radius = 3.0f;
    const float moon_dist = 10.0f;
    const float moon_radius = 1.0f;

    hWnd_ = hwnd;

    irr::SIrrlichtCreationParameters param;
    param.DriverType = driverType_;
    param.WindowId = hWnd_;

    device_ = irr::createDeviceEx(param);
    device_->setResizable(true);

    smgr_ = device_->getSceneManager();
    driver_ = device_->getVideoDriver();

    irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_DIRECT3D9;

    // create device
    if (device_ == 0)
        return false; // could not create selected driver.

    driver_ = device_->getVideoDriver();
    smgr_   = device_->getSceneManager();

    // add centre solar system
    centre_ = smgr_->addEmptySceneNode();
    if (centre_)
        centre_->setPosition(irr::core::vector3df(0, 0, 0));

    // add sun
    sun_ = smgr_->addSphereSceneNode(
        3.0f,   // radius
        100,    // no of polys
        centre_);

    if (sun_)
    {
        sun_->setPosition(irr::core::vector3df(0, 0, 0));
        sun_->setMaterialTexture(0, driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\fire.bmp"));
        sun_->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }

    // add earth orbit centre
    earth_orbit_centre_ = smgr_->addEmptySceneNode(centre_);
    if (earth_orbit_centre_)
        earth_orbit_centre_->setPosition(irr::core::vector3df(0, 0, 0));

    // add earth centre
    earth_centre_ = smgr_->addEmptySceneNode(earth_orbit_centre_);
    if (earth_centre_)
        earth_centre_->setPosition(irr::core::vector3df(earth_dist, 0, 0));

    // add earth
    earth_ = smgr_->addSphereSceneNode(
        earth_radius,    // radius
        100,
        earth_centre_);  // no of polys

    if (earth_)
    {
        earth_->setPosition(irr::core::vector3df(0, 0, 0));
        earth_->setMaterialTexture(0, driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\wall.bmp"));
        earth_->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    }

    // add moon centre
    moon_centre_ = smgr_->addEmptySceneNode(earth_centre_);
    if (moon_centre_)
        moon_centre_->setPosition(irr::core::vector3df(0, 0, 0));

    // add moon
    moon_ = smgr_->addSphereSceneNode(
        moon_radius,   // radius
        100,            // no of polys
        moon_centre_); 

    if (moon_)
    {
        moon_->setPosition(irr::core::vector3df(moon_dist, 0, 0));
        moon_->setMaterialTexture(0, driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\terrain-heightmap.bmp"));
        moon_->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    }

    // create light
    irr::scene::ISceneNode* light = smgr_->addLightSceneNode(0, irr::core::vector3df(0, 0, 0),
        irr::video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);

    // add camera
    switch (cameraView_)
    { 
    case EarthSurface:
        camera_ = smgr_->addCameraSceneNode(earth_centre_, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2000, 0, 0));
        camera_->bindTargetAndRotation(true);
        break;
    case Above:
        camera_ = smgr_->addCameraSceneNode(centre_, irr::core::vector3df(0, 100, 0), irr::core::vector3df(0, -100, 0));
        break;
    }

    initialised_ = true;
    return true;
}

void CSolarSystemScene::uninitialise()
{
    if (!initialised_) return;
    device_->closeDevice();
    device_->drop();
    initialised_ = false;
}

bool CSolarSystemScene::run(CTimer &timer)
{
    if (!initialised_) return true;

    if (device_->run())
    { 
        irr::u32 now = device_->getTimer()->getTime();

        irr::core::vector3df pos;
        float angle;

        // sun rotation
        //angle = timer.elapsed() * 360.0f / 40.0f;
        //sun_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        // earth orbit
        angle = timer.elapsed() * 360.0f / 365.25f;
        earth_orbit_centre_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        // rotate earth and camera in tandem
        angle = timer.elapsed() * 360.0f;
        earth_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        // move camera for earth surface view
        if (cameraView_ == EarthSurface)
            camera_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        // moon orbit, 28 days
        angle = timer.elapsed() * 360.0f / 28.0f;
        moon_centre_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        // rotate moon
        moon_->setRotation(irr::core::vector3df(0.0f, angle, 0.0f));

        driver_->beginScene(true, true, 0);
        smgr_->drawAll();
        driver_->endScene();
    }
    return true;
}

bool CSolarSystemScene::getInitialised()
{
    return initialised_;
}



