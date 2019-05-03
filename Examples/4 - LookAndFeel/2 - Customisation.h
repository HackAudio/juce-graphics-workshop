/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             LookAndFeel Customisation
  vendor:           Antonio Lassandro
  website:          https://www.github.com/lassandroan/juce-graphics-workshop
  description:      A basic overview of the juce::Component API

  dependencies:     juce_core, juce_gui_basics
  exporters:        linux_make, vs2013, vs2015, vs2017, vs2019, xcode_mac

  moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1

  type:             Component
  mainClass:        Demo

 END_JUCE_PIP_METADATA

*******************************************************************************/

/*
  Author: Antonio Lassandro
  Copyright 2019 Harrison Consoles

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#pragma once

/** Here we create a custom LookAndFeel by subclassing one of the default
    LookAndFeel types and overriding its virtual methods.
**/
struct CustomLookAndFeel : public LookAndFeel_V4
{
    /** I often supplement missing features from the LookAndFeel (such as being
        able to define default outline sizes, margin sizes, etc.) by using
        static members in my classes. This way I can always refer to this
        value in my drawing routines.
    **/
    static constexpr float DefaultOutlineSize   = 1.0f;
    static constexpr float DefaultCornerRadius  = 4.0f;
    static constexpr float DisabledTransparency = 0.5f;
    static constexpr float DefaultFontSize      = 12.0f;

    static Font getDefaultFont()
    {
        return Font().withHeight(DefaultFontSize).boldened();
    }

    /** Many widgets have their "pieces" broken up so that you can easily alter
        the style without having to re-write an entire drawing routine. For
        example getTextButtonFont() is used by the default LookAndFeel
        implementations to set the font for a TextButton, but you can also
        utilize this method in your own custom drawing routines.
    **/
    Font getTextButtonFont(TextButton &button, const int buttonHeight) override
    {
        Font font = getDefaultFont();
        return font.withHeight(
            jmin(font.getHeight(), (float)buttonHeight * 0.75f)
        );
    }

    /** Certain methods may apply to a variety of widgets, such as this method
        drawButtonBackground(). It will apply to any of the built-in JUCE button
        classes that derive from the main juce::Button class.
    **/
    void drawButtonBackground(
        Graphics &g,
        Button &button,
        const Colour &backgroundColour,
        const bool shouldDrawButtonAsHighlighted,
        const bool shouldDrawButtonAsDown) override
    {
        /** You can often use the LookAndFeels to manage things like the
            Component's MouseCursor without having to subclass the Component
            type.
        **/
        if (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown)
            button.setMouseCursor(MouseCursor::PointingHandCursor);

        const ColourScheme   scheme(getCurrentColourScheme());
        const Rectangle<int> bounds(button.getLocalBounds());

        if (!button.isEnabled())
            g.beginTransparencyLayer(DisabledTransparency);

        Path path;
        path.addRoundedRectangle(
            bounds.reduced(DefaultOutlineSize),
            DefaultCornerRadius
        );

        /** Here we use a checkerboard pattern to fill our button. Because our
            button shape is rounded, we clip the Graphics context to our
            rounded rectangle Path.
        **/
        {
            Graphics::ScopedSaveState saveState(g);
            g.reduceClipRegion(path);

            g.fillCheckerBoard(
                path.getBounds(),
                2.0f, 2.0f,
                backgroundColour.brighter(),
                backgroundColour.darker()
            );
        }

        g.setColour(scheme.getUIColour(ColourScheme::outline));
        g.strokePath(
            path,
            PathStrokeType(
                DefaultOutlineSize,
                PathStrokeType::JointStyle::curved,
                PathStrokeType::EndCapStyle::rounded
            )
        );

        if (!button.isEnabled())
            g.endTransparencyLayer();
    }

    /** This method handles drawing a TextButton's text. It is called from the
        TextButton class after drawButtonBackground() has been called.
    **/
    void drawButtonText(
        Graphics &g,
        TextButton &button,
        const bool shouldDrawButtonAsHighlighted,
        const bool shouldDrawButtonAsDown) override
    {
        if (shouldDrawButtonAsDown)
            g.setColour(button.findColour(TextButton::textColourOnId));
        else
            g.setColour(button.findColour(TextButton::textColourOffId));

        if (!button.isEnabled())
            g.setOpacity(DisabledTransparency);

        g.setFont(getTextButtonFont(button, button.getHeight()));

        g.drawFittedText(
            button.getButtonText(),
            button.getLocalBounds(),
            Justification::centred,
            1
        );
    }

    /** This method handles drawing a ToggleButton's contents. Because it
        encompasses the whole button we can fully customize the order in which
        things are drawn. For example, we don't use the drawButtonBackground()
        method for our ToggleButtons.
    **/
    void drawToggleButton(
        Graphics &g,
        ToggleButton &button,
        const bool shouldDrawButtonAsHighlighted,
        const bool shouldDrawButtonAsDown) override
    {
        if (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown)
            button.setMouseCursor(MouseCursor::PointingHandCursor);

        const Font font = getDefaultFont();

        Rectangle<int> bounds = button.getLocalBounds();

        const float fontSize = jmin(
            font.getHeight(),
            (float)bounds.getHeight() * 0.75f
        );

        const Rectangle<float> tickBounds = bounds
            .removeFromLeft(bounds.getHeight())
            .toFloat();

        drawTickBox(
            g,
            button,
            tickBounds.getX(),
            tickBounds.getY(),
            tickBounds.getWidth(),
            tickBounds.getHeight(),
            button.getToggleState(),
            button.isEnabled(),
            shouldDrawButtonAsHighlighted,
            shouldDrawButtonAsDown
        );

        g.setColour(button.findColour(ToggleButton::textColourId));
        g.setFont(font.withHeight(fontSize));

        if (!button.isEnabled())
            g.setOpacity(DisabledTransparency);

        g.drawFittedText(
            button.getButtonText(),
            bounds.withTrimmedLeft(4),
            Justification::centredLeft,
            1
        );
    }

    /** This method defines the default style of a tick-box in JUCE. This is
        used in LookAndFeel_V4::drawToggleButton(), and we'll use it in our
        custom LookAndFeel as well.
    **/
    void drawTickBox(
        Graphics &g,
        Component &component,
        const float x, const float y,
        const float width, const float height,
        const bool isTicked,
        const bool isEnabled,
        const bool shouldDrawButtonAsHighlighted,
        const bool shouldDrawButtonAsDown) override
    {
        const ColourScheme     scheme(getCurrentColourScheme());
        const Rectangle<float> bounds(x, y, width, height);

        if (!isEnabled)
            g.beginTransparencyLayer(DisabledTransparency);

        /** Draw the tick box outline. **/
        {
            Path path;
            path.addRoundedRectangle(
                bounds.reduced(DefaultOutlineSize),
                DefaultCornerRadius
            );

            g.setColour(scheme.getUIColour(ColourScheme::outline));

            g.strokePath(
                path,
                PathStrokeType(
                    DefaultOutlineSize,
                    PathStrokeType::JointStyle::curved,
                    PathStrokeType::EndCapStyle::rounded
                )
            );
        }

        /** Draw the tick itself. **/
        if (isTicked)
        {
            Path path;
            path.addStar(
                bounds.getCentre(),
                5,
                bounds.getWidth() / 4.0f,
                bounds.getWidth() / 2.0f
            );

            const int tickColourId = (isEnabled)
                ? ToggleButton::tickColourId
                : ToggleButton::tickDisabledColourId;

            /** When drawing Components with a custom LookAndFeel, you always
                want to be sure to use the findColour() method on the Component
                itself. This gives you the flexibility to change a given colour
                for a specific Component, rather than the colour only being
                derived from the LookAndFeel's colours.
            **/
            g.setColour(component.findColour(tickColourId));
            g.fillPath(path);
        }

        if (!isEnabled)
            g.endTransparencyLayer();
    }

    /** The ComboBox can also be manipulated in our custom LookAndFeel too!

        Try overriding some of the ComboBox::LookAndFeelMethods here to create
        your own unique style.

        https://docs.juce.com/master/structComboBox_1_1LookAndFeelMethods.html
    **/
};

struct Demo : public Component
{
    TextButton   textButton;
    ToggleButton toggleButton;
    ComboBox     comboBox;

    CustomLookAndFeel customLookAndFeel;

    Demo()
    {
        textButton.setButtonText("Toggle Enablement");
        textButton.setToggleState(true, dontSendNotification);
        textButton.setBounds(150, 150, 200, 25);
        textButton.onClick = [this]() -> void
        {
            toggleButton.setEnabled(!toggleButton.isEnabled());
            comboBox.setEnabled(!comboBox.isEnabled());
        };
        addAndMakeVisible(textButton);

        /** ================================================================ **/

        toggleButton.setButtonText("Use Custom L&F");
        toggleButton.setBounds(150, 200, 200, 25);
        toggleButton.onClick = [this]() -> void
        {
            if (toggleButton.getToggleState())
                setLookAndFeel(&customLookAndFeel);
            else
                setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());

            // Refresh the ColourScheme for the purposes of the demo
            comboBox.onChange();
        };
        addAndMakeVisible(toggleButton);

        /** ================================================================ **/

        comboBox.addItemList({"Dark", "Grey", "Light", "Midnight"}, 1);
        comboBox.onChange = [this]() -> void
        {
            static const LookAndFeel_V4::ColourScheme schemes[4] = {
                LookAndFeel_V4::getDarkColourScheme(),
                LookAndFeel_V4::getGreyColourScheme(),
                LookAndFeel_V4::getLightColourScheme(),
                LookAndFeel_V4::getMidnightColourScheme()
            };

            if (auto * const lf = dynamic_cast<LookAndFeel_V4*>(&getLookAndFeel()))
            {
                lf->setColourScheme(schemes[comboBox.getSelectedId() - 1]);

                /** Normally setting a LookAndFeel for a Component will trigger
                    this call and all of its children will be updated... but
                    when you're keeping the same LookAndFeel and only updating
                    one of its values or something similar, you will need to
                    make sure the top level component using the LookAndFeel
                    sends this change message.
                **/
                sendLookAndFeelChange();
            }
        };
        comboBox.setBounds(150, 250, 200, 25);
        comboBox.setSelectedId(1);
        addAndMakeVisible(comboBox);

        /** ================================================================ **/

        setSize(500, 500);
    }

    /** ==================================================================== **/

    ~Demo()
    {
        setLookAndFeel(nullptr);
    }

    /** ==================================================================== **/

    /** We can use the new ColourScheme features that are present in JUCE's
        LookAndFeel_V4 to grab the ColourScheme colours for certain generic
        attributes, such as the default window background colour.
    **/
    void paint(Graphics &g)
    {
        using ColourScheme = LookAndFeel_V4::ColourScheme;

        if (auto * const lf = dynamic_cast<LookAndFeel_V4*>(&getLookAndFeel()))
        {
            const ColourScheme scheme = lf->getCurrentColourScheme();
            g.fillAll(scheme.getUIColour(ColourScheme::windowBackground));
        }
    }
};

