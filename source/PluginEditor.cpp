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
    , discrete_time_rotary_(p.getApvts())
    , time_control_(p.getApvts(), Gui::Params::TIME)
    , feedback_control_(p.getApvts(), Gui::Params::FEEDBACK)
    , wet_control_(p.getApvts(), Gui::Params::WET_LEVEL)
    , dry_control_(p.getApvts(), Gui::Params::DRY_LEVEL)
    , xy_graph_(p)
{
    setLookAndFeel(&lnf_);

    // addAndMakeVisible(discrete_time_rotary_);
    addAndMakeVisible(time_control_);
    addAndMakeVisible(feedback_control_);
    addAndMakeVisible(wet_control_);
    addAndMakeVisible(dry_control_);
    addAndMakeVisible(xy_graph_);
    addAndMakeVisible(interval_buttons_);
    addAndMakeVisible(interval_combo_box_);

    time_control_.getRotary().onValueChange     = [this] { xy_graph_.repaint(); };
    feedback_control_.getRotary().onValueChange = [this] { xy_graph_.repaint(); };

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

    constexpr auto rotary_group_diameter = Gui::ROTARY_DIAMETER + (Gui::UI_MULTIPLE * 4);

    const auto left_rotary_x   = (graph_x - rotary_group_diameter);
    const auto right_rotary_x  = (graph_right);
    const auto top_rotary_y    = (graph_top);
    const auto bottom_rotary_y = (graph_bottom - rotary_group_diameter);

    time_control_.setBounds(left_rotary_x, top_rotary_y, rotary_group_diameter, rotary_group_diameter);
    feedback_control_.setBounds(left_rotary_x, bottom_rotary_y, rotary_group_diameter, rotary_group_diameter);
    dry_control_.setBounds(right_rotary_x, top_rotary_y, rotary_group_diameter, rotary_group_diameter);
    wet_control_.setBounds(right_rotary_x, bottom_rotary_y, rotary_group_diameter, rotary_group_diameter);

    // constexpr auto button_height         = 32;
    // const auto     initial_button_bounds = juce::Rectangle< int >(0, bottom - button_height, width, button_height);
    // interval_buttons_.setBounds(initial_button_bounds.reduced(4));

    // interval_combo_box_.setBounds(Gui::PADDING, Gui::PADDING, button_height * 2, button_height);

#if 0
    discrete_time_rotary_.setBounds(0,
                                    0,
                                    Gui::ROTARY_DIAMETER + (Gui::LABEL_HEIGHT * 2),
                                    Gui::ROTARY_DIAMETER + (Gui::LABEL_HEIGHT * 2));
#endif
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ juce::Rectangle< int >
PluginEditor::getRotaryLabelBounds(const RotaryControl& rotary_to_annotate)
{
    return { rotary_to_annotate.getX(), rotary_to_annotate.getBottom(), rotary_to_annotate.getWidth(), Gui::LABEL_HEIGHT };
}

/*---------------------------------------------------------------------------
** End of File
*/
