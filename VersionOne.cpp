#include "VersionOne.h"
#include <wx/wx.h> 
#include "Task.h"
#include <vector>
#include <string>


// MAINFRAME CLASS
VersionOne::VersionOne(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	CreateControls();
	// SetupSizers();	 // NOT READY
	BindEventHandlers();
	AddSavedTasks();

	panel->Bind(wxEVT_MOTION, &VersionOne::OnMouseEvent, this);
	//Bind(wxEVT_SIZE, &VersionOne::OnResize, this);	 // NOT READY

	wxStatusBar* statusBar = CreateStatusBar();
	statusBar->SetDoubleBuffered(true);



	/*
	---> TO-DO:	Add Widgets <---	 // NOT READY
	
	wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(300, 275), wxSize(200, 50)); // 
	wxSlider* slider = new wxSlider(panel, wxID_ANY, 0, 0, 100, wxPoint(300, 200), wxSize(200, -1), wxSL_VALUE_LABEL); // int params: initial value, a minimum value, a maximum value, Style: displays slider's current value
	wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(300, 375), wxSize(200, -1));

	this->Bind(wxEVT_CLOSE_WINDOW, &VersionOne::OnClose, this);
	button->Bind(wxEVT_BUTTON, &VersionOne::OnButtonClicked, this); // can call on panel, VersionOne bc inheritance
	slider->Bind(wxEVT_SLIDER, &VersionOne::OnSliderChanged, this);
	text->Bind(wxEVT_TEXT, &VersionOne::OnTextChanged, this);

	
	panel->Bind(wxEVT_KEY_DOWN, &VersionOne::OnKeyEvent, this);

	//button->Unbind(wxEVT_BUTTON, &VersionOne::OnButtonClicked, this);
	*/
	
	
	// --> END MAINFRAME <--
}

// Mainframe controls:
// All window frame widget definitions and settings
void VersionOne::CreateControls() {
	wxFont headLineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));


	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headLineText = new wxStaticText(panel, wxID_ANY, "Spinning Wheel of Indecision!",
		wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headLineText->SetFont(headLineFont);

	listBox = new wxListBox(panel, wxID_ANY, wxPoint(80, 110), wxSize(400, 300), wxLB_NEEDED_SB);
	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(500, 220), wxSize(295, 35), wxTE_PROCESS_ENTER);
	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(800, 220), wxSize(100, 35));
	checkListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(500, 260), wxSize(300, 200));
	clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(500, 465), wxSize(100, 35));


	/*
	---> TO-DO:	Auto-Window Resizing <---	 // NOT READY

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	wxSizerFlags flags = wxSizerFlags().CenterHorizontal().Border(wxALL, 25);

	boxSizer->Add(headLineText, flags);
	boxSizer->Add(listBox, flags);
	boxSizer->Add(inputField, flags);
	boxSizer->Add(addButton, flags);
	boxSizer->Add(checkListBox, flags);
	boxSizer->Add(clearButton, flags);

	wxBoxSizer* inputSizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(boxSizer);
	boxSizer->SetSizeHints(this);
	SetClientSize(1000, 600);
	
	// Event handler:
	void VersionOne::OnResize(wxSizeEvent& event)
	{
		wxSize clientSize = GetClientSize();
	}
	// Event handler:
	void VersionOne::SetupSizers()
	{
	}
	*/


}
// MAIN Event Handler:
// Binds all event actions to event handler functions
void VersionOne::BindEventHandlers() 
{
	addButton->Bind(wxEVT_BUTTON, &VersionOne::OnAddButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &VersionOne::OnInputEnter, this);
	checkListBox->Bind(wxEVT_KEY_DOWN, &VersionOne::OnListKeyDown, this);
	clearButton->Bind(wxEVT_BUTTON, &VersionOne::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &VersionOne::OnWindowClosed, this);

}


// Event handler:
// Click event on 'Add' button calls AddItemFromInput() action
void VersionOne::OnAddButtonClicked(wxCommandEvent& event)
{
	AddItemFromInput();
}

// Event handler:
// Keyboard event 'Enter' keystroke calls AddItemFromInpu()t action
void VersionOne::OnInputEnter(wxCommandEvent& event)
{
	AddItemFromInput();
}

// Event handler: Switch statement
// Keyboard event 'DELETE' calls DeleteSelectedItem() action
// Keyboard events 'UP', 'DOWN' keystrokes call MoveSelectedItem() action
void VersionOne::OnListKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode()) {
		case WXK_DELETE:
			DeleteSelectedItem();
			break;
		case WXK_UP:
			MoveSelectedItem(-1);
			break;
		case WXK_DOWN:
			MoveSelectedItem(1);
			break;
	}
}

// Event handler:
// Click event on 'Clear' button opens a dialog window and calls Clear() action
void VersionOne::OnClearButtonClicked(wxCommandEvent& event)
{
	if (checkListBox->IsEmpty()) {
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to clear all tasks?", "Clear", wxYES_NO | wxCANCEL);
	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		checkListBox->Clear();
	}
}

// Event handler: Mostly for debugging purposes at the moment
// Mouse motion event displays x,y coordinates of cursor current position
void VersionOne::OnMouseEvent(wxMouseEvent& event) {
	wxPoint mousePos = event.GetPosition();
	wxString message = wxString::Format("Mouse (x=%d y=%d)", mousePos.x, mousePos.y);
	wxLogStatus(message);

}

// Event handler:
// Close window event saves user session tasks to a file
void VersionOne::OnWindowClosed(wxCloseEvent& event)
{
	std::vector<Task> tasks;

	for (int i = 0; i < checkListBox->GetCount(); i++) {
		Task task;
		task.description = checkListBox->GetString(i);
		task.done = checkListBox->IsChecked(i);
		tasks.push_back(task);
	}

	SaveTasksToFile(tasks, "tasks.txt");
	event.Skip();
}

// Event action: 
// Adds task from input line to current tasks ListBox and clears input field
void VersionOne::AddItemFromInput()
{
	wxString description = inputField->GetValue();

	if (!description.IsEmpty()) {
		checkListBox->Insert(description, checkListBox->GetCount());
		inputField->Clear();
	}
	inputField->SetFocus();
}

// Event action:
// Loads user tasks from last session file to resume when app is reopened
void VersionOne::AddSavedTasks()
{
	std::vector<Task> tasks = LoadTasksFromFile("tasks.txt");

	for (const Task& task : tasks) {
		int index = checkListBox->GetCount();
		checkListBox->Insert(task.description, index);
		checkListBox->Check(index, task.done);
	}
}

// Event action:
// Deletes selected task from ListBox
void VersionOne::DeleteSelectedItem()
{
	int selectedIndex = checkListBox->GetSelection();

	if (selectedIndex == wxNOT_FOUND) {
		return;
	}
	checkListBox->Delete(selectedIndex);
}

// Event action:
// Moves selected tasks up or down in ListBox
// NOTE: for debugging only; will remove later because the goal is to have a randomized picker not a prioritized one
void VersionOne::MoveSelectedItem(int offset)
{
	int selectedIndex = checkListBox->GetSelection();

	if (selectedIndex == wxNOT_FOUND) {
		return;
	}
	int newIndex = selectedIndex + offset;

	if (newIndex >= 0 && newIndex < checkListBox->GetCount()) {
		SwapItems(selectedIndex, newIndex);
		checkListBox->SetSelection(newIndex, true);
	}
}
// Event action: Helper function to MoveSelectedItem() function above
// Swaps task index positions
void VersionOne::SwapItems(int i, int j)
{
	Task taskI{ checkListBox->GetString(i).ToStdString(), checkListBox->IsChecked(i) };
	Task taskJ{ checkListBox->GetString(j).ToStdString(), checkListBox->IsChecked(j) };

	checkListBox->SetString(i, taskJ.description);
	checkListBox->Check(i, taskJ.done);

	checkListBox->SetString(j, taskI.description);
	checkListBox->Check(j, taskI.done);
}



/*


void VersionOne::OnButtonClicked(wxCommandEvent& event) {
	wxLogStatus("Button Clicked");
	wxLogMessage("Button Clicked");
}

void VersionOne::OnSliderChanged(wxCommandEvent& event) {
	wxString str = wxString::Format("Slider Value: %d", event.GetInt());
	wxLogStatus(str);
}

void VersionOne::OnTextChanged(wxCommandEvent& event) {
	wxString str = wxString::Format("Text: %s", event.GetString());
	wxLogStatus(str);
}
*/
