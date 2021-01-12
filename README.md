# Experiments with Qt 6.0 QProperty

This repository contains some performance tests for QProperty.
PubSub.(h|cpp) contains an experimental alternative implementation.

# Generating Graphs

Running the application creates some .txt files. Copying them
to the "latex" folder and executing "latexmk -pdf report" inside
the latex folder generates the graphs in report.pdf.

# Code Duplication

There is a lot of copy-paste code because I did not figure out 
how to capture a compile-time specified number of properties
by reference into a lambda. Any help appreciated.
