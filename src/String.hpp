#ifndef STRING_H
#define STRING_H

class String {
private:
	char * val;
	int ssize;
	int bsize;
	int extend;

	void allocate(const char *);
	void allocate(char *);
	void _APPEND(char);
	void _APPEND(const char *);
    void _INSERT(char, int);
    void _INSERT(const char *, int);
	void _PREPEND(char);
	void _PREPEND(const char *);
	void resize(int, int);

public:
	String();
	String(int);
	String(const char *);
	String(const String &);
	~String();

	String & operator<<(char);
	String & operator<<(const char *);
	String & operator<<(const String &);
	String & operator+=(char);
	String & operator+=(const char *);
	String & operator+=(const String &);

	//String & operator=(char);
	String & operator=(const char *);
	String & operator=(const String &);

	bool operator == (const char *) const;
	bool operator == (const String &) const;
	friend bool operator == (const char *, const String &);

	bool operator != (const char *) const;
	bool operator != (const String &) const;
	friend bool operator != (const char *, const String &);

	//bool operator < (const char *);
	//bool operator < (const String &);
	//friend bool operator < (const char *, const String &);

	//bool operator > (const char *);
	//bool operator > (const String &);
	//friend bool operator > (const char *, const String &);

	char &operator [](int);
	char operator [](int) const;

	int operator [](char) const;

	char &charAt(int);
	char charAt(int) const;
	char &first();
	char first() const;
	char &last();
	char last() const;
	const char * getCString() const;
	const char * c_str() const;

	void pushFront(char);
	void pushBack(char);
	void append(const char *);
	void append(char);
    void insert(int, char);
    void insert(int, const char *);
    void erase(int, int count = 1);
//	void popFront();
//	void popBack();
//	void erase(int, int count = 1);

	//int length() const;
	int size() const;
	const int &length = ssize;

	int indexOf(char, int start = 0) const;
	int lastindexOf(char) const;
	bool contains(char) const;
	bool contains(const char *) const;
	bool contains(const String &) const;
	bool equals(const char *) const;
	bool equals(const String &) const;
	bool equalsAll(const char *) const;
	bool equalsAll(const String &) const;
	bool startsWith(const char *) const;
	bool startsWith(const String &) const;
	bool endsWith(const char *) const;
	bool endsWith(const String &) const;

	String substring(int, int end = -1) const;
	String substring(int start, char end) const;
	String substring(char start, char end, int startpos = 0) const;

	static int stringlen(const char *);

};

#endif
