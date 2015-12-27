
/*
 * LTXValue C++11 version
 */

#ifndef LTXVALUE_H
#define LTXVALUE_H

#include <initializer_list>
#include "NVList.hpp"
#include "String.hpp"
//#include "LTXKey.hpp"

namespace LTX {

	enum class LTXValueType {
		EMPTY = -0x01,
		NULL = 0x01,
		INTNUMBER = 0x02,
		FLOATNUMBER = 0x04,
		NUMBER = (0x02 | 0x04),
		BOOLEAN = 0x08,
		PAIR = 0x10,
		BLOCK = 0x20,
		STRING = 0x40,
		LINK = 0x80,
		ARRAY = 0x100;
	};

	class LTXValue {
		//friend class LTXKey;

	public:
		LTXValue();
		LTXValue(const char *keyname);
		LTXValue(const char *keyname, const char *value);
		LTXValue(const char *keyname, const LTXValue & value);
		LTXValue(const LTXValue & value);
		//LTXValue(const String & keyname);
		LTXValue(const String & keyname, const String & value);
		LTXValue(const String & keyname, const LTXValue & value);
		LTXValue(const String &, bool);
		LTXValue(const String &, long);
		LTXValue(const String &, long double);
		LTXValue(const String &, const ArrayList<LTXValue> &);
		//LTXValue(LTXValue & value);
		//LTXValue(const LTXValue && value);
		//LTXValue(const char *keyname, LTXValue & value);
		//LTXValue(const char *keyname, LTXValue && value);
		~LTXValue();
	private:
		String key;
		//LTXKey *parent;
		//-------------------------------------
		LTXValueType type;
		long *intnumber = nullptr;
		long double *floatnumber = nullptr;
		bool *boolean = nullptr;
		String *string = nullptr;
		LTXValue *pair = nullptr;
		ArrayList<LTXValue> *block = nullptr;

	// Const getter functions
	public:
		int getIntegerValue() const;
		long getLongValue() const;
		float getFloatValue() const;
		double getDoubleValue() const;
		bool getBooleanValue() const;
		long double getLongDoubleValue() const;
		const char * getConstCharValue() const;
		String getStringValue() const;
		ArrayList<LTXValue> getBlockValue() const;
		LTXValue getPairValue() const;
		LTXValueType getType() const;
		bool equalBlockEntries(std::initializer_list<LTXValueType> types) const;
		//bool equalBlockEntries(const ArrayList<LTXValueType> types) const;

		//const char * getKey() const;
		String getKey() const;

		void clear();

		LTXValue & operator = (const LTXValue &);

		//void operator =(const LTXValue &val);
		static ArrayList<String> formvalues(const String &);
	private:
		void parceValue(const String &);
		//ArrayList<string> formvalues(const char *value);
		void allocate();
	};

	class LTXNumber : public LTXValue
	{
		long double * num;
		long long int * inum;
	public:
		LTXNumber();
		LTXNumber(short);
		LTXNumber(int);
		LTXNumber(long);
		LTXNumber(float);
		LTXNumber(double);
		LTXNumber(long double);
		LTXNumber(const String &);
		~LTXNumber();

		bool isInteger();
		bool isFloat();

		long long int getIntValue() const;
		long double getFloatValue() const;
	};

	class LTXArray : public LTXValue
	{
		LTXValue * val;
		unsigned short size;
	public:
		LTXArray();
	};

	class LTXPair : public LTXValue
	{
		String key;
		LTXValue * val;
	public:
		LTXPair(String, const LTXValue *);
		~LTXPair();

		String getKey() const;
		LTXValue getValue() const;
		LTXValueType getValueType() const;
	};
}

#endif
