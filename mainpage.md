# Bradipo Library Documentation

Welcome to the documentation for the Bradipo Library.

You can find the code here: [Source project](https://github.com/flowibbia/data_structure)

## Introduction to the Library

Is a data structure library, contains Tree, Graph and Heap implementation.
The name of this library is Bradipo ( Sloth in English) , as it's not an efficient and complete library, but slow like a sloth.

This library is for educational purposes and can be used to study algorithms and experiment with some data structures.
The input and output are in CSV format, and there is also the possibility, through the outputDotList method, to write the output to a Dot file, which can be used for graphical generation of trees and graphs with the GraphViz tool.

## Getting Started

The library can be used through manual compilation. To compile it, you just need to use CMake with the minimum required version (3.10).

Once CMake is installed, navigate to the root project directory and execute the following command:
```bash
mkdir build
cd build
cmake ..
make
```

If everything goes well, you will find the executable in your_project_folder/build/app/executable.
When running the binary, you will see the message "Benvenuto nella libreria".