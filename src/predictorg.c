#include <stdio.h>
#include <iostream>
#include "predictorg.h"
#include<math.h>
// A very stupid predictor.  It will always predict not taken.
// but it will be better

void init_predictor ()
{
    for( int i = 0; i < 14; ++i )
	GlobalHistoryTable[i] = 0;

    for( int i = 0; i < 16384; ++i )
    {
	BranchHistoryTable[i].counter[0] = 0;
	BranchHistoryTable[i].counter[1] = 0;
    }
}

unsigned int convertGHT2Int()
{
    unsigned int value;
    for(int i = 0; i < 14; i++)
    {
        if(GlobalHistoryTable[i] == 1)
        {
            value += 1 << i; 
        }
    }
    return value;
}

void convertInt2GHT(unsigned int counter)
{
    unsigned int mask = 1 << (sizeof(int) * 8 - 1);
    
    for(int i = 0; i < 14; i++)
     {
         if( (counter & mask) == 1)
         {
             GlobalHistoryTable[i] = 1;
         }
         else
         {
             GlobalHistoryTable[i] = 0;
         }
         mask >>= 1;
     }
}

bool make_prediction (unsigned int pc)
{
    unsigned int GHTValue = convertGHT2Int();
    unsigned int prediction = (GHTValue ^ pc) % 16384;
    if(BranchHistoryTable[prediction].counter[0] == 1 &&
        BranchHistoryTable[prediction].counter[1] == 1)
    {
        //strongly taken
        return true;
    }
    if(BranchHistoryTable[prediction].counter[0] == 1 &&
        BranchHistoryTable[prediction].counter[1] == 0)
    {
        //weakly taken
        return true;
    }
    if(BranchHistoryTable[prediction].counter[0] == 0 &&
        BranchHistoryTable[prediction].counter[1] == 1)
    {
        //weakly not taken
        return false;
    }
    if(BranchHistoryTable[prediction].counter[0] == 0 &&
        BranchHistoryTable[prediction].counter[1] == 0)
    {
        //strongly not taken
        return false;
    }
    
    
    return true;
}

void train_predictor (unsigned int pc, bool outcome)
{
    unsigned int GHTValue = convertGHT2Int();
    int prediction = (GHTValue ^ pc) % 16384;
    if(outcome)
    {
        //Branch has been taken, update the BHT counter(s), 
        //and the global counter 
        if(BranchHistoryTable[prediction].counter[0] == 1 &&
            BranchHistoryTable[prediction].counter[1] == 0)
        {
            BranchHistoryTable[prediction].counter[1] = 1;
        }
        if(BranchHistoryTable[prediction].counter[0] == 1 &&
            BranchHistoryTable[prediction].counter[1] == 1)
        {
            ; //nop
        }
        if(BranchHistoryTable[prediction].counter[0] == 0 &&
            BranchHistoryTable[prediction].counter[1] == 0)
        {
            BranchHistoryTable[prediction].counter[1] = 1;
        }
        if(BranchHistoryTable[prediction].counter[0] == 0 &&
            BranchHistoryTable[prediction].counter[1] == 1)
        {
            BranchHistoryTable[prediction].counter[0] = 1;
        }
        //update the global counter here...
        //convertInt2GHT(GHTValue++);
    }
    else
    {
        //Branch not taken, decrement counters in BHT
        //update the global counter
        if(BranchHistoryTable[prediction].counter[0] == 1 &&
            BranchHistoryTable[prediction].counter[1] == 0)
        {
            BranchHistoryTable[prediction].counter[1] = 1;
            BranchHistoryTable[prediction].counter[0] = 0;
        }
        if(BranchHistoryTable[prediction].counter[0] == 1 &&
            BranchHistoryTable[prediction].counter[1] == 1)
        {
            BranchHistoryTable[prediction].counter[1] = 0;
        }
        if(BranchHistoryTable[prediction].counter[0] == 0 &&
            BranchHistoryTable[prediction].counter[1] == 0)
        {
            ; //nop
        }
        if(BranchHistoryTable[prediction].counter[0] == 0 &&
            BranchHistoryTable[prediction].counter[1] == 1)
        {
            BranchHistoryTable[prediction].counter[1] = 0;
        }
        //convertInt2GHT(GHTValue--);
    }

}
