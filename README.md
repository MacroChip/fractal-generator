This project generates a fractal png based on a julia set of numbers.

To use this, you will need to have the boost libraries (tested on version 1.62.0). julia.cc generates the text file that defines each pixel and convert.java converts the text file to a png.

I don't fully remember the reasoning behind a lot of the choices I made in this project, but I do remember some. I had a hard time creating an image in c++ so I made a separate java program for that because I knew it was easy for me in Java. I did not know that there were nice ways of doing arg parsing so I made constants instead that have to be changed and recompiled every time. Change DIMENSION to be the height and width of your image, then change the same values in the java file. Change C_REAL AND C_IMAGINARY to get a different fractal.

That should be all that you need to run the program. Enjoy!

Additional information: I wrote this program to demonstrate a highly parallelizable task that could be implemented with thread pooling. This was for an independant study class where we took turns presenting parallelized programs.

Since each pixel can be computed separately, I leveraged an asio io_service to queue up each pixel's computation as work for the thread pool. The work class keeps the io_service alive until all work has finished.

I remember seeing a strange crash in the java program one time and I could not reproduce it. Somehow, I saw either a segfault or a stack trace from the internals of the java image creation. I think java uses the c or c++ library (libpng maybe?) that I was trying to use myself in my c++ program before I decided to use java. Let me know if you see this!

