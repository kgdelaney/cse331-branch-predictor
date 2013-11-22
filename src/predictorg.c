#include <stdio.h>
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

bool make_prediction (unsigned int pc)
{
    unsigned int GHTValue = convertGHT2Int();
    int prediction = GHTValue ^ pc;
    if(BranchHistoryTable[prediction].counter[0] == 1 &&
        BranchHistoryTable[prediction].counter[1] == 1)
    {
        //strongly taken
    }
    if(BranchHistoryTable[prediction].counter[0] == 1 &&
        BranchHistoryTable[prediction].counter[1] == 0)
    {
        //weakly taken
    }
    if(BranchHistoryTable[prediction].counter[0] == 0 &&
        BranchHistoryTable[prediction].counter[1] == 1)
    {
        //weakly not taken
    }
    if(BranchHistoryTable[prediction].counter[0] == 0 &&
        BranchHistoryTable[prediction].counter[1] == 0)
    {
        //strongly not taken
    }
    
    
    return false;
}

void train_predictor (unsigned int pc, bool outcome)
{
    unsigned int GHTValue = convertGHT2Int();
    int prediction = GHTValue ^ pc;
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
    }

}
