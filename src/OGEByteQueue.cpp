/*****************************************************************************
*   Open-source Game Engine (OGE) 0.1.0 programmed in C++
******************************************************************************
*   Copyright (C) 2016 - Fernando Alan Quinteros, 10th Dec 2015.
*   http://email:lordfers@gmail.com
******************************************************************************
*   This program is open-source and free software.
*   OGE used the standard libraries CEGUI 8.4.x and DirectX 9.
*   https://github.com/LordFers/OGE.git
*****************************************************************************/
#include "OGEByteQueue.hpp"

#define BOOST_NO_CXX11_SCOPED_ENUMS
#define BOOST_NO_SCOPED_ENUMS

#include <locale>
#include <codecvt>

OGEByteQueue::OGEByteQueue() : readPos(0) { }

void OGEByteQueue::commitRead(int pos) {
	data.erase(data.begin(), data.begin() + pos);
	readPos -= pos;
}

void OGEByteQueue::revertRead(int oldPos) {
	readPos = oldPos;
}

void OGEByteQueue::WriteByte(std::int8_t value) {
	data.push_back(static_cast<std::int8_t>(0xff & value));
}

void OGEByteQueue::WriteInteger(std::int16_t value) {
	union {
		std::int16_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void OGEByteQueue::WriteLong(std::int32_t value) {
	union {
		std::int32_t a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void OGEByteQueue::WriteSingle(float value) {
	union {
		float a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void OGEByteQueue::WriteDouble(double value) {
	union {
		double a;
		std::int8_t b[8];
	} w;
	w.a = value;
	data.insert(data.end(), w.b, w.b + sizeof(w.a));
}

void OGEByteQueue::WriteBoolean(bool value) {
	data.push_back(value ? 1 : 0);
}

void OGEByteQueue::WriteUnicodeStringFixed(const std::string& value) {
	WriteBinaryFixed(value);
}

void OGEByteQueue::WriteUnicodeString(const std::string& value) {
	WriteBinary(value);
}

void OGEByteQueue::WriteBinary(const std::string& value) {
	WriteInteger((short)value.size());
	WriteBinaryFixed(value);
}

void OGEByteQueue::WriteBlock(const char* buf, int n) {
	data.insert(data.end(), buf, buf + n);
}

std::string OGEByteQueue::ReadASCIIFixed(int length) {
	return PeekBinaryFixed(length);
}

std::string OGEByteQueue::ReadBinaryFixed(int length) {
	std::string tmp = PeekBinaryFixed(length);
	readPos += tmp.size();
	return tmp;
}

std::string OGEByteQueue::ReadUnicodeStringFixed(int length) {
	return ReadBinaryFixed(length);
}

std::string OGEByteQueue::ReadBinary() {
	std::string tmp = PeekBinary();
	readPos += tmp.size() + 2;
	return tmp;
}

std::string OGEByteQueue::ReadUnicodeString() {
	return ReadBinary();
}

std::string OGEByteQueue::PeekBinaryFixed(std::size_t length) {
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p, p + length);
}

std::string OGEByteQueue::PeekUnicodeStringFixed(int length) {
	return PeekBinaryFixed(length);
}

std::string OGEByteQueue::PeekBinary() {
	std::size_t length = PeekInteger();
	if (length > BQ_MAX_STRING_SIZE)
		throw bytequeue_data_error("length > BQ_MAX_STRING_SIZE");
	if (readPos + length + 2 > data.size())
		throw insufficient_data_error();
	const char* p = reinterpret_cast<const char*>(data.data() + readPos);
	return std::string(p + 2, p + 2 + length);
}

std::string OGEByteQueue::PeekUnicodeString() {
	return PeekBinary();
}

int OGEByteQueue::length() {
	return data.size() - readPos;
}