#include <stdio.h>
#include "predictor21264.h"
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
    int index = 0;
    for( int i = 0; i < 1024; ++i )
    {
	if( LocalHistoryTable[i].pc == pc )
	{
	    index = i;
	    i = 1024;
	}
    }

    int localPredictionIndex = LocalHistoryTable[index].createIndex();
    int globalPredictionIndex = histTableToInt();

    if( ChooserPredictionTable[globalPredictionIndex].counter[0] == 1 )
	return GlobalPredictionTable[globalPredictionIndex].counter[0] == 1;
    else
	return LocalPredictionTable[localPredictionIndex].counter[0] == 1;
}

void train_predictor (unsigned int pc, bool outcome)
{
    int LRUindex = 0;
    bool updatedExisting = false;

    for( int i = 0; i < 1024; ++i )
    {
	// Increment time since last usage
	LocalHistoryTable[i].lastUsed++;

	// If this is the pc we're looking for, update its stats
	if( LocalHistoryTable[i].pc == pc )
	{
	    // Mark that we've updated existing data
	    updatedExisting = true;

	    // Update the information for this branch
	    LocalHistoryTable[i].lastUsed = 0;
	    for( int j = 9; j > 0; --j )
	    {
		LocalHistoryTable[i].outcomes[j - 1] = 
		    LocalHistoryTable[i].outcomes[j];
	    }
	    LocalHistoryTable[i].outcomes[9] = outcome ? 1 : 0;

	    // Update the local history
	    int localIndex = LocalHistoryTable[i].createIndex();
	    for( int j = 2; j > 0; --j )
	    {
		LocalPredictionTable[localIndex].counter[j-1] =
		    LocalPredictionTable[localIndex].counter[j];
	    }
	    LocalPredictionTable[localIndex].counter[2] = outcome ? 1 : 0;

	    // Update the global history
	    int ghtIndex = histTableToInt();
	    for( int j = 12; j > 0; --j )
	    {
		GlobalHistoryTable[j-1] = GlobalHistoryTable[j];
	    }
	    GlobalHistoryTable[11] = outcome ? 1 : 0;

	    // Update the global prediction
	    GlobalPredictionTable[ghtIndex].counter[0] =
		GlobalPredictionTable[ghtIndex].counter[1];
	    GlobalPredictionTable[ghtIndex].counter[1] = outcome ? 1 : 0;

	    // Update the Chooser, if needed
	    if( GlobalPredictionTable[ghtIndex].counter[0] != 
		    LocalPredictionTable[localIndex].counter[1] )
	    {
		if( ChooserPredictionTable[ghtIndex].counter[1] == 1
		 && GlobalPredictionTable[ghtIndex].counter[0] != (int)outcome)
		{
		    ChooserPredictionTable[ghtIndex].counter[0] = 1;
		    ChooserPredictionTable[ghtIndex].counter[1] = 0;
		} else if( ChooserPredictionTable[ghtIndex].counter[1] == 0
			&& LocalPredictionTable[localIndex].counter[1] != (int)outcome)
		{
		    ChooserPredictionTable[ghtIndex].counter[0] = 0;
		    ChooserPredictionTable[ghtIndex].counter[1] = 1;
		}
	    }
	}

	// Find the Least recently used, if we need to add pc to the table
	if(LocalHistoryTable[i].lastUsed > LocalHistoryTable[LRUindex].lastUsed)
	    LRUindex = i;
    }

    // If we already updated, we can just return here
    if( updatedExisting )
	return;

    // Add pc to the table
    LocalHistoryTable[LRUindex].pc = pc;
    LocalHistoryTable[LRUindex].lastUsed = 0;
    for( int i = 9; i > -1; --i )
    {
	LocalHistoryTable[LRUindex].outcomes[i] = 0;;
    }
    LocalHistoryTable[LRUindex].outcomes[9] = outcome ? 1 : 0;
}
