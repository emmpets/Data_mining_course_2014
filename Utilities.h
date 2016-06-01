#include <vector>

template <class T>
std::vector<T> operator- (std::vector<T> &l, std::vector<T> &r)
{
	
	if(l.size() != r.size())
	{
		throw new std::exception("vector sizes should match");
	}
	std::vector<T> ret(l);
	for(int i = l.size()-1; i >=0; i--)
		ret[i] -= r[i];
	return ret;
}

template <class T>
std::vector<T> operator+ (std::vector<T> &l, std::vector<T> &r)
{
	
	if(l.size() != r.size())
	{
		throw new std::exception("vector sizes should match");
	}
	std::vector<T> ret(l);
	for(int i = l.size()-1; i >=0; i--)
		ret[i] += r[i];
	return ret;
}

template< class T> T inner_product (const std::vector<T> &l, const std::vector<T> &r)
{
	if(l.size()!=r.size())
		throw new std::exception("Sizes must agree");
	T ret(0);
	for(int i = l.size()-1; i >=0; i--)
		ret+= r[i]*l[i];
	return ret;
}