
#pragma once

class CTimer;

class IScene
{
public:

    virtual bool initialise(HWND hwnd) = 0;
    virtual void uninitialise() = 0;
    virtual bool run(CTimer &timer) = 0;
    virtual bool getInitialised() = 0;
};

class CTimer
{
public:

    void initialise(float scale);
    void update();
    float elapsed();

private:

    double              timerFrequency_;
    unsigned __int64    startTime_;
    double              scale_;
    float               elapsed_;
};

class EventReceiver : public irr::IEventReceiver
{
public:

    EventReceiver();
    virtual ~EventReceiver() {};

    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event);

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

private:

    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};
