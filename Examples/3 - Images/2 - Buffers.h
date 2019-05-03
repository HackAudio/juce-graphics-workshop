/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Image Buffers
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
    Image buffer;

    Demo()
    {
        setSize(500, 500);

        /** ================================================================ **/

        /** We can create a new Image here, which will allocate the Image's
            pixel data based on the format and size that we provide.
        **/
        buffer = Image(
            /** The image will have red, green, blue, and alpha channels. **/
            Image::PixelFormat::ARGB,
            /** The image will match the size of our component. **/
            500, 500,
            /** We leave the image data uninitialised since we will be drawing
                into it and filling the entire area.
            **/
            false
        );

        /** ================================================================ **/

        /** We can create a Graphics context using an Image object. The context
            will have its clip region set to the size of the Image, and anything
            drawn using the context will be written into the image's pixel data.
        **/
        Graphics g(buffer);

        g.fillAll(Colours::deepskyblue);
        g.setColour(Colours::white);
        g.setFont(48.0f);
        g.drawText("Hello World!", g.getClipBounds(), Justification::centred);
    }

    /** ==================================================================== **/

    void paint(Graphics& g) override
    {
        if (buffer.isValid())
            g.drawImageAt(buffer, 0, 0);
    }
};

