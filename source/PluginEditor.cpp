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
    , time_rotary_(p.getApvts(), Gui::Params::TIME)
    , time_label_(Gui::Params::TIME + "_label", Gui::Params::TIME)
    , feedback_rotary_(p.getApvts(), Gui::Params::FEEDBACK)
    , feedback_label_(Gui::Params::FEEDBACK + "_label", Gui::Params::FEEDBACK)
    , wet_rotary_(p.getApvts(), Gui::Params::WET_LEVEL)
    , wet_label_(Gui::Params::WET_LEVEL + "_label", Gui::Params::WET_LEVEL)
    , dry_rotary_(p.getApvts(), Gui::Params::DRY_LEVEL)
    , dry_label_(Gui::Params::DRY_LEVEL + "_label", Gui::Params::DRY_LEVEL)
    , xy_graph_(p)
{
    setLookAndFeel(&lnf_);

    // addAndMakeVisible(discrete_time_rotary_);
    addAndMakeVisible(time_rotary_);
    addAndMakeVisible(time_label_);
    addAndMakeVisible(feedback_rotary_);
    addAndMakeVisible(feedback_label_);
    addAndMakeVisible(wet_rotary_);
    addAndMakeVisible(wet_label_);
    addAndMakeVisible(dry_rotary_);
    addAndMakeVisible(dry_label_);
    addAndMakeVisible(xy_graph_);
    addAndMakeVisible(interval_buttons_);
    addAndMakeVisible(interval_combo_box_);

    time_rotary_.onValueChange     = [this] { xy_graph_.repaint(); };
    feedback_rotary_.onValueChange = [this] { xy_graph_.repaint(); };

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

    const auto left_rotary_x   = (graph_x - Gui::ROTARY_DIAMETER - Gui::UI_MULTIPLE);
    const auto right_rotary_x  = (graph_right + Gui::UI_MULTIPLE);
    const auto top_rotary_y    = (graph_top + Gui::UI_MULTIPLE);
    const auto bottom_rotary_y = (graph_bottom - Gui::ROTARY_DIAMETER - Gui::LABEL_HEIGHT - Gui::UI_MULTIPLE);

    time_rotary_.setBounds(left_rotary_x, top_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    time_label_.setBounds(getRotaryLabelBounds(time_rotary_));

    feedback_rotary_.setBounds(left_rotary_x, bottom_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    feedback_label_.setBounds(getRotaryLabelBounds(feedback_rotary_));

    dry_rotary_.setBounds(right_rotary_x, top_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    dry_label_.setBounds(getRotaryLabelBounds(dry_rotary_));

    wet_rotary_.setBounds(right_rotary_x, bottom_rotary_y, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    wet_label_.setBounds(getRotaryLabelBounds(wet_rotary_));

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
