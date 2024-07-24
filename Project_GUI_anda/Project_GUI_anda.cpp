

#include <wx/wx.h>
#include <wx/url.h>
#include <wx/listbook.h>
#include <wx/wrapsizer.h>
#include <iostream>
#include <CJsonObject.hpp>
#include <fstream>
#include <string>

int CountNonemptyStrings(wxString array[],int size);
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
    void OnQueryNetworkFirmware(wxCommandEvent& event);
    void OnDownloadFirmware(wxCommandEvent& event);
    void OnBurnFirmware(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
	void Ondownload_breath(wxCommandEvent& event);
	void Ondownload_height(wxCommandEvent& event);
	void Ondownload_human(wxCommandEvent& event);
	void QueryFirmwareVersion();
	void Sizer_network(wxWindow* myparent,wxString* radioBox_breathChoices);
	void Sizer_current();
	void Sizer_load();
    wxButton* querySerialFirmwareButton;
    wxButton* queryNetworkFirmwareAndDownloadButton;
    wxButton* burnFirmwareButton;

    wxPanel* Panel;
    wxMenu* FileMenu;
    wxMenuItem* helpMenu;
    wxMenuBar* FirmwareMenuBar;
    
	std::string versions_breath;
	std::string versions_height;
	std::string versions_human;
   


	wxListbook* m_listbook1;
	wxPanel* m_panel_network;
	wxStaticText* m_staticText_breath;
	wxButton* m_button_breath;
	wxRadioBox* m_radioBox_breath;
	wxStaticText* m_staticText_height;
	wxButton* m_button_height;
	wxRadioBox* m_radioBox_height;
	wxStaticText* m_staticText_human;
	wxButton* m_button_human;
	wxRadioBox* m_radioBox_human;
	wxButton* m_button2;
	wxButton* m_button4;
	wxPanel* m_panel_current;
	wxButton* m_button14;
	wxStaticText* m_staticText9;
	wxTextCtrl* m_textCtrl1;
	wxButton* m_button15;
	wxPanel* m_panel_load;
	wxChoice* m_choice1;
	wxComboBox* m_comboBox1;
	wxButton* m_button10;
	wxButton* m_button9;

	wxString m_radioBox_breathChoices[5] = { "默认版本" };
	wxString m_radioBox_heightChoices[5] = { "默认版本" };
	wxString m_radioBox_humanChoices[5] = { "默认版本" };
	
	
};



FirmwareGUI::FirmwareGUI(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_listbook1 = new wxListbook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT);
	QueryFirmwareVersion();
	m_panel_network = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	Sizer_network(m_panel_network,m_radioBox_breathChoices);

	

	wxWrapSizer* wSizer2;
	wSizer2 = new wxWrapSizer(wxHORIZONTAL, wxWRAPSIZER_DEFAULT_FLAGS);

	m_button2 = new wxButton(m_panel_network, wxID_ANY, _("查询"), wxDefaultPosition, wxDefaultSize, 0);
	wSizer2->Add(m_button2, 0, wxALL, 5);
	Connect(m_button2->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::Ondownload_breath));
	m_button4 = new wxButton(m_panel_network, wxID_ANY, _("取消"), wxDefaultPosition, wxDefaultSize, 0);
	wSizer2->Add(m_button4, 0, wxALL, 5);



	m_panel_network->SetSizer(wSizer2);
	m_panel_network->Layout();
	wSizer2->Fit(m_panel_network);


	m_listbook1->AddPage(m_panel_network, _("查询网络固件版本"), true);

	m_panel_current = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	Sizer_current();
	m_listbook1->AddPage(m_panel_current, _("查询当前固件版本"), false);
	
	m_panel_load = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	Sizer_load();
	m_listbook1->AddPage(m_panel_load, _("烧录"), false);

#ifdef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbook1ListView = m_listbook1->GetListView();
	long m_listbook1Flags = m_listbook1ListView->GetWindowStyleFlag();
	if (m_listbook1Flags & wxLC_SMALL_ICON)
	{
		m_listbook1Flags = (m_listbook1Flags & ~wxLC_SMALL_ICON) | wxLC_ICON;
	}
	m_listbook1ListView->SetWindowStyleFlag(m_listbook1Flags);
#endif

	bSizer1->Add(m_listbook1, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);



    /*Panel = new wxPanel(this, wxID_ANY);
    

    querySerialFirmwareButton = new wxButton(Panel, wxID_ANY, "查询串口固件", wxPoint(50, 50));
    queryNetworkFirmwareAndDownloadButton = new wxButton(Panel, wxID_ANY, "查询网络固件与下载", wxPoint(50, 100));
    burnFirmwareButton = new wxButton(Panel, wxID_ANY, "烧录固件", wxPoint(50, 150));

    Connect(querySerialFirmwareButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnQuerySerialFirmware));
    Connect(queryNetworkFirmwareAndDownloadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnQueryNetworkFirmware));
    Connect(burnFirmwareButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::OnBurnFirmware));
    

    FileMenu = new wxMenu;
    
    helpMenu = new wxMenuItem(FileMenu,wxID_MenuHelp,"&Help","Open Help!");
    FileMenu->Append(helpMenu);

    FirmwareMenuBar = new wxMenuBar;
    FirmwareMenuBar->Append(FileMenu, "File");


   Connect(helpMenu->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FirmwareGUI::OnHelp));

 
    SetMenuBar(FirmwareMenuBar);
    CreateStatusBar();*/

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

void FirmwareGUI::OnQueryNetworkFirmware(wxCommandEvent& event)
{
    // 这里实现查询网络固件版本和下载的代码
    wxMessageBox(wxT("this is 查询网络固件版本与下载!"), wxT("查询网络固件版本与下载"), wxOK | wxICON_INFORMATION, this);
    QueryFirmwareVersion();

	


	
    

}
void FirmwareGUI::Ondownload_breath(wxCommandEvent& event)
{    //m_radioBox_breath->FindString("1.0.bin")   如果选项有则为真
	if (m_radioBox_breath->GetSelection() == 2 || m_radioBox_breath->GetSelection() == 3)
	{
		wxURL url("http://....");
		if (url.GetError() != wxURL_NOERR)
		{
			wxLogError("can not access");
			return;
		}
		wxInputStream* InStream = url.GetInputStream();
		if (!InStream)
		{
			wxLogError("failed to get input stream!");
			return;
		}
		
		//接受缓存
		wxString wxReceiData;
		char Buffer[1024];
		while (! InStream->Read(Buffer, sizeof(Buffer)))
		{
		    wxReceiData += wxString(Buffer, InStream->LastRead());
		}
		
		
		

		//.....

	}
	m_radioBox_breathChoices[2] =  "99";
	
	
	//m_radioBox_human->Show(2, false);
	
	

	wxDialog* ChoiseDialog = new wxDialog(NULL, wxID_ANY, "Choises",wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE);
	wxPanel* ChoisePanel = new wxPanel(ChoiseDialog);
	Sizer_network(ChoiseDialog, m_radioBox_breathChoices);
	//dialog退出判断（showModal（）：自动调用destroy（））
	if (ChoiseDialog->ShowModal() == wxID_CANCEL)
	{
		wxMessageBox(" Succeful","Firmware Download", wxOK | wxICON_INFORMATION,this);
	}
	
	
	//ChoiseDialog->Destroy();

    

}

void FirmwareGUI::Ondownload_height(wxCommandEvent& event)
{
	;
}
void FirmwareGUI::Ondownload_human(wxCommandEvent& event)
{
	;
}
void FirmwareGUI::OnBurnFirmware(wxCommandEvent& event)
{
    // 这里实现烧录固件的代码
    wxMessageBox(wxT("this is 烧录固件!"), wxT("烧录固件"), wxOK | wxICON_INFORMATION, this);
    wxLogError("can not access");
}
    



void FirmwareGUI::QueryFirmwareVersion()
{
    //wxURL url("http://....");
    //if (url.GetError() != wxURL_NOERR)
    //{
    //    wxLogError("can not access");
    //    return;
    //}
    //wxInputStream* InStream = url.GetInputStream();
    //if (!InStream)
    //{
    //    wxLogError("failed to get input stream!");
    //    return;
    //}
    ////接受缓存
    wxString wxReceiData;
    //char Buffer[1024];
    //while (! InStream->Read(Buffer, sizeof(Buffer)))
    //{
    //    wxReceiData += wxString(Buffer, InStream->LastRead());
    //}


    std::ifstream file("abc.txt");
    if (!file.is_open())
    {
        wxLogError("fail open file");
        return;
    }
    char c;
    std::string filedata;
    while (file.get(c)) {
        filedata += c;
    }
    file.close();
    std::string str = "praise";
    neb::CJsonObject Ojson;
    
	if (Ojson.Parse(filedata))
	{
		/*
			{
				"Top": {
							"breath": ["1.0.bin"],
							"height": ["1.0.bin","2.0.bin"],
							"human"	: ["1.0.bin","2.0.bin","3.0.bin"]
						}
			}
		*/
		str = Ojson.ToString();
		wxMessageBox(str);
		int num_out = 3;
		std::string funcName[3] = { "breath","height","human"};
		
		for (int i = 0;i < num_out; i++) 
		{

			int num_in = Ojson["Top"][funcName[i]].GetArraySize();
			for (int j = 0; j < num_in ;j++)
			{
				std::string strtmp = Ojson["Top"][funcName[i]](j);
				//wxMessageBox(strtmp);
				switch (i)
				{
				case 0:	m_radioBox_breathChoices[j+1] = strtmp; //避免覆盖默认值
					break;
				case 1: m_radioBox_heightChoices[j+1] = strtmp;
					break;
				case 2:	m_radioBox_humanChoices[j+1] = strtmp;
					break;
				default:
					break;
				}
			}
			//Ojson["Top"].Get("breath", versions_breath);
			//wxMessageBox(versions_breath);
		}
    }
    else
    {
        wxMessageBox("failed to parse Json data!");
    }
    
}

int CountNonemptyStrings(wxString array[], int size)
{
	int count = 0;
	for (int i = 0; i < size;i++)
	{
		if (!array[i].empty())
			count++;
	}
	return count;
}

void FirmwareGUI::Sizer_network(wxWindow* myparent,wxString* radioBox_breathChoices)
{
	
	wxBoxSizer* bSizer_Top;
	bSizer_Top = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* wxStaticBoxSizer_Breath;
	wxStaticBoxSizer_Breath = new wxStaticBoxSizer(new wxStaticBox(myparent, wxID_ANY, _("Breath")), wxHORIZONTAL);

	wxFlexGridSizer* fgSizer_breath;
	fgSizer_breath = new wxFlexGridSizer(0, 1, 0, 0);
	fgSizer_breath->SetFlexibleDirection(wxBOTH);
	fgSizer_breath->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_breath = new wxStaticText(wxStaticBoxSizer_Breath->GetStaticBox(), wxID_ANY, _("Version:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_breath->Wrap(-1);
	fgSizer_breath->Add(m_staticText_breath, 0, wxALL, 5);

	m_button_breath = new wxButton(wxStaticBoxSizer_Breath->GetStaticBox(), wxID_ANY, _("获取"), wxDefaultPosition, wxDefaultSize, 0);
	Connect(m_button_breath->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::Ondownload_breath));

	fgSizer_breath->Add(m_button_breath, 0, wxALL, 5);
	wxStaticBoxSizer_Breath->Add(fgSizer_breath, 1, wxEXPAND, 5);

	wxFlexGridSizer* fgSizer_breath_bin;
	fgSizer_breath_bin = new wxFlexGridSizer(0, 4, 0, 0);
	fgSizer_breath_bin->SetFlexibleDirection(wxBOTH);
	fgSizer_breath_bin->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	

	//int m_radioBox_breathNChoices = sizeof(m_radioBox_breathChoices) / sizeof(wxString);
	int m_radioBox_breathNChoices = CountNonemptyStrings(radioBox_breathChoices, 5);
	m_radioBox_breath = new wxRadioBox(wxStaticBoxSizer_Breath->GetStaticBox(), wxID_ANY, _("Bin"), wxDefaultPosition, wxDefaultSize, m_radioBox_breathNChoices, m_radioBox_breathChoices, 1, wxRA_SPECIFY_ROWS);
	m_radioBox_breath->SetSelection(0);

	fgSizer_breath_bin->Add(m_radioBox_breath, 0, wxALL, 5);


	wxStaticBoxSizer_Breath->Add(fgSizer_breath_bin, 1, wxEXPAND, 5);


	wxStaticBoxSizer_Breath->Add(0, 0, 1, wxEXPAND, 5);


	bSizer_Top->Add(wxStaticBoxSizer_Breath, 1, wxEXPAND, 5);

	wxStaticBoxSizer* wxStaticBoxSizer_Height;
	wxStaticBoxSizer_Height = new wxStaticBoxSizer(new wxStaticBox(myparent, wxID_ANY, _("Height")), wxHORIZONTAL);

	wxFlexGridSizer* fgSizer_height;
	fgSizer_height = new wxFlexGridSizer(0, 1, 0, 0);
	fgSizer_height->SetFlexibleDirection(wxBOTH);
	fgSizer_height->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_height = new wxStaticText(wxStaticBoxSizer_Height->GetStaticBox(), wxID_ANY, _("Version:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_height->Wrap(-1);
	fgSizer_height->Add(m_staticText_height, 0, wxALL, 5);

	m_button_height = new wxButton(wxStaticBoxSizer_Height->GetStaticBox(), wxID_ANY, _("获取"), wxDefaultPosition, wxDefaultSize, 0);
	Connect(m_button_height->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::Ondownload_height));

	fgSizer_height->Add(m_button_height, 0, wxALL, 5);
	wxStaticBoxSizer_Height->Add(fgSizer_height, 1, wxEXPAND, 5);

	wxFlexGridSizer* fgSizer_height_bin;
	fgSizer_height_bin = new wxFlexGridSizer(0, 4, 0, 0);
	fgSizer_height_bin->SetFlexibleDirection(wxBOTH);
	fgSizer_height_bin->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);


	//int m_radioBox_heightNChoices = sizeof(m_radioBox_heightChoices) / sizeof(wxString);

	int m_radioBox_heightNChoices = CountNonemptyStrings(m_radioBox_heightChoices, 5);
	m_radioBox_height = new wxRadioBox(wxStaticBoxSizer_Height->GetStaticBox(), wxID_ANY, _("Bin"), wxDefaultPosition, wxDefaultSize, m_radioBox_heightNChoices, m_radioBox_heightChoices, 1, wxRA_SPECIFY_ROWS);
	m_radioBox_height->SetSelection(1);
	fgSizer_height_bin->Add(m_radioBox_height, 0, wxALL, 5);


	wxStaticBoxSizer_Height->Add(fgSizer_height_bin, 1, wxEXPAND, 5);


	wxStaticBoxSizer_Height->Add(0, 0, 1, wxEXPAND, 5);


	bSizer_Top->Add(wxStaticBoxSizer_Height, 1, wxEXPAND, 5);

	wxStaticBoxSizer* wxStaticBoxSizer_Human;
	wxStaticBoxSizer_Human = new wxStaticBoxSizer(new wxStaticBox(myparent, wxID_ANY, _("Human")), wxHORIZONTAL);

	wxFlexGridSizer* fgSizer_human;
	fgSizer_human = new wxFlexGridSizer(0, 1, 0, 0);
	fgSizer_human->SetFlexibleDirection(wxBOTH);
	fgSizer_human->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText_human = new wxStaticText(wxStaticBoxSizer_Human->GetStaticBox(), wxID_ANY, _("Version:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_human->Wrap(-1);
	fgSizer_human->Add(m_staticText_human, 0, wxALL, 5);

	m_button_human = new wxButton(wxStaticBoxSizer_Human->GetStaticBox(), wxID_ANY, _("获取"), wxDefaultPosition, wxDefaultSize, 0);
	Connect(m_button_human->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FirmwareGUI::Ondownload_human));

	fgSizer_human->Add(m_button_human, 0, wxALL, 5);
	wxStaticBoxSizer_Human->Add(fgSizer_human, 1, wxEXPAND, 5);

	wxFlexGridSizer* fgSizer_human_bin;
	fgSizer_human_bin = new wxFlexGridSizer(0, 4, 0, 0);
	fgSizer_human_bin->SetFlexibleDirection(wxBOTH);
	fgSizer_human_bin->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);


	//int m_radioBox_humanNChoices = sizeof(m_radioBox_humanChoices) / sizeof(wxString);
	int  m_radioBox_humanNChoices = CountNonemptyStrings(m_radioBox_humanChoices, 5);
	m_radioBox_human = new wxRadioBox(wxStaticBoxSizer_Human->GetStaticBox(), wxID_ANY, _("Bin"), wxDefaultPosition, wxDefaultSize, m_radioBox_humanNChoices, m_radioBox_humanChoices, 1, wxRA_SPECIFY_ROWS);
	m_radioBox_human->SetSelection(1);
	fgSizer_human_bin->Add(m_radioBox_human, 0, wxALL, 5);


	wxStaticBoxSizer_Human->Add(fgSizer_human_bin, 1, wxEXPAND, 5);


	wxStaticBoxSizer_Human->Add(0, 0, 1, wxEXPAND, 5);


	bSizer_Top->Add(wxStaticBoxSizer_Human, 1, wxEXPAND, 5);

	wxWrapSizer* wSizer2;
	wSizer2 = new wxWrapSizer(wxHORIZONTAL, wxWRAPSIZER_DEFAULT_FLAGS);

	m_button2 = new wxButton(myparent, wxID_ANY, _("查询"), wxDefaultPosition, wxDefaultSize, 0);
	wSizer2->Add(m_button2, 0, wxALL, 5);

	m_button4 = new wxButton(myparent, wxID_ANY, _("取消"), wxDefaultPosition, wxDefaultSize, 0);
	wSizer2->Add(m_button4, 0, wxALL, 5);


	bSizer_Top->Add(wSizer2, 1, wxEXPAND, 5);


	myparent->SetSizer(bSizer_Top);
	myparent->Layout();
	bSizer_Top->Fit(myparent);
	
	
	
}
void FirmwareGUI::Sizer_current()
{

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxHORIZONTAL);

	m_button14 = new wxButton(m_panel_current, wxID_ANY, _("查询"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer20->Add(m_button14, 0, wxALL, 5);

	m_staticText9 = new wxStaticText(m_panel_current, wxID_ANY, _("当前版本："), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText9->Wrap(-1);
	bSizer20->Add(m_staticText9, 0, wxALL, 5);
	m_textCtrl1 = new wxTextCtrl(m_panel_current, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer20->Add(m_textCtrl1, 0, wxALL, 5);

	m_button15 = new wxButton(m_panel_current, wxID_ANY, _("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer20->Add(m_button15, 0, wxALL, 5);


	bSizer19->Add(bSizer20, 1, wxEXPAND, 5);


	m_panel_current->SetSizer(bSizer19);
	m_panel_current->Layout();
	bSizer19->Fit(m_panel_current);
	
}
void FirmwareGUI::Sizer_load()
{
	
	wxBoxSizer* bSizer_load;
	bSizer_load = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice(m_panel_load, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0);
	m_choice1->SetSelection(0);
	bSizer12->Add(m_choice1, 0, wxALL, 5);

	m_comboBox1 = new wxComboBox(m_panel_load, wxID_ANY, _("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	bSizer12->Add(m_comboBox1, 0, wxALL, 5);

	m_button10 = new wxButton(m_panel_load, wxID_ANY, _("borwn"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(m_button10, 0, wxALL, 5);


	bSizer_load->Add(bSizer12, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	m_button9 = new wxButton(m_panel_load, wxID_ANY, _("一键烧录"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(m_button9, 0, wxALL, 5);


	bSizer_load->Add(bSizer13, 1, wxEXPAND, 5);


	m_panel_load->SetSizer(bSizer_load);
	m_panel_load->Layout();
	bSizer_load->Fit(m_panel_load);
	
}
//std::string* filetestdemo(const char* filename)
//{
//    std::ifstream file(filename);
//    if (!file.is_open())
//    {
//        wxLogError("fail open file");
//        return NULL;
//    }
//    char c;
//    std::string* filedata = new(std::string);
//    while (file.get(c)) {
//        filedata += c;
//    }
//    file.close();
//}
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