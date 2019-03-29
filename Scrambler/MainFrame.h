#pragma once

#include "wx/wx.h"
#include "wx/filepicker.h"

class MainFrame : public wxFrame
{
public:
	// ctor(s)
	MainFrame(const wxString& title, const wxString& file = wxEmptyString);

	void fileChanged(const wxString& path);
	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnEncryptDecrypt(wxCommandEvent& event);
	void OnFileSelect(wxFileDirPickerEvent& event);

private:
	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();

	wxBoxSizer* layout;

	wxMenu *fileMenu, *helpMenu;

	wxMenuBar* menuBar;

	wxFilePickerCtrl* filePicker;

	wxTextCtrl* password;

	wxButton* encryptDecrypt;

	wxCheckBox* deleteOriginal;
};

// IDs for the controls and the menu commands
enum
{
    // menu items
    Main_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Main_About = wxID_ABOUT,

	Main_EncryptDecrypt = wxID_EXECUTE,

	Main_File
};