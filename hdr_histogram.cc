#include "hdr_histogram.h"

#include <algorithm>
#include <cstring>
#include <stdexcept>

HdrHistogram::HdrHistogram(
  int64_t lowest_discernable_value,
  int64_t highest_discernable_value,
  int     significant_figures
) {
  auto ret = hdr_init(lowest_discernable_value, highest_discernable_value, significant_figures, &histogram_);
  if (ret != 0) {
    throw std::runtime_error{std::string("failed to initialize hdr histogram: ") + std::strerror(ret)};
  }
}

HdrHistogram::HdrHistogram(HdrHistogram&& other) : histogram_(std::exchange(other.histogram_, nullptr)) {
}

HdrHistogram& HdrHistogram::operator=(HdrHistogram&& other) {
  std::swap(other.histogram_, histogram_);
  return *this;
}

HdrHistogram::~HdrHistogram() {
  hdr_close(histogram_);
}

bool HdrHistogram::RecordValue(int64_t value, int64_t count) const noexcept {
  return hdr_record_values_atomic(histogram_, value, count);
}

double HdrHistogram::Mean() const noexcept {
  return hdr_mean(histogram_);
}

double HdrHistogram::Stddev() const noexcept {
  return hdr_stddev(histogram_);
}

double HdrHistogram::Min() const noexcept {
  return hdr_min(histogram_);
}

double HdrHistogram::Max() const noexcept {
  return hdr_max(histogram_);
}

int64_t HdrHistogram::ValueAtPercentile(double percentile) const noexcept {
  return hdr_value_at_percentile(histogram_, percentile);
}

void HdrHistogram::Reset() {
  hdr_reset(histogram_);
}
