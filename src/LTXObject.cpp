#include "LTXObject.hpp"

namespace LTX{
	LTXObject::LTXObject(){
		this->objects = nullptr;
		this->keys = nullptr;
		this->extends = nullptr;
	}

	LTXObject::LTXObject(const LTXObject &obj):LTXObject(){
		if(obj.keys != nullptr)
			keys = new ArrayList<LTXKey>(obj.keys);
		if(obj.extends != nullptr)
			extends = new ArrayList<LTXObject>(obj.extends);
		if(obj.objects != nullptr)
			objects = new ArrayList<LTXObject>(obj.objects);
		objectname = obj.objectname;
	}

	LTXObject::LTXObject(const String &name):LTXObject(){
		objectname = name;
	}

	LTXObject::LTXObject(const String &name, std::initializer_list<LTXKey> _keys):LTXObject(name){
		keys = new ArrayList<LTXKey>(_keys);
	}

	LTXObject::~LTXObject(){
		if(objects != nullptr) delete objects;
		if(keys != nullptr) delete keys;
		if(extends != nullptr) delete extends;
	}

	ArrayList<LTXKey> LTXObject::getKeysEqualsType(std::initializer_list<LTXValueType> types){
	int init = 0;
		for(LTXValueType t : types)init |= t;
		ArrayList<LTXKey> k;
		for(int i = 0; i < keys->size(); ++i){
			if((*keys)[i].getValueType() & init)k.add((*keys)[i]);
		}
		return k;
	}

	void LTXObject::addKey(const LTXKey &key){
		if(this->keys == nullptr)this->keys = new ArrayList<LTXKey>();
		keys->add(key);
	}

	void LTXObject::addKey(std::initializer_list<LTXKey> key){
		for(LTXKey x : key)addKey(x);
	}

	void LTXObject::addObject(const LTXObject &obj){
		if(this->objects == nullptr)this->objects = new ArrayList<LTXObject>();
		objects->add(obj);
	}

	void LTXObject::addObject(std::initializer_list<LTXObject> objs){
		for(LTXObject x : objs)addObject(x);
	}

	int LTXObject::getKeysNum() const {
		if(this->keys == nullptr)return 0;
		else return (int)keys->size();
	}

	int LTXObject::getObjectsNum() const {
		if(this->objects == nullptr)return 0;
		else return (int)objects->size();
	}

	LTXKey LTXObject::getKeyByName(String name) const {
		for(unsigned int i = 0; i < keys->size(); ++i)
			if((*keys)[i].getKeyName().equals(name))
				return (*keys)[i];
		return LTXKey("*empty");
	}

	LTXKey & LTXObject::getKeyByName(String name) {
		for(unsigned int i = 0; i < keys->size(); ++i)
			if((*keys)[i].getKeyName().equals(name))
				return (*keys)[i];
		return LTXKey("*empty");
	}

	bool LTXObject::containsKey(String &name) const {
		for(unsigned int i = 0; i < this->keys->size(); ++i){
			if((*keys)[i].getKeyName() == name)return true;
		}
		return false;
	}

	bool LTXObject::containsKey(LTXValueType type) const {
		for(unsigned int i = 0; i < this->keys->size(); ++i){
			if((*keys)[i].getValueType() == type)return true;
		}
		return false;
	}
}
