
#ifndef LTXKEY_H
#define LTXKEY_H

//#include "NVList.hpp"
#include "String.hpp"
#include "LTXValue.hpp"

namespace LTX {
	class LTXKey {
	public:
		LTXKey(const char *keyname);
		LTXKey(const char *keyname, const char *valueSource);
		LTXKey(const String & keyname);
		LTXKey(const String & keyname, const String & valueSource);
		LTXKey(const String & keyname, const LTXValue & value);
		LTXKey(const LTXKey & key);

		~LTXKey();

		String getKeyName() const;
		LTXValue getValue() const;
		LTXValueType getValueType() const;
		bool isEmpty() const;

		LTXValue & getValue();
		void setValue(const LTXValue &);
		void setValue(const String &);
		void setKeyName(const String &);

	private:
		LTXValue *value;
		String key;

		String _CONVERTSTRINGVALUE(const String & value);

	};
}
#endif //LTXKEY_H
