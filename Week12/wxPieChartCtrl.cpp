#include "wxpiechartctrl.h"

wxPieChartCtrl::wxPieChartCtrl(wxWindow* parent,
    wxWindowID id,
    wxPieChartData::ptr data,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_pieChart(data, size)
{
    SetMinSize(wxSize(100, 100));
    data->AddObserver(this);
}

wxPieChartCtrl::wxPieChartCtrl(wxWindow* parent,
    wxWindowID id,
    wxPieChartData::ptr data,
    wxSharedPtr<wxPieChartOptions>& options,
    const wxPoint& pos,
    const wxSize& size,
    long style)
    : wxChartCtrl(parent, id, pos, size, style),
    m_pieChart(data, options, size)
{
    data->AddObserver(this);
}

wxPieChart& wxPieChartCtrl::GetChart()
{
    return m_pieChart;
}

void wxPieChartCtrl::OnUpdate(const std::map<wxString,
    wxChartSliceData>& data)
{
    m_pieChart.SetData(data);
    auto parent = this->GetParent();
    if (parent)
        parent->Layout();
}