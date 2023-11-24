
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//------------------------------------------------------------------
/*
    Global Variable
*/

int m;
int n;

double totalpred = 0;
double misspred = 0;

unsigned int GBH = 0;

bool taken;

//------------------------------------------------------------------
/*
    Runs the branch predictor. Accepts trace file and 
    preset-to-2 table. Table is passed by reference so
    the data is reflected back into main, where it was 
    declared. Returns nothing for return type because it
    updates global counter variables. 
*/
void predict( FILE *tracefile, int *table )
{
    int prediction;
    
    unsigned long long int addy;
    unsigned long long int index;

    char takenstat;

    while( fscanf( tracefile, "%llx %c", &addy, &takenstat ) != EOF )
    {
        index = ((addy >> 2) & ((1 << m) - 1)) ^ (GBH << (m - n));

        if( table[index] >= 2 )
        {
            prediction = 1;
        }

        else
        {
            prediction = 0;
        }

        if( takenstat == 't' )
        {
            taken = true;
        }

        else
        {
            taken = false;
        }

        totalpred++;

        if( prediction != taken )
        {
            misspred++;
        }

        if( taken == true )
        {
            if( table[ index ] < 3 ) 
            {
                table[ index ]++;
            }
        }

        else
        {
            if( table[ index ] > 0 )
            {
                table[ index ]--;
            }
        }

        GBH = GBH >> 1;

        if( taken == true && n != 0 )
        {
            GBH = GBH | ( 1 << ( n - 1 ) );
        }
    }
}

//------------------------------------------------------------------
/*
    Main function. Accepts command line inputs of <M> <N> and <tracefile>.
    Returns int to confirm program ran or exited for error. Parses information
    from command line into approriapte places, checks that input conditions 
    are ok to continue, opens trace file, presets table and determines size,
    calls the predict function, closes file, prints results.
*/
int main( int noi, char **inputs)
{
    char *tracefilepath;
    
    if( noi != 4 )
    {
        printf("Not enough inputs, please try again or refer to instructions (readme or makefile)");
        return 1;
    }

    else
    {
        m = atoi( inputs[1] );
        n = atoi( inputs[2] );

        tracefilepath = inputs[3];
    }
    
    if( m > 18 )
    {
        printf("M value is too large, please try again with a m value smaller than 19");
        return 1;
    }

    FILE *tracefile = fopen(tracefilepath, "r");
    
    if( tracefile == NULL )
    {
        printf("No file found in this location or could not open file");
        return 1;
    }

    int powervalue = 2;

    for( int i = m - 1; i != 0; i--  )
    {
        powervalue = powervalue * 2;
    }

    int table[ powervalue ];

    for( int i = 0; i < powervalue; i++ )
    {
        table[i] = 2;
    }

    predict( tracefile, table );

    fclose( tracefile );
    
    printf("\nM: %d\tN: %d\tMisprediction Ratio: %.2lf%%\n\n", m, n, 100 * misspred / totalpred );
}

//------------------------------------------------------------------
/*
  End of file

  Current to 11-24-2023

  UCF - Computer Architecture - Suboh Suboh
  Project 2 - Branch Predictor Simulator

  Andrew Fugate
*/
//------------------------------------------------------------------
