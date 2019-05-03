# JUCE Graphics Workshop

## Introduction

This workshop was created for Belmont University in Spring 2019 as an
introduction for students into working with graphical user interfaces in the
JUCE C++ library.

The workshop covers a range of topics ranging from drawing graphics on the
screen to setting up component hierarchies and handling user interface
events.

## Requirements

### macOS

- Xcode 9.0 or higher, Xcode Developer Tools must be installed

- macOS 10.11 or higher

### Windows

- Visual Studio 2013 or higher

- Windows 7 or higher

### Linux

- GCC 5.0 or higher recommended

## Installing

This repository requires JUCE be installed in the proper directory.

On Windows this directory is `C:\JUCE`.

On macOS and Linux (case sensitive!) this directory is `~/JUCE` where `~` is the
HOME directory of your account.

You can download the JUCE repository from https://github.com/WeAreROLI/JUCE.git

## Building & Running

The Projucer project management application is required for running the demo
code. IDE project files can be found in `JUCE/extras/Projucer/Builds` which
will allow you to compile the Projucer.

The demo code included in the repository as C++ headers with JUCE's PIP format
metadata. These PIP headers may be opened directly with the Projucer to easily
create a new project using the contained C++ code.

When a PIP is opened the Projucer can either run a live build (Projucer's
live build engine must be installed) or the Projucer can build the relevant IDE
project files to create a project out of the PIP. Every PIP in the repo has the
following IDEs enabled:

- Xcode (9.0+ recommended)
- Visual Studio 2013
- Visual Studio 2015
- Visual Studio 2017
- Visual Studio 2019
- Linux Makefiles

## Live Build

The Projucer's Live Build feature will allow you to build each example project
right from the Projucer!

To enable live building, you must first download the Live Build Engine. This can
be done by opening any example, and selecting the live build tab (designated by
the wrench/screwdriver icon) which is under the project's name.

For the purposes of the demo, you will likely want to enable continuous
compilation in the Live Build Engine. This can be done from the Build menu of
the Projucer when a project is open. You will have to enable this option each
time you open one of the examples.

When using Live Building, the Projucer will show all Component subclasses it
finds in the project under the Components panel in the left-hand side. You can
launch the example by clicking on the "play" icon to the right of the Component
labeled "Demo". Each example uses a "Demo" Component for its contents.
