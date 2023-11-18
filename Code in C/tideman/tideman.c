#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_repeater(int l, int w);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //loop pentru a da functiei o valoare pe care sa o ia si sa o numeroteze
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = i + 1; j < candidate_count; j++)
        {
            // add 1 until loop its finished, return i candidate prefered compared with the others
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // cati oameni prefera i fata de j
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
    // would highly recommend carefully watching the week 1 short, functions; week 3, recursion; and week 4, call stacks.
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int i = pair_count - 1;
    //while there are pairs left
    while (i > 0)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair memory = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = memory;
            }
        }
        i--;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    //trece prin sir, verifica daca vreun prierzator indica catre un castigator din spatele sirurlui spre fata
    //if pairs[a].loser == pairs[b].winer && b > a remove pairs[a]
    //daca indica atunci scoate l din pereche si modifica tot siru
    //daca nu se intampla ce am zis mai sus atribuie valoarea unei matrici 2D boolene locked[i][j]
    //creaza o functie care sa faca toate astea
    // pair_count--
    //crated a recursive function for the ease of use
    //
    for (int i = 0; i < pair_count; i++)
    {
        if (!check_repeater(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // ultimul winner din sir ar trebui sa fie castigatorul alegerilor
    // daca ultimul winner e egal cu penultimul atunci afiseaza i pe amandoi
    // TODO
    int n;

    for (int i = 0; i < candidate_count; i++)
    {
        n = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                n++;
            }
        }
        //checks if candidate collumn its full of 0
        if (n == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool check_repeater(int w, int l)
{
    //recurcion breaker
    //check if the user is pointing at the winner (locked its a boolean matrix/array)
    if (locked[l][w])
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)
    {
        //the loser points forward until it meets the winner
        if (locked[l][i] && check_repeater(w, i))
        {
            return true;
        }
    }
    return false;
}

