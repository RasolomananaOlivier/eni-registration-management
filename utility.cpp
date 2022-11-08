#include "utility.h"

Utility::Utility()
{

}

int Utility::max(QVector<int> vector) {
    int m = vector[0];

    for (int i = 1 ; i < vector.size() ; ++i ) {
        if(m < vector[i]){
            m = vector[i];
        }

    }
    return m;
}

int Utility::min(QVector<int> vector){
    int m = vector[0];

    for (int i = 1 ; i < vector.size() ; ++i ) {
        if(m > vector[i]){
            m = vector[i];
        }

    }
    return m;
}
