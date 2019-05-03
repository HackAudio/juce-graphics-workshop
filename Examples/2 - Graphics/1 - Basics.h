/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Graphics Basics
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
    void paint(Graphics &g) override
    {
        Random &random = Random::getSystemRandom();

        g.setColour(Colour(
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt())
        ));

        g.fillEllipse(getLocalBounds().toFloat());
    }
};

struct Demo : public Component
{
    Square square;

    Demo()
    {
        setSize(500, 500);

        /** ================================================================ **/

        /** This tells the component that the following mouse events should
            trigger the component to repaint itself:

                - mouse enter/exit
                - mouse click/double-click
                - mouse release

            We set it for both the Demo and Square Components here to allow
            click-to-repaint for each.
        **/
        square.setRepaintsOnMouseActivity(true);
        setRepaintsOnMouseActivity(true);

        /** ================================================================ **/

        /** Marking a component as "opaque" means that when it paints its covers
            its entire area.

            Because you cannot see "past" opaque components, JUCE can skip
            repainting any sections behind opaque components. When our square is
            marked as opaque, triggering a repaint on it does not cause any
            parts of the parent to be repainted.

            If a component is marked opaque but does _not_ paint its entire
            area, you will likely see black in its background or garbage pixel
            data.
        **/

        #if 0 // change to 1 to prevent parent from also repainting
          square.setOpaque(true);
        #endif

        /** ================================================================ **/

        addAndMakeVisible(square);
        square.centreWithSize(250, 250);
    }

    /** ==================================================================== **/

    void paint(Graphics& g) override
    {
        Random &random = Random::getSystemRandom();

        g.fillAll(Colour(
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt()),
            static_cast<uint8>(random.nextInt())
        ));
    }
};

