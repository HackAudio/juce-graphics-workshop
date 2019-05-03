/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Grid
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

        setSize(500, 500);
    }

    /** ==================================================================== **/

    /** Grid is a layout system that originated in the web development world
        and is used extensively when writing CSS3 for websites. JUCE implements
        its own version of this layout system and makes it available for
        Components.

        The Grid works similarly to FlexBox in that it defines an item type
        (GridItem) and uses an array of those items to lay out components.
        Unlike FlexBox though, you need to specifically tell the Grid the
        properties of its layout: how the columns and rows will be organized.

        The layout of a Grid is done using the TrackInfo class. TrackInfo
        is constructed using a given type (either Grid::Px for absolute size, or
        Grid::Fr for fractions of free space) and passed to the Grid. The Grid
        will consider each TrackInfo object when applying its layout.

        Fractions of free space are allotted after all absolute sizes have been
        used up. For example, you can split a 100x100 box so that the first row
        is Px(40) and the second row is Fr(1). This second row will be given
        60px worth of space when the Grid performs its layout.

        https://docs.juce.com/master/classGrid.html

        https://docs.juce.com/master/structGrid_1_1TrackInfo.html

        https://docs.juce.com/master/classGridItem.html
    **/
    void resized() override
    {
        Grid grid;

        #if 0 // change to 1 to enable gaps
          grid.columnGap = Grid::Px(20);
          grid.rowGap    = Grid::Px(20);
        #endif

        /** ================================================================ **/

        /** You can set up your grid using the template row/column arrays.

            The tracks can be specified in pixels, fractions of free space, or
            be aligned to specific named lines.

            You can also the auto rows/columns members to set one TrackInfo type
            for each and allow the Grid to automatically do the rest for you.

            https://docs.juce.com/master/structGrid_1_1TrackInfo.html
        **/
        #if 0 // change to 1 to disable auto rows/columns
          grid.templateRows.add(Grid::TrackInfo(Grid::Fr(2)));
          grid.templateRows.add(Grid::TrackInfo(Grid::Fr(1)));
          grid.templateRows.add(Grid::TrackInfo(Grid::Fr(3)));
          grid.templateRows.add(Grid::TrackInfo(Grid::Fr(1)));

          grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
          grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
          grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
          grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
        #else
          grid.autoRows    = Grid::TrackInfo(Grid::Fr(1));
          grid.autoColumns = Grid::TrackInfo(Grid::Fr(1));
        #endif

        /** ================================================================ **/

        int row = 0;
        int col = 0;

        for (Component * const child : getChildren())
        {
            GridItem item;

            /** Be sure to set the associatedComponent pointer when adding
                items!
            **/
            item.associatedComponent = child;

            /** We can increment our row/col variables so that the squares
                cascade horizontally down the grid.
            **/
            item.setArea(++row, ++col);

            grid.items.add(item);
        }

        /** Calling Grid::performLayout() will run the Grid layout
            calculations and update the associated component for each GridItem
            in the items array.
        **/
        grid.performLayout(getLocalBounds());
    }
};

