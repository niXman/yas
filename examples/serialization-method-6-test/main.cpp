
#include <cassert>

#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/serializers/std_types_serializers.hpp>

/***************************************************************************/

struct type {
	type()
		:i(33)
		,d()
	{}

	int i;
	yas::uint64_t d;
};

/***************************************************************************/

// writer
template<bool>
struct serializator {
	template<typename archive_type>
	static void apply(archive_type& ar, const type& t) {
		ar & t.i
			& t.i;
	}
};

// reader
template<>
struct serializator<false> {
	template<typename archive_type>
	static void apply(archive_type& ar, type& t) {
		ar & t.d;
	}
};

/***************************************************************************/

// one free-function serializer/deserializer
template<typename archive_type>
void serialize(archive_type& ar, type& t) {
	serializator<archive_type::_is_writable>::apply(ar, t);
}

/***************************************************************************/

int main() {
	type t1;
	yas::binary_mem_oarchive oa;
	oa & t1;

	type t2;
	yas::binary_mem_iarchive ia(oa.get_intrusive_buffer());
	ia & t2;

	assert(t2.d == 141733920801);
}

/***************************************************************************/
