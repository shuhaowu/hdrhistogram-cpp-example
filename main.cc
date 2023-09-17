#include <iostream>

#include "hdr_histogram.h"

int main() {
  HdrHistogram histogram(1, 1000000, 4);
  histogram.RecordValue(0, 10);
  histogram.RecordValue(2, 10);
  histogram.RecordValue(4, 10);
  histogram.RecordValue(6, 10);

  std::cout << histogram.Mean() << "\n";
  return 0;
}
