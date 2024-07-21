#include <wx/wx.h>
#include "main.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(main);

bool main::OnInit() 
{
	MainFrame* mainFrame = new MainFrame("C++ GUI");
	mainFrame->SetClientSize(WIDTH, HEIGHT);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}