#include "Scrambler.h"
#include "MainFrame.h"


// 'Main program' equivalent: the program execution "starts" here
bool Scrambler::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    if ( !wxApp::OnInit() )
        return false;

    // create the main application window
    MainFrame *frame = new MainFrame(SCRAMBLER_VERSION, argc > 1 ? argv[1] : wxEmptyString);

    // and show it (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}

void Scrambler::OnInitCmdLine(wxCmdLineParser& parser)
{

	parser.AddParam("File to (un)scramble", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL);
}

bool Scrambler::OnCmdLineParsed(wxCmdLineParser& parser)
{

	// to get at your unnamed parameters use
	wxArrayString files;
	for (unsigned i = 0; i < parser.GetParamCount(); i++)
	{
		files.Add(parser.GetParam(i));
	}

	// and other command line parameters

	// then do what you need with them.

	return true;
}