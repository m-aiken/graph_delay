#include "GlobalConstants.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "Theme.h"

/*---------------------------------------------------------------------------
**
*/
PluginEditor::PluginEditor(PluginProcessor& p)
    : AudioProcessorEditor(&p)
    , processor_ref_(p)
    , time_control_(p.getApvts(), GraphDelay::TIME)
    , feedback_control_(p.getApvts(), GraphDelay::FEEDBACK)
    , wet_control_(p.getApvts(), GraphDelay::WET_LEVEL)
    , dry_control_(p.getApvts(), GraphDelay::DRY_LEVEL)
    , xy_graph_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(time_control_);
    addAndMakeVisible(feedback_control_);
    addAndMakeVisible(wet_control_);
    addAndMakeVisible(dry_control_);
    addAndMakeVisible(xy_graph_);

    time_control_.getPositionMarker().onValueChange     = [this] { xy_graph_.repaint(); };
    feedback_control_.getPositionMarker().onValueChange = [this] { xy_graph_.repaint(); };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(GraphDelay::WINDOW_WIDTH, GraphDelay::WINDOW_HEIGHT);
}

/*---------------------------------------------------------------------------
**
*/
PluginEditor::~PluginEditor()
{
    setLookAndFeel(nullptr);
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);
    g.fillAll(Theme::getColour(Theme::LIGHT_BLUE).withAlpha(0.85f));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    xy_graph_.centreWithSize(GraphDelay::GRAPH_DIAMETER, GraphDelay::GRAPH_DIAMETER);

    const auto graph_top    = xy_graph_.getY();
    const auto graph_bottom = xy_graph_.getBottom();
    const auto graph_x      = xy_graph_.getX();
    const auto graph_right  = xy_graph_.getRight();

    constexpr auto rotary_group_diameter = GraphDelay::ROTARY_DIAMETER + (GraphDelay::UI_MAGIC_NUMBER * 4);

    const auto left_rotary_x   = (graph_x - rotary_group_diameter);
    const auto right_rotary_x  = (graph_right);
    const auto top_rotary_y    = (graph_top);
    const auto bottom_rotary_y = (graph_bottom - rotary_group_diameter);

    time_control_.setBounds(left_rotary_x, top_rotary_y, rotary_group_diameter, rotary_group_diameter);
    feedback_control_.setBounds(left_rotary_x, bottom_rotary_y, rotary_group_diameter, rotary_group_diameter);
    dry_control_.setBounds(right_rotary_x, top_rotary_y, rotary_group_diameter, rotary_group_diameter);
    wet_control_.setBounds(right_rotary_x, bottom_rotary_y, rotary_group_diameter, rotary_group_diameter);
}

/*---------------------------------------------------------------------------
** End of File
*/
