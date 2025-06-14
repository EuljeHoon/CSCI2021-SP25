#include <stdio.h>
#include <string.h>

#include "race_results.h"

#define MAX_CMD_LEN 128

/*
 * This is in general *very* similar to the list_main file seen in lab 2
 * One big difference is the notion of switching between result logs in one run of the program.
 * You have to create or load a result log from a file before you can do things
 * like add, lookup, or write.
 * The code below has to check if result log is NULL before each operation is executed.
 * Also, the user has to explicitly clear the current result log before
 * they can create or load in a new one.
 */
int main(int argc, char **argv) {
    results_log_t *log = NULL;
    /*
     * Command line argument that I created.
     */
    if (argc > 1) {
        char *file_name = argv[1];
        char *lastAppear = strrchr(file_name, '.');
        if (lastAppear != NULL) {
            if (strcmp(lastAppear, ".txt") == 0) {
                log = read_results_log_from_text(file_name);
                if (log != NULL) {
                    printf("Results log loaded from text file\n");
                } else {
                    printf("Failed to read results log from text file\n");
                }
            } else if (strcmp(lastAppear, ".bin") == 0) {
                log = read_results_log_from_binary(file_name);
                if (log != NULL) {
                    printf("Results log loaded from binary file\n");
                } else {
                    printf("Failed to read results log from binary file\n");
                }
            } else {
                printf("Error: Unknown results log file extension\n");
            }
        } else {
            printf("Error: Unknown results log file extension\n");
        }
    }

    printf("CSCI 2021 Race Results Log\n");
    printf("Commands:\n");
    printf("  create <name>:            creates a new log with specified name\n");
    printf("  log:                      shows the name of the active results log\n");
    printf("  add <name> <age> <time>:  adds a new participant\n");
    printf("  lookup <name>:            searches for a race participant by name\n");
    printf("  clear:                    resets current results log\n");
    printf("  print:                    shows all participants in active log\n");
    printf("  write_text:               saves results log to text file\n");
    printf("  read_text <file_name>:    loads results log from text file\n");
    printf("  write_bin:                saves results log to binary file\n");
    printf("  read_bin <file_name>:     loads results log from binary file\n");
    printf("  exit:                     exits the program\n");

    char cmd[MAX_CMD_LEN];
    while (1) {
        printf("results> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            break;
        }

        else if (strcmp("create", cmd) == 0) {
            scanf("%s", cmd);    // Read in new log name
            if (log != NULL) {
                printf("Error: You already have an active results log.\n");
                printf("You can remove it with the \'clear\' command\n");
            } else {
                log = create_results_log(cmd);
                if (log == NULL) {
                    printf("Results log creation failed\n");
                }
            }
        }

        // TODO
        // log command
        else if (strcmp("log", cmd) == 0) {
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                printf("%s\n", get_results_log_name(log));
            }
        }

        // add command
        else if (strcmp("add", cmd) == 0) {
            char nameList[NAME_LEN];
            unsigned age, hours, minutes, seconds, total_seconds;
            scanf("%s %u %u:%u:%u", nameList, &age, &hours, &minutes, &seconds);
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                total_seconds = (hours * 3600) + (minutes * 60) + seconds;
                add_participant(log, nameList, age, total_seconds);
            }
        }

        // lookup command
        else if (strcmp("lookup", cmd) == 0) {
            char name[NAME_LEN];
            scanf("%s", name);
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                const participant_t *participant = find_participant(log, name);
                if (participant == NULL) {
                    printf("No participant found with name '%s'\n", name);
                } else {
                    printf("%s\n", participant->name);
                    printf("Age: %u\n", participant->age);
                    printf("Time: ");
                    print_formatted_time(participant->time_seconds);
                    printf("\n");
                }
            }
        }

        // clear command
        else if (strcmp("clear", cmd) == 0) {
            if (log == NULL) {
                printf("Error: No results log to clear\n");
            } else {
                free_results_log(log);
                log = NULL;
            }
        }

        // print command
        else if (strcmp("print", cmd) == 0) {
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                print_results_log(log);
                printf("\n");
            }
        }

        // write_text command
        else if (strcmp("write_text", cmd) == 0) {
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                if (write_results_log_to_text(log) == -1) {
                    printf("Failed to write results log to text file\n");
                } else {
                    printf("Results log successfully written to %s.txt", get_results_log_name(log));
                    printf("\n");
                }
            }
        }

        // read_text command
        else if (strcmp("read_text", cmd) == 0) {
            char newFile[MAX_CMD_LEN];
            scanf("%s", newFile);
            if (log != NULL) {
                printf("Error: You must clear current results log first\n");
            } else {
                log = read_results_log_from_text(newFile);
                if (log == NULL) {
                    printf("Failed to read results log from text file\n");
                } else {
                    printf("Results log loaded from text file\n");
                }
            }
        }

        // write_bin command
        else if (strcmp("write_bin", cmd) == 0) {
            if (log == NULL) {
                printf("Error: You must create or load a results log first\n");
            } else {
                if (write_results_log_to_binary(log) == -1) {
                    printf("Failed to write results log to binary file\n");
                } else {
                    printf("Results log successfully written to %s.bin\n",
                           get_results_log_name(log));
                }
            }
        }

        // read_bin command
        else if (strcmp("read_bin", cmd) == 0) {
            char newFile[MAX_CMD_LEN];
            scanf("%s", newFile);
            if (log != NULL) {
                printf("Error: You must clear current results log first\n");
            } else {
                log = read_results_log_from_binary(newFile);
                if (log == NULL) {
                    printf("Failed to read results log from binary file\n");
                } else {
                    printf("Results log loaded from binary file\n");
                }
            }
        } else {
            printf("Unknown command %s\n", cmd);
        }
    }

    if (log != NULL) {
        free_results_log(log);
    }
    return 0;
}
