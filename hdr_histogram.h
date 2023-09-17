#ifndef HDR_HISTOGRAM_WRAPPER_H_
#define HDR_HISTOGRAM_WRAPPER_H_

#include <hdr/hdr_histogram.h>

class HdrHistogram {
  struct hdr_histogram* histogram_ = nullptr;

 public:
  HdrHistogram(
    int64_t lowest_discernable_value,
    int64_t highest_discernable_value,
    int     significant_figures
  );

  HdrHistogram(const HdrHistogram&) = delete;
  HdrHistogram& operator=(const HdrHistogram&) = delete;

  HdrHistogram(HdrHistogram&& other);
  HdrHistogram& operator=(HdrHistogram&& other);

  ~HdrHistogram();

  bool RecordValue(int64_t value, int64_t count = 1) const noexcept;

  double  Mean() const noexcept;
  double  Stddev() const noexcept;
  double  Min() const noexcept;
  double  Max() const noexcept;
  int64_t ValueAtPercentile(double percentile) const noexcept;

  void Reset();
};

#endif
