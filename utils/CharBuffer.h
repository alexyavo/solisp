#pragma once

#include <string>

#include "BufferReader.h"

namespace utils {

class CharBuffer : public BufferReader<char> {
private:
  const std::string * m_str;
  size_t m_pos;

public:
  CharBuffer(const char * str);
  CharBuffer(const std::string& str);

  virtual const char& read() override;
  virtual const char& peek() const override;
  virtual void set_position(size_t pos) override;
  virtual size_t remaining() const override;
  virtual size_t position() const override;

public:
  void skip_whitespace();
  const std::string& get_str() const;
  std::string get_remaining_str() const;

  /*
   * Reads string until pred returns false or buffer runs
   * out of characters.
   */
  template<typename Func>
  std::string read_until(const Func& pred);

private:
  void assert_has_remaining() const;
};

template<typename Func>
std::string CharBuffer::read_until(Func const& pred) {
  std::string result {""};
  while (has_remaining() && pred(*this))
    result.append(1, read());
  return result;
}

}
