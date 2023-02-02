# Custom Shell for Linux/Minix

Copyright (c) 2023
College of Natural Science, Computer Science, University of Hawaii at Manoa
Class: ICS 612 Spring 2023
All rights reserved.
  
This source code is part of Operating Systems Project 1.  This prpgram is a
shell program that can execute commands, redirect the standard input or
standard output of commands to files, pipe the output of commands to other
commands, and put commands in the background. This shell also prompts the user
when it is ready to accept commands.

Copyright of the project is maintained by the developer, and the project is
distributed under the terms of the Creative Commons Attribution-NonCommercial
4.0 International Public License 
http://creativecommons.org/licenses/by-nc/4.0/legalcode.
The source code is free and you can redistribute and/or modify it providing
that the following conditions are met:
  
 1) Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer. 
  
 2) Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Developer list: 
  Craig Opie      Email: opieca at hawaii dot edu

## Description
This project is written to be deployed on a Linux machine and was compiled using the g++ compiler with the following flags: `CFLAGS = -v -c -ansi -pedantic-errors -Wall`.  The test machine was an Ubuntu 20.04 machine (x86_64).  The code meets all of the criteria in the assignment.  I have provided a Makefile to use on a linux OS which creates the `shell` program in the `bin` directory.  The included linux_shell and minix_shell executables have were compiled before making the strcpy fix so they are potentially vulnerable to buffer overflows.  This security vulnerability has been corrected in the current source code.

This project has been compiled and installed on a Minix VM without using a Makefile with the clang compiler and the executable is included in the included `bin` directory.  I also included the ability to change directories and run the previous command using !!