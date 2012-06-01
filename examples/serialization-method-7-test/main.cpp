
#include <cassert>

#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/serializers/std_types_serializers.hpp>

/***************************************************************************/

struct base {
	base()
		:x(33)
	{}

	int x;

	template<typename archive_type>
	void serialize(archive_type& ar) {
		ar & x;
	}
};

struct derived: base {
	derived()
		:y(44)
	{}

	int y;

	template<typename archive_type>
	void serialize(archive_type& ar) {
		ar & yas::base_object<base>(*this)
			& y;
	}
};

/***************************************************************************/

int main() {
	derived t1, t2;
	yas::binary_mem_oarchive oa;
	oa & t1;

	yas::binary_mem_iarchive ia(oa.get_intrusive_buffer());
	ia & t2;

	assert(t2.x == 33 && t2.y == 44);
}

/***************************************************************************/
