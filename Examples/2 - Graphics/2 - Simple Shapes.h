/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Simple Shapes
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

/** Here we demonstrate the various methods to easily draw a shape using a
    Graphics object.

    https://docs.juce.com/master/classGraphics.html
**/
struct Demo : public Component
{
    Demo()
    {
        setSize(500, 500);
    }

    /** ==================================================================== **/

    /** Graphics are drawn procedurally, so the order in which you draw the
        shapes will match the back-to-front order in which they appear.
    **/
    void paint(Graphics& g) override
    {
        /** The Graphics class provides easy methods for filling in lists of
            rectangles or drawing checkerboards.

            https://docs.juce.com/master/classGraphics.html#af5cf5f78e8acc01c30f9f181eedacf2c

            https://docs.juce.com/master/classGraphics.html#aa21f94a026bf57a86423a71c84907751
        **/
        g.fillCheckerBoard(
            getLocalBounds().toFloat(),
            10.0f,
            10.0f,
            Colours::darkgrey,
            Colours::grey
        );

        /** ================================================================ **/

        /** You can instruct the Graphics object to draw various types of shapes
            like rectangles, rounded rectangles, ellipses, lines, and more.

            Using Graphics::setColour() will set a single-colour fill that will
            be used for any subsequent Graphics calls.
        **/
        g.setColour(Colours::palevioletred);
        g.fillRect(Rectangle<int>(50, 50, 50, 50));

        g.setColour(Colours::palegoldenrod);
        g.fillEllipse(Rectangle<float>(100.0f, 100.0f, 100.0f, 100.0f));

        g.setColour(Colours::skyblue);
        g.drawLine(
            Line<float>(
                getLocalBounds().getTopLeft().toFloat(),
                getLocalBounds().getBottomRight().toFloat()
            ),
            4.0f
        );

        g.setColour(Colours::violet);
        g.drawArrow(
            Line<float>(
                Point<float>(300.0f, 50.0f),
                Point<float>(400.0f, 50.0f)
            ),
            2.0f,
            10.0f,
            10.0f
        );

        /** ================================================================ **/

        /** The "draw____" methods simply draw the outline of a shape, rather
            than filling it in.

            The outline of the shape will be aligned so its centre is on the
            edges of the shape's bounds, so you should always account for the
            outline width when drawing shapes!
        **/

        g.setColour(Colours::white);
        g.drawRect(Rectangle<int>(75, 75, 75, 75));

        g.setColour(Colours::lightpink);
        g.drawEllipse(Rectangle<float>(150.0f, 275.0f, 200.0f, 200.0f), 2.0f);
    }
};

