#pragma once
#include <wx/wx.h> 


// MAINFRAME CLASS
class VersionOne : public wxFrame
{
public:
	VersionOne(const wxString& title);
private:
	void CreateControls();
	//void SetupSizers();
	void BindEventHandlers();
	void AddSavedTasks();

	//void OnResize(wxSizeEvent& event);	 // NOT READY
	void OnAddButtonClicked(wxCommandEvent& event);
	void OnInputEnter(wxCommandEvent& event);
	void OnListKeyDown(wxKeyEvent& event);
	void OnClearButtonClicked(wxCommandEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnWindowClosed(wxCloseEvent& event);


	void AddItemFromInput();
	void DeleteSelectedItem();
	void MoveSelectedItem(int offset);
	void SwapItems(int i, int j);

	wxPanel* panel;
	wxStaticText* headLineText;
	wxListBox* listBox;
	wxTextCtrl* inputField;
	wxButton* addButton;
	wxCheckListBox* checkListBox;
	wxButton* clearButton;

	
	
	
	/*
	* TO-DO:
	void OnButtonClicked(wxCommandEvent& event);
	void OnSliderChanged(wxCommandEvent& event);
	void OnTextChanged(wxCommandEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnKeyEvent(wxKeyEvent& event);

	void OnAnyButtonClicked(wxCommandEvent& event);
	*/

};

