#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
  time_t prev_time;
public:
  Timer() {
  }
  void Start() {
    prev_time = clock();
  }
  double GetMs() {
    time_t current_time = clock();
    double ms = static_cast<double> (current_time - prev_time) / CLOCKS_PER_SEC * 1000;
    prev_time = current_time;
    return ms;
  }
};

#endif
