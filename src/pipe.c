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
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/path.h"
#include "../lib/pipe.h"

using namespace std;

void exec_with_pipe(char* child01_argv[], char* child02_argv[]) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe() failed");
        exit(EXIT_FAILURE);
    }

    // split the path into a list of directories
    char *dirs[MAX_PATH_DIRS];
    char mypath[MAX_LINE_LENGTH];
    strncpy(mypath, PATH, sizeof(mypath));
    mypath[sizeof(mypath) - 1] = '\0';
    char *token = strtok(mypath, ":");
    int i = 0;
    while (token != NULL) {
        dirs[i] = token;
        token = strtok(NULL, ":");
        i++;
    }

    if (fork() == 0) {

        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        int executed = 0;
        for (int j = 0; j < i; j++) {
            if (!executed) {
                char full_path[MAX_LINE_LENGTH];
                snprintf(full_path, sizeof(full_path), "%s/%s", dirs[j], child01_argv[0]);

                // try to execute the command
                if (execvp(full_path, child01_argv) != -1) {
                    executed = 1;
                }
            }
        }
        if (!executed) {
            perror("Fail to execute first command");
            exit(EXIT_FAILURE);
        }
    }

    if (fork() == 0) {

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);

        int executed = 0;
        for (int j = 0; j < i; j++) {
            if (!executed) {
                char full_path[MAX_LINE_LENGTH];
                snprintf(full_path, sizeof(full_path), "%s/%s", dirs[j], child02_argv[0]);

                // try to execute the command
                if (execvp(full_path, child02_argv) != -1) {
                    executed = 1;
                }
            }
        }
        if (!executed) {
            perror("Fail to execute second command");
            exit(EXIT_FAILURE);
        }
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(0);
    wait(0);
}
