/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Component Painting
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
    Colour colour;

    void paint(Graphics &g) override
    {
        g.fillAll(colour);
    }
};

/** When components are painted, they have their paint() method called first
    before JUCE continues on to draw that component's children. When iterating
    children each child will have its paint() method called, and then all of its
    children will be painted.

    After each component has its children painted its paintOverChildren() method
    will be called to allow it to overlay graphics over top of its children.
**/
struct Demo : public Component
{
    Square square;

    Demo()
    {
        setSize(500, 500);

        square.colour = Colours::palevioletred;
        addAndMakeVisible(square);
        square.centreWithSize(250, 250);
    }

    /** ==================================================================== **/

    /** Any painting that happens here in paint() will be covered up by the
        component's children.
    **/
    void paint(Graphics &g) override
    {
        g.setColour(Colours::skyblue);
        g.fillRect(getLocalBounds().reduced(50));
    }

    /** ==================================================================== **/

    /** Any painting that happens in paintOverChildren() is allowed to draw
        over top of the children, but is still constrained to the parent
        component's area.
    **/
    void paintOverChildren(Graphics &g) override
    {
        g.setColour(Colours::white);
        g.drawText("Hello World!", square.getBounds(), Justification::centred);
    }
};

