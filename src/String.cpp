#include "String.hpp"

String::String(const char * sval){
	this->val = nullptr;
	this->extend = 5;
	//std::cout << "s=" << sval;
	this->allocate(sval);
	//std::cout << " " << this->val << std::endl;
	//std::cout << std::endl << val << " == " << this->val << std::endl;
	//std::cout << "\t" << getCString() << std::endl;
}

String::String(const String & val):extend(5){
	this->val = nullptr;
	this->allocate(val.val);
	//std::cout << "\t" << getCString() << std::endl;
}

String::String():val(nullptr),extend(3){
	val = new char [extend];
	ssize = extend;
	bsize = ssize;
}

String::String(int asize):val(nullptr),extend(5){
	val = new char [asize==0?extend:asize];
	ssize = 0;
	bsize = asize;
}

String::~String(){
	//std::cout << "free S " << this << " : " << &val << std::endl;
	if(val)delete [] val;
	val = 0;
}

void String::resize(int newsize, int offset = 0){
	char * buffer = new char [newsize];
	for(int i = 0; i < ssize && i < newsize; ++i){
		//if(i < offset)continue;
		buffer[i+offset] = val[i];
	}
	delete [] val;
	val = buffer;
	bsize = newsize;
//	if(ssize < bsize)ssize = bsize-1;
   // val[ssize] = '\0';
}


void String::allocate(char * cc){
	if(val != 0){
		delete [] val;
	}
	int _size = 0;
	for(_size = 0;cc[_size] != '\0';_size++);
	val = new char[_size];
	for(int i = 0; i < _size; ++i){
		val[i] = cc[i];
	//	std::cout << "val[" << i << "] = " << val[i] << " || cc[" << i << "] = " << cc[i] << std::endl;
	}
	val[_size] = '\0';
	ssize = _size;
	bsize = ssize;
}

void String::allocate(const char * cc){
	if(val != 0){
		delete [] val;
	}
	int _size = 0;
	for(_size = 0;cc[_size] != '\0';_size++);
	val = new char[_size];
	for(int i = 0; i < _size; ++i){
		val[i] = cc[i];
	//	std::cout << "val[" << i << "] = " << val[i] << " || cc[" << i << "] = " << cc[i] << std::endl;
	}
	val[_size] = '\0';
	//std::cout << "VAL:" << val << " = " << getCString() << std::endl;
	ssize = _size;
	bsize = ssize;
}

void String::_APPEND(char cc){
	if(ssize == bsize)resize(bsize + extend);
	val[ssize++] = cc;
	val[ssize] = '\0';
}

void String::_APPEND(const char * cc){
	for(int i = 0; cc[i] != '\0'; ++i)_APPEND(cc[i]);
}

void String::_PREPEND(char c){
	resize(bsize + 1, 1);
	val[0] = c;
	++ssize;
	val[ssize] = '\0';
}

void String::_PREPEND(const char * c){
	int len;
	for(len = 0; c[len] != '\0'; ++len);
	resize(bsize + len, len);
	ssize += len;
	for(int i = 0; i < len; ++i){
		val[i] = c[i];
	}
	val[ssize] = '\0';
}

void String::_INSERT(char c, int pos)
{
    char * buffer = new char[bsize + 1];
    for(int i = 0;i < bsize + 1; ++i){
        if(i == pos)
            buffer[i] = c;
        else
            buffer[i] = val[i < pos?i:i-1];
    }
    delete [] val;
    val = buffer;
    bsize++;
    ssize++;
}

void String::_INSERT(const char *str, int pos)
{
    int strsize = String::stringlen(str);
    char * buffer = new char[bsize + strsize];
    for(int i = 0, valpos = 0; i < bsize + strsize; ++i, ++valpos){
        if(i == pos){
            for(int l = 0; l < strsize; ++l, ++i){
                buffer[i] = str[l];
            }
		}
		buffer[i] = val[valpos];

    }
    delete [] val;
    val = buffer;
    bsize += strsize;
    ssize += strsize;
}

String & String::operator << (char c){
	_APPEND(c);
	return *this;
}

String & String::operator << (const char * c){
	_APPEND(c);
	return *this;
}

String & String::operator << (const String & str){
	_APPEND(str.val);
	return *this;
}

String & String::operator += (char c){
	_APPEND(c);
	return *this;
}

String & String::operator += (const char * c){
	_APPEND(c);
	return *this;
}

String & String::operator += (const String & str){
	_APPEND(str.val);
	return *this;
}

//String & String::operator = (char c){
//	allocate((const char *)c);
//	return *this;
//}

String & String::operator = (const char * c){
	allocate(c);
	return *this;
	//std::cout << c;
	//String str(c);
	//std::cout << "[" << str.val << "]" << std::endl;
	//return str;
}

String & String::operator = (const String & str){
	allocate(str.val);
	//std::cout << val << "!!" << str.val;
	return *this;
	//std::cout << "!!" << str.val;
	//String sstr(str);
	//return sstr;
}

char & String::operator [] (int pos){
    return pos >=0 && pos < this->length ? val[pos] : val[0];
}

char String::operator [] (int pos) const {
    return pos >=0 && pos < this->length ? val[pos] : '\0';
}

bool String::operator == (const char * c) const{
	int len = stringlen(c);
	if(len != ssize)return false;
	for(int i = 0; i < ssize; ++i){
		if(val[i] != c[i])return false;
	}
	return true;
}

bool String::operator == (const String & vval) const{
	if(vval.ssize != ssize)return false;
	for(int i = 0; i < ssize; ++i){
		if(val[i] != vval[i])return false;
	}
	return true;
}

bool operator == (const char * c, const String & v){
	int len = String::stringlen(c);
	if(len != v.ssize)return false;
	for(int i = 0; i < v.ssize; ++i){
		if(v[i] != c[i])return false;
	}
	return true;
}

bool String::operator != (const char * c) const{
	int len = stringlen(c);
	if(len != ssize)return true;
	for(int i = 0; i < ssize; ++i){
		if(val[i] != c[i])return true;
	}
	return false;
}

bool String::operator != (const String & vval) const{
	if(vval.ssize != ssize)return true;
	for(int i = 0; i < ssize; ++i){
		if(val[i] != vval[i])return true;
	}
	return false;
}

bool operator != (const char * c, const String & v){
	int len = String::stringlen(c);
	if(len != v.ssize)return true;
	for(int i = 0; i < v.ssize; ++i){
		if(v[i] != c[i])return true;
	}
	return false;
}

char & String::charAt(int pos){
    return pos >=0 && pos < this->length ? val[pos] : val[0];
}

char String::charAt(int pos) const {
    return pos >=0 && pos < this->length ? val[pos] : '\0';
}

char & String::first(){
	return val[0];
}

char String::first() const{
	return val[0];
}

char & String::last(){
	return val[ssize - 1];
}

char String::last() const{
	return val[ssize-1];
}

const char * String::getCString() const{
	//std::cout << val;
	return val;
}

const char * String::c_str() const
{
	return val;
}

void String::pushBack(char c){
	_APPEND(c);
}

void String::pushFront(char c){
	_PREPEND(c);
}

void String::insert(int pos, char c)
{
    _INSERT(c, pos);
}

void String::insert(int pos, const char *str)
{
    _INSERT(str, pos);
}

void String::erase(int pos, int count)
{
	if(count > 0 && (pos + count) < ssize){
		char *buffer = new char[bsize-count];
		for(int i = 0, valpos = 0; i < bsize; ++i, ++valpos){
			if(i == pos)
				valpos+=count;

			buffer[i] = val[valpos];
		}
		delete [] val;
		val = buffer;
		bsize-=count;
		ssize-=count;
	}
}

int String::size() const{
	return ssize;
}

int String::indexOf(char c, int start) const{
	for(int i = start; i < ssize; ++i){
		if(val[i] == c)return i;
	}
	return -1;
}
int String::lastindexOf(char c) const{
	for(int i = ssize-1; i >= 0; --i){
		if(val[i] == c)return i;
	}
	return -1;
}
bool String::contains(char c) const{
	for(int i = 0; i < ssize; ++i){
		if(val[i] == c)return true;
	}
	return false;
}
bool String::contains(const char * c) const{
	bool iret;
	for(int i = 0; i < ssize; ++i){
		iret = true;
		for(int s = 0; c[s] != '\0' && (s + i) < ssize; ++c){
			if(val[s + i] != c[s]){
				iret = false;
				break;
			}
		}
		if(iret)return true;
	}
	return false;
}
bool String::contains(const String & c) const{
	return contains(c.val);
}
bool String::equals(const char *c) const{
	int i;
	for(i = 0; i < ssize && c[i] != '\0'; ++i){
		if(val[i] != c[i])return false;
	}
	if(i+1 < ssize || c[ssize] != '\0')return false;
	else return true;
}
bool String::equals(const String & c) const{
	return equals(c.val);
}
bool String::equalsAll(const char * c) const {
	bool er;
	for(int i = 0; i < ssize; ++i){
		er = false;
		for(int k = 0; c[k] != '\0'; ++k){
			if(val[i] == c[k]){
				er = true;
				break;
			}
		}
		if(!er)return false;
	}
	return true;
}
bool String::equalsAll(const String &str) const {
	return equalsAll(str.val);
}
bool String::startsWith(const char * c) const{
	int i;
	for(i = 0; i < ssize && c[i] != '\0'; ++i){
		if(val[i] != c[i])return false;
	}
	return true;
}
bool String::startsWith(const String & c) const{
	return startsWith(c.val);
}
bool String::endsWith(const char * c) const{
	int clen = stringlen(c);
	if(clen > ssize)return false;
	for(int i = ssize - clen, s = 0; i < ssize; ++i, ++s){
		if(val[i] != c[s])return false;
	}
	return true;
}
bool String::endsWith(const String & c) const{
	return endsWith(c.val);
}

//String String::substring(int start) const{
	//return substring(start, -1);
//}

String String::substring(int start, int end) const{
	if(start < ssize && end <= ssize){
		if(start < 0)start = 0;
		if(end < 0 || end <= start)end = ssize;
		String str(end-start);
		for(int i = start; i < end; ++i)str << val[i];
		return str;
	}
	return String(0);
}
String String::substring(int start, char end) const{
	return substring(start, indexOf(end, start));
}
String String::substring(char start, char end, int startpos) const{
	return substring(indexOf(start, startpos), end);
}

int String::stringlen(const char * str){
	int l;
	for(l = 0; str[l] != '\0'; ++l);
	return l;
}

//#include <iostream>
//using std::cout;
//
//int main()
//{
//	String str("Hello World!");
//	cout << str.getCString() << "\n";
//	str.erase(5, 4);
//	cout << str.getCString();
//	str.insert(5, " Wor");
//	cout << "\n" << str.getCString();
//	return 0;
//}
