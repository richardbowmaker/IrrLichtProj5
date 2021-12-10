
#include <irrlicht.h>
#include <Windows.h>

#include "General.h"

void CTimer::initialise(float scale)
{
    scale_ = scale;
    unsigned __int64 freq;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    timerFrequency_ = (1.0/freq);
    QueryPerformanceCounter((LARGE_INTEGER *)&startTime_);
}

void CTimer::update()
{
    unsigned __int64 time;
    QueryPerformanceCounter((LARGE_INTEGER *)&time);
    double tdms = ((time - startTime_) * timerFrequency_) * 1000.0;
    elapsed_ = static_cast<float>(tdms / scale_);
}

float CTimer::elapsed()
{
    return elapsed_;
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

