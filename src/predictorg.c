#include <stdio.h>
#include "predictorg.h"
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

bool make_prediction (unsigned int pc)
{
  return false;
}

void train_predictor (unsigned int pc, bool outcome)
{
}
