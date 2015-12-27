
#ifndef NVLIST_H
#define NVLIST_H
#include <initializer_list>
//#include <iostream>

template <typename Type>
class ArrayList {
public:
	ArrayList(){
	//	this->step = 3;
	//	this->size = this->step;
//		val = new Type[this->_size];
	//	this->usize = 0;
	//	this->length = usize;
		this->_size = 0;
	}
	ArrayList(unsigned int size){
	//	this->step = 3;
		this->_size = size;
		if(size != 0)
			val = new Type[this->_size];
	//	this->usize = 0;
	//	length = size;
	}

	ArrayList(unsigned int size, const Type &def):ArrayList(size){
		for(int i = 0; i < size; ++i){
			val[i] = def;
		}
	}

	ArrayList(std::initializer_list<Type> args){
		this->_size = args.size();
		val = new Type[this->_size];
		int i = 0;
		for(Type t : args){
			val[i++] = t;
		}
	}

	ArrayList(const ArrayList<Type> & list){
		this->_size = list.size();
		val = new Type[this->_size];
		for(int i = 0; i < _size; i++){
			val[i] = list[i];
		}
	}
	//ArrayList(const ArrayList<Type> & list);
	//ArrayList(ArrayList<Type> && list);
	~ArrayList(){
		//std::cout << "free AL " << this << " : " << val << std::endl;
		//if(_size > 0)delete [] val;
	}

	Type get(int pos) const{
		return val[pos];
	}

	Type &get(int pos){
		return val[pos];
	}

	void set(int pos, const Type &t){
		val[pos] = t;
	}
	void add(const Type &v){
		resize(_size+1);
		val[_size-1] = v;
	}
	//void addFront(Type v);
	//void set(int pos, Type v);

	Type & operator [](int pos){
		return val[pos];
	}

	Type operator [](int pos) const{
		return val[pos];
	}

	void clear(){
		//std::cout << "free " << this << std::endl;
		delete [] val;
		_size = 0;
	}

	unsigned int size() const{
		return this->_size;
	}
	//const unsigned int &length = this->_size;

	unsigned int resize(unsigned int newsize){
        if(this->_size == 0){
            val = new Type[newsize];
            this->_size = newsize;
            return newsize;
        }
		Type * buffer = new Type[newsize];
		for(int i = 0; i < _size && i < newsize; ++i){
			buffer[i] = val[i];
		}
		delete [] val;
		val = buffer;
		_size = newsize;
		return newsize;
	}

private:
	unsigned int _size;
//	int usize;
//	int step;
//	short accesses;
	Type * val;
};

//class String {
//private:
	//char * val;
	//int size;

//public:
	//String(const char * str);
	//String(const String & val);

	//void operator << (char c);
	//void operator << (const char * c);
	//void operator += (char c);
	//void operator += (const char * c);

	//void pushFront(char c);
	//void pushBack(char c);
	//void popFront();
	//void popBack();
	//void erase(int pos);
//};

#endif //NVLIST_H
