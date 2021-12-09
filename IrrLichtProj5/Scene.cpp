
#include <irrlicht.h>
#include <Windows.h>

#include "General.h"
#include "Scene.h"

CScene::CScene() : initialised_(false), driverType_(irr::video::EDT_DIRECT3D9), videodata_(0)
{

}

CScene::~CScene()
{

}

bool CScene::initialise(HWND hwnd)
{
    hWnd_ = hwnd;

    irr::SIrrlichtCreationParameters param;
    param.DriverType = driverType_;
    param.WindowId = hWnd_;

    device_ = irr::createDeviceEx(param);
    device_->setResizable(true);

    smgr_ = device_->getSceneManager();
    driver_ = device_->getVideoDriver();

    HDC HDc=GetDC(hWnd_);
    PIXELFORMATDESCRIPTOR pfd={0};
    pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
    int pf = GetPixelFormat(HDc);
    DescribePixelFormat(HDc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    pfd.dwFlags |= PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.cDepthBits=16;
    pf = ChoosePixelFormat(HDc, &pfd);
    SetPixelFormat(HDc, pf, &pfd);
    videodata_.OpenGLWin32.HDc = HDc;
    videodata_.OpenGLWin32.HRc=wglCreateContext(HDc);
    wglShareLists((HGLRC)driver_->getExposedVideoData().OpenGLWin32.HRc, (HGLRC)videodata_.OpenGLWin32.HRc);

    irr::scene::ICameraSceneNode* cam = smgr_->addCameraSceneNode();
    cam->setTarget(irr::core::vector3df(0,0,0));

    irr::scene::ISceneNodeAnimator* anim =
        smgr_->createFlyCircleAnimator(irr::core::vector3df(0,15,0), 30.0f);
    cam->addAnimator(anim);
    anim->drop();

    irr::scene::ISceneNode* cube = smgr_->addCubeSceneNode(20);

    cube->setMaterialTexture(0, driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\wall.bmp"));
    cube->setMaterialTexture(1, driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\water.jpg"));
    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false );
    cube->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER );

    smgr_->addSkyBoxSceneNode(
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_up.jpg"),
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_dn.jpg"),
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_lf.jpg"),
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_rt.jpg"),
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_ft.jpg"),
        driver_->getTexture("D:\\irrlicht\\irrlicht-1.8.5\\media\\irrlicht2_bk.jpg"));

    initialised_ = true;
    return true;
}

void CScene::uninitialise()
{
    if (!initialised_) return;
    device_->closeDevice();
    device_->drop();
}

bool CScene::run()
{
    if (!initialised_) return true;
    if (device_->run())
    { 
        driver_->beginScene(true, true, 0, videodata_);
        smgr_->drawAll();
        driver_->endScene();
    }
    return true;
}
