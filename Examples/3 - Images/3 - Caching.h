/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Image Caching
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

struct Square : public Component
{
    void mouseDown(const MouseEvent &e) override
    {
        repaint();
    }

    void paint(Graphics &g) override
    {
        Random &random = Random::getSystemRandom();

        g.fillAll(Colour(
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt())
        ));
    }
};

struct Demo : public Component
{
    Square square;
    TextButton repaintParent;
    ToggleButton enableCache;

    Demo()
    {
        setSize(500, 500);

        addAndMakeVisible(square);
        square.centreWithSize(150, 150);

        repaintParent.setButtonText("Trigger Repaint");
        repaintParent.setBounds(125, 400, 250, 25);
        addAndMakeVisible(repaintParent);

        enableCache.setButtonText("Enable Cache");
        enableCache.setBounds(125, 450, 250, 25);
        addAndMakeVisible(enableCache);

        /** ================================================================ **/

        /** Clicking the repaint button will trigger a repaint *just* on the
            Demo component.
        **/
        repaintParent.onClick = [this]() -> void
        {
            repaint();
        };

        /** ================================================================ **/

        /** Clicking on the enable cache button will toggle whether the square
            is backed by a cached Image or not. When it is buffered to an Image
            cache, only repaints called directly on the Component will trigger
            the cache to update. Repaints triggered in the Component's parent
            will simply re-use the cached Image for efficiency.
        **/
        enableCache.onClick = [this]() -> void
        {
            square.setBufferedToImage(enableCache.getToggleState());
            repaint();
        };
    }

    /** ==================================================================== **/

    void paint(Graphics& g) override
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));

        g.setColour(Colours::white);
        g.setFont(48.0f);
        g.drawText(
            Time::getCurrentTime().toString(false, true),
            getLocalBounds().reduced(25),
            Justification::centredTop
        );
    }
};

