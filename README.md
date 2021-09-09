# Contents:
* About
* How to use
* Future Plans
* Documentation

# About:
CGI (Console Graphics Interface) is a Windows only c++ library 
that allows for a wide array of features. The library has a 
wide variety of features to cover the redundancies between 
projects. 

If you come up with ideas/implementations to update here, be
sure to add your name to the credits using the same format 
before pushing :)

# How to use:
Setup should be simple enough, Just add this project to the
project that youre working on, then right click on your 
project and go to Add -> Reference -> Select CGI

Alternatively, you can build the library separately and then
move cgi.lib to the same directory as your solution

All functionality will be part of the cgi namespace so
that the code is more organized.

Dont forget to add the lib file next to the EXE if running
outside of visual studio.

# Future plans:

These are mostly ideas/suggestions, *might* get implemented:
* Multithreaded Audio Interface
	- Multichannel audio (like NES probably)
	- Audio loading from file
		- Format: 
			COUNT::NOTE:SCALE:DURATION::...
			 int ::enum: int :   int  ::...
		- Example:
			3:A:7:100::C#:7:150::E:7:200
			3:W:0:100::W :0:050::W:0:000

* Performance improvements
	- Right now we load each row into a buffer 
	  then we add the buffer to the a string and print that

	  An Optimization could be to get rid of the intermediate
	  buffer somehow, or better yet, instead of storing each
	  color into an array if we had direct access to the buffer
	  string that would solve all the problems

	- A faster way to load images on to our buffer would also
	  be a much needed optimization but it completely depends
	  on how the buffer works

	- We have a function called PerformanceTest that returns 
	  the time a function took to execute in milliseconds. 
	  The value for all the draws to the buffer as well as the 
	  swapping should be below 16ms ideally

* Game Class that draws asynchronously
	- Not a string necessity because the game class depends on 
	  the kind of game made, this depends more on the entity 
	  component system. If we do implement this we should try 
	  to make the draw calls on a separate thread so that we our 
	  main thread calculations arent paused

* An input system
	- Something that reads the entire keyboard state and then
	  polls is as required

* An error messaging and debugging system
	- We already print colored text onto the buffer but we also
	  need a separate buffer that somehow displays the output 
	  without disturbing the console. A shortcut to generate a 
	  log dump would also be very useful
