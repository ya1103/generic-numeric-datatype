#ifndef NUMERICTYPE_HPP
#define NUMERICTYPE_HPP

#include "Numeric.hpp"
#include "stdexcept"

template<typename T>
class NumericType: public Numeric{
    private:
        T value;
    public:
        NumericType(T val) : value(val){}

        T getValue() const {return value;}
        
        std::unique_ptr<Numeric> add(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform addition on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value + ptr->getValue());

        } 

        std::unique_ptr<Numeric> subtract(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform addition on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value - ptr->getValue());

        }

        std::unique_ptr<Numeric> multiply(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform addition on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value * ptr->getValue());

        }

        std::unique_ptr<Numeric> divide(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform addition on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value / ptr->getValue());

        }

        bool isLessThan(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(&other);
                return this->value < ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }
            //expecting compiler error
        }

        bool isGreaterThan(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(&other);
                return this->value > ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }
            //expecting compiler error            
        }

        bool isEqualTo(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(&other);
                return this->value == ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }
            //expecting compiler error            
        }
};

#endif
