
#include <irrlicht.h>
#include <Windows.h>

#include "General.h"


CTimer::CTimer(float scale)
{
    // ratio of ms to desired interval
    // e.g. if 1 day  = 1 sec then scale = 1000
    //      if 10 day = 1 sec then scale = 100
    scale_ = static_cast<double>(scale);
    reset();
}

void CTimer::reset()
{
    unsigned __int64 freq;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    timerFrequency_ = (1.0/freq);
    QueryPerformanceCounter((LARGE_INTEGER *)&startTime_);
}

float CTimer::elapsed()
{
    unsigned __int64 time;
    QueryPerformanceCounter((LARGE_INTEGER *)&time);
    double tdms = ((time - startTime_) * timerFrequency_) * 1000.0;
    return static_cast<float>(tdms / scale_);
}

EventReceiver::EventReceiver()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

// This is the one method that we have to implement
bool EventReceiver::OnEvent(const irr::SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}

// This is used to check whether a key is being held down
bool EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

