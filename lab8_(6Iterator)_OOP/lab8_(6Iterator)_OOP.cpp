/*паттерн "ітератор"
Створити шаблонний клас – послідовність абстрактних символів.
Тип елементів послідовності (цілі числа, дійсні числа, символи
або символьні рядки) визначається параметром шаблона. Передбачити
функції для виконання таких операцій: введення елементів у послідовність,
відношення < , > , == , != , виведення послідовності на екран.*/

#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class sequence {
private:
	T* data;
	int size;
public:
	sequence(int = 0);
	~sequence();
	void add(T new_e);
	int get_size() { return size; }
	T get_element(unsigned);
	sequence& operator+(sequence&);
	sequence& operator=(const sequence&);
	template <typename T>friend ostream& operator<<(ostream&, sequence<T>&);
	template <typename T> friend istream& operator>>(istream&, sequence<T>&);
	template <typename T> friend class Iterator;
};

template <class T>
class Iterator {
private:
	const sequence<T>& seq;
	int id;
public:
	Iterator(const sequence<T>& sq) : seq(sq) {
		id = 0;
	}
	~Iterator() {}
	void operator++(int) {
		id++;
	}
	void operator++() {
		id++;
	}
	bool operator() () {
		return (id < seq.size);
	}
	T& operator*() {
		return (seq.data[id]);
	}
};

template<class T1, class T2>
bool operator==(sequence<T1>& s1, sequence<T2>& s2)
{
	if (s1.get_size() != s2.get_size())
		return false;
	for (int i = 0; i < s1.get_size(); i++) {
		if (s1.get_element(i) != s2.get_element(i))
			return false;
	}
	return true;
}

template<class T1, class T2>
bool operator!=(sequence<T1>& s1, sequence<T2>& s2)
{
	if (s1.get_size() != s2.get_size())
		return true;
	for (int i = 0; i < s1.get_size(); i++) {
		if (s1.get_element(i) != s2.get_element(i))
			return true;
	}
	return false;
}

template<class T1, class T2>
bool operator<(sequence<T1>& s1, sequence<T2>& s2)
{
	return (s1.get_size() < s2.get_size());
}

template<class T1, class T2>
bool operator>(sequence<T1>& s1, sequence<T2>& s2)
{
	return (s1.get_size() > s2.get_size());
}

int main() {
	system("chcp 1251"); system("cls");
	sequence<int> s1;
	sequence<string> s2;

	cout << "Введіть першу послідовність(символ -- кінець):\n";
	cin >> s1;
	Iterator<int> itr(s1);

	cout << "\n\tПерша послідовність\n";
	while (itr()) {
		cout << *itr << "   ";
		itr++;
	}

	s2.add("some");
	s2.add("txt");
	s2.add("here");
	Iterator<string> str_itr(s2);
	cout << "\n\tДруга послідовність:\n";
	while (str_itr()) {
		cout << *str_itr << "   ";
		str_itr++;
	}

	cout << "\n\nперша > друга?\n" << ((s1 > s2) ? "Так" : "Ні") << endl;
	cout << "\nперша < друга?\n" << ((s1 < s2) ? "Так" : "Ні") << endl;
	//cout << "\nперша == друга?\n" << ((s1 == s2) ? "Так" : "Ні") << endl;
	//cout << "\nперша != друга?\n" << ((s1 != s2) ? "Так" : "Ні") << endl;

	return 0;
}

template <class T>
sequence<T>::sequence(int size) {
	data = new T[this->size = size];
	for (int i = 0; i < size; i++)
		data[i] = T(0);
}

template <class T>
sequence<T>::~sequence() {
	delete[] data;
	data = NULL;
}

template<class T>
void sequence<T>::add(T new_e)
{
	size++;
	T* temp = new T[size];
	try {
		//copy(data, data + size, temp);
		for (int i = 0; i < size-1; i++) {
			temp[i] = data[i];
		}
	}
	catch (...) {
		delete[] temp;
		throw;
	}
	delete[] data;
	data = new T[size];
	data = temp;
	data[size - 1] = new_e;
}

template<class T>
T sequence<T>::get_element(unsigned index)
{
	if (index >= size)
		return data[size - 1];
	return data[index];
}

template<class T>
sequence<T>& sequence<T>::operator+(sequence<T>& s)
{
	T* temp = new T[this->size + s.size];
	try {
		copy(data, data + this->size, temp);
		copy(s.data, s.data + s.size, temp + size);
	}
	catch (...) {
		delete[] temp;
		throw;
	}
	delete[] data;
	data = temp;
	size += s.size;
	return *this;
}

template<class T>
sequence<T>& sequence<T>::operator=(const sequence<T>& s)
{
	T* temp = new T[s.size];
	copy(s.data, s.data + s.size, temp);
	delete[] this->data;
	this->data = new T[s.size];
	copy(temp, temp + s.size, this->data);
	this->size = s.size;
	return *this;
}

template <typename T>
ostream& operator<<(ostream& os, sequence<T>& s)
{
	copy(s.data, s.data + s.size, ostream_iterator<T>(os, "  "));
	return os;
}

template<typename T>
istream& operator>>(istream& is, sequence<T>& s)
{
	is.clear();
	is.seekg(0);
	T temp;
	while (is >> temp)
		s.add(temp);
	return is;
}

/*Input template:
1
2
3
4
5
q
6
7
8
9
q
*/