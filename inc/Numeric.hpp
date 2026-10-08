#ifndef NUMERIC_HPP
#define NUMERIC_HPP

#include <memory>

class Numeric{
    public:
        virtual ~Numeric() = default;
        
        //Add Arithmetic Method
        virtual std::unique_ptr<Numeric> add(const Numeric& other) const = 0;
        
        //Subtract Arithmetic Method
        virtual std::unique_ptr<Numeric> subtract(const Numeric& other) const = 0;
        
        //Multiply Arithmetic Method
        virtual std::unique_ptr<Numeric> multiply(const Numeric& other) const = 0;
        
        //Divide Arithmetic Method
        virtual std::unique_ptr<Numeric> divide(const Numeric& other) const = 0;

        //Comparison Methods
        virtual bool isLessThan(const Numeric& other) const = 0;
        virtual bool isGreaterThan(const Numeric& other) const = 0;
        virtual bool isEqualTo(const Numeric& other) const = 0;

        //Helper Functions
        virtual void print(std::ostream&) = 0;
        virtual std::string toString() const = 0;
};

#endif
