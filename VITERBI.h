#ifndef ViterbiH
#define ViterbiH

#include <vcl.h>
#include <memory.h>
#pragma hdrstop

#define MAXK 9
#define MAXN 6

#define cmetric_array_size  (1 << (MAXK-1))
#define xpath_array_size    (15000)

class Viterbi
{
public:
   char output_bits[4096];               // output decoded bits ("0" and "1" char)
   int output_nbits;                     // number of output bits
   int metric;                           // calculated metric

   int Syms[1 << MAXK];
   unsigned int encstate;                // encoder internal shift register
   int mets[1 << MAXN];                  // metric
   int mettab[2][256];                   // Metric table, [sent sym][rx symbol]
   int cmetric[cmetric_array_size];      // current metric
   int nmetric[cmetric_array_size];      // new metric
   int bitcount;                         // bitcount
   unsigned int paths[xpath_array_size]; // paths
   char decoded_data[4096];              // decoded data ("0" and "1" char)
   bool ready;                           // flag there are data
   unsigned int *pp;                     // Current path
   int PathSize;
   unsigned char input_table[128];
   unsigned char dummy_table[128];
   int input_table_counter;

   int N;
   int K;
   int D;
   unsigned int Polys[MAXN];

   void __fastcall decode(unsigned char *symbols);
   void __fastcall SymbolDecode(unsigned char symbol);
   AnsiString __fastcall encode(AnsiString data);
   void __fastcall RebuildPath(int nbits);
   void __fastcall InitDecoder();
   void __fastcall SetParm(int n, int k);
   void __fastcall SetPathSize(int ps);
};

class ParallelViterbi
{
public:
   int ndecoders;

   Viterbi V[64];
   int N;
   int K;

   char output_bits[4096];               // output decoded bits ("0" and "1" char)
   int output_nbits;                     // number of output bits
   int metric;                           // calculated metric
   bool ready;                            

   int PathSize;
   int Slice;

   void __fastcall SetParm(int n, int k);
   void __fastcall SetPathSize(int ps);
   void __fastcall SymbolDecode(unsigned char symbol);

   ParallelViterbi();
};

#endif
