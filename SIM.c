
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//------------------------------------------------------------------

int m;
int n;

double totalpred = 0;
double misspred = 0;

unsigned int GBH = 0;

bool taken;

//------------------------------------------------------------------

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

