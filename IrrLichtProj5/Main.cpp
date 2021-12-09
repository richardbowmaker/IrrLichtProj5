// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wx.h>
//#include <irrlicht.h>

#include "Main.h"

using namespace irr;

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );

    wxBoxSizer *topsizer = new wxBoxSizer( wxVERTICAL );

    panel1_ = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 400));
    panel2_ = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 300));

    topsizer->Add(
        panel1_,
        1,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        10 );
    
    topsizer->Add(
        panel2_,
        1,            // make vertically stretchable
        wxEXPAND |    // make horizontally stretchable
        wxALL,        //   and make border all around
        10 );
   
    SetSizerAndFit(topsizer); // use the sizer for layout and size window
                              // accordingly and prevent it from being resized
                              // to smaller size

    Bind(wxEVT_IDLE, &MyFrame::OnIdle, this);
    Bind(wxEVT_MENU, &MyFrame::OnMenu, this);

    userData1_ = new CUserEventData(panel1_, &scene1_);
    userData2_ = new CUserEventData(panel2_, &scene2_);

    panel1_->Bind(wxEVT_SIZE, &MyFrame::OnSize, this, wxID_ANY, wxID_ANY, userData1_);
    panel2_->Bind(wxEVT_SIZE, &MyFrame::OnSize, this, wxID_ANY, wxID_ANY, userData2_);

    scene1_.initialise(panel1_->GetHWND());
    scene2_.initialise(panel2_->GetHWND());
}

void MyFrame::OnSize(wxSizeEvent& event)
{

    CUserEventData *data = (CUserEventData*)event.GetEventUserData();
    int width, height;

    data->panel_->GetClientSize(&width, &height);


    int s = std::min(width, height);

    data->panel_->SetClientSize(s, s);


    //::PostMessage(data->panel_->GetHWND(), WM_SIZE, 0, (DWORD)(s << 16 | s));

    //data->scene_->setSize(s, s);
    event.Skip();

}

void MyFrame::OnIdle(wxIdleEvent& event)
{
    bool b1 = scene1_.run();
    bool b2 = scene2_.run();

    if (b1 || b2)
        event.RequestMore(true);
}

void MyFrame::OnMenu(wxCommandEvent& event)
{
    switch (event.GetId())
    { 
    case wxID_EXIT:
        OnExit(event);  break;
    case wxID_ABOUT:
        OnAbout(event);  break;
    case ID_Hello:
        OnHello(event);  break;
    }
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    scene1_.uninitialise();
    scene2_.uninitialise();
    delete userData1_;
    delete userData2_;
    Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}