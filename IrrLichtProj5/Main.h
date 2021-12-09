#pragma once

#include <wx/wx.h>
#include <irrlicht.h>

//#include <memory>

// #include "Scene.h"
// #include "SolarSystemScene.h"

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

    class CUserEventData : public wxObject 
    { 
    public: 

        CUserEventData(wxPanel* panel) 
        { 
            panel_ = panel; 
        } 
        wxPanel *panel_; 
    }; 

 //   typedef std::unique_ptr<IScene> ScenePtrT;
 //   typedef std::unique_ptr<CUserEventData> CUserEventDataPtrT;

    wxPanel *panel1_;
    wxPanel *panel2_;
    //ScenePtrT scene1_;
    //ScenePtrT scene2_;
    //CUserEventDataPtrT userData1_;
    //CUserEventDataPtrT userData2_;
 
    enum
    {
        ID_Hello = 1
    };

};


