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

void resetLHTEntry(int i){
    LocalHistoryTable[i].pc = 0;
    LocalHistoryTable[i].lastUsed = 1;
	for( int j = 0; j < 10; ++j )
	    LocalHistoryTable[i].outcomes[j] = 0;

}

int charToBin(char c[10], int size){
    int num = 0;
    int i;
    for(i = size; i >= 0; i--){
        num += c[i] << size-i-1;
    }
    return num;

}
bool make_prediction (unsigned int pc)
{
    char *currOutcome;
    int found = 0;
    int LRUIndex = 0;
    int index;
    int LRUNum = 0;
    char sigBits[3];
    int localPrediction[3];
    for(int i = 0; i < LHT_SIZE; i++){
        if(LocalHistoryTable[i].pc == pc){
            found = 1;
            currOutcome = LocalHistoryTable[i].outcomes;
            index = i;
        }
        if(LocalHistoryTable[i].lastUsed > LRUNum ){
            LRUNum = LocalHistoryTable[i].lastUsed;
            LRUIndex = i;
        }
        if(LocalHistoryTable[i].pc == 0 && found == 0){
            LocalHistoryTable[i].pc = pc; 
            index=i;
            break;
        }
    }
    if(found == 0){
        index = LRUIndex;
        resetLHTEntry(index);
        LocalHistoryTable[index].pc = pc;
        currOutcome = LocalHistoryTable[index].outcomes;
    }
    int location = charToBin(currOutcome, 10);
    for(int i = 0; i < 3; i++){
        localPrediction[i] = LocalPredictionTable[location].counter[i];
    }
    return false;
}

void train_predictor (unsigned int pc, bool outcome)
{

}
