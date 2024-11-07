#ifndef ROBOCIN_UTILITY_IPROTO_CONVERTIBLE
#define ROBOCIN_UTILITY_IPROTO_CONVERTIBLE

namespace robocin {

template <class T>
class IProtoConvertible {
 public:
  IProtoConvertible() = default;

  IProtoConvertible(const IProtoConvertible&) = default;
  IProtoConvertible& operator=(const IProtoConvertible&) = default;
  IProtoConvertible(IProtoConvertible&&) noexcept = default;
  IProtoConvertible& operator=(IProtoConvertible&&) noexcept = default;

  virtual ~IProtoConvertible() = default;

  
  virtual T toProto() const = 0;
  virtual void fromProto(const T& proto) = 0;
};

} // namespace robocin

#endif // ROBOCIN_UTILITY_IPROTO_CONVERTIBLE
