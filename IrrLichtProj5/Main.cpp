// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".


#include <irrlicht.h>
#include <memory>
#include <wx/wx.h>

#include "Main.h"
#include "Scene.h"
#include "SolarSystemScene.h"

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

    wxBoxSizer *topsizer = new wxBoxSizer( wxHORIZONTAL );

    panel1_ = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));
    panel2_ = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 100));

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

    Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
    Bind(wxEVT_IDLE, &MyFrame::OnIdle, this);
    Bind(wxEVT_MENU, &MyFrame::OnMenu, this);

    scene1_ = std::make_unique<CSolarSystemScene>(CSolarSystemScene::EarthSurface);
    scene2_ = std::make_unique<CSolarSystemScene>(CSolarSystemScene::Above);

    userData1_ = new CUserEventData(panel1_, scene1_.get());
    userData2_ = new CUserEventData(panel2_, scene2_.get());

    panel1_->Bind(wxEVT_SIZE, &MyFrame::OnSize, this, wxID_ANY, wxID_ANY, static_cast<wxObject*>(userData1_));
    panel2_->Bind(wxEVT_SIZE, &MyFrame::OnSize, this, wxID_ANY, wxID_ANY, static_cast<wxObject*>(userData2_));

    scene1_->initialise(panel1_->GetHWND());
    scene2_->initialise(panel2_->GetHWND());

    timer_.initialise(2500.0f);
}

void MyFrame::OnSize(wxSizeEvent& event)
{
    CUserEventData *data = static_cast<CUserEventData*>(event.GetEventUserData());

    // keep aspect ratio 1:1
    int width, height;
    data->panel_->GetClientSize(&width, &height);
    int s = std::min(width, height);
    if (data->size_ != s)
    {
        data->size_ = s;
        data->doResize_ = true;
    }
    event.Skip();
}

void MyFrame::OnIdle(wxIdleEvent& event)
{
    // if the parent window has resized then the graphics device needs to be restarted to reflact
    // the new screen resolution
    auto resize = [](CUserEventData &data) 
    {
        if (data.doResize_)
        {
            data.doResize_ = false;
            data.scene_->uninitialise();
            data.panel_->SetClientSize(data.size_, data.size_);
            data.scene_->initialise(data.panel_->GetHWND());
        }
    };

    resize(*userData1_);
    resize(*userData2_);

    timer_.update();
    bool b1 = scene1_->run(timer_);
    bool b2 = scene2_->run(timer_);

    if (b1 || b2)
        event.RequestMore(true);
    else
        this->Close();
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
    Close(true);
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

void MyFrame::OnClose(wxCloseEvent& event)
{
    scene1_->uninitialise();
    scene2_->uninitialise();
    event.Skip();
}