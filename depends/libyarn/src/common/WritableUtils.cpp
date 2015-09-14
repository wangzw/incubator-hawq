/********************************************************************
 * Copyright (c) 2014, Pivotal Inc.
 * All rights reserved.
 *
 * Author: Zhanwei Wang
 ********************************************************************/
#include <stdexcept>
#include <limits>
#include <cstring>
#include <arpa/inet.h>

#include "WritableUtils.h"

namespace Yarn {
namespace Internal {

WritableUtils::WritableUtils(char * b, size_t l) :
    buffer(b), len(l), current(0) {
}

bool WritableUtils::ReadInt32(int32_t * value) {
    int64_t val;

    if (ReadInt64(&val)
            && (val >= std::numeric_limits<int32_t>::min()
                && val <= std::numeric_limits<int32_t>::max())) {
        *value = val;
        return true;
    }

    return false;
}

bool WritableUtils::ReadInt64(int64_t * value) {
    try {
        int firstByte = readByte();
        int len = decodeWritableUtilsSize(firstByte);

        if (len == 1) {
            *value = firstByte;
            return true;
        }

        long i = 0;

        for (int idx = 0; idx < len - 1; idx++) {
            unsigned char b = readByte();
            i = i << 8;
            i = i | (b & 0xFF);
        }

        *value = (isNegativeWritableUtils(firstByte) ? (i ^ -1L) : i);
        return true;
    } catch (const std::range_error &) {
        return false;
    }
}

bool WritableUtils::readByte(char * byte) {
    try {
        *byte = readByte();
        return true;
    } catch (const std::range_error &) {
        return false;
    }
}

bool WritableUtils::ReadRaw(char * buf, size_t size) {
    if (size + current >= len) {
        return false;
    }

    memcpy(buf, buffer + current, size);
    current += size;
    return true;
}

bool WritableUtils::ReadString(std::string & str) {
    try {
        int32_t len = ReadBigEndian32();
        str.resize(len + 1);
        ReadRaw(&str[0], len);
        str[len] = 0;
    } catch (const std::range_error &) {
        return false;
    }

    return true;
}

bool WritableUtils::ReadText(std::string & str) {
    try {
        int32_t len;

        if (!ReadInt32(&len)) {
            return false;
        }

        if (len == 0) {
            str.clear();
            return true;
        }

        str.resize(len + 1);
        ReadRaw(&str[0], len);
        str[len] = 0;
    } catch (const std::range_error &) {
        return false;
    }

    return true;
}

size_t WritableUtils::WriteInt32(int32_t value) {
    return WriteInt64(value);
}

size_t WritableUtils::WriteInt64(int64_t value) {
    size_t retval = 1;

    if (value >= -112 && value <= 127) {
        writeByte((int) value);
        return retval;
    }

    int len = -112;

    if (value < 0) {
        value ^= -1L; // take one's complement'
        len = -120;
    }

    long tmp = value;

    while (tmp != 0) {
        tmp = tmp >> 8;
        len--;
    }

    ++retval;
    writeByte((int) len);
    len = (len < -120) ? -(len + 120) : -(len + 112);

    for (int idx = len; idx != 0; idx--) {
        int shiftbits = (idx - 1) * 8;
        long mask = 0xFFL << shiftbits;
        ++retval;
        writeByte((int)((value & mask) >> shiftbits));
    }

    return retval;
}

bool WritableUtils::WriteRaw(const char * buf, size_t size) {
    if (current + size >= len) {
        return false;
    }

    memcpy(buffer + current, buf, size);
    current += size;
    return true;
}

int WritableUtils::decodeWritableUtilsSize(int value) {
    if (value >= -112) {
        return 1;
    } else if (value < -120) {
        return -119 - value;
    }

    return -111 - value;
}

int WritableUtils::readByte() {
    if (current >= len) {
        throw std::range_error("overflow");
    }

    return buffer[current++];
}

void WritableUtils::writeByte(int val) {
    if (current >= len) {
        throw std::range_error("overflow");
    }

    buffer[current++] = val;
}

bool WritableUtils::isNegativeWritableUtils(int value) {
    return value < -120 || (value >= -112 && value < 0);
}

int32_t WritableUtils::ReadBigEndian32() {
    char buf[sizeof(int32_t)];

    for (size_t i = 0; i < sizeof(int32_t); ++i) {
        buf[i] = readByte();
    }

    return ntohl(*(uint32_t *) buf);
}

}
}
