#pragma once

#include <irrlicht.h>
#include <memory>
#include <wx/wx.h>

#include "General.h"

class MyFrame: public wxFrame
{
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnMenu(wxCommandEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnClose(wxCloseEvent& event);

    class CUserEventData : public wxObject 
    { 
    public: 

        CUserEventData(wxPanel *panel, IScene *scene) 
        { 
            panel_ = panel; 
            scene_ = scene; 
            size_  = 0;
            doResize_ = false;
        }

        wxPanel *panel_; 
        IScene* scene_; 
        int size_;
        bool doResize_;
    }; 
 
    typedef std::unique_ptr<IScene> ScenePtrT;

    wxPanel *panel1_;
    wxPanel *panel2_;
    ScenePtrT scene1_;
    ScenePtrT scene2_;
    CUserEventData *userData1_;
    CUserEventData *userData2_;
    CTimer timer_;

    enum
    {
        ID_Hello = 1
    };

};


