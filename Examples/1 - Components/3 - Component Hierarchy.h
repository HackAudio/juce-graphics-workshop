/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Component Hierarchy
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

struct Demo : public Component
{
    Square redSquare;
    Square blueSquare;
    Square greenSquare;

    Demo()
    {
        setSize(500, 500);

        /** ================================================================ **/

        redSquare.colour = Colours::palevioletred;
        addAndMakeVisible(redSquare);

        /** centreWithSize() can be used for easy centring when the component is
            a child of a parent with non-zero size.

            https://docs.juce.com/master/classComponent.html#abb58dc5a1f89822e4a5dcae2a538a8a7
        **/
        redSquare.centreWithSize(250, 250);

        /** ================================================================ **/

        blueSquare.setBounds(125, 125, 125, 125);
        blueSquare.colour = Colours::skyblue;
        redSquare.addAndMakeVisible(blueSquare);

        /** ================================================================ **/

        greenSquare.setBounds(0, 0, 50, 50);
        greenSquare.colour = Colours::seagreen;

        #if 0 // change to 1 to make greenSquare a child of the demo instead
          addAndMakeVisible(greenSquare);
        #else
          redSquare.addAndMakeVisible(greenSquare);
        #endif
    }
};

