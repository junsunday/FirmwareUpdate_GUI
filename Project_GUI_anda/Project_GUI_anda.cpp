#include <wx/wx.h>
#include <iostream>


enum
{
    wxID_MenuFile = wxID_HIGHEST + 1,
    wxID_MenuHelp,
    wxID_MenuAbout

};

class FirmwareGUI : public wxFrame
{
public:
    FirmwareGUI(const wxString& title);

   
private:
    void OnQuerySerialFirmware(wxCommandEvent& event);
    void OnQueryNetworkFirmwareAndDownload(wxCommandEvent& event);
    void OnBurnFirmware(wxCommandEvent& event);
   
    void OnHelp(wxCommandEvent& event);
   

    wxButton* querySerialFirmwareButton;
    wxButton* queryNetworkFirmwareAndDownloadButton;
    wxButton* burnFirmwareButton;

    wxPanel* Panel;
    wxMenu* FileMenu;
    wxMenuItem* helpMenu;
    wxMenuBar* FirmwareMenuBar;
    
};

FirmwareGUI::FirmwareGUI(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{
    Panel = new wxPanel(this, wxID_ANY);


    querySerialFirmwareButton = new wxButton(Panel, wxID_ANY, "查询串口固件", wxPoint(50, 50));
    queryNetworkFirmwareAndDownloadButton = new wxButton(Panel, wxID_ANY, "查询网络固件与下载", wxPoint(50, 100));
    burnFirmwareButton = new wxButton(Panel, wxID_ANY, "烧录固件", wxPoint(50, 150));

    Connect(querySerialFirmwareButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnQuerySerialFirmware));
    Connect(queryNetworkFirmwareAndDownloadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnQueryNetworkFirmwareAndDownload));
    Connect(burnFirmwareButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnBurnFirmware));
    

    FileMenu = new wxMenu;
    
    helpMenu = new wxMenuItem(FileMenu,wxID_MenuHelp,"&Help","Open Help!");
    FileMenu->Append(helpMenu);

    FirmwareMenuBar = new wxMenuBar;
    FirmwareMenuBar->Append(FileMenu, "File");


   Connect(helpMenu->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FirmwareGUI::OnHelp));

 
    SetMenuBar(FirmwareMenuBar);
    CreateStatusBar();

}

void FirmwareGUI::OnHelp(wxCommandEvent& event)
{
    wxMessageBox("this is Help!", "Help", wxOK | wxICON_INFORMATION,this);
}
void FirmwareGUI::OnQuerySerialFirmware(wxCommandEvent& event)
{
    // 这里实现查询串口固件版本的代码
    wxMessageBox(wxT("this is 查询串口固件版本!"), wxT("查询串口固件"), wxOK | wxICON_INFORMATION, this);
}

void FirmwareGUI::OnQueryNetworkFirmwareAndDownload(wxCommandEvent& event)
{
    // 这里实现查询网络固件版本和下载的代码
    wxMessageBox(wxT("this is 查询网络固件版本与下载!"), wxT("查询网络固件版本与下载"), wxOK | wxICON_INFORMATION, this);

}

void FirmwareGUI::OnBurnFirmware(wxCommandEvent& event)
{
    // 这里实现烧录固件的代码
    wxMessageBox(wxT("this is 烧录固件!"), wxT("烧录固件"), wxOK | wxICON_INFORMATION, this);

}

class MyApp : public wxApp
{
public:
    bool OnInit()
    {
        FirmwareGUI* frame = new FirmwareGUI("固件管理工具");
        frame->Show(true);
        return true;
    }
};



wxIMPLEMENT_APP(MyApp);