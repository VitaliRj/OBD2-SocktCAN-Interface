# You have to Compile it Yourself

Follow these steps:

#### 1. On Linux, no C compiler is supplied with MATLAB, although the GNU compiler (GCC) is included with many Linux distributions.

* chose and make sure you installed a C compiler for your system: https://www.mathworks.com/support/compilers.html
* setup the compiler with by typing the `mex -setup` command in MATLAB

#### 2. Download the source for Linux and make it your current working folder in MATLAB (just navigate there).

#### 3. Run the "run_this_to_compile.m" file in MATLAB

* this will generate a .mex file for this library.

![Image of example](/images/compileIt.PNG)

#### 4. Pack the Add-On with the `OBD2 SocktCan Interface.prj` file.
* or just build your project in this current working folder
