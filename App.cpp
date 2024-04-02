#include "App.h"
#include "VersionOne.h"
#include <wx/wx.h> 

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	VersionOne* versionOne = new VersionOne("Spin the Wheel v1.1");
	versionOne->SetClientSize(1000, 600);
	versionOne->Center();
	versionOne->Show(); 
	return true;
}