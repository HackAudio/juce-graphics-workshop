/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Component Basics
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
        /** A Component can be given a name and ID to use for identification,
            drawing, etc.
        **/
        setName("Demo Component");
        setComponentID("DemoComponent");

        /** ================================================================ **/

        /** Components have an enablement status which can be used for various
            purposes.

            By default, the enablement status does not affect whether a
            component is allowed to receive mouse or keyboard events. Classes
            such as Slider, TextButton, Label, etc. incorporate this logic, but
            any custom components will need to check Component::isEnabled() to
            decide if they are allowed to handle events or not.

            Often you will want to have your drawing routines take the
            enablement status into account, giving the user visual cues as to
            whether or not a certain control is able to be interacted with.
        **/
        #if 0 // change to 1 to disable the component
          setEnabled(false);
        #endif

        /** ================================================================ **/

        /** Every Component contains a NamedValueSet for properties. The
            properties can be accessed using an Identifier, and their value can
            be set to any type available in juce::var.
        **/
        #if 1 // change to 0 to remove the initial greeting
          getProperties().set("Greeting", "Hello world, ");
        #endif

        /** ================================================================ **/

        /** We can set the size of our component using setSize() or setBounds().
            Here we just set the size and leave our position at default (0, 0)
            since our component is made to take up the whole window.
        **/
        setSize(500, 500);
    }

    /** ==================================================================== **/

    /** Components have certain callbacks to indicate when certain state has
        changed, such as if their parent component has been changed or removed.
    **/
    void parentHierarchyChanged() override
    {
        /** Components have a visibility flag to decide whether they should be
            shown on screen or not. When the component is not visible, none of
            its paint methods will be called and it will not be allowed to
            receive mouse or keyboard events.

            Components start out invisible, and are usually added to parents
            using the Component::addAndMakeVisible() method.

            Because that happens in our demos, we can only reliably set the
            visibility _after_ we've already been added to the parent window
            and had our visibility set.
        **/
        #if 0 // change to 1 to hide the component
          setVisible(false);
        #endif
    }

    /** ==================================================================== **/

    void paint(Graphics& g) override
    {
        /** We can check whether the component is enabled or not and use that
            to determine which colour we should draw.
        **/
        if (isEnabled())
            g.setColour(Colours::cadetblue);
        else
            g.setColour(Colours::palevioletred);

        /** Component::getLocalBounds() will return the bounds of the component,
            but with a position of {0, 0}. This is useful when you're working
            with graphics or child components that you know are relative to a
            given parent component.

            https://docs.juce.com/master/classComponent.html#aecc40b8a244527fcb142213151b6d00d
        **/
        g.fillRect(getLocalBounds());

        /** ================================================================ **/

        /** We can access the "Greeting" property we previously set and get its
            string representation. We'll set our text variable to this to begin
            our sentence.
        **/
        String text = getProperties()["Greeting"].toString();

        /** We can construct the rest of the sentence by stating the name of the
            component, which we previously set in the constructor.
        **/
        text += "I am " + getName() + "!";

        g.setFont(Font(16.0f));
        g.setColour(Colours::white);
        g.drawText(
            text,
            getLocalBounds(),
            Justification::centred,
            true
        );
    }
};

