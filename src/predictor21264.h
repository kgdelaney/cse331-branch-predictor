#ifndef PREDICTOR_H
#define PREDICTOR_H

/*
  Define all your tables and their sizes here.
  All tables must be statically-sized.
  Please don't call malloc () or any of its relatives within your
  program.  The predictor will have a budget, namely (64K + 256) bits
  (not bytes).  That encompasses all storage (all tables, plus GHR, if
  necessary -- but not PC) used for the predictor.  That may not be
  the amount of storage your predictor uses, however -- for example,
  you may implement 2-bit predictors with a table of ints, in which
  case the simulator will use more memory -- that's okay, we're only
  concerned about the memory used by the simulated branch predictor.
*/
#define LHT_SIZE 1024
struct LHT_Entry  /* LocalHistoryTable Entry, contains program counter, LRU bit, and the 10 bit outcomes */
{
    unsigned int pc;
    unsigned int lastUsed;
    char outcomes[10]; /* Last 10 outcomes, 1 is taken, 0 is not taken */
};
static LHT_Entry LocalHistoryTable[LHT_SIZE];

struct LPT_Entry /* Local Prediction Table Entry. */
{
    char counter[3];
};
static LPT_Entry LocalPredictionTable[1024];

static char GlobalHistoryTable[12];

struct GPT_Entry
{
    char counter[2];
};
static GPT_Entry GlobalPredictionTable[4096];

struct CPT_Entry
{
    char counter[2];
};
static CPT_Entry ChooserPredictionTable[4096];


/*
  Initialize the predictor.
*/
void init_predictor ();

/*
  Make a prediction for conditional branch instruction at PC 'pc'.
  Returning true indicates a prediction of taken; returning false
  indicates a prediction of not taken.
*/
bool make_prediction (unsigned int pc);

/*
  Train the predictor the last executed branch at PC 'pc' and with
  outcome 'outcome' (true indicates that the branch was taken, false
  indicates that the branch was not taken).
*/
void train_predictor (unsigned int pc, bool outcome);

#endif
