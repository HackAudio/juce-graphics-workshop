/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Affine Transforms
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

    /** You can use the AffineTransform class to apply transformations to the
        Graphics context when you're painting to the screen.

        The Graphics context maintains its own AffineTransform member which can
        be manipulated via Graphics::addTransform(). Each AffineTransform passed
        to this method is applied _on top_ of the Graphics context's previous
        transform. If you add a rotation transform, then a skew transform, the
        final result is that the context will be rotated and skewed.

        When a transform is applied, it applies to the entire clip region that
        the context currently has. So if you were to add a rotation transform,
        its as if you took the entire contents of our window and rotated it
        around the top left point (the origin) of the view.

        Some Graphics methods allow you to pass an AffineTransform object so
        that you don't have to maintain state changes with
        Graphics::addTransform(). This transform will be applied after the text,
        shapes, etc. have been converted to paths and before those paths are
        rasterized.
    **/
    void paint(Graphics& g) override
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));

        g.setOrigin(Point<int>(100, 100));

        g.setColour(Colours::palevioletred);
        g.fillRect(Rectangle<int>(0, 0, 100, 100));

        /** ================================================================ **/

        /** We rotate our context by (π/7) around our origin. This puts this
            blue rectangle facing downwards and right from our original red
            rectangle.
        **/
        g.addTransform(AffineTransform().rotated(M_PI / 7.0f));
        g.setColour(Colours::skyblue);
        g.fillRect(Rectangle<int>(0, 0, 100, 100));

        /** ================================================================ **/

        /** We can add a translation to line up this violet rectangle with the
            end corner of our previous, blue rectangle. Remember that the
            context will still have the rotation applied here as well.
        **/
        g.addTransform(AffineTransform().translated(100.0f, 100.0f));
        g.setColour(Colours::violet);
        g.fillRect(Rectangle<int>(0, 0, 100, 100));

        /** ================================================================ **/

        /** Finally, we scale our context down by 50%. All shapes we draw will
            be scaled down this much too (so our rectangle is really 50px by
            50px in size), and our context's area will only be half as large.
        **/
        g.addTransform(AffineTransform().scaled(0.5f, 0.5f));
        g.setColour(Colours::lightyellow);
        g.fillRect(Rectangle<int>(0, 0, 100, 100));

        /** ================================================================ **/

        /** If we shear the context along its x axis, our next rectangle will
            appear as a rhombus. The shear values are percentages of the total
            size of the context area.
        **/
        g.addTransform(AffineTransform().sheared(3.0f, 1.0f));
        g.setColour(Colours::palegreen);
        g.fillRect(Rectangle<int>(100, 0, 100, 100));
    }
};

