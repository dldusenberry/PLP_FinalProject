#pragma once
#include <wx/wx.h> 

class App : public wxApp 
{
public:
	virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnAddButtonClick(wxCommandEvent& event);
    void OnRemoveButtonClick(wxCommandEvent& event);

    void OnRectAdded(wxCommandEvent& event);
    void OnRectRemoved(wxCommandEvent& event);

    wxPanel* createButtonPanel(wxWindow* parent);

    WheelApp* canvas;
    ChartControl* chart;

    int rectCount = 0;
    std::mt19937 randomGen;
};

