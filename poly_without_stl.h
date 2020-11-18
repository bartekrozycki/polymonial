#pragma once

#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <math.h>

#define DATA_SIZE 1

class poly {
    private:

    double *data = nullptr;
    size_t data_size;


    public:

    poly (const double val = 0)
    {
        data = new double[DATA_SIZE];
        data_size = DATA_SIZE;
        data[0] = val;
    }

    poly (const poly &o)
    {
        this->data = new double[o.data_size]();
        this->data_size = o.data_size;
        std::copy_n(o.data, o.data_size, this->data);
    }

    ~poly ()
    {
        delete [] data;
    }
    
    double operator()(const double p) const
    {
        double val = 0;
        for (size_t i = 0; i < data_size; i++)
            val += data[i] * (pow(p, i));
        return val;
    }

    poly & operator =( const poly & o)
    {
        double *data_new = new double[o.data_size];

        delete [] data; 
        data = data_new;

        std::copy_n(o.data, o.data_size, data);
        data_size = o.data_size;

        return *this;
    }

    double &operator[] (const size_t size)
    {
        if (size >= data_size)
        {
            double *data_new = new double[size + 1]();
            std::copy_n(data, data_size, data_new);

            delete [] data;
            data = data_new;

            data_size = size + 1;
        }
        
        return *(data + size);
    }

    poly operator+(const poly &arg) const
    {
        poly p;

        for (size_t i = 0; i < this->data_size; i++)
            p[i] += this->data[i];
        for (size_t i = 0; i < arg.data_size; i++)
            p[i] += arg.data[i];
            
        return p;
    }

    friend poly operator*(const poly &larg, const poly &rarg) 
    {
        poly p;

        for (size_t i = 0; i < rarg.data_size; i++)
            for (size_t j = 0; j < larg.data_size; j++)
                p[i + j] += (rarg.data[i] * larg.data[j]); 

        return p;
    }

    friend std::ostream & operator<< (std::ostream& cout, const poly &p)
    {
        // A x ^ B
        for (int i = (int) p.data_size - 1; i >= 0; --i)
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
