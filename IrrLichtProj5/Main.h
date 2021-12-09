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

        CUserEventData(wxPanel* panel) 
        { 
            panel_ = panel; 
        } 
        wxPanel *panel_; 

        ~CUserEventData()
        {
            panel_ = 0;
        }

    }; 

    typedef std::unique_ptr<IScene> ScenePtrT;

    wxPanel *panel1_;
    wxPanel *panel2_;
    ScenePtrT scene1_;
    ScenePtrT scene2_;
    CUserEventData *userData1_;
    CUserEventData *userData2_;
 
    enum
    {
        ID_Hello = 1
    };

};


