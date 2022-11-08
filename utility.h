#ifndef UTILITY_H
#define UTILITY_H

#include <QVector>

class Utility
{
public:
    Utility();
    static int max(QVector<int> vector);
    static int min(QVector<int> vector);
};

#endif // UTILITY_H
