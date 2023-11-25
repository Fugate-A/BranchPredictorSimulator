-----------------------------------------------------------------------------------------------------------------------------
This is a gshare Branch Predictor Simulator Project made for the 
Computer Architecture course at the University of Central Florida

Professor Suboh Suboh
Due: 11/24/2023
Student: Andrew Fugate, CpE undergrad

This code and associated files will be apart of a final report. 

This code will run with provided test inputs in the format of:
    75401028 t
    75401024 n

All test files provided are viewable on GitHub and follow the above format.
The main 2 files are the mcf_trace.txt and gobmk_trace.txt files. 
The other ValidationRuns.txt is a test case file but is NOT in the 
acceptable format to be used as a command line input. This file
provides the M and N parameteres to be used with the other 2 trace
files and shows the expected misprediction ratio (%) so you know the code is
running and outputing as intended.

To compile this code please refer to the makefile.txt that was also delivered
with the report; or access the code base on GitHub @ 
https://github.com/Fugate-A/BranchPredictorSimulator  

-----------------------------------------------------------------------------------------------------------------------------

Output format:

    <M> <N> <MispredictionRatio (%)>

    For example:
        M: 5    N: 0    Misprediction Ratio: 0.66%

-----------------------------------------------------------------------------------------------------------------------------