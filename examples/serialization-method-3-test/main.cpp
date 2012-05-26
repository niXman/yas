
#include <cassert>

#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/serializers/std_types_serializers.hpp>

/***************************************************************************/

struct type {
	type()
		:i(33)
		,d(.33)
		,s("33")
		,v({33, 33, 33})
	{}

	int i;
	double d;
	std::string s;
	std::vector<int> v;

	// serializer/deserializer
	template<typename archive_type>
	void serialize(archive_type& ar) {
		ar & i
			& d
			& s
			& v;
	}
};

/***************************************************************************/

int main() {
	type t1;
	yas::binary_mem_oarchive oa;
	oa & t1;

	type t2;
	yas::binary_mem_iarchive ia(oa.get_intrusive_buffer());
	ia & t2;

	type t3;
	assert(t2.i == t3.i && t2.d == t3.d && t2.s == t3.s && t2.v == t3.v);
}

/***************************************************************************/
