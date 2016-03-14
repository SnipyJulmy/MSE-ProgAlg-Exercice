#include <iostream>
#include <omp.h>

using namespace std;

void ex1(int n)
{
    #pragma omp parallel num_threads(n)
    {
        printf("Hello Wolrd!\n");
    }
}

void ex2(int a, int b)
{
    omp_set_nested(1);
    #pragma omp parallel for
    for (int i = 0; i < a; ++i)
    {
        #pragma omp parallel for
        for (int j = 0; j < b; ++j)
        {
            printf("Hello World from %d-%d!\n", omp_get_thread_num(),
                   omp_get_ancestor_thread_num(omp_get_active_level()));
        }
    }
}

void ex3(int n)
{
    int votes = 0;
    printf("First printf !\n");
    srand((unsigned int) clock());
    #pragma omp parallel for if(votes < n/2) shared(votes)
    for (int i = 0; i < n; ++i)
    {
        if (rand() % 2 == 1)
            votes++;
    }
    printf("Last printf !\n Nbr votes : %d\n", votes);
}

void ex4(int n)
{
    int votes = 0;
    int nbr_passes = 0;
    printf("First printf !\n");
    srand((unsigned int) clock());
    volatile bool flag = false;

    #pragma omp parallel for shared(flag,votes) reduction(+:nbr_passes)
    for (int i = 0; i < n; ++i)
    {
        if (flag)
            continue;
        if (rand() % 2 == 1)
        {
            votes++;
            if (votes > n / 2)
                flag = true;
        }
        nbr_passes++;
    }
    printf("Last printf !\nNbr votes : %d\nNbr passes : %d\n", votes, nbr_passes);
}

void ex5(int n)
{
    int votes_no = 0, votes_yes = 0;
    int nbr_passes = 0;
    printf("First printf !\n");
    srand((unsigned int) clock());
    volatile bool flag = false;

    #pragma omp parallel for shared(flag) reduction(+:nbr_passes) reduction(+:votes_yes) reduction(+:votes_no)
    for (int i = 0; i < n; ++i)
    {
        if (flag)
            continue;
        if (rand() % 2 == 1)
        {
            votes_no++;
        }
        else
        {
            votes_yes++;
        }
        if(votes_no > (n/1000) || votes_yes > (n/1000))
            flag = true;
        nbr_passes++;
    }
    printf("Last printf !\n\tNbr votes : %d / %d\n\tNbr passes : %d\n", votes_yes,votes_no, nbr_passes);
}

void ex6(int n)
{

}

int main()
{
    ex5(1000000);
    return 0;
}