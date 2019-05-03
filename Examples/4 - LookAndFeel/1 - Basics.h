/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             LookAndFeel Basics
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

struct Demo : public Component
{
    Label label;
    Slider slider;
    TextButton textButton;
    ComboBox comboBox;

    LookAndFeel_V1 lookAndFeel1;
    LookAndFeel_V2 lookAndFeel2;
    LookAndFeel_V3 lookAndFeel3;
    LookAndFeel_V4 lookAndFeel4;

    Demo()
    {
        label.setEditable(true);
        label.setText("Edit me!", sendNotification);
        label.setBounds(0, 0, 200, 25);
        addAndMakeVisible(label);

        /** We can set colours for a Component so that it will always use the
            same colour for drawing specific parts of itself. Here we set the
            background colour of the Label to always be black and its text
            colour to always be white.

            setColour() takes any integer value for the ID, but most painting
            routines for widgets will only look for ColourIds that are related
            to the given widget (such as Label::ColourIds for our Label here).
        **/
        label.setColour(Label::backgroundColourId, Colours::black);
        label.setColour(Label::textColourId, Colours::white);

        /** ================================================================ **/

        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setBounds(0, 75, 300, 50);
        addAndMakeVisible(slider);

        /** ================================================================ **/

        textButton.setButtonText("Click Me!");
        textButton.setBounds(0, 150, 200, 25);
        addAndMakeVisible(textButton);

        /** ================================================================ **/

        comboBox.addItem("Version 1", 1);
        comboBox.addItem("Version 2", 2);
        comboBox.addItem("Version 3", 3);
        comboBox.addItem("Version 4", 4);
        comboBox.setBounds(0, 250, 200, 50);
        addAndMakeVisible(comboBox);

        /** We can change the LookAndFeel for a Component by passing a new
            pointer to the setLookAndFeel() method. The LookAndFeel object will
            not be managed by the Component, so if you have heap allocated the
            LookAndFeel you will be responsible for deleting it.
        **/
        comboBox.onChange = [this]() -> void
        {
            switch (comboBox.getSelectedId())
            {
                case 1: setLookAndFeel(&lookAndFeel1); break;
                case 2: setLookAndFeel(&lookAndFeel2); break;
                case 3: setLookAndFeel(&lookAndFeel3); break;
                case 4: setLookAndFeel(&lookAndFeel4); break;
            }
        };

        /** ================================================================ **/

        /** The LookAndFeel objects can have specific colours set for them as
            well, and in fact most of the default JUCE ones will.

            Here we can set the colour for the TextButton::buttonColourId to be
            red, so that when "Version 3" is selected from the ComboBox our
            button will appear in red.
        **/
        lookAndFeel3.setColour(
            TextButton::buttonColourId,
            Colours::palevioletred
        );

        /** ================================================================ **/

        setSize(500, 500);
    }

    /** ==================================================================== **/

    ~Demo()
    {
        /** Setting the LookAndFeel for Components (or even for the static
            LookAndFeel::setDefaultLookAndFeel() method) keeps a weak reference
            around to that LookAndFeel. JUCE will assert if you do not un-set
            any LookAndFeels that you may have set previously.
        **/
        setLookAndFeel(nullptr);
    }

    void paint(Graphics &g) override
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));
    }
};

