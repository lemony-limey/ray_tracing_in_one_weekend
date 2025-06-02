#ifndef INTERVAL_H
#define INTERVAL_H

class interval
{
public:
    // Public attributes
    double min, max;

    // Constructors
    interval() : min(+infinity), max(-infinity) {} // Default interval is empty
    interval(double min, double max) : min(min), max(max) {}

    // Methods
    double size() const
    {
        return max - min;
    }

    bool contains(double x) const
    {
        return (min <= x) && (x <= max);
    }

    bool surrounds(double x) const
    {
        return (min < x) && (x < max);
    }

    // Static attributes (public visibility)
    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif // INTERVAL_H