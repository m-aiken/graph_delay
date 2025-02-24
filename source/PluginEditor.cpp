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
    , time_rotary_(p.getApvts(), DelayParams::TIME)
    , feedback_rotary_(p.getApvts(), DelayParams::FEEDBACK)
    , wet_rotary_(p.getApvts(), DelayParams::WET_LEVEL)
    , dry_rotary_(p.getApvts(), DelayParams::DRY_LEVEL)
    , xy_graph_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(time_rotary_);
    addAndMakeVisible(feedback_rotary_);
    addAndMakeVisible(wet_rotary_);
    addAndMakeVisible(dry_rotary_);
    addAndMakeVisible(xy_graph_);
    addAndMakeVisible(interval_buttons_);

    time_rotary_.getRotaryRef().onValueChange     = [this] { xy_graph_.repaint(); };
    feedback_rotary_.getRotaryRef().onValueChange = [this] { xy_graph_.repaint(); };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(Gui::WINDOW_WIDTH, Gui::WINDOW_HEIGHT);
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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Theme::getColour(Theme::EGGSHELL));
}

/*---------------------------------------------------------------------------
**
*/
void
PluginEditor::resized()
{
    const auto& bounds = getLocalBounds();
    const auto  width  = bounds.getWidth();
    const auto  bottom = bounds.getBottom();

    xy_graph_.centreWithSize(Gui::GRAPH_DIAMETER, Gui::GRAPH_DIAMETER);

    const auto graph_top    = xy_graph_.getY();
    const auto graph_bottom = xy_graph_.getBottom();
    const auto graph_x      = xy_graph_.getX();
    const auto graph_right  = xy_graph_.getRight();

    const auto left_rotary_x   = (graph_x - Gui::ROTARY_DIAMETER - Gui::PADDING);
    const auto right_rotary_x  = (graph_right + Gui::PADDING);
    const auto top_rotary_y    = (graph_top + Gui::PADDING);
    const auto bottom_rotary_y = (graph_bottom - Gui::ROTARY_DIAMETER - Gui::PADDING);

    time_rotary_.setBounds(left_rotary_x, top_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    feedback_rotary_.setBounds(left_rotary_x, bottom_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    dry_rotary_.setBounds(right_rotary_x, top_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    wet_rotary_.setBounds(right_rotary_x, bottom_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);

    constexpr auto button_height         = 32;
    const auto     initial_button_bounds = juce::Rectangle< int >(0, bottom - button_height, width, button_height);
    interval_buttons_.setBounds(initial_button_bounds.reduced(4));
}

/*---------------------------------------------------------------------------
** End of File
*/
