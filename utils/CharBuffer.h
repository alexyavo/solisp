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
  virtual const char& peek() override;
  virtual void set_position(size_t pos) override;
  virtual size_t remaining() const override;
  virtual size_t position() const override;

public:
  void skip_whitespace();
  const std::string& get_str() const;
  std::string get_remaining_str() const;

private:
  const char& get_char(bool incPos);
};

}
