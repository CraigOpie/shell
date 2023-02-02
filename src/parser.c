/*******************************************************************************
* Copyright (c) 2023
* College of Natural Science, Computer Science, University of Hawaii at Manoa
* Class: ICS 612 Spring 2023
* All rights reserved.
*   
* This source code is part of Operating Systems Project 1.  This prpgram is a
* shell program that can execute commands, redirect the standard input or
* standard output of commands to files, pipe the output of commands to other
* commands, and put commands in the background. This shell also prompts the user
* when it is ready to accept commands.
*
* Copyright of the project is maintained by the developer, and the project is
* distributed under the terms of the Creative Commons Attribution-NonCommercial
* 4.0 International Public License 
* http://creativecommons.org/licenses/by-nc/4.0/legalcode.
* The source code is free and you can redistribute and/or modify it providing
* that the following conditions are met:
*   
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer. 
*   
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*   
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* Developer list: 
*   Craig Opie      Email: opieca at hawaii dot edu
********************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "../lib/parser.h"

using namespace std;

void parse_command(char input[], char* argv[], int* wait) {
   for (unsigned idx = 0; idx < BUF_SIZE; idx++) {
      argv[idx] = NULL;
   }

   if (input[strlen(input) - 1] == '&') {
      *wait = 1;
      input[strlen(input) - 1] = '\0';
   }
   else {
      *wait = 0;
   }

   const char *delim = " ";
   unsigned idx = 0;

   char *token = strtok(input, delim);
   while (token != NULL) {
      argv[idx++] = token;
      token = strtok(NULL, delim);
   }

   argv[idx] = NULL;
}

void parse_redir(char* argv[], char* redir_argv[]) {
   unsigned idx = 0;
   redir_argv[0] = NULL;
   redir_argv[1] = NULL;

   while (argv[idx] != NULL) {
      if (strcmp(argv[idx], "<") == 0 || strcmp(argv[idx], ">") == 0) {
         if (argv[idx + 1] != NULL) {
            redir_argv[0] = strdup(argv[idx]);
            size_t length = strlen(argv[idx + 1]) + 1;
            redir_argv[1] = (char*) malloc(length);
            strncpy(redir_argv[1], argv[idx + 1], length);
            argv[idx] = NULL;
            argv[idx + 1] = NULL;
         }
      }

      idx++;
   }
}

bool parse_pipe(char* argv[], char *child01_argv[], char *child02_argv[]) {
   unsigned idx = 0, split_idx = 0;
   bool contains_pipe = false;

   while (argv[idx] != NULL) {
      if (strcmp(argv[idx], "|") == 0) {
         split_idx = idx;
         contains_pipe = true;
      }
      idx++;
   }

   if (!contains_pipe) {
      return false;
   }

   for (idx = 0; idx < split_idx; idx++) {
      child01_argv[idx] = strdup(argv[idx]);
   }
   child01_argv[idx++] = NULL;

   while (argv[idx] != NULL) {
      child02_argv[idx - split_idx - 1] = strdup(argv[idx]);
      idx++;
   }
   child02_argv[idx - split_idx - 1] = NULL;

   return true;
}
