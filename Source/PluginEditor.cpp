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
    , time_label_(DelayParams::TIME)
    , feedback_label_(DelayParams::FEEDBACK)
    , wet_label_(DelayParams::WET_LEVEL)
    , dry_label_(DelayParams::DRY_LEVEL)
    , xy_grid_(p)
{
    setLookAndFeel(&lnf_);

    addAndMakeVisible(time_rotary_);
    addAndMakeVisible(feedback_rotary_);
    addAndMakeVisible(wet_rotary_);
    addAndMakeVisible(dry_rotary_);

    addAndMakeVisible(time_label_);
    addAndMakeVisible(feedback_label_);
    addAndMakeVisible(wet_label_);
    addAndMakeVisible(dry_label_);

    addAndMakeVisible(xy_grid_);

    time_rotary_.onValueChange     = [this] { xy_grid_.repaint(); };
    feedback_rotary_.onValueChange = [this] { xy_grid_.repaint(); };

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
    const auto     bounds  = getLocalBounds();
    const auto     width   = bounds.getWidth();
    const auto     bottom  = bounds.getBottom();
    constexpr auto padding = 20;

    constexpr auto label_height = Gui::ROTARY_DIAMETER / 4;

    time_rotary_.setBounds(padding, Gui::ROTARY_DIAMETER * 0.5, Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    feedback_rotary_.setBounds(padding, bottom - (Gui::ROTARY_DIAMETER * 1.75), Gui::ROTARY_DIAMETER, Gui::ROTARY_DIAMETER);
    dry_rotary_.setBounds(width - Gui::ROTARY_DIAMETER - padding,
                          Gui::ROTARY_DIAMETER * 0.5,
                          Gui::ROTARY_DIAMETER,
                          Gui::ROTARY_DIAMETER);
    wet_rotary_.setBounds(width - Gui::ROTARY_DIAMETER - padding,
                          bottom - (Gui::ROTARY_DIAMETER * 1.75),
                          Gui::ROTARY_DIAMETER,
                          Gui::ROTARY_DIAMETER);

    time_label_.setBounds(time_rotary_.getX(), time_rotary_.getBottom(), Gui::ROTARY_DIAMETER, label_height);
    feedback_label_.setBounds(feedback_rotary_.getX(), feedback_rotary_.getBottom(), Gui::ROTARY_DIAMETER, label_height);
    wet_label_.setBounds(wet_rotary_.getX(), wet_rotary_.getBottom(), Gui::ROTARY_DIAMETER, label_height);
    dry_label_.setBounds(dry_rotary_.getX(), dry_rotary_.getBottom(), Gui::ROTARY_DIAMETER, label_height);

    xy_grid_.setBounds(bounds.getCentreX() - (Gui::GRAPH_DIAMETER / 2),
                       bounds.getCentreY() - (Gui::GRAPH_DIAMETER / 2),
                       Gui::GRAPH_DIAMETER,
                       Gui::GRAPH_DIAMETER);
}

/*---------------------------------------------------------------------------
** End of File
*/
