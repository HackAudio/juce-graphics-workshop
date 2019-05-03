/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Fill Types
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
    Demo()
    {
        setSize(500, 500);
    }

    /** ==================================================================== **/

    /** The Graphics context can create fills using a single, solid colour _or_
        a colour gradient.

        The colour gradient takes a list of colours and maps it across the
        defined start and end points.

        https://docs.juce.com/master/classColourGradient.html
    **/
    void paint(Graphics& g) override
    {
        const Rectangle<int> rect1(0, 0, 250, 250);
        const Rectangle<int> rect2(250, 250, 250, 250);

        g.setColour(Colours::skyblue);
        g.fillRect(rect1);

        /** ================================================================ **/

        /** The colour gradient class manages a list of colours with given
            position values. The gradient will convert the relative positions of
            the colours to absolute coordinates between point1 and point2.
        **/
        ColourGradient gradient;

        #if 0 // change to 1 to turn the linear gradient into a radial gradient
          gradient.isRadial = true;
        #endif

        gradient.point1 = rect2.getTopLeft().toFloat();
        gradient.point2 = rect2.getBottomRight().toFloat();

        gradient.addColour(0.0 / 6.0, Colours::red);
        gradient.addColour(1.0 / 6.0, Colours::orange);
        gradient.addColour(2.0 / 6.0, Colours::yellow);
        gradient.addColour(3.0 / 6.0, Colours::green);
        gradient.addColour(4.0 / 6.0, Colours::blue);
        gradient.addColour(5.0 / 6.0, Colours::indigo);
        gradient.addColour(6.0 / 6.0, Colours::violet);

        g.setGradientFill(gradient);
        g.fillRect(rect2);
    }
};

