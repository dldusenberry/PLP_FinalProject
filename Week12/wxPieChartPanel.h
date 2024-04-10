

#pragma once

//#include <wx/charts/wxcharts.h>
#include <wx/panel.h>

class wxPieChartPanel : public wxPanel
{
public:
    wxPieChartPanel(wxWindow* parent);

private:
    wxPieChartCtrl* m_pieChart;
};




