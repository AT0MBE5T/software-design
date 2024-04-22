#ifndef TIMES_H
#define TIMES_H

class Times{
    int hours, minutes, seconds;
public:
    Times(int _hr, int _min, int _sec);
    static Times getTime(int _milliseconds);
    int getSeconds() const;
    int getMinutes() const;
    int getHours() const;
};

#endif // TIMES_H
