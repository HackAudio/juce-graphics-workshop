/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Text
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

    void paint(Graphics& g) override
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));

        Rectangle<int> bounds = getLocalBounds().withHeight(25);

        g.setColour(Colours::whitesmoke);
        g.setFont(Font(24.0f));

        /** ================================================================ **/

        /** The drawText() method is the simplest way of getting text onto the
            screen with JUCE. It only takes a String, a given area, and a
            Justification argument.

            If the text ends up too long to fit in the given arean, JUCE will
            draw as many characters as it can followed by "...".

            https://docs.juce.com/master/classGraphics.html#a0c3c9a14db0d2c69c43a6c7b225a2b4d
        **/
        g.drawText("Hello World!", bounds, Justification::centredLeft);

        bounds.translate(0, 30);

        /** ================================================================ **/

        /** JUCE can also draw fitted text: the text will be horizontally
            squashed to fit the given area. If it still cannot fit in the area
            after being squashed down, JUCE will draw as many characters as it
            can followed by "...".

            https://docs.juce.com/master/classGraphics.html#a295421ac744e2948a59c760fce420ecb
        **/
        g.drawFittedText(
            /** In C++ you can concatenate string literals together as long as
                there are no other keywords or operators between them.
                For example:

                    "This is a "
                    "brand new sentence"

                Will yield the string literal "This is a brand new sentence".

                Note that placing each literal on a new line does not actually
                insert newlines into the string itself. You must use the \n
                character or type out the string as a raw string (see below).
            **/
            "Hello World! This text is going to be too long to fit inside our "
            "window so JUCE will truncate it to fit within the area that we "
            "gave it to work with",
            bounds,
            Justification::centredLeft,
            1, // we didn't us newlines in our string so it is 1 line anyway
            0.0f // this value will manipulate the horizontal scaling
        );

        bounds.translate(0, 30);

        /** ================================================================ **/

        /** C++ raw strings (formatted by the R""(...)"" delimiters) are a great
            way to write large chunks of text as a string literal while also
            preserving newlines in the string.

            Note that our tabs are also even preserved in the resulting string,
            as well as the starting newline after the R""(.
        **/
        const String text = R""(
            Hello World!
            This is some multi-line text!
            Pretty cool, huh?
        )"";

        /** The multi-line text drawing method is a bit different from the other
            text drawing methods. Instead of an area, this takes a starting X
            position, a baseline Y position, and a maximum allowed width.

            The baseline position will align with the bottom of the characters
            on the first line of the string, so here we have to offset our
            bounds' Y position with the height of the font.

            https://docs.juce.com/master/classGraphics.html#aa300ad943b821866cb8f3be72859bab7
        **/
        g.drawMultiLineText(
            text,
            0,
            bounds.getY() + g.getCurrentFont().getHeight(),
            bounds.getWidth()
        );

        bounds.translate(0, 130);

        /** ================================================================ **/

        /** We can draw text boldened... **/
        g.setFont(g.getCurrentFont().boldened());
        g.drawText("Hello World!", bounds, Justification::centredLeft);
        bounds.translate(0, 30);

        /** ...in italics... **/
        g.setFont(g.getCurrentFont().italicised());
        g.drawText("Hello World!", bounds, Justification::centredLeft);
        bounds.translate(0, 30);

        /** ...underlined... **/
        g.setFont(g.getCurrentFont().withStyle(Font::underlined));
        g.drawText("Hello World!", bounds, Justification::centredLeft);
        bounds.translate(0, 30);

        /** ...and more!

            https://docs.juce.com/master/classFont.html
        **/

        /** ================================================================ **/

        /** The AttributedString class can be used to create text layouts that
            have varying colours and fonts.

            https://docs.juce.com/master/classAttributedString.html
        **/
        AttributedString attribString;
        attribString.append("One text! ", Font(24.0f), Colours::white);
        attribString.append("Two text! ", Font(12.0f));

        /** The font and colour used are based on previous calls on the
            AttributedString. Here we want our coloured text to use a 24pt Font
            again, so must pass in a new Font object that updates the
            AttributedString's current Font.
        **/
        attribString.append("Red text! ", Font(24.0f), Colours::palevioletred);
        attribString.append("Blue text!", Colours::skyblue);

        /** Because the AttributedString manages its own layout, you pass it
            the Graphics context instead of the other way around. The
            AttributedString class will call the context multiple times to draw
            the different parts of the text layout.
        **/
        attribString.draw(g, bounds.toFloat());
    }
};

