#ifndef DECISION_MESSAGES_IPROTO_CONVERTIBLE
#define DECISION_MESSAGES_IPROTO_CONVERTIBLE

namespace decision {

template <class T>
class IProtoConvertible {
 public:
  IProtoConvertible() = default;

  IProtoConvertible(const IProtoConvertible&) = delete;
  IProtoConvertible& operator=(const IProtoConvertible&) = delete;
  IProtoConvertible(IProtoConvertible&&) noexcept = default;
  IProtoConvertible& operator=(IProtoConvertible&&) noexcept = default;

  virtual ~IProtoConvertible() = default;

  virtual T toProto() const = 0;
};

} // namespace decision

#endif // DECISION_MESSAGES_IPROTO_CONVERTIBLE
