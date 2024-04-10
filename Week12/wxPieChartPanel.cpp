#include "wxPieChartPanel.h"

#include "wxpiechartpanel.h"
#include <wx/sizer.h>
#include <wx/choice.h>

wxPieChartPanel::wxPieChartPanel(wxWindow* parent) : wxPanel(parent)
{
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    wxArrayString str;
    str.Add("three");
    str.Add("four");
    wxChoice* choice = new wxChoice(this, -1, wxDefaultPosition, wxDefaultSize, str);
    sizer->Add(choice);

    // Create the data for the pie chart widget
    wxPieChartData::ptr chartData = wxPieChartData::make_shared();
    chartData->AppendSlice(wxChartSliceData(300, wxColor(0x4A46F7), "Red"));
    chartData->AppendSlice(wxChartSliceData(50, wxColor(0xBDBF46), "Green"));
    chartData->AppendSlice(wxChartSliceData(100, wxColor(0x5CB4FD), "Yellow"));
    chartData->AppendSlice(wxChartSliceData(40, wxColor(0xB19F94), "Grey"));
    chartData->AppendSlice(wxChartSliceData(120, wxColor(0x60534D), "Dark Grey"));

    // Create the pie chart widget
    m_pieChart = new wxPieChartCtrl(this, wxID_ANY, chartData,
        wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    sizer->Add(m_pieChart, 1, wxEXPAND);

    SetSizer(sizer);
}