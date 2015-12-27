#include "LTXKey.hpp"

namespace LTX{
	LTXKey::LTXKey(const char *keyname){
		this->key = keyname;
	}

	LTXKey::LTXKey(const char *keyname, const char *valueSource):LTXKey(keyname){
		this->value = new LTXValue(this->key, this->_CONVERTSTRINGVALUE(String(valueSource)));
	}

	LTXKey::LTXKey(const LTXKey &key){
		this->key = key.key;
		this->value = new LTXValue(this->key, *key.value);
	}

	LTXKey::LTXKey(const String &keyname){
		this->key = keyname;
		this->value = nullptr;
	}

	LTXKey::LTXKey(const String &keyname, const String &valueSource){
		this->key = keyname;
		this->value = new LTXValue(this->key, this->_CONVERTSTRINGVALUE(valueSource));
	}

	LTXKey::LTXKey(const String &keyname, const LTXValue &value){
		this->key = keyname;
		this->value = new LTXValue(this->key, value);
	}

	LTXKey::~LTXKey(){
		if(!isEmpty())delete value;
	}

	String LTXKey::getKeyName() const{
		return key;
	}

	LTXValue LTXKey::getValue() const{
		return *this->value;
	}

	LTXValue & LTXKey::getValue(){
		return *this->value;
	}

	LTXValueType LTXKey::getValueType() const{
		return (this->value != nullptr ? this->value->getType() : LTXValueType::_empty);
	}

	bool LTXKey::isEmpty() const{
		return value == nullptr;
	}

	void LTXKey::setValue(const LTXValue &val){
		if(!isEmpty())delete value;
		value = new LTXValue(key, val);
	}

	void LTXKey::setValue(const String &value){
		if(!isEmpty())delete value;
		value = new LTXValue(key, this->_CONVERTSTRINGVALUE(value));
	}

	void LTXKey::setKeyName(const String &keyname){
		this->key = keyname;
	}

	String LTXKey::_CONVERTSTRINGVALUE(const String &value){
		String arg = value;
		if(arg.contains(',')){
			if(arg.first() != '{')arg.pushFront('{');
			if(arg.last() != '}')arg.pushBack('}');
		}
		return arg;
	}
}

#include <iostream>

int main(){
	using namespace LTX;
	using namespace std;
	const LTXKey key("TestKey", "53,16,9");
	LTXValue val = key.getValue();
	if(val.getType() == LTXValueType::_block){
		for(unsigned int i = 0; i < val.getBlockValue().size(); ++i)cout << val.getKey().getCString() << " = " << ((val.getBlockValue())[i]).getIntegerValue() << endl;
	}
}
