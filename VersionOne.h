#pragma once
#include <wx/wx.h> 


class VersionOne : public wxFrame
{
public:
	VersionOne(const wxString& title);
private:
	void OnButtonClicked(wxCommandEvent& event);
	void OnSliderChanged(wxCommandEvent& event);
	void OnTextChanged(wxCommandEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnKeyEvent(wxKeyEvent& event);

	void OnClose(wxCloseEvent& event);


	//	void OnAnyButtonClicked(wxCommandEvent& event);

};

