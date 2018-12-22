#include <cstddef>
#include <stdexcept>

template <typename T>
class Nullable final
{
public:
    Nullable();
    Nullable(const T &value);
    Nullable(nullptr_t nullpointer);
    const Nullable<T> & operator=(const Nullable<T> &value);
    const Nullable<T> & operator=(const T &value);
    const Nullable<T> & operator=(nullptr_t nullpointer);
    bool HasValue() const;
    const T & GetValueOrDefault() const;
    const T & GetValueOrDefault(const T &def) const;
    bool TryGetValue(T &value) const;

public:
        class NullableValue final
        {
        public:
            friend class Nullable;

        private:
            NullableValue();
            NullableValue(const T &value);

        public:
            NullableValue & operator=(const NullableValue &) = delete;
            operator const T &() const;
            const T & operator*() const;
            const T * operator&() const;

            // https://stackoverflow.com/questions/42183631/inability-to-overload-dot-operator-in-c
            const T * operator->() const;

        public:
            template <typename T2>
                friend bool operator==(const Nullable<T2> &op1, const Nullable<T2> &op2);
            
            template <typename T2>
                friend bool operator==(const Nullable<T2> &op, const T2 &value);
            
            template <typename T2>
                friend bool operator==(const T2 &value, const Nullable<T2> &op);
            
            template <typename T2>
                friend bool operator==(const Nullable<T2> &op, nullptr_t nullpointer);
            
            template <typename T2>
                friend bool operator!=(const Nullable<T2> &op1, const Nullable<T2> &op2);
            
            template <typename T2>
                friend bool operator!=(const Nullable<T2> &op, const T2 &value);
            
            template <typename T2>
                friend bool operator!=(const T2 &value, const Nullable<T2> &op);
            
            template <typename T2>
                friend bool operator==(nullptr_t nullpointer, const Nullable<T2> &op);
            
            template <typename T2>
                friend bool operator!=(const Nullable<T2> &op, nullptr_t nullpointer);
            
            template <typename T2>
                friend bool operator!=(nullptr_t nullpointer, const Nullable<T2> &op);
            
        private:
            void checkHasValue() const;
            
        private:
            bool m_hasValue;
            T m_value;
        };
        
public:
        NullableValue Value;
};

template <typename T>
Nullable<T>::NullableValue::NullableValue()
: m_hasValue(false), m_value(T()) { }

template <typename T>
Nullable<T>::NullableValue::NullableValue(const T &value)
: m_hasValue(true), m_value(value) { }

template <typename T>
Nullable<T>::NullableValue::operator const T &() const
{
    checkHasValue();
    return m_value;
}

template <typename T>
const T & Nullable<T>::NullableValue::operator*() const
{
    checkHasValue();
    return m_value;
}

template <typename T>
const T * Nullable<T>::NullableValue::operator&() const
{
    checkHasValue();
    return &m_value;
}

template <typename T>
const T * Nullable<T>::NullableValue::operator->() const
{
    checkHasValue();
    return &m_value;
}

template <typename T>
void Nullable<T>::NullableValue::checkHasValue() const
{
    if (!m_hasValue)
        throw std::exception("Nullable object must have a value");
}

template <typename T>
bool Nullable<T>::HasValue() const { return Value.m_hasValue; }

template <typename T>
const T & Nullable<T>::GetValueOrDefault() const
{
    return Value.m_value;
}

template <typename T>
const T & Nullable<T>::GetValueOrDefault(const T &def) const
{
    if (Value.m_hasValue)
        return Value.m_value;
    else
        return def;
}

template <typename T>
bool Nullable<T>::TryGetValue(T &value) const
{
    value = Value.m_value;
    return Value.m_hasValue;
}

template <typename T>
Nullable<T>::Nullable() { }

template <typename T>
Nullable<T>::Nullable(nullptr_t nullpointer) { (void)nullpointer; }

template <typename T>
Nullable<T>::Nullable(const T &value)
: Value(value) { }

template <typename T2>
bool operator==(const Nullable<T2> &op1, const Nullable<T2> &op2)
{
    if (op1.Value.m_hasValue != op2.Value.m_hasValue)
        return false;
    
    if (op1.Value.m_hasValue)
        return op1.Value.m_value == op2.Value.m_value;
    else
        return true;
}

template <typename T2>
bool operator==(const Nullable<T2> &op, const T2 &value)
{
    if (!op.Value.m_hasValue)
        return false;
    
    return op.Value.m_value == value;
}

template <typename T2>
bool operator==(const T2 &value, const Nullable<T2> &op)
{
    if (!op.Value.m_hasValue)
        return false;
    
    return op.Value.m_value == value;
}

template <typename T2>
bool operator==(const Nullable<T2> &op, nullptr_t nullpointer)
{
    (void)nullpointer;
    return !op.Value.m_hasValue;
}

template <typename T2>
bool operator==(nullptr_t nullpointer, const Nullable<T2> &op)
{
    (void)nullpointer;
    return !op.Value.m_hasValue;
}

template <typename T2>
bool operator!=(const Nullable<T2> &op1, const Nullable<T2> &op2)
{
    if (op1.Value.m_hasValue != op2.Value.m_hasValue)
        return true;
    
    if (op1.Value.m_hasValue)
        return op1.Value.m_value != op2.Value.m_value;
    else
        return false;
}

template <typename T2>
bool operator!=(const Nullable<T2> &op, const T2 &value)
{
    if (!op.Value.m_hasValue)
        return true;
    
    return op.Value.m_value != value;
}

template <typename T2>
bool operator!=(const T2 &value, const Nullable<T2> &op)
{
    if (!op.Value.m_hasValue)
        return false;
    
    return op.Value.m_value != value;
}

template <typename T2>
bool operator!=(const Nullable<T2> &op, nullptr_t nullpointer)
{
    (void)nullpointer;
    return op.Value.m_hasValue;
}

template <typename T2>
bool operator!=(nullptr_t nullpointer, const Nullable<T2> &op)
{
    (void)nullpointer;
    return op.Value.m_hasValue;
}

template <typename T>
const Nullable<T> & Nullable<T>::operator=(const Nullable<T> &value)
{
    Value.m_hasValue = value.Value.m_hasValue;
    Value.m_value = value.Value.m_value;
    return *this;
}

template <typename T>
const Nullable<T> & Nullable<T>::operator=(const T &value)
{
    Value.m_hasValue = true;
    Value.m_value = value;
    return *this;
}
        
template <typename T>
const Nullable<T> & Nullable<T>::operator=(nullptr_t nullpointer)
{
    (void)nullpointer;
    Value.m_hasValue = false;
    Value.m_value = T();
    return *this;
}
            
