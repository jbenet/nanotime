#ifndef __NOMINAL_H__
#define __NOMINAL_H__

// Nominal and Ordinal implementation based on David R. Cheriton's approach
// Author: jbenet


namespace Fwk {

template<class UnitType, class RepType>
class Nominal {
public:
    Nominal(RepType v) : value_(v) {}

  bool operator==(const Nominal<UnitType, RepType>& v) const
  { return value_ == v.value_; }

  bool operator!=(const Nominal<UnitType, RepType>& v) const
  { return value_ != v.value_; }

  const Nominal<UnitType, RepType>& operator=(const Nominal<UnitType,
    RepType>& v) { value_ = v.value_; return *this; }

  RepType value() const
  { return value_; }

protected:
  RepType value_;
};


template<class UnitType, class RepType>
class Ordinal : public Nominal<UnitType, RepType> {
public:
    Ordinal(RepType v) : Nominal<UnitType, RepType>(v) {}

  bool operator<(const Ordinal<UnitType, RepType>& v) const
    { return Nominal<UnitType, RepType>::value_ < v.value_; }

  bool operator<=(const Ordinal<UnitType, RepType>& v) const
    { return Nominal<UnitType, RepType>::value_ <= v.value_; }

  bool operator>(const Ordinal<UnitType, RepType>& v) const
    { return Nominal<UnitType, RepType>::value_ > v.value_; }

  bool operator>=(const Ordinal<UnitType, RepType>& v) const
    { return Nominal<UnitType, RepType>::value_ >= v.value_; }

  Ordinal<UnitType, RepType> operator+(const Ordinal<UnitType, RepType>& other)
    { return (Nominal<UnitType, RepType>::value_ + other.value_); }

  Ordinal<UnitType, RepType> operator+=(const Ordinal<UnitType, RepType>& other)
    { Nominal<UnitType, RepType>::value_ += other.value_; return *this; }

  Ordinal<UnitType, RepType> operator-(const Ordinal<UnitType, RepType>& other)
    { return (Nominal<UnitType, RepType>::value_ - other.value_); }

  Ordinal<UnitType, RepType> operator-=(const Ordinal<UnitType, RepType>& other)
    { Nominal<UnitType, RepType>::value_ -= other.value_; return *this; }

  Ordinal<UnitType, RepType> operator/(const Ordinal<UnitType, RepType>& other)
    { return (Nominal<UnitType, RepType>::value_ / other.value_); }

  operator UnitType() const
    { return UnitType(Nominal<UnitType, RepType>::value_); }

  const Ordinal<UnitType, RepType>& operator++()
    { ++Nominal<UnitType, RepType>::value_; return *this; }

  const Ordinal<UnitType, RepType>& operator--()
    { --Nominal<UnitType, RepType>::value_; return *this; }
};

} // end namespace Fwk

#endif // __NOMINAL_H__
