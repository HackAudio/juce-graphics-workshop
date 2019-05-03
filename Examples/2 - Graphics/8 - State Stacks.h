/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             State Stacks
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

    /** The Graphics context maintains a stack of its current state. You can
        use Graphics::saveState() to save the current state of the context,
        and use Graphics::restoreState() to go back to that last saved state
        when needed.

        You can only call restoreState() if you have previously saved state in
        the context. You should _always_ be sure you don't call saveState()
        without eventually popping the stack using restoreState().

        The Graphics::ScopedSaveState class is a helpful way to make sure you
        never leave an extra saved state behind. You can use it by creating a
        ScopedSaveState object on the stack, and once that object goes out of
        scope (your function, conditional statement, code block, etc. ends) it
        will call restoreState() on the graphics context for you. This makes it
        easy to section off state changes using brackets and simply creating
        a ScopedSaveState object at the top of each section.

        The data saved in the state includes fill type, font, clip region(s),
        affine transforms, transparency layers, origin, and image resampling
        quality settings.
    **/
    void paint(Graphics &g) override
    {
        g.fillAll(findColour(ResizableWindow::backgroundColourId));

        const StringRef      text          ("Hello World!");
        const Rectangle<int> rect          (0, 25, 250, 25);
        const Justification  justification (Justification::centred);

        /** Placing the ScopedSaveState here at the top ensures that when our
            paint() exit functions the graphics context will have the same exact
            state that it started with.
        **/
        Graphics::ScopedSaveState scopedSavedState(g);

        /** ================================================================ **/

        /** Here we draw some red text in a 24pt, bold font. We then save the
            state so these settings are saved in our state stack.
        **/
        g.setColour(Colours::palevioletred);
        g.setFont(Font(24.0f).boldened());
        g.drawText(text, rect, justification);
        g.saveState();

        /** ================================================================ **/

        /** We then change the colours and font, as well as move the context's
            origin 100px down and to the right.
        **/
        g.setColour(Colours::skyblue);
        g.setFont(Font(12.0f));
        g.setOrigin(Point<int>(100, 100));
        g.drawText(text, rect, justification);

        /** ================================================================ **/

        /** When we restore the state, we get our original colour, font, and
            origin back from when we drew the first line of text. If we set
            the origin to {30, 30} without restoring the state, our actual
            origin would end up at {130, 130} because our previous call to
            setOrigin() would still be part of the current state.
        **/
        g.restoreState();
        g.setOrigin(Point<int>(30, 30));
        g.drawText(text, rect, justification);
    }
};

