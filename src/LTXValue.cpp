#include "LTXValue.hpp"
#include <cstdlib>
//#include <iostream>

namespace LTX {
	LTXValue::LTXValue(){
		this->type = LTXValueType::_empty;
	}

	LTXValue::LTXValue(const char *keyname){
		this->key = keyname;
	}

	LTXValue::LTXValue(const char *keyname, const char *value){
	//	std::cout << keyname << " " << value << " = ";
		key = keyname;
	//	std::cout << key.getCString() << std::endl;
		this->parceValue(String(value));
	}

	LTXValue::LTXValue(const LTXValue &value){
		this->key = value.key;
		switch(value.getType()){
			case LTXValueType::_intnumber:
				this->type = value.type;
				intnumber = new long;
				*intnumber = value.getIntegerValue();
				break;
			case LTXValueType::_floatnumber:
				this->type = value.type;
				floatnumber = new long double;
				*floatnumber = value.getLongDoubleValue();
				break;
			case LTXValueType::_pair:
				this->type = value.type;
				//key = value.getKey();
				pair = new LTXValue(value.getPairValue());
				//*(pair) = value.getPairValue();
				break;
			case LTXValueType::_block:
				this->type = value.type;
				//key = value.getKey();
				block = new ArrayList<LTXValue>(value.getBlockValue());
				//*block = value.getBlockValue();
				break;
			case LTXValueType::_string:
				this->type = value.type;
				string = new String();
				*string = value.getStringValue();
				break;
			case LTXValueType::_null:
				this->type = value.type;
				break;
			case LTXValueType::_boolean:
				this->type = value.type;
				boolean = new bool;
				*boolean = *value.boolean;
				break;
			case LTXValueType::_empty:case LTX::LTXValueType::_link:
				this->type = value.type;
				break;
		}
	}

//	LTXValue::LTXValue(const String &keyname){
//		this->key = keyname;
//	}

	LTXValue::LTXValue(const String &keyname, const String &value){
		this->key = keyname;
		//std::cout << value.getCString();
		this->parceValue(value);
	}

	LTXValue::LTXValue(const String &keyname, const LTXValue &value):LTXValue(value){
		this->key = keyname;
	}

	LTXValue::LTXValue(const char *keyname, const LTXValue & value):LTXValue(keyname){
		//this->clear();
		//this->allocate();
		switch(value.getType()){
			case LTXValueType::_intnumber:
				this->type = value.type;
				intnumber = new long;
				*intnumber = value.getIntegerValue();
				break;
			case LTXValueType::_floatnumber:
				this->type = value.type;
				floatnumber = new long double;
				*floatnumber = value.getLongDoubleValue();
				break;
			case LTXValueType::_pair:
				this->type = value.type;
				//key = value.getKey();
				pair = new LTXValue(value.getPairValue());
				//*(pair) = value.getPairValue();
				break;
			case LTXValueType::_block:
				this->type = value.type;
				//key = value.getKey();
				block = new ArrayList<LTXValue>(value.getBlockValue());
				//*block = value.getBlockValue();
				break;
			case LTXValueType::_string:
				this->type = value.type;
				string = new String();
				*string = value.getStringValue();
				break;
			case LTXValueType::_null:
				this->type = value.type;
				break;
			case LTXValueType::_boolean:
				this->type = value.type;
				boolean = new bool;
				*boolean = *value.boolean;
				break;
			case LTXValueType::_empty:case LTX::LTXValueType::_link:
				this->type = value.type;
				break;
		}
	}

	LTXValue::LTXValue(const String &keyname, bool value){
		this->key = keyname;
		this->type = LTXValueType::_boolean;
		this->boolean = new bool(value);
	}

	LTXValue::LTXValue(const String &keyname, long value){
		this->key = keyname;
		this->type = LTXValueType::_intnumber;
		this->intnumber = new long(value);
	}

	LTXValue::LTXValue(const String &keyname, const ArrayList<LTXValue> &value){
		this->key = keyname;
		this->type = LTXValueType::_block;
		this->block = new ArrayList<LTXValue>(value);
	}

	LTXValue::LTXValue(const String &keyname, long double value){
		this->key = keyname;
		this->type = LTXValueType::_floatnumber;
		this->floatnumber = new long double(value);
	}

	LTXValue & LTXValue::operator = (const LTXValue & value){
	//	LTXValue ret(value);
	//	return ret;
		//if(value.type == LTXValueType::_pair)std::cout << value.key.getCString() << std::endl;
		this->key = value.key;
		clear();
		switch(value.getType()){
			case LTXValueType::_intnumber:
				this->type = value.type;
				intnumber = new long;
				*intnumber = value.getIntegerValue();
				break;
			case LTXValueType::_floatnumber:
				this->type = value.type;
				floatnumber = new long double;
				*floatnumber = value.getLongDoubleValue();
				break;
			case LTXValueType::_pair:
				this->type = value.type;
				key = value.getKey();
				pair = new LTXValue(value.getPairValue());
				//*(pair) = value.getPairValue();
				break;
			case LTXValueType::_block:
				this->type = value.type;
				//key = value.getKey();
				block = new ArrayList<LTXValue>(value.getBlockValue());
				//*block = value.getBlockValue();
				break;
			case LTXValueType::_string:
				this->type = value.type;
				string = new String();
				*string = value.getStringValue();
				break;
			case LTXValueType::_null:
				this->type = value.type;
				break;
			case LTXValueType::_boolean:
				this->type = value.type;
				boolean = new bool;
				*boolean = *value.boolean;
				break;
			case LTXValueType::_empty:case LTX::LTXValueType::_link:
				this->type = value.type;
				break;
		}
		return *this;
	}

	LTXValue::~LTXValue(){
		//std::cout << "free LTXV " << this;
		this->clear();
		//std::cout << ">>endl" << std::endl;
	}

	int LTXValue::getIntegerValue() const {
		if(type == LTXValueType::_intnumber)return (int)*intnumber;
		if(type == LTXValueType::_floatnumber)return (int)*floatnumber;
		return 0;
	}

	long LTXValue::getLongValue() const {
		if(type == LTXValueType::_intnumber)return *intnumber;
		if(type == LTXValueType::_floatnumber)return (long)*floatnumber;
		return 0;
	}

	long double LTXValue::getLongDoubleValue() const {
		if(type == LTXValueType::_intnumber)return (long double)*intnumber;
		if(type == LTXValueType::_floatnumber)return *floatnumber;
		return 0;
	}

	float LTXValue::getFloatValue() const {
		if(type == LTXValueType::_intnumber)return (float)*intnumber;
		if(type == LTXValueType::_floatnumber)return (float)*floatnumber;
		return 0;
	}

	double LTXValue::getDoubleValue() const {
		if(type == LTXValueType::_intnumber)return (double)*intnumber;
		if(type == LTXValueType::_floatnumber)return (double)*floatnumber;
		return 0;
	}

	bool LTXValue::getBooleanValue() const {
		if(boolean == nullptr)return false;
		else return *boolean;
	}

	const char * LTXValue::getConstCharValue() const {
		if(string == nullptr)return "";
		else return string->getCString();
	}

	String LTXValue::getStringValue() const {
		if(string == nullptr)return nullptr;
		else return *string;
	}

	ArrayList<LTXValue> LTXValue::getBlockValue() const {
		if(type != LTXValueType::_block)
			return ArrayList<LTXValue>({LTXValue()});
		else return *block;
	}

	LTXValue LTXValue::getPairValue() const {
		if(pair == nullptr)return LTXValue();
		//LTXValue val();
		return *pair;
	}

	LTXValueType LTXValue::getType() const {
		return type;
	}

	String LTXValue::getKey() const {
		return this->key;
	}

	bool LTXValue::equalBlockEntries(std::initializer_list<LTXValueType> types) const {
		if(type != LTXValueType::_block)return false;
		if(types.size() >= block->size()){
			unsigned int i = 0;
			for(LTXValueType t : types){
				LTXValue p = block->get(i++);
				if(p.getType() != t)return false;
				if(i >= block->size())break;
			}
			return true;
		}
		return false;
	}

	void LTXValue::clear(){
		if(intnumber != nullptr){
			delete intnumber;
			intnumber = nullptr;
		}
		if(floatnumber != nullptr){
			delete floatnumber;
			floatnumber = nullptr;
		}
		if(boolean != nullptr){
			delete boolean;
			boolean = nullptr;
		}
		if(string != nullptr){
			delete string;
			string = nullptr;
		}
		if(pair != nullptr){
			delete pair;
			pair = nullptr;
		}
		if(block != nullptr){
			delete block;
			//std::cout << "free " << block << std::endl;
			block = nullptr;
		}
		type = LTXValueType::_empty;
	}

	void LTXValue::allocate(){
		switch(type){
			case LTXValueType::_intnumber:
				intnumber = new long;
				break;
			case LTXValueType::_floatnumber:
				floatnumber = new long double;
				break;
			case LTXValueType::_pair:
				pair = new LTXValue();
				break;
			case LTXValueType::_block:
				block = new ArrayList<LTXValue>(0);
				break;
			case LTXValueType::_string:
				string = new String(0);
				break;
			case LTXValueType::_null:
				break;
			case LTXValueType::_boolean:
				boolean = new bool;
				break;
			case LTXValueType::_empty:case LTX::LTXValueType::_link:
				break;
		}
	}

	void LTXValue::parceValue(const String &value){
		if(/*chareqall(value, "0123456789")*/ value.equalsAll("-0123456789")){
			type = LTXValueType::_intnumber;
			this->intnumber = new long;
			//std::cout << "[int:" << value.getCString() <<"]" << std::endl;
			*(this->intnumber) = atol(value.getCString());
			//std::cout << std::endl << "VAL:" << *(this->intnumber) << std::endl;
			return;
		}
		if(/*chareqall(value, "0123456789.,")*/value.equalsAll("-0123456789.")){
			type = LTXValueType::_floatnumber;
			this->floatnumber = new long double;
			*(this->floatnumber) = strtold(value.getCString(), NULL);
			return;
		}
		if(/*chareq(value, "true") || chareq(value, "false")*/value.equals("true") || value.equals("false")){
			type = LTXValueType::_boolean;
			this->boolean = new bool;
			*(this->boolean) = value.equals("true");
			return;
		}
		if(value.equals("null") || value.equals("nil")){
			type = LTXValueType::_null;
			return;
		}
		if(value.contains('=') && ((value.indexOf('=') < value.indexOf('{')) || !value.contains('{'))){
			//std::cout << "1";
			type = LTXValueType::_pair;
			//std::cout << "1";
			this->pair = new LTXValue(value.substring(0, '='), value.substring((value.indexOf('=')+1)));
			//std::cout << std::endl << pair->getKey().getCString() << " " << pair->getIntegerValue() << std::endl;
			//LTXValue val(*pair);
			//std::cout << pair->getIntegerValue();
			//std::cout << "1";
			return;
		}
		if(value.contains('{') && value.contains('}')){
			ArrayList<String> args = formvalues(value.substring(value.indexOf('{')+1, value.lastindexOf('}')));
			type = LTXValueType::_block;
			this->block = new ArrayList<LTXValue>(args.size());
			for(unsigned int i = 0; i < args.size(); ++i){
				//std::cout << args.get(i).getCString() << std::endl;
				LTXValue lav(this->key, args[i]);
				//block->set(i, lav);
				(*block)[i] = lav;
			//	if(lav.getType() == LTXValueType::_pair){
			//		std::cout << (*block)[i].getPairValue().getKey().getCString() << std::endl;
			//	}
			//	std::cout << "BLOCK:" << this->key.getCString() << "=" << args[i].getCString() << ":"
			//	<< block->get(i).getKey().getCString() << "=" << block->get(i).getIntegerValue() << std::endl;
			//	LTXValue v;
			//	v = LTXValue(this->key, args[i]);
			//	std::cout << "TEST:" << v.getKey().getCString() << "=" << v.getIntegerValue() << std::endl;
			}
			return;
		}
		type = LTXValueType::_string;
		this->string = new String(value);
	}

	ArrayList<String> LTXValue::formvalues(const String &value){
		ArrayList<String> args(10);
		//string str(value);
		unsigned int size = 0;
		for(int i = 0, li = 0, coma = 0; i < value.length; i++){
			if(value[i] == '{')coma++;
			else if(value[i] == '}')coma--;
			else if(value[i] == ',' && coma <= 0){
				if(size >= args.size())args.resize(args.size() + 5);
				//std::cout << value.substring(li, i).getCString();
				args.set(size++, value.substring(li, i));
				//size++;
				li = i+1;
			}
			if(i == value.length - 1){
				if(size >= args.size())args.resize(args.size() + 5);
				//std::cout << value.substring(li).getCString();
				args.set(size++, value.substring(li));
				//size++;
			}
		}
		if(args.size() > size)args.resize(size);
		return args;
	}

	//LTXValue & LTXValue::operator = (const LTXValue & value){
		//this->clear();
		//this->allocate();
		//switch(value.getType()){
			//case LTXValueType::_intnumber:
				//this->type = value.type;
				//*intnumber = value.getIntegerValue();
				//break;
			//case LTXValueType::_floatnumber:
				//this->type = value.type;
				//*floatnumber = value.getLongDoubleValue();
				//break;
			//case LTXValueType::_pair:
				//this->type = value.type;
				//key = value.getKey();
				//*(pair) = value.getPairValue();
				//break;
			//case LTXValueType::_block:
				//this->type = value.type;
				////key = value.getKey();
				//*block = value.getBlockValue();
				//break;
			//case LTXValueType::_string:
				//this->type = value.type;
				//*string = value.getStringValue();
				//break;
			//case LTXValueType::_null:
				//this->type = value.type;
				//break;
			//case LTXValueType::_boolean:
				//this->type = value.type;
				//*boolean = *value.boolean;
				//break;
			//case LTXValueType::_empty:
				//this->type = value.type;
				//break;
		//}
		//return *this;
	//}

}

//void printKey(LTX::LTXValue, int inl = 0);
//
//int main(){
//	using std::cout;
//	//LTX::LTXValue sval("testKey", "{25,56,88}");
//	//ArrayList <LTX::LTXValue> va = sval.getBlockValue();
////	LTX::LTXValue vals[] = {LTX::LTXValue("key1", "2"), LTX::LTXValue("key2", "2.5"), LTX::LTXValue("key3", "Hello"), LTX::LTXValue("key4", "val=86"), LTX::LTXValue("key5", "null"),
////	LTX::LTXValue("key6", "true"), LTX::LTXValue("key7", "val={23,16}"), LTX::LTXValue("key9", "{{23,6},hello}"), LTX::LTXValue("key8", "{Hello,53}")};
////	const char *h = "Hello";
////	String arg1;
////
////	arg1 = h;
////	cout << h << "::" << arg1.getCString() << std::endl;
////	for(int i = 0; i < arg1.length; ++i)cout << arg1[i] << ' ';
////	String arg2 = arg1;
////	cout << arg2.getCString() << std::endl;
//	printKey(LTX::LTXValue("key_A_", "2"));
//	printKey(LTX::LTXValue("key_B_", "2.4"));
//	printKey(LTX::LTXValue("key_C_", "hello"));
//	printKey(LTX::LTXValue("key_D_", "{23,11}"));
//	printKey(LTX::LTXValue("key_E_", "true"));
//	printKey(LTX::LTXValue("key_F_", "{{23,15.3},hello,pair=9,key}"));
//	printKey(LTX::LTXValue("key_G_", "pt={hello,world,36}"));
////	LTX::LTXValue val;
//
////	val = LTX::LTXValue("test", "ps=12.5");
////	cout << val.getKey().getCString() << std::endl;
////	for(unsigned int i = 0; i < 9; ++i){
////		cout << vals[i].getKey().getCString();
////		printKey(vals[i]);
////	}
//	return 0;
//}
//
//void printKey(LTX::LTXValue val, int inl){
//	using std::cout;
//	if(inl > 0){
//		for(int i = 0; i < inl; ++i)cout << "\t";
//	}
//	cout << val.getKey().getCString() << " = ";
//	ArrayList <LTX::LTXValue> swd;
//	switch(val.getType()){
//		case LTX::LTXValueType::_intnumber:
//			cout << val.getIntegerValue();
//			break;
//		case LTX::LTXValueType::_floatnumber:
//			cout << val.getFloatValue();
//			break;
//		case LTX::LTXValueType::_pair:
//			cout << " >> ";
//			printKey(val.getPairValue());
//			break;
//		case LTX::LTXValueType::_block:
//			swd = val.getBlockValue();
//			cout << "{" << std::endl;
//			for(unsigned int i = 0; i < swd.size(); ++i){
//				printKey(swd.get(i), inl+1);
//			}
//			if(inl >= 0){
//				for(int i = 0; i <= inl; ++i)cout << "\t";
//			}
//			cout << "}" << std::endl;
//			return;
//		case LTX::LTXValueType::_string:
//			cout << val.getStringValue().getCString();
//			break;
//		case LTX::LTXValueType::_null:
//			cout << "<nil> value";
//			break;
//		case LTX::LTXValueType::_boolean:
//			cout << (val.getBooleanValue()?"true":"false");
//			break;
//		case LTX::LTXValueType::_empty:case LTX::LTXValueType::_link:
//			cout << "<empty> value";
//			break;
//	}
//	cout << std::endl;
//}
