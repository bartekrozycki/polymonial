#pragma once

#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

class poly {
    private:

    std::vector<double> data; 
    
    
    public:

    poly (const double val = 0)
    {
        data.resize(1);
        data.at(0) = val;
    }
    
    double operator()(const double p) const
    {
        double val = 0;
        for (size_t i = 0; i < data.size(); i++)
            val += data[i] * (pow(p, i));
        return val;
    }

    double &operator[] (const size_t index)
    {
        if (index >= data.size())
            data.resize(index + 1);

        return data.at(index);
    }

    poly operator+(const poly &arg) const
    {
        poly p;

        for (size_t i = 0; i < data.size(); i++)
            p[i] += this->data[i];
        for (size_t i = 0; i < arg.data.size(); i++)
            p[i] += arg.data[i];
            
        return p;
    }

    friend poly operator*(const poly &larg, const poly &rarg) 
    {
        poly p;

        for (size_t i = 0; i < rarg.data.size(); i++)
            for (size_t j = 0; j < larg.data.size(); j++)
                p[i + j] += (rarg.data[i] * larg.data[j]); 

        return p;
    }

    friend std::ostream & operator<< (std::ostream& cout, const poly &p)
    {
        // A x ^ B
        for (int i = (int) p.data.size() - 1; i >= 0; --i)
        {
            if (p.data[i] == 0) continue;

            if (p.data[i] != 1)
                cout << p.data[i]; // A

            if (i == 0) // B
                continue;
            if (i == 1)
                cout << "x + ";
            else 
                cout << "x^" << i << " + ";
        }
        return cout;
    }

};
