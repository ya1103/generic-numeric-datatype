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

        std::string toString() const override {
            std::ostringstream oss;
            oss << value; // Formats as (real, imag)
            return oss.str();
        }
        
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
                throw std::invalid_argument("Cannot perform subtraction on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value - ptr->getValue());

        }

        std::unique_ptr<Numeric> multiply(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform multiplication on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value * ptr->getValue());

        }

        std::unique_ptr<Numeric> divide(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<T>*>(&other);

            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform division on non-matching numeric types!");
            }

            return std::make_unique<NumericType<T>>(this->value / ptr->getValue());

        }

        bool isLessThan(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(other);
                return this->value < ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }
        }

        bool isGreaterThan(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(other);
                return this->value > ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }        
        }

        bool isEqualTo(const Numeric& other) const override
        {
            try{
                auto ptr = dynamic_cast<const NumericType<T>&>(other);
                return this->value == ptr.getValue();
            } 
            catch(const std::bad_cast&)
            {
                throw std::invalid_argument("Cannot compare between non-matching numeric types!");
            }       
        }

        void print(std::ostream& os) override{
            os << value;
        }
};

#include <complex>

//Full specialization for std::complex
template<>
class NumericType<std::complex<double>> : public Numeric{
    private:
        std::complex<double> value;
    public:
        NumericType(std::complex<double> val) : value(val) {}

        const std::complex<double>& getValue() const {return value;}

        std::string toString() const override {
            std::ostringstream oss;
            oss << value; // Formats as (real, imag)
            return oss.str();
        }
        std::unique_ptr<Numeric> add(const Numeric& other) const override
        {
            auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
            
            //Check if cast is valid
            if(ptr == nullptr)
            {
                throw std::invalid_argument("Cannot perform addition on non-matching numeric types!");
            }

            return std::make_unique<NumericType<std::complex<double>>>(this->value + ptr->getValue());
        
        }
    std::unique_ptr<Numeric> subtract(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot perform subtraction on non-matching numeric types!");
        }
        return std::make_unique<NumericType<std::complex<double>>>(this->value - ptr->getValue());
    }

    std::unique_ptr<Numeric> multiply(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot perform multiplication on non-matching numeric types!");
        }
        return std::make_unique<NumericType<std::complex<double>>>(this->value * ptr->getValue());
    }

    std::unique_ptr<Numeric> divide(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot perform division on non-matching numeric types!");
        }
        return std::make_unique<NumericType<std::complex<double>>>(this->value / ptr->getValue());
    }

    // --- Comparisons based on Absolute Magnitude ---
    bool isLessThan(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot compare non-matching numeric types!");
        }
        return std::abs(this->value) < std::abs(ptr->getValue());
    }

    bool isGreaterThan(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot compare non-matching numeric types!");
        }
        return std::abs(this->value) > std::abs(ptr->getValue());
    }

    bool isEqualTo(const Numeric& other) const override {
        auto ptr = dynamic_cast<const NumericType<std::complex<double>>*>(&other);
        if (!ptr) {
            throw std::invalid_argument("Cannot compare non-matching numeric types!");
        }
        return this->value == ptr->getValue();
    }
};

#endif
