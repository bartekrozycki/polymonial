#ifndef POLY_H
#define POLY_H

#include <stddef.h>
#include <iostream>
#include <algorithm>
#include <exception>

#define DATA_SIZE 1

class poly {
    private:
    
    double *data = nullptr;
    size_t data_size;

    public:

    poly (double val = 0)
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

    double &operator[] (const size_t size)
    {
        if (size >= data_size)
        {
            double *new_data = new double[size + 1]();
            std::copy_n(data, data_size, new_data);

            delete [] data;
            data = new_data;

            data_size = size + 1;
        }
        
        return *(data + size);
    }

    poly& operator+(const poly &arg) const
    {
        poly *p;
        if (this->data_size > arg.data_size)
        {
            p = new poly(*this);
        
            for (size_t i = 0; i < this->data_size; i++)
                p->data[i] += arg.data[i];
        }
        else 
        {
            p = new poly(arg);

            for (size_t i = 0; i < arg.data_size; i++)
                p->data[i] += this->data[i];
        }
        return *p;
    }

    poly& operator*(const poly &arg)
    {
        poly *p = new poly();

        for (size_t i = 0; i < this->data_size; i++)
        {
            for (size_t j = 0; j < arg.data_size; j++)
            {
                (*p)[i + j] += (this->data[i] * arg.data[j]); 
            }
        }

        return *p;
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
inline poly& operator*(const poly &a, const poly &b)
{
    return a*b;
}
#endif