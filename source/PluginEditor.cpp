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
    , xy_graph_(p)
    , wet_control_(p.getApvts(), GraphDelay::WET_LEVEL)
    , dry_control_(p.getApvts(), GraphDelay::DRY_LEVEL)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(xy_graph_);
    addAndMakeVisible(wet_control_);
    addAndMakeVisible(dry_control_);

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
    const auto& bounds = getLocalBounds();

    xy_graph_.setBounds(GraphDelay::UI_PADDING,
                        GraphDelay::UI_PADDING,
                        GraphDelay::GRAPH_DIAMETER,
                        GraphDelay::GRAPH_DIAMETER);

    const auto     rotary_x = (bounds.getRight() - GraphDelay::ROTARY_IMAGE_DIAMETER - GraphDelay::UI_PADDING);
    constexpr auto rotary_group_height = (GraphDelay::ROTARY_IMAGE_DIAMETER + GraphDelay::LABEL_HEIGHT);
    const auto     top_rotary_y        = xy_graph_.getY();
    const auto     bottom_rotary_y     = (xy_graph_.getBottom() - rotary_group_height);

    wet_control_.setBounds(rotary_x, top_rotary_y, GraphDelay::ROTARY_IMAGE_DIAMETER, rotary_group_height);
    dry_control_.setBounds(rotary_x, bottom_rotary_y, GraphDelay::ROTARY_IMAGE_DIAMETER, rotary_group_height);
}

/*---------------------------------------------------------------------------
** End of File
*/
