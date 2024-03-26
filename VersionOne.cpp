#include "VersionOne.h"
#include <wx/wx.h> 


VersionOne::VersionOne(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);

	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(300, 275), wxSize(200, 50)); // 
	wxSlider* slider = new wxSlider(panel, wxID_ANY, 0, 0, 100, wxPoint(300, 200), wxSize(200, -1), wxSL_VALUE_LABEL); // int params: initial value, a minimum value, a maximum value, Style: displays slider's current value
	wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 375), wxSize(200, -1));

	this->Bind(wxEVT_CLOSE_WINDOW, &VersionOne::OnClose, this);
	button->Bind(wxEVT_BUTTON, &VersionOne::OnButtonClicked, this); // can call on panel, VersionOne bc inheritance
	slider->Bind(wxEVT_SLIDER, &VersionOne::OnSliderChanged, this);
	text->Bind(wxEVT_TEXT, &VersionOne::OnTextChanged, this);

	panel->Bind(wxEVT_MOTION, &VersionOne::OnMouseEvent, this);
	panel->Bind(wxEVT_KEY_DOWN, &VersionOne::OnKeyEvent, this);

	//button->Unbind(wxEVT_BUTTON, &VersionOne::OnButtonClicked, this);


	wxStatusBar* statusBar = CreateStatusBar();
	statusBar->SetDoubleBuffered(true);

}

void VersionOne::OnMouseEvent(wxMouseEvent& event) {
	wxPoint mousePos = event.GetPosition();
	wxString message = wxString::Format("Mouse Event Detected (x=%d y=%d)", mousePos.x, mousePos.y);
	wxLogStatus(message);

}
void VersionOne::OnKeyEvent(wxKeyEvent& event) {
	wxChar keyChar = event.GetUnicodeKey();

	if (keyChar == WXK_NONE) {
		int keyCode = event.GetKeyCode();
		wxLogStatus("Key Event %d", keyCode);
	}
	else {
		wxLogStatus("Key Event %c", keyChar);
	}

}

void VersionOne::OnClose(wxCloseEvent& event) {
	wxLogStatus("GOODBYE!");
	event.Skip();
}

void VersionOne::OnButtonClicked(wxCommandEvent& event) {
	wxLogStatus("Button Clicked");
	wxLogMessage("Button Clicked");
}

void VersionOne::OnSliderChanged(wxCommandEvent& event) {
	wxString str = wxString::Format("Slider Value: %d", event.GetInt());
	wxLogStatus(str);
}

void VersionOne::OnTextChanged(wxCommandEvent& event) {
	//wxString str = wxString::Format("Text: %s", event.GetString());
	//wxLogStatus(str);
}
