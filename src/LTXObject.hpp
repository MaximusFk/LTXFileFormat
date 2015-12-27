#ifndef LTXOBJECT_H
#define LTXOBJECT_H

#include "NVList.hpp"
#include "LTXKey.hpp"
#include "String.hpp"
namespace LTX {
	class LTXObject{
	public:
		LTXObject();
		LTXObject(const LTXObject &obj);
		LTXObject(const String &name);
		LTXObject(const String &name, std::initializer_list<LTXKey> _keys);
		~LTXObject();

		void implement(const LTXObject &obj);
		void implement(std::initializer_list<LTXObject> objs);

		void addObject(const LTXObject &obj);
		void addObject(std::initializer_list<LTXObject> objs);

		void addKey(const LTXKey &key);
		void addKey(std::initializer_list<LTXKey> key);

		ArrayList<LTXKey> getKeysEqualsType(std::initializer_list<LTXValueType> types) const;

		int getKeysNum() const;
		int getObjectsNum() const;

		bool containsKey(String &name) const;
		bool containsKey(LTXValueType type) const;

		LTXKey getKeyByName(String name) const;
		LTXKey & getKeyByNameL(String name);
		ArrayList<LTXKey> getKeysEntry() const;
		ArrayList<LTXKey> & getKeysEntryL();

	private:
		String objectname;
		ArrayList<LTXKey> *keys;
		ArrayList<LTXObject> *objects;
		ArrayList<LTXObject> *extends;
	};
}
#endif // LTXOBJECT_H
