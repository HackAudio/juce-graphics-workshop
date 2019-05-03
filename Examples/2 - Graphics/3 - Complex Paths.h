/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             Complex Paths
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

/** The Path class can be used to create more complex vector shapes.

    In this demo we will go over constructing our own unique shapes using
    lines and bezier curves.

    https://docs.juce.com/master/classPath.html
**/
struct Demo : public Component
{
    Demo()
    {
        setSize(500, 500);
    }

    /** ==================================================================== **/

    void paint(Graphics& g) override
    {
        /** Path classes are usually allocated on the stack, and don't need
            to be kept around unless you're creating shapes that have many
            points.
        **/
        Path path;

        /** The Graphics and Path classes share a lot of their API, for example
            the simple methods for drawing shapes using the Graphics class also
            have similar methods in the Path class.

            Path extends the available shape options to include drawing
            triangles, stars, pie-segments, arcs, and even speech bubbles.

            Rectangles:
            https://docs.juce.com/master/classPath.html#af63b8419acedc43ced5c79578be0f0ea

            Triangles:
            https://docs.juce.com/master/classPath.html#a1508e0d3dd2048dc5304721bee6ee2c1

            Quadrilaterals:
            https://docs.juce.com/master/classPath.html#aced2dafcb8a12f73fcffe032def577be

            Arcs:
            https://docs.juce.com/master/classPath.html#a1486b650a586f1be84e2decc47bcc844

            Pie Segments:
            https://docs.juce.com/master/classPath.html#a6c09cddf0316e722af69129c6738be34

            Arrows:
            https://docs.juce.com/master/classPath.html#abd4b324342831ba94b8882b5310e5ce4

            Stars:
            https://docs.juce.com/master/classPath.html#a90d9510c290d3028f5115d7759472811

            Speech Bubbles:
            https://docs.juce.com/master/classPath.html#a755bbc5fd9a2872ed164cb9ca111c470
        **/
        path.addRectangle(getLocalBounds().reduced(25));

        /** Path objects can be passed to the Graphics context to be filled in.
        **/
        g.setColour(Colours::violet);
        g.fillPath(path);

        /** When drawing a Path, the Graphics context will use all the points
            in the Path to fill in the shape.

            If you want to draw multiple shapes using the Path class, you must
            use multiple Path objects _or_ clear the Path object you're using
            before making any more draw calls with the Graphics context.
        **/
        path.clear();

        path.addStar(Point<float>(350.0f, 150.0f), 5, 30.0f, 90.0f);

        /** ================================================================ **/

        /** You can construct your own shapes using Path's methods for creating
            lines and bezier curves.

            The Path class will assume each subsequent line/curve is connected
            to the previous one, so you must start and end sub-paths to create
            disjointed shapes.

            When we close the subpath, a line will be added to connect the last
            point in the subpath back to the beginning point.

            When we fill this shape, it will be drawn as filled triangle.

            If you do not close the subpath JUCE will automatically do it for
            you, but you will need to explicitly call closeSubPath() if you plan
            on drawing multiple shapes using one Path object.
        **/
        path.startNewSubPath(Point<float>(50.0f, 50.0f));
        path.lineTo(Point<float>(175.0f, 50.0f));
        path.lineTo(Point<float>(175.0f, 175.0f));
        path.closeSubPath();

        /** ================================================================ **/

        /** We can create a second shape in the path by starting a new subpath
            and making more lines. This time we will use bezier curves to create
            an oblong shape.
        **/
        path.startNewSubPath(Point<float>(200.0f, 200.0f));

        /** The quadraticTo() method takes a single control point and an
            endpoint. The further the control point is the sharper and further
            out the curve will be.
        **/
        #if 1 // change to 0 to see the cubic bezier instead
          path.quadraticTo(
              Point<float>(275.0f, 275.0f), // control point
              Point<float>(200.0f, 400.0f)  // end point
          );

        /** The cubicTo() method takes two control points and an endpoint. JUCE
            will draw the line as a cubic bezier, performing cubic splines to
            each control point and finally to the end point.
        **/
        #else
          path.cubicTo(
              Point<float>(375.0f, 225.0f), // control point one
              Point<float>(100.0f, 275.0f), // control point two
              Point<float>(200.0f, 400.0f)  // end point
          );
        #endif

        /** ================================================================ **/

        /** When we fill the path, both the triangle and the oblong shape will
            be filled in.
        **/
        g.setColour(Colours::white);
        g.fillPath(path);

        /** ================================================================ **/

        /** Creates a stroke type with a thickness of 4.0f and default
            joint and end-cap styles.
        **/
        PathStrokeType stroke(2.0f);

        /**
        **/
        stroke.setJointStyle(PathStrokeType::JointStyle::curved);

        /**
        **/
        stroke.setEndStyle(PathStrokeType::EndCapStyle::rounded);

        /** Stroking the path will create outlines around our shapes we
            previously filled in.

            If we were to stroke the paths before filling the shapes, the fill
            would be drawn partially over top of the outline. Instead, here the
            outline is drawn partially over the fill since the outline's centre
            is aligned with the shape edges.
        **/
        g.setColour(Colours::black);
        g.strokePath(path, stroke);
    }
};

