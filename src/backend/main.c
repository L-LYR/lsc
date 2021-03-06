#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../exception/exception.h"
#include "../lib/llsc.h"
#include "vm.h"

FILE* inFile;
FILE* bbFile;
void SetOpts(int argc, char* argv[]);

int main(int argc, char* argv[]) {
  SetOpts(argc, argv);
  Run(inFile, bbFile);
  return 0;
}

const char* OptFmt = ":i:b:h";

const char* Usage =
    "Usage: lscvm [-h] -i <filename> -b <filename>\n"
    "Options:\n"
    "  -i <filename>\tRun the IR file.\n"
    "  -b <filename>\tOutput the basic blocks into file.\n"
    "  -h           \tPrint this help.\n";

void SetOpts(int argc, char* argv[]) {
  if (argc < 2) {
    notify(Usage);
  }
  int opt;
  while ((opt = getopt(argc, argv, OptFmt)) != -1) {
    switch (opt) {
      case 'i':
        inFile = fopen(optarg, "r");
        if (inFile == NULL) {
          RAISE(InFileOpenErr);
        }
        break;
      case 'b':
        bbFile = fopen(optarg, "w");
        if (bbFile == NULL) {
          RAISE(OutFileOpenErr);
        }
        break;
      default:
      case 'h':
        notify(Usage);
    }
  }
}