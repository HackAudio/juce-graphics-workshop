/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Image Basics
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
    Image selectedImage;

    Demo()
    {
        /** Here we create a simple file chooser that is only allowed to open
            PNG or JPEG files.

            https://docs.juce.com/master/classFileChooser.html
        **/
        FileChooser fileChooser("Open An Image", File(), "*.png;*.jpeg;*.jpg");

        /** browseForFileToOpen() will return true if the user didn't hit
            "cancel" in the file picker window.
        **/
        if (fileChooser.browseForFileToOpen())
        {
            /** The ImageCache class is useful for storing images in memory,
                especially if they don't get used very often and can be unloaded
                when not in use.

                The class provides several functions to easily load an image,
                which is what we use it for here.

                https://docs.juce.com/master/classImageCache.html
            **/
            selectedImage = ImageCache::getFromFile(fileChooser.getResult());
        }

        /** An Image is said to be "valid" if it has a block of allocated data
            assocaited with it. If the Image isn't pointing to any data, the
            isValid() call will return false.

            Here we grab the width and height of our Image - if we successfully
            loaded one - and use it to set the size of our window.

            https://docs.juce.com/master/classImage.html#a761214d2fa016e3e793b5a2d6b8b85ec
        **/
        if (selectedImage.isValid())
            setSize(selectedImage.getWidth(), selectedImage.getHeight());
        else
            setSize(500, 500);
    }

    /** ==================================================================== **/

    void paint(Graphics &g) override
    {
        /** You can only draw an image if it is valid! Otherwise the graphics
            class will bring up an assertion.
        **/
        if (selectedImage.isValid())
            g.drawImageAt(selectedImage, 0, 0);
    }
};

