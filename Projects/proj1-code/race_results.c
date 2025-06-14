#include "race_results.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is the (somewhat famous) djb2 hash
unsigned hash(const char *str) {
    unsigned hash_val = 5381;
    int i = 0;
    while (str[i] != '\0') {
        hash_val = ((hash_val << 5) + hash_val) + str[i];
        i++;
    }
    return hash_val % NUM_BUCKETS;
}

results_log_t *create_results_log(const char *log_name) {
    results_log_t *log = malloc(sizeof(results_log_t));
    if (log == NULL) {
        return NULL;
    }
    strncpy(log->name, log_name, NAME_LEN - 1);
    log->name[NAME_LEN - 1] = '\0';
    log->size = 0;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        log->buckets[i] = NULL;
    }
    return log;
}

/*
 * This function is to get a name of the log.
 */
const char *get_results_log_name(const results_log_t *log) {
    // TODO
    if (log == NULL) {
        return NULL;
    } else {
        return log->name;
    }
}

/*
 * This function is to add participants using a hash table.
 */
int add_participant(results_log_t *log, const char *name, unsigned age, unsigned time_seconds) {
    // TODO
    if (log == NULL || name == NULL) {
        return -1;
    }
    if (find_participant(log, name) != NULL) {
        return -1;
    }
    unsigned index = hash(name);
    while (log->buckets[index] != NULL) {
        index = (index + 1) % NUM_BUCKETS;
    }
    participant_t *newParticipant = malloc(sizeof(participant_t));
    if (newParticipant == NULL) {
        return -1;
    }
    strcpy(newParticipant->name, name);
    newParticipant->age = age;
    newParticipant->time_seconds = time_seconds;
    log->buckets[index] = newParticipant;
    log->size = log->size + 1;
    return 0;
}

/*
 * This function performs the function of finding the name information of the participant.
 */
const participant_t *find_participant(const results_log_t *log, const char *name) {
    // TODO
    if (log == NULL || name == NULL) {
        return NULL;
    }
    unsigned index = hash(name);
    participant_t *participant = log->buckets[index];
    if (participant == NULL || strcmp(participant->name, name) != 0) {
        return NULL;
    }
    return participant;
}

void print_formatted_time(unsigned time_seconds) {
    unsigned hours = time_seconds / (60 * 60);
    time_seconds %= (60 * 60);
    unsigned minutes = time_seconds / 60;
    time_seconds %= 60;
    printf("%u:%02u:%02u", hours, minutes, time_seconds);
}

/*
 * A function that outputs participant information.
 */
void print_results_log(const results_log_t *log) {
    // TODO
    if (log == NULL) {
        return;
    }
    printf("%s Results\n", log->name);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        participant_t *printParticipant = log->buckets[i];
        if (printParticipant != NULL) {
            printf("Name: %s\n", printParticipant->name);
            printf("Age: %u\n", printParticipant->age);
            printf("Time: ");
            print_formatted_time(printParticipant->time_seconds);
            printf("\n");
        }
    }
}

/*
 * Function that releases dynamic memory.
 */
void free_results_log(results_log_t *log) {
    if (log == NULL) {
        return;
    }
    for (int i = 0; i < NUM_BUCKETS; i++) {
        if (log->buckets[i] != NULL) {
            free(log->buckets[i]);
            log->buckets[i] = NULL;
        }
    }
    free(log);
}

/*
 * A function that stores data as a text file.
 */
int write_results_log_to_text(const results_log_t *log) {
    if (log == NULL) {
        return -1;
    }
    char file_name[NAME_LEN + 5];
    snprintf(file_name, sizeof(file_name), "%s.txt", log->name);
    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        return -1;
    }
    fprintf(f, "%u\n", log->size);
    if (log->size > 0) {
        for (int i = 0; i < NUM_BUCKETS; i++) {
            if (log->buckets[i] != NULL) {
                participant_t *participant = log->buckets[i];
                fprintf(f, "%s %u %u\n", participant->name, participant->age,
                        participant->time_seconds);
            }
        }
    }
    fclose(f);
    return 0;
}

/*
 * A function that reads data from a text file.
 */
results_log_t *read_results_log_from_text(const char *file_name) {
    // TODO
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return NULL;
    }
    // This is for print out a file name without .txt
    char newName[NAME_LEN];
    strncpy(newName, file_name, NAME_LEN - 1);
    newName[NAME_LEN - 1] = '\0';
    char *find = strrchr(newName, '.');
    if (find != NULL && strcmp(find, ".txt") == 0) {
        *find = '\0';
    }

    results_log_t *log = create_results_log(newName);
    if (log == NULL) {
        fclose(file);
        return NULL;
    }
    unsigned numParticipant;
    if (fscanf(file, "%u", &numParticipant) != 1) {
        fclose(file);
        return NULL;
    }
    char name[NAME_LEN];
    unsigned age, time_seconds;
    while (fscanf(file, "%s %u %u", name, &age, &time_seconds) == 3) {
        if (add_participant(log, name, age, time_seconds) != 0) {
            free_results_log(log);
            fclose(file);
            return NULL;
        }
    }
    fclose(file);
    return log;
}

/*
 * A function that stores data as a binary file.
 */
int write_results_log_to_binary(const results_log_t *log) {
    // TODO Not Yet Implemented
    if (log == NULL) {
        return -1;
    }
    char newFile[NAME_LEN + 4];
    strcpy(newFile, log->name);
    strcat(newFile, ".bin");
    FILE *file = fopen(newFile, "w");
    if (file == NULL) {
        return -1;
    }
    fwrite(&log->size, sizeof(unsigned), 1, file);
    for (int i = 0; i < NUM_BUCKETS; i++) {
        if (log->buckets[i] != NULL) {
            unsigned length = strlen(log->buckets[i]->name);
            fwrite(&length, sizeof(unsigned), 1, file);
            fwrite(log->buckets[i]->name, sizeof(char), length, file);
            fwrite(&log->buckets[i]->age, sizeof(unsigned), 1, file);
            fwrite(&log->buckets[i]->time_seconds, sizeof(unsigned), 1, file);
        }
    }
    fclose(file);
    return 0;
}

/*
 * A function that reads data from a binary file.
 */
results_log_t *read_results_log_from_binary(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        return NULL;
    }
    unsigned size;
    fread(&size, sizeof(unsigned), 1, file);
    // This is for print out a file name without .bin
    char newName[NAME_LEN];
    strcpy(newName, file_name);
    newName[NAME_LEN - 1] = '\0';
    char *find = strrchr(newName, '.');
    if (find != NULL && strcmp(find, ".bin") == 0) {
        *find = '\0';
    }

    results_log_t *log = create_results_log(newName);
    if (log == NULL) {
        fclose(file);
        return NULL;
    }
    unsigned length;
    char name[NAME_LEN];
    unsigned age;
    unsigned time_seconds;
    for (unsigned i = 0; i < size; i++) {
        fread(&length, sizeof(unsigned), 1, file);
        fread(name, sizeof(char), length, file);
        name[length] = '\0';
        fread(&age, sizeof(unsigned), 1, file);
        fread(&time_seconds, sizeof(unsigned), 1, file);
        add_participant(log, name, age, time_seconds);
    }
    fclose(file);
    return log;
}
