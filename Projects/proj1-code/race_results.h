#ifndef RACE_RESULTS_H
#define RACE_RESULTS_H

#define NUM_BUCKETS 4057
#define NAME_LEN 32

// Data type for elements stored in hash table
typedef struct {
    char name[NAME_LEN];      // Participant's name
    unsigned age;             // Participant's age in years
    unsigned time_seconds;    // Final race time in seconds
} participant_t;

typedef struct {
    unsigned size;                          // Number of elements currently stored in table
    char name[NAME_LEN];                    // Results log's name
    participant_t *buckets[NUM_BUCKETS];    // Array of hash buckets
} results_log_t;

// Create a new results log instance
// log_name: The name of the results log
// Returns: Pointer to a results_log_t representing an empty log
//          or NULL if an error occurs
results_log_t *create_results_log(const char *log_name);

// Returns a pointer to the results log name
// log: A pointer to a log to get the name of
// Returns: Pointer to log's name (not to be modified)
const char *get_results_log_name(const results_log_t *log);

// Add a new participant to the log (insert into hash table)
// log: A pointer to a results log to add the participant to
// name: Participant's name, as a C string
// age: Participant's age, in years
// time_seconds: Participant's race time, in seconds
// Returns: 0 if the result was successfully added or -1 if the result could not be added
int add_participant(results_log_t *log, const char *name, unsigned age, unsigned time_seconds);

// Search for a specific participant in a log by name
// log: A pointer to a log to search
// name: Participant name to search for
// Returns: A pointer to the participant data if found, or NULL if no matching name is found
const participant_t *find_participant(const results_log_t *log, const char *name);

// Print out a race time given as total number of seconds in a more readable notation
// with hours, minutes, and seconds separated by a colon (':') character
// Note that minutes and seconds should always be represented with two digits
// Examples:
//    Input 0 -> Prints "0:00:00"
//    Input 60 -> Prints "0:01:00"
//    Input 3600 -> Prints "1:00:00"
//    Input 4815 -> Prints "1:20:15"
void print_formatted_time(unsigned time_seconds);

// Print out all participants in the results log
// log: A pointer to the log containing the participants to print
void print_results_log(const results_log_t *log);

// Frees all memory used to store the contents of the results log
// log: A pointer to the results log to free
void free_results_log(results_log_t *log);

// Write out all participants in the log to a text file
// log: A pointer to the log containing the results to write out
// Returns: 0 on success or -1 if an error occurs opening the destination file
int write_results_log_to_text(const results_log_t *log);

// Read in all participants from a text file and add to a new results_log
// file_name: The name of the text file to read
// Returns: A pointer to a new results log containing all results as recorded in the file
//          or NULL if the read operation fails
results_log_t *read_results_log_from_text(const char *file_name);

// Write all participants in a results log to a binary file
// log: A pointer to a results log containing the participants to write out
// Returns: 0 on success or -1 if an error occurs opening the destination file
int write_results_log_to_binary(const results_log_t *log);

// Read in all participants from a binary file and add to a new results log
// file_name: The name of the binary file to read
// Returns: A pointer to a new results log containing all participants as recorded
//          in the file or NULL if the read operation fails
results_log_t *read_results_log_from_binary(const char *file_name);

#endif    // RACE_RESULTS_H
