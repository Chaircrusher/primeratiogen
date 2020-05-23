#include <iostream>
#include <stdlib.h>
#include "Bjorklund.h"

int main(int argc, char **argv) {
  if(argc < 3)
    return 0;
  char *endptr;
  int numEvents(strtol(argv[1],&endptr,10));
  int numTime(strtol(argv[2],&endptr,10));
  Bjorklund b(numTime,numEvents);
  b.print();
  return 0;
}
