#ifndef ZEDIT_CLASS_TEXTCONVERTER_DEFINED

#define ZEDIT_CLASS_TEXTCONVERTER_DEFINED

// https://qiita.com/benikabocha/items/e943deb299d0f816f161

#include <vector>
#include <array>
#include <string>
#include <stdexcept>

class TextConverter {
  private:
    static int getU8ByteCount(const char c);
    static bool isU8LaterByte(char c);
    static char32_t convertCharU8ToU32(const std::array<char, 4>& u8c);
  public:
    static std::vector<char32_t> u8to32(const std::string& u8Str);
};

int TextConverter::getU8ByteCount(const char c) {
  if (0 <= uint8_t(c) && uint8_t(c) < 0x80) return 1;
  if (0xC2 <= uint8_t(c) && uint8_t(c) < 0xE0) return 2;
  if (0xE0 <= uint8_t(c) && uint8_t(c) < 0xF0) return 3;
  if (0xF0 <= uint8_t(c) && uint8_t(c) < 0xF8) return 4;
  throw std::runtime_error("Invalid char");
}

bool TextConverter::isU8LaterByte(char c) {
  return 0x80 <= uint8_t(c) && uint8_t(c) < 0xC0;
}

char32_t TextConverter::convertCharU8ToU32(const std::array<char, 4>& u8c) {
  char32_t u32c;
  int numBytes = getU8ByteCount(u8c[0]);
  switch (numBytes) {
    case 1:
      u32c = char32_t(uint8_t(u8c[0]));
      break;
    case 2:
      if (!isU8LaterByte(u8c[1])) {
        throw std::runtime_error("u8c[1] is not utf-8 later byte.");
      }
      if ((uint8_t(u8c[0]) & 0x1E) == 0) {
        throw std::runtime_error("not valid utf-8 char.");
      }

      u32c = char32_t(u8c[0] & 0x1F) << 6;
      u32c |= char32_t(u8c[1] & 0x3F);
      break;
    case 3:
      if (!isU8LaterByte(u8c[1]) || !isU8LaterByte(u8c[2])) {
        throw std::runtime_error("u8c[1] or u8c[2] is not utf-8 later byte.");
      }
      if ((uint8_t(u8c[0]) & 0x0F) == 0 &&
          (uint8_t(u8c[1]) & 0x20) == 0) {
        throw std::runtime_error("not valid utf-8 char.");
      }

      u32c = char32_t(u8c[0] & 0x0F) << 12;
      u32c |= char32_t(u8c[1] & 0x3F) << 6;
      u32c |= char32_t(u8c[2] & 0x3F);
      break;
    case 4:
      if (!isU8LaterByte(u8c[1]) || !isU8LaterByte(u8c[2]) ||
          !isU8LaterByte(u8c[3])) {
        throw std::runtime_error("u8c[1] or u8c[2] or u8c[3] is not utf-8 later byte.");
      }
      if ((uint8_t(u8c[0]) & 0x07) == 0 &&
          (uint8_t(u8c[1]) & 0x30) == 0) {
        throw std::runtime_error("not valid utf-8 char.");
      }

      u32c = char32_t(u8c[0] & 0x07) << 18;
      u32c |= char32_t(u8c[1] & 0x3F) << 12;
      u32c |= char32_t(u8c[2] & 0x3F) << 6;
      u32c |= char32_t(u8c[3] & 0x3F);
      break;
    default:
      throw std::runtime_error("invalid byte count.");
  }

  return u32c;
}

std::vector<char32_t> TextConverter::u8to32(const std::string& u8s) {
  std::vector<char32_t> u32s;
  for (auto u8It = u8s.begin(); u8It != u8s.end(); ++u8It) {
    auto numBytes = getU8ByteCount((*u8It));

    std::array<char, 4> u8c;
    u8c[0] = (*u8It);
    for (int i = 1; i < numBytes; i++) {
      ++u8It;
      /*if (u8It == u8s.end()) {
        return false;
      }*/
      u8c[i] = (*u8It);
    }

    char32_t u32c = convertCharU8ToU32(u8c);
    u32s.emplace_back(u32c);
  }
  return u32s;
}

#endif
