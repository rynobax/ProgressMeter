# ProgressMeter 
A C++ progress meter.  In your program, if you can calculate the number of times a certain point will be reached, you can put a call to ProgressMeter::update() at that point, and a command line progress meter will accurately track the progress.  To initialize the progress meter, you must call the constructor to set the max count and banner format.

This program was developed with the goal of writing well organized and documented code.

Counter.cpp is an example program that uses the progress meter.
