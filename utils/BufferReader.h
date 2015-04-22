#pragma once

namespace utils {

template<typename T>
class BufferReader {
public:
  virtual ~BufferReader() = 0;

public:
  virtual const T& read() = 0;
  virtual const T& peek() = 0;
  virtual void set_position(size_t pos) = 0;
  virtual size_t remaining() const = 0;
  virtual size_t position() const = 0;

public:
  void reset();
  size_t skip(size_t toSkip);
  bool has_remaining() const;
};

template<typename T>
BufferReader<T>::~BufferReader() {}

template<typename T>
bool BufferReader<T>::has_remaining() const {
  return remaining() > 0;
}

template<typename T>
void BufferReader<T>::reset() {
  set_position(0);
}

template<typename T>
size_t BufferReader<T>::skip(size_t toSkip) {
  size_t actualToSkip = std::min(toSkip, remaining());
  set_position(position() + actualToSkip);
  return actualToSkip;
}

}