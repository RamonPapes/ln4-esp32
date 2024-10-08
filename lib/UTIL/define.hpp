#ifndef DEFINE_HPP
#define DEFINE_HPP

#define printlnf(txt, ...) printf(txt "\r\n", ##__VA_ARGS__)
#define signum(value) ((float)value >= 0)? 1:-1

#endif