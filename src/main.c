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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hierarchy.h"
#include "history.h"
#include "parser.h"
#include "pipe.h"

using namespace std;

const unsigned int MAX_INPUT_LENGTH = 1201;
const unsigned int MAX_COMMAND_NAME = 80;
const unsigned int REDIR_SIZE = 2;
const unsigned int PIPE_SIZE = 3;
const char SHELL_SYMBOL[3] = "$>";

int main() {
    bool running = true;
    unsigned int history_count = 0;
    int wait;
    char user_input[MAX_INPUT_LENGTH];
    char *argv[BUF_SIZE], *redir_argv[REDIR_SIZE];
    char *child01_argv[PIPE_SIZE], *child02_argv[PIPE_SIZE];
    char *history[MAX_HISTORY];

    for (unsigned int i = 0; i < MAX_HISTORY; i++) {
        history[i] = (char*)calloc(MAX_COMMAND_NAME, sizeof(char));
    }

    while (running) {
        printf("%s", SHELL_SYMBOL);
        fflush(stdout);

        while (fgets(user_input, MAX_INPUT_LENGTH, stdin) == NULL) {
            perror("Cannot read user input!");
            fflush(stdin);
        }

        user_input[strcspn(user_input, "\n")] = '\0';

        if (strcmp(user_input, "exit") == 0) {
            running = false;
            continue;
        }

        if (strcmp(user_input, "!!") == 0) {
            if (history_count == 0) {
                fprintf(stderr, "No commands in history\n");
                continue;
            }
            strncpy(user_input, history[history_count - 1], MAX_COMMAND_NAME - 1);
            user_input[MAX_COMMAND_NAME - 1] = '\0';
            printf("%s%s\n", SHELL_SYMBOL, user_input);
        }

        add_history_feature(history, history_count, user_input);

        if (strncmp(user_input, "cd ", 3) == 0) {
            if (chdir(user_input + 3) != 0) {
                perror("Failed to change directory");
            }
            continue;
        }
        parse_command(user_input, argv, &wait);
        parse_redir(argv, redir_argv);

        if (parse_pipe(argv, child01_argv, child02_argv)) {
            exec_with_pipe(child01_argv, child02_argv);
            continue;
        }

        pid_t pid = fork();

        switch (pid) {
            case -1:
            perror("fork() failed!");
            exit(EXIT_FAILURE);

            case 0:
            child(argv, redir_argv);
            exit(EXIT_SUCCESS);

            default:
            parent(pid, wait);
        }
    }
    return 0;
}
