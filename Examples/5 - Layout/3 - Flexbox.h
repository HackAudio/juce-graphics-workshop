/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Flexbox
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

    /** ==================================================================== **/

    /** Flexbox is a layout system that originated in the web development world
        and is used extensively when writing CSS3 for websites. JUCE implements
        its own version of this layout system and makes it available for
        Components.

        https://docs.juce.com/master/classFlexBox.html

        https://docs.juce.com/master/classFlexItem.html
    **/
    void resized() override
    {
        /** FlexBox holds many members for changing the alignment,
            justification, and other attributes of the layout.

            It has an Array<FlexItem> that you can add items to to define what
            will be affected in the layout. When FlexBox performs a layout, all
            items in the array will be considered in order (unless explicit
            orders are specified in the FlexItems themselves).
        **/
        FlexBox flexbox;

        /** The FlexBox will only lay out items according to a single axis of
            direction, either rows or columns. It does, however, support
            reversal of this axis.
        **/
        #if 0 // change to 1 to use columns for the flex direction
          flexbox.flexDirection =
            #if 0 // change to 1 for reversed columns
              FlexBox::Direction::columnReverse;
            #else
              FlexBox::Direction::column;
            #endif
        #else
          flexbox.flexDirection =
            #if 0 // change to 1 for reversed rows
              FlexBox::Direction::rowReverse;
            #else
              FlexBox::Direction::row;
            #endif
        #endif

        for (Component * const child : getChildren())
        {
            FlexItem flexItem;

            /** By default FlexItems don't include any size information other
                than being allowed to shrink if needed.

                Here we set the flexGrow property to 1.0f to allow the items
                to grow to 100% of the size required.

                Using explicit width/height constraints is also supported by
                FlexItem.
            **/
            flexItem.flexGrow = 1.0f;

            /** Each FlexItem can control a Component's bounds or the bounds
                of another FlexBox. Be sure to set either the
                associatedComponent or associatedFlexBox pointer before adding
                the FlexItem to your items array.
            **/
            flexItem.associatedComponent = child;

            /** The FlexItem::Margin class is similar to a BorderSize<float>
                class in that it defines a given margin/border to leave around
                each side of a rectangle. The default constructor for this class
                will assign 0.0f for each margin, but setting some margins will
                cause FlexBox to leave space around that edge of the given
                FlexItem.
            **/
            #if 0 // change to 1 to enable margins
              flexitem.margin = FlexItem::Margin(10);
            #endif

            flexbox.items.add(flexItem);
        }

        /** Calling FlexBox::performLayout() will run the FlexBox layout
            calculations and update the associated component for each FlexItem
            in the items array.
        **/
        flexbox.performLayout(getLocalBounds());
    }
};

