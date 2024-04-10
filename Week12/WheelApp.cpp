#include "WheelApp.h"
#include <wx/wx.h> 
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "Task.h"
#include <vector>
#include <string>

#include <cstdlib>
#include <ctime>
#include <iostream>

wxDEFINE_EVENT(CANVAS_RECT_ADDED, wxCommandEvent);
wxDEFINE_EVENT(CANVAS_RECT_REMOVED, wxCommandEvent);


WheelApp::WheelApp(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size) : wxWindow(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT); // needed for windows

    this->Bind(wxEVT_PAINT, &WheelApp::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &WheelApp::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &WheelApp::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &WheelApp::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &WheelApp::OnMouseLeave, this);

    addRect(this->FromDIP(100), this->FromDIP(80), this->FromDIP(210), this->FromDIP(140), 0, *wxRED, "Rect #1");
    addRect(this->FromDIP(130), this->FromDIP(110), this->FromDIP(280), this->FromDIP(210), M_PI / 3.0, *wxBLUE, "Rect #2");
    addRect(this->FromDIP(110), this->FromDIP(110), this->FromDIP(300), this->FromDIP(120), -M_PI / 4.0, wxColor(255, 0, 255, 128), "Rect #3");

    this->draggedObj = nullptr;
    this->shouldRotate = false;
}

void WheelApp::addRect(int width, int height, int centerX, int centerY, double angle, wxColor color, const std::string& text)
{
    GraphicObject obj{
        {-width / 2.0,
         -height / 2.0,
         static_cast<double>(width),
         static_cast<double>(height)},
        color,
        text,
        {} };

    obj.transform.Translate(
        static_cast<double>(centerX),
        static_cast<double>(centerY));

    obj.transform.Rotate(angle);

    this->objectList.push_back(obj);

    sendRectAddedEvent(text);
    Refresh();
}

void WheelApp::removeTopRect()
{
    if (!this->objectList.empty() && draggedObj == nullptr)
    {
        auto& text = this->objectList.back().text;
        this->objectList.pop_back();

        sendRectRemovedEvent(text);
        Refresh();
    }
}

void WheelApp::OnPaint(wxPaintEvent& evt)
{
    // needed for windows
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        for (const auto& object : objectList)
        {
            gc->SetTransform(gc->CreateMatrix(object.transform));

            gc->SetBrush(wxBrush(object.color));
            gc->DrawRectangle(object.rect.m_x, object.rect.m_y, object.rect.m_width, object.rect.m_height);

            gc->SetFont(*wxNORMAL_FONT, *wxWHITE);

            double textWidth, textHeight;
            gc->GetTextExtent(object.text, &textWidth, &textHeight);

            gc->DrawText(object.text, object.rect.m_x + object.rect.m_width / 2.0 - textWidth / 2.0, object.rect.m_y + object.rect.m_height / 2.0 - textHeight / 2.0);
        }

        delete gc;
    }
}

void WheelApp::OnMouseDown(wxMouseEvent& event)
{
    auto clickedObjectIter = std::find_if(objectList.rbegin(), objectList.rend(), [event](const GraphicObject& o)
        {
            wxPoint2DDouble clickPos = event.GetPosition();
            auto inv = o.transform;
            inv.Invert();
            clickPos = inv.TransformPoint(clickPos);
            return o.rect.Contains(clickPos);
        });

    if (clickedObjectIter != objectList.rend())
    {
        auto forwardIt = std::prev(clickedObjectIter.base());

        objectList.push_back(*forwardIt);
        objectList.erase(forwardIt);

        draggedObj = &(*std::prev(objectList.end()));

        lastDragOrigin = event.GetPosition();
        shouldRotate = wxGetKeyState(WXK_ALT);

        Refresh(); // for z order reversal
    }
}

void WheelApp::OnMouseMove(wxMouseEvent& event)
{
    if (draggedObj != nullptr)
    {
        if (shouldRotate)
        {
            double absoluteYDiff = event.GetPosition().y - lastDragOrigin.m_y;
            draggedObj->transform.Rotate(absoluteYDiff / 100.0 * M_PI);
        }
        else
        {
            auto dragVector = event.GetPosition() - lastDragOrigin;

            auto& inv = draggedObj->transform;
            inv.Invert();
            dragVector = inv.TransformDistance(dragVector);

            draggedObj->transform.Translate(dragVector.m_x, dragVector.m_y);
        }

        lastDragOrigin = event.GetPosition();
        Refresh();
    }
}

void WheelApp::OnMouseUp(wxMouseEvent& event)
{
    finishDrag();
    finishRotation();
}

void WheelApp::OnMouseLeave(wxMouseEvent& event)
{
    finishDrag();
    finishRotation();
}

void WheelApp::finishDrag()
{
    draggedObj = nullptr;
}

void WheelApp::finishRotation()
{
    shouldRotate = false;
}

void WheelApp::sendRectAddedEvent(const wxString& rectTitle)
{
    wxCommandEvent event(CANVAS_RECT_ADDED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}

void WheelApp::sendRectRemovedEvent(const wxString& rectTitle)
{
    wxCommandEvent event(CANVAS_RECT_REMOVED, GetId());
    event.SetEventObject(this);
    event.SetString(rectTitle);

    ProcessWindowEvent(event);
}

/*
* 
WheelApp::WheelApp(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->Bind(wxEVT_PAINT, WheelApp::OnPaint, this);



}
void WheelApp::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

	if (gc) {
		wxPoint circleOrigin = this->FromDIP(wxPoint(189, 200));
		wxSize circleSize = this->FromDIP(wxPoint(100, 80));

		gc->SetBrush(*wxRED_BRUSH);
		gc->DrawRoundedRectangle(circleOrigin);

	}
}

int WheelApp::SpinWheelControls()
{
    int spin_value = rand() % 42 + 22; // sets boundaries for spins
    int last_number = 0; // variable used to determine points
        for (int i = 0; i < spin_value; i++)
        {
            cout << values[index % NUM_VALUES] << " ";
            last_number = values[index % NUM_VALUES];
            index++;
        }
    return last_number;
    
}

void WheelApp::UpdateWheelText()
{
}

void WheelApp::OnSpinButtonClick()
{
}

bool WheelApp::IsWheelSpinning()
{
	return false;
}

void WheelApp::TaskSelection()
{
}

void WheelApp::ClearWheel()
{
}
*/