# README
* Overview
* Demo
* Requirements
* Installation
* Code style
## Overview
I created an epidemic simulator that takes user input for various parameters
and simulates the spread of the virus over time. A specified virus details how
many days an infected person is incubating (not yet infectious), how many
days they're infectious, and with what probability an infectious person
will infect their neighbors. 

## Demo
Each person (represented by a small circle) lines up along the outside of a circle.
After each day, every person moves to a new random location on the circle,
where they have a chance of infecting their right and
left neighbors if infectious.

<p align="center">
    <img src="https://i.imgur.com/QNCLxSN.gif" width="800" height="567">
</p>


Movement speed can be varied for a more fluid graph generation:

<p align="center">
    <img src="https://i.imgur.com/dGS5sfj.gif" width="800" height="567">
</p>

## Requirements
Running the epidemic simulator requires:
* 64-bit Microsoft Windows
* Cinder v0.9.1 and above (older versions may work but not guaranteed)
* CMake
* Visual Studio 2015

## Installation
* Install Visual Studio Community 2015 [here](https://my.visualstudio.com/Downloads?q=visual%20studio%202015&wt.mc_id=o~msft~vscom~older-downloads)
* Download Cinder [here](https://libcinder.org/download)
* Clone the repository using `git clone https://github.com/uiuc-fa20-cs126/final-project-jlivshots.git`
* Build and run with Clion or another C++ IDE

## Code Style
This project is written in accordance with the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
