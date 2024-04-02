#pragma once
#include <wx/wx.h> 


class WheelApp
{
public:
	WheelApp(const wxString& title);
private:
	void SpinWheelControls();
	void UpdateWheelText();
	void OnSpinButtonClick();
	bool IsWheelSpinning();
	void TaskSelection();
	void ClearWheel();

};

