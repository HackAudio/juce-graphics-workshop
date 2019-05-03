/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Rectangle Slicing
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
    Square yellowSquare;
    Square violetSquare;

    Demo()
    {
        redSquare.colour = Colours::palevioletred;
        addAndMakeVisible(redSquare);

        blueSquare.colour = Colours::skyblue;
        addAndMakeVisible(blueSquare);

        greenSquare.colour = Colours::palegreen;
        addAndMakeVisible(greenSquare);

        yellowSquare.colour = Colours::lightyellow;
        addAndMakeVisible(yellowSquare);

        violetSquare.colour = Colours::violet;
        addAndMakeVisible(violetSquare);

        setSize(500, 500);
    }

    /** The Rectangle class provides methods that will remove and return a given
        area. This is useful when you want to create a layout using given pixel
        sizes (e.g. split a 500px wide area into five sections 100px wide).

        https://docs.juce.com/master/classRectangle.html
    **/
    void resized() override
    {
        /** Component::getLocalBounds() will return the bounds of the component,
            but with a position of {0, 0}. This is useful when you're working
            with graphics or child components that you know are relative to a
            given parent component.

            https://docs.juce.com/master/classComponent.html#aecc40b8a244527fcb142213151b6d00d
        **/
        Rectangle<int> bounds = getLocalBounds();

        /** You can use Rectangle::reduced() to return a rectangle that is
            shrunken (relative to its centre) by a given padding amount.

            The BorderSize class can be used as well if you want to use unique
            margin values for each side of a Rectangle (e.g. call the method
            BorderSize::subtractedFrom(const Rectangle&)).

            https://docs.juce.com/master/classRectangle.html#a5623a7886c63a08917b392c7bc1135a9
        **/
        #if 0 // change to 1 to apply padding to each square's bounds
          const int padding = 5;
        #else
          const int padding = 1;
        #endif

        /** ================================================================ **/
        /** Slice 25px off from the top for redSquare.

            https://docs.juce.com/master/classRectangle.html#a3fbd4e7e1df5336980fb7ec5e752a222
        **/
        redSquare.setBounds(
            bounds
                .removeFromTop(25)
                .reduced(padding)
        );

        /** ================================================================ **/

        /** Slice 125px off from the right for blueSquare.

            https://docs.juce.com/master/classRectangle.html#a67c1ae2bf4753bda71894271dc94b4f6
        **/
        blueSquare.setBounds(
            bounds
                .removeFromRight(125)
                .reduced(padding)
        );

        /** ================================================================ **/

        /** Slice 50px off from the bottom for greenSquare.

            https://docs.juce.com/master/classRectangle.html#a6f7d3a88adfc3b3bf699ca4ce5b9e6c0
        **/
        greenSquare.setBounds(
            bounds
                .removeFromBottom(50)
                .reduced(padding)
        );

        /** ================================================================ **/

        /** Slice 50px off from the left for yellowSquare.

            https://docs.juce.com/master/classRectangle.html#a6f09929fd89d447eb230c170446788ac
        **/
        yellowSquare.setBounds(
            bounds
                .removeFromLeft(50)
                .reduced(padding)
        );

        /** ================================================================ **/

        /** Set the violetSquare bounds using the remaining area. **/
        violetSquare.setBounds(bounds.reduced(padding));
    }
};

