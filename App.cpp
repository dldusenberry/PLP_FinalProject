#include "App.h"
#include "VersionOne.h"
#include <wx/wx.h> 

wxIMPLEMENT_APP(App);
/*
bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("C++ GUI");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
*/
bool App::OnInit() {
	VersionOne* versionOne = new VersionOne("C++ GUI");
	versionOne->SetClientSize(800, 600);
	versionOne->Center();
	versionOne->Show(); 
	return true;
}