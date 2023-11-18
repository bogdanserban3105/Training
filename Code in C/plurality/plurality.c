#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election

    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    //we create a for loop for adding on votes, we compare with the help of
    //strcmp() if the introduced string its the same as the one in the array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //first we need 2 loops
    //the memory structure helps memorise the candidates structure while it changes spots
    for (int i = 0; i < candidate_count; i++)
    {
        candidate memory;
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[i].votes < candidates[j].votes)
            {
                //now we will go through the structure and make it increasing
                memory = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = memory;
            }
        }
    }
    //because we dont know if inside the structure there are candidates with the same number of votes
    //we create 2 loops, this time the first one starts from the back, because thats how we ordered
    //the structure: increasing numbers - to be printed in ascending order A B C etc
    for (int m = candidate_count - 1; m >= 0; m--)
    {
        for (int n = 0; n < candidate_count; n++)
        {
            if (candidates[m].votes == candidates[n].votes && strcmp(candidates[m].name, candidates[n].name) != 0)
            {
                if (candidates[candidate_count - 1].votes > candidates[m].votes)
                {
                    printf("%s\n", candidates[candidate_count - 1].name);
                    return;
                }
                else
                {
                    printf("%s\n", candidates[n].name);
                }
            }

        }
    }
    // if there are no duplicate that are equal with the biggest number of votes we print the last
    //candidate
    printf("%s\n", candidates[candidate_count - 1].name);
    return;
}

