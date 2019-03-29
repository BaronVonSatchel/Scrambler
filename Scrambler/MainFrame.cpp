#include "MainFrame.h"

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(Main_Quit, MainFrame::OnQuit)
	EVT_MENU(Main_About, MainFrame::OnAbout)
	EVT_BUTTON(Main_EncryptDecrypt, MainFrame::OnEncryptDecrypt)
	EVT_FILEPICKER_CHANGED(Main_File, MainFrame::OnFileSelect)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxString& file)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, { 600, 400 })
{
	// set the frame icon
	SetIcon(wxICON(sample));

#if wxUSE_MENUS
	// create a menu bar
	fileMenu = new wxMenu;
	fileMenu->Append(Main_Quit, "E&xit\tAlt-X", "Quit this program");

	// the "About" item should be in the help menu
	helpMenu = new wxMenu;
	helpMenu->Append(Main_About, "&About\tF1", "Show about dialog");

	// now append the freshly created menu to the menu bar...
	menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(helpMenu, "&Help");

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#else // !wxUSE_MENUS
	// If menus are not available add a button to access the about box
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* aboutBtn = new wxButton(this, wxID_ANY, "About...");
	aboutBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAbout, this);
	sizer->Add(aboutBtn, wxSizerFlags().Center());
#endif // wxUSE_MENUS/!wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(2);
	SetStatusText("Welcome to wxWidgets!", 1);
#endif // wxUSE_STATUSBAR
	layout = new wxBoxSizer(wxVERTICAL);

	filePicker = new wxFilePickerCtrl(this, Main_File, file, wxFileSelectorPromptStr, wxFileSelectorDefaultWildcardStr,
		wxDefaultPosition, wxSize(300, wxDefaultCoord));
	filePicker->GetTextCtrl()->SetHint("File to encrypt/decrypt");

	password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	password->SetHint("Password");

	layout->Add(filePicker, 0, wxGROW);
	layout->Add(password, 0, wxGROW);

	wxPanel* panel = new wxPanel(this);
	wxStaticBoxSizer* options = new wxStaticBoxSizer(wxVERTICAL, panel, "More Options");

	deleteOriginal = new wxCheckBox(options->GetStaticBox(), wxID_ANY, "Delete Original");
	options->Add(deleteOriginal);
	options->Add(new wxCheckBox(options->GetStaticBox(), wxID_ANY, "Option 2"));
	options->Add(new wxCheckBox(options->GetStaticBox(), wxID_ANY, "Option 3"));

	panel->SetSizerAndFit(options);
	layout->Add(panel, wxSizerFlags(1).Expand());

	encryptDecrypt = new wxButton(this, Main_EncryptDecrypt, "Select a file");
	layout->Add(encryptDecrypt, 0);

	SetSizerAndFit(layout);

	fileChanged(file);
}

// event handlers

void MainFrame::fileChanged(const wxString & path)
{
	if (path.IsEmpty()) {
		encryptDecrypt->SetLabel("Select a file");
		encryptDecrypt->Disable();
	}
	else {
		encryptDecrypt->Enable();
		if (path.EndsWith(".scrambled")) encryptDecrypt->SetLabel("Decrypt");
		else encryptDecrypt->SetLabel("Encrypt");
	}
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		"Welcome to %s!\n"
		"\n"
		"Running under %s.",
		SCRAMBLER_VERSION,
		wxGetOsDescription()
	),
		"About wxWidgets minimal sample",
		wxOK | wxICON_INFORMATION,
		this);
}

void MainFrame::OnEncryptDecrypt(wxCommandEvent & event)
{
	if (deleteOriginal->IsChecked()) {
		wxMessageDialog* confirm = new wxMessageDialog(this,
			"You have the \"Delete Original\" option enabled.\n"
			"If you forget your password, your file will be\n"
			"gone forever! Are you sure you wish to continue?",
			"Delete Original File?", wxCANCEL | wxOK | wxCANCEL_DEFAULT | wxICON_EXCLAMATION | wxCENTER);
		confirm->ShowModal();
	}
}

void MainFrame::OnFileSelect(wxFileDirPickerEvent& event)
{
	fileChanged(event.GetPath());
}
