#include <stdio.h>
#include "predictor.h"
// A very stupid predictor.  It will always predict not taken.
// but it will be better

void init_predictor ()
{
    for( int i = 0; i < 1024; ++i )
    {
	LocalHistoryTable[i].pc = 0;
	LocalHistoryTable[i].lastUsed = 1;
	for( int j = 0; j < 10; ++j )
	    LocalHistoryTable[i].outcomes[j] = 0;

	for( int j = 0; j < 3; ++j )
	    LocalPredictionTable[i].counter[j] = 0;
    }

    for( int i = 0; i < 12; ++i )
	GlobalHistoryTable[i] = 0;

    for( int i = 0; i < 4096; ++i )
    {
	GlobalPredictionTable[i].counter[0] = 0;
	GlobalPredictionTable[i].counter[1] = 0;

	ChooserPredictionTable[i].counter[0] = 0;
	ChooserPredictionTable[i].counter[1] = 0;
    }
}

bool make_prediction (unsigned int pc)
{
  return false;
}

void train_predictor (unsigned int pc, bool outcome)
{
}
