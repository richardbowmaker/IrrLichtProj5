#pragma once

#include <wx/wx.h>
#include <irrlicht.h>

#include "Scene.h"

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

        CUserEventData(wxPanel* panel, CScene* scene)
        {
            panel_ = panel;
            scene_ = scene;
        }

        wxPanel *panel_;
        CScene* scene_;
    };

    wxPanel *panel1_;
    wxPanel *panel2_;
    CScene scene1_;
    CScene scene2_;
    CUserEventData *userData1_;
    CUserEventData *userData2_;

    enum
    {
        ID_Hello = 1
    };

};


