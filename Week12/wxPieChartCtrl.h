#pragma once
#include "wxchartctrl.h"
#include "wxpiechart.h"

/// A control that displays a pie chart.

/// \ingroup chartclasses
class WXCHARTS_EXPORT wxPieChartCtrl : public wxChartCtrl, public wxChartValueObserver<std::map<wxString, wxChartSliceData>>
{
public:
    /// Constructs a wxPieChartCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The data that will be used to initialize the chart.
    /// @param pos Control position. wxDefaultPosition indicates that
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable
    /// size can  be found, the window will be sized to 20x20 pixels
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please
    /// see wxWindow.
    wxPieChartCtrl(wxWindow* parent, wxWindowID id, wxPieChartData::ptr data,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
        long style = 0);

    /// Constructs a wxPieChartCtrl control.
    /// @param parent Pointer to a parent window.
    /// @param id Control identifier. If wxID_ANY, will automatically
    /// create an identifier.
    /// @param data The data that will be used to initialize the chart.
    /// @param options The settings to be used for this chart.
    /// @param pos Control position. wxDefaultPosition indicates that
    /// wxWidgets should generate a default position for the control.
    /// @param size Control size. wxDefaultSize indicates that wxWidgets
    /// should generate a default size for the window. If no suitable
    /// size can  be found, the window will be sized to 20x20 pixels
    /// so that the window is visible but obviously not correctly sized.
    /// @param style Control style. For generic window styles, please
    /// see wxWindow.
    wxPieChartCtrl(wxWindow* parent, wxWindowID id, wxPieChartData::ptr data,
        wxSharedPtr<wxPieChartOptions>& options, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0);

private:
    virtual wxPieChart& GetChart();
    void OnUpdate(const std::map<wxString, wxChartSliceData>& data) override;

private:
    wxPieChart m_pieChart;
};