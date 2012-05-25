
#ifndef _yas__text__test_hpp_included_
#define _yas__text__test_hpp_included_

#include <yas/text_iarchive.hpp>
#include <yas/text_oarchive.hpp>

#include <yas/serializers/std_types_serializers.hpp>

#if defined(YAS_SERIALIZE_BOOST_TYPES)
#include <yas/serializers/boost_types_serializers.hpp>

#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/include/comparison.hpp>
#endif

/***************************************************************************/

bool version_test() {
   yas::text_oarchive oa;
   yas::text_iarchive ia(oa.get_intrusive_buffer());

   if ( oa.archive_type() != ia.archive_type() ) {
      std::cout << "VERSION test failed! archive type is not equal!" << std::endl;
      return false;
   }
   if ( oa.bits() != ia.bits() ) {
      std::cout << "VERSION test failed! archive bits is not equal!" << std::endl;
      return false;
   }
   if ( oa.version() != ia.version() ) {
      std::cout << "VERSION test failed! archive versions is not equal!" << std::endl;
      return false;
   }
//   std::cout
//   << "text_oarchive: type = " << oa.archive_type() << std::endl
//   << "text_oarchive: bits = " << oa.bits() << std::endl
//   << "text_oarchive: vers = " << oa.version() << std::endl << std::endl;
//   std::cout
//   << "text_iarchive: type = " << ia.archive_type() << std::endl
//   << "text_iarchive: bits = " << ia.bits() << std::endl
//   << "text_iarchive: vers = " << ia.version() << std::endl << std::endl;

   return true;
}

/***************************************************************************/

bool pod_test() {
   yas::text_oarchive oa;

   char c = 1, cc;
   short s = 2, ss;
   int i = 3, ii;
   long l = 4, ll;
   float f = 3.14, ff;
   double d = 3.14256159, dd;
   oa & c
      & s
      & i
      & l
      & f
      & d;

   const size_t expected =
      4+ // archive information
      sizeof(c)+
      sizeof(s)+
      sizeof(i)+
      sizeof(l)+
      sizeof(f)+
      sizeof(d)
   ;
   if ( oa.size() != expected ) {
      std::cout
      << "POD test failed! bad size from serializer archive! expected = " << expected
      << ", current = " << oa.size() << std::endl;
      return false;
   }

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & cc
      & ss
      & ii
      & ll
      & ff
      & dd;

   if ( c != cc || s != ss || i != ii || l != ll || f != ff || d != dd ) {
      std::cout << "POD deserialization result error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool auto_array_test() {
   static const size_t array_size = 6;

   char ca1[] = {"123456"}, ca2[array_size+1] = {0};
   unsigned char uca1[] = {"123456"}, uca2[array_size+1] = {0};
   short sa1[array_size] = {1,2,3,4,5,6}, sa2[array_size];
   unsigned short usa1[array_size] = {1,2,3,4,5,6}, usa2[array_size];
   int ia1[array_size] = {1,2,3,4,5,6}, ia2[array_size];
   unsigned int uia1[array_size] = {1,2,3,4,5,6}, uia2[array_size];
   long la1[array_size] = {1,2,3,4,5,6}, la2[array_size];
   unsigned long ula1[array_size] = {1,2,3,4,5,6}, ula2[array_size];
   long long lla1[array_size] = {1,2,3,4,5,6}, lla2[array_size];
   unsigned long long ulla1[array_size] = {1,2,3,4,5,6}, ulla2[array_size];
   long double lda1[array_size] = {1,2,3,4,5,6}, lda2[array_size];
   double da1[array_size] = {1,2,3,4,5,6}, da2[array_size];
   float fa1[array_size] = {1,2,3,4,5,6}, fa2[array_size];

   {  yas::text_oarchive oa;
      oa & ca1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & ca2;
      if ( memcmp(ca1, ca2, array_size*sizeof(ca1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & uca1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & uca2;
      if ( memcmp(uca1, uca2, array_size*sizeof(uca1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & sa1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & sa2;
      if ( memcmp(sa1, sa2, array_size*sizeof(sa1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & usa1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & usa2;
      if ( memcmp(usa1, usa2, array_size*sizeof(usa1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & ia1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & ia2;
      if ( memcmp(ia1, ia2, array_size*sizeof(ia1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & uia1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & uia2;
      if ( memcmp(uia1, uia2, array_size*sizeof(uia1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & la1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & la2;
      if ( memcmp(la1, la2, array_size*sizeof(la1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & ula1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & ula2;
      if ( memcmp(ula1, ula2, array_size*sizeof(ula1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & lla1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & lla2;
      if ( memcmp(lla1, lla2, array_size*sizeof(lla1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & ulla1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & ulla2;
      if ( memcmp(ulla1, ulla2, array_size*sizeof(ulla1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & lda1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & lda2;
      if ( memcmp(lda1, lda2, array_size*sizeof(lda1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & da1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & da2;
      if ( memcmp(da1, da2, array_size*sizeof(da1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }
   {  yas::text_oarchive oa;
      oa & fa1;
      yas::text_iarchive ia(oa.get_intrusive_buffer());
      ia & fa2;
      if ( memcmp(fa1, fa2, array_size*sizeof(fa1[0])) ) {
         std::cout << "AUTO_ARRAY deserialization error!" << std::endl;
         return false;
      }
   }

   return true;
}

/***************************************************************************/

bool array_test() {
#if defined(YAS_HAS_STD_ARRAY)
   std::array<int, 10> arr1 = {
      {0,1,2,3,4,5,6,7,8,9}
   }, arr2;

   yas::text_oarchive oa;
   oa & arr1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & arr2;

   if ( arr1 != arr2 ) {
      std::cout << "ARRAY deserialization error!" << std::endl;
      return false;
   }

   std::array<std::string, 10> arr3 = {
      {"0","1","2","3","4","5","6","7","8","9"}
   }, arr4;

   yas::text_oarchive oa2;
   oa2 & arr3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & arr4;

   if ( arr3 != arr4 ) {
      std::cout << "ARRAY deserialization error!" << std::endl;
      return false;
   }

#endif // defined(YAS_HAS_STD_ARRAY)

#if defined(YAS_HAS_BOOST_ARRAY)
   boost::array<int, 10> arr5 = {
      {0,1,2,3,4,5,6,7,8,9}
   }, arr6;

   yas::text_oarchive oa3;
   oa3 & arr5;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & arr6;

   if ( arr5 != arr6 ) {
      std::cout << "ARRAY deserialization error!" << std::endl;
      return false;
   }

   boost::array<std::string, 10> arr7 = {
      {"0","1","2","3","4","5","6","7","8","9"}
   }, arr8;

   yas::text_oarchive oa4;
   oa4 & arr7;

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & arr8;

   if ( arr7 != arr8 ) {
      std::cout << "ARRAY deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_ARRAY)
   return true;
}

/***************************************************************************/

bool string_test() {
   yas::text_oarchive oa;
   std::string s("string string"), ss;
   oa & s;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & ss;

   if ( ss != s ) {
      std::cout << "STRING deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool wstring_test() {
   yas::text_oarchive oa;
   std::wstring ws(L"wstring wstring"), wss;
   oa & ws;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & wss;

   if ( ws != wss ) {
      std::cout << "WSTRING deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool pair_test() {
   yas::text_oarchive oa;
   std::pair<std::wstring, std::string> p = std::make_pair(L"wstring wstring", "string string"), pp;
   oa & p;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & pp;

   if ( p != pp ) {
      std::cout << "PAIR deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/


#if defined(YAS_HAS_BOOST_TUPLE)
#include <boost/tuple/tuple_comparison.hpp>
#endif // defined(YAS_HAS_BOOST_TUPLE)

bool tuple_test() {
#if defined(YAS_HAS_BOOST_TUPLE)
   boost::tuples::tuple<int, int> t1(1, 3), t2;

   yas::text_oarchive oa;
   oa & t1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & t2;

   if ( t1 != t2 ) {
      std::cout << "TUPLE test failed!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_TUPLE)

#if defined(YAS_HAS_STD_TUPLE)
   std::tuple<int, int> t3(4, 7), t4;
   yas::text_oarchive oa2;
   oa2 & t3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & t4;

   if ( t3 != t4 ) {
      std::cout << "TUPLE test failed!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_STD_TUPLE)
   return true;
}

/***************************************************************************/

bool vector_test() {
   yas::text_oarchive oa;
   std::vector<int> v, vv;
   v.push_back(0);
   v.push_back(1);
   v.push_back(2);
   v.push_back(3);
   v.push_back(4);
   v.push_back(5);
   v.push_back(6);
   v.push_back(7);
   v.push_back(8);
   v.push_back(9);

   oa & v;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & vv;

   if ( v != vv ) {
      std::cout << "VECTOR deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool map_test() {
   yas::text_oarchive oa;
   std::map<int, int> pod_map, pod_map2;
   pod_map.insert(std::make_pair(1, 2));
   pod_map.insert(std::make_pair(2, 3));
   pod_map.insert(std::make_pair(3, 4));

   oa & pod_map;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & pod_map2;

   if ( pod_map != pod_map2 ) {
      std::cout << "MAP deserialization error!" << std::endl;
      return false;
   }

   std::map<int, std::string> map, map2;
   map.insert(std::make_pair(1, "1"));
   map.insert(std::make_pair(2, "2"));
   map.insert(std::make_pair(3, "3"));

   yas::text_oarchive oa2;
   oa2 & map;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & map2;

   if ( map != map2 ) {
      std::cout << "MAP deserialization error!" << std::endl;
      return false;
   }

   std::map<std::string, int> map3, map4;
   map3.insert(std::make_pair("1", 1));
   map3.insert(std::make_pair("2", 2));
   map3.insert(std::make_pair("3", 3));

   yas::text_oarchive oa3;
   oa3 & map3;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & map4;

   if ( map3 != map4 ) {
      std::cout << "MAP deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool set_test() {
   std::set<int> set1, set2;
   set1.insert(0);
   set1.insert(1);
   set1.insert(2);
   set1.insert(3);
   set1.insert(4);
   set1.insert(5);
   set1.insert(6);
   set1.insert(7);
   set1.insert(8);
   set1.insert(9);

   yas::text_oarchive oa;
   oa & set1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & set2;

   if ( set1 != set2 ) {
      std::cout << "SET deserialization error!" << std::endl;
      return false;
   }

   std::set<std::string> set3, set4;
   set3.insert("1");
   set3.insert("2");
   set3.insert("3");

   yas::text_oarchive oa2;
   oa2 & set3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & set4;

   if ( set3 != set4 ) {
      std::cout << "SET deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool multimap_test() {
   std::multimap<int, int> pod_map, pod_map2;
   pod_map.insert(std::make_pair(1, 2));
   pod_map.insert(std::make_pair(3, 3));
   pod_map.insert(std::make_pair(3, 4));

   yas::text_oarchive oa;
   oa & pod_map;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & pod_map2;

   if ( pod_map != pod_map2 ) {
      std::cout << "MULTIMAP deserialization error!" << std::endl;
      return false;
   }

   std::multimap<int, std::string> map, map2;
   map.insert(std::make_pair(1, "2"));
   map.insert(std::make_pair(3, "3"));
   map.insert(std::make_pair(3, "4"));

   yas::text_oarchive oa2;
   oa2 & map;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & map2;

   if ( map != map2 ) {
      std::cout << "MULTIMAP deserialization error!" << std::endl;
      return false;
   }

   std::multimap<std::string, int> map3, map4;
   map3.insert(std::make_pair("1", 1));
   map3.insert(std::make_pair("2", 2));
   map3.insert(std::make_pair("3", 4));

   yas::text_oarchive oa3;
   oa3 & map3;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & map4;

   if ( map3 != map4 ) {
      std::cout << "MULTIMAP deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool multiset_test() {
   std::multiset<int> set1, set2;
   set1.insert(0);
   set1.insert(1);
   set1.insert(2);
   set1.insert(3);
   set1.insert(4);
   set1.insert(5);
   set1.insert(6);
   set1.insert(7);
   set1.insert(8);
   set1.insert(9);

   yas::text_oarchive oa;
   oa & set1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & set2;

   if ( set1.size() != 10 || set2.size() != 10 || set1 != set2 ) {
      std::cout << "MULTISET deserialization error!" << std::endl;
      return false;
   }

   std::multiset<std::string> set3, set4;
   set3.insert("1");
   set3.insert("2");
   set3.insert("3");

   yas::text_oarchive oa2;
   oa2 & set3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & set4;

   if ( set3.size() != 3 || set4.size() != 3 || set3 != set4 ) {
      std::cout << "MULTISET deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool unordered_map_test() {
#if defined(YAS_HAS_STD_UNORDERED)
   yas::text_oarchive oa;
   std::unordered_map<int, int> pod_map = {
      {1, 2},
      {2, 3},
      {3, 4}
   }, pod_map2;

   oa & pod_map;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & pod_map2;

   if ( pod_map != pod_map2 ) {
      std::cout << "UNORDERED_MAP deserialization error!" << std::endl;
      return false;
   }

   std::unordered_map<int, std::string> map = {
      {1, "1"},
      {2, "2"},
      {3, "3"}
   }, map2;

   yas::text_oarchive oa2;
   oa2 & map;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & map2;

   if ( map != map2 ) {
      std::cout << "UNORDERED_MAP deserialization error!" << std::endl;
      return false;
   }

   std::unordered_map<std::string, int> map3 = {
      {"1", 1},
      {"2", 2},
      {"3", 3}
   }, map4;

   yas::text_oarchive oa3;
   oa3 & map3;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & map4;

   if ( map3 != map4 ) {
      std::cout << "UNORDERED_MAP deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_STD_UNORDERED)

#if defined(YAS_HAS_BOOST_UNORDERED)
   boost::unordered_map<int, int> map5, map6;
   map5.insert(std::make_pair(1, 2));
   map5.insert(std::make_pair(2, 3));
   map5.insert(std::make_pair(3, 4));
   map5.insert(std::make_pair(4, 5));

   yas::text_oarchive oa4;
   oa4 & map5;

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & map6;

   if ( map5 != map6 ) {
      std::cout << "UNORDERED_MAP deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_UNORDERED)
   return true;
}

/***************************************************************************/

bool unordered_set_test() {
#if defined(YAS_HAS_STD_UNORDERED)
   std::unordered_set<int> set1 = {
      0,1,2,3,4,5,6,7,8,9
   }, set2;

   yas::text_oarchive oa;
   oa & set1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & set2;

   if ( set1 != set2 ) {
      std::cout << "UNORDERED_SET deserialization error!" << std::endl;
      return false;
   }

   std::unordered_set<std::string> set3 = {
      "0",
      "1",
      "2"
   }, set4;

   yas::text_oarchive oa2;
   oa2 & set3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & set4;

   if ( set3 != set4 ) {
      std::cout << "UNORDERED_SET deserialization error!" << std::endl;
      return false;
   }

#endif // defined(YAS_HAS_STD_UNORDERED)

#if defined(YAS_HAS_BOOST_UNORDERED)
   boost::unordered_set<int> set5, set6;
   set5.insert(0);
   set5.insert(1);
   set5.insert(2);
   set5.insert(3);
   set5.insert(4);
   set5.insert(5);
   set5.insert(6);
   set5.insert(7);
   set5.insert(8);
   set5.insert(9);

   yas::text_oarchive oa4;
   oa4 & set5;

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & set6;

   if ( set5 != set6 ) {
      std::cout << "UNORDERED_SET deserialization error!" << std::endl;
      return false;
   }

   boost::unordered_set<std::string> set7, set8;
   set7.insert("1");
   set7.insert("1");
   set7.insert("2");
   set7.insert("5");

   yas::text_oarchive oa5;
   oa5 & set7;

   yas::text_iarchive ia5(oa5.get_intrusive_buffer());
   ia5 & set8;

   if ( set7 != set8 ) {
      std::cout << "UNORDERED_SET deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_UNORDERED)
   return true;
}

/***************************************************************************/

bool unordered_multimap_test() {
#if defined(YAS_HAS_STD_UNORDERED)
   yas::text_oarchive oa;
   std::unordered_multimap<int, int> pod_map = {
      {1, 2},
      {2, 3},
      {2, 4}
   }, pod_map2;

   oa & pod_map;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & pod_map2;

   if ( pod_map != pod_map2 ) {
      std::cout << "UNORDERED_MULTIMAP deserialization error!" << std::endl;
      return false;
   }

   std::unordered_multimap<int, std::string> map = {
      {1, "1"},
      {2, "2"},
      {2, "3"}
   }, map2;

   yas::text_oarchive oa2;
   oa2 & map;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & map2;

   if ( map != map2 ) {
      std::cout << "UNORDERED_MULTIMAP deserialization error!" << std::endl;
      return false;
   }

   std::unordered_multimap<std::string, int> map3 = {
      {"1", 1},
      {"2", 2},
      {"3", 3}
   }, map4;

   yas::text_oarchive oa3;
   oa3 & map3;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & map4;

   if ( map3 != map4 ) {
      std::cout << "UNORDERED_MULTIMAP deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_STD_UNORDERED)

#if defined(YAS_HAS_BOOST_UNORDERED)
   boost::unordered_multimap<int, int> map5, map6;
   map5.insert(std::make_pair(1, 2));
   map5.insert(std::make_pair(1, 2));
   map5.insert(std::make_pair(3, 2));
   map5.insert(std::make_pair(1, 5));
   map5.insert(std::make_pair(3, 5));

   yas::text_oarchive oa4;
   oa4 & map5;

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & map6;

   if ( map5 != map6 ) {
      std::cout << "UNORDERED_MULTIMAP deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_UNORDERED)
   return true;
}

/***************************************************************************/

bool unordered_multiset_test() {
#if defined(YAS_HAS_STD_UNORDERED)
   std::unordered_multiset<int> set1 = {
      0,0,2,3,4,4,6,7,8,9
   }, set2;

   yas::text_oarchive oa;
   oa & set1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & set2;

   if ( set1.size() != 10 || set2.size() != 10 || set1 != set2 ) {
      std::cout << "UNORDERED_MULTISET deserialization error!" << std::endl;
      return false;
   }

   std::unordered_multiset<std::string> set3 = {
      "0",
      "1",
      "1"
   }, set4;

   yas::text_oarchive oa2;
   oa2 & set3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & set4;

   if ( set3.size() != 3 || set4.size() != 3 || set3 != set4 ) {
      std::cout << "UNORDERED_MULTISET deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_STD_UNORDERED)

#if defined(YAS_HAS_BOOST_UNORDERED)
   boost::unordered_multiset<int> set5, set6;
   set5.insert(0);
   set5.insert(1);
   set5.insert(2);
   set5.insert(3);
   set5.insert(4);
   set5.insert(5);
   set5.insert(5);
   set5.insert(7);
   set5.insert(8);
   set5.insert(8);

   yas::text_oarchive oa3;
   oa3 & set5;

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & set6;

   if ( set5.size() != 10 || set6.size() != 10 || set5 != set6 ) {
      std::cout << "UNORDERED_MULTISET deserialization error!" << std::endl;
      return false;
   }

   boost::unordered_multiset<std::string> set7, set8;
   set7.insert("1");
   set7.insert("1");
   set7.insert("3");

   yas::text_oarchive oa4;
   oa4 & set7;

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & set8;

   if ( set7.size() != 3 || set8.size() != 3 || set7 != set8 ) {
      std::cout << "UNORDERED_MULTISET deserialization error!" << std::endl;
      return false;
   }
#endif // defined(YAS_HAS_BOOST_UNORDERED)
   return true;
}

/***************************************************************************/

#if defined(YAS_HAS_BOOST_FUSION)
bool fusion_pair_test() {
   boost::fusion::pair<std::size_t, char> p1('f'), p2;
   yas::text_oarchive oa;
   oa & p1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & p2;

   if ( p1 != p2 ) {
      std::cout << "FUSION_PAIR deserialization error!" << std::endl;
      return false;
   }

   std::vector<std::string> vec;
   vec.push_back("5");
   vec.push_back("5");
   vec.push_back("6");
   vec.push_back("7");

   boost::fusion::pair<std::size_t, std::vector<std::string> > p3(vec), p4;
   yas::text_oarchive oa2;
   oa2 & p3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & p4;

   if ( p3 != p4 ) {
      std::cout << "FUSION_PAIR deserialization error!" << std::endl;
      return false;
   }
   return true;
}

/***************************************************************************/

bool fusion_tuple_test() {
   boost::fusion::tuple<int, double> v1(33, 3.14159265), v2;
   yas::text_oarchive oa;
   oa & v1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & v2;
   if ( v1 != v2 ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   std::set<std::string> set;
   set.insert("2");
   set.insert("3");
   set.insert("4");

   boost::fusion::tuple<
      std::string,
      std::set<std::string>
   > v3("1", set), v4;

   yas::text_oarchive oa2;
   oa2 & v3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & v4;
   if ( v3 != v4 ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::tuple<int, int> vv;
   yas::text_oarchive oa3;
   oa3 & boost::fusion::make_tuple(33,44);

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & vv;

   if ( vv != boost::fusion::make_tuple(33,44) ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::tuple<boost::uint64_t, std::string> v5(33, "str"), v6;
   yas::text_oarchive oa4;
   oa4 & v5;

   const size_t expected_size =
      4+ // archive information
      sizeof(boost::uint8_t)+ // fusion::tuple size marker
      sizeof(boost::uint64_t)+ // first type
      sizeof(size_t) // string size marker
      +3; // string length
   const size_t current_size = oa4.get_intrusive_buffer().size;
   if ( current_size != expected_size ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   yas::text_oarchive oa5;
   oa5 & boost::fusion::make_tuple<boost::uint64_t, std::string>(33, "str");

   const size_t current_size2 = oa5.get_intrusive_buffer().size;
   if ( current_size2 != expected_size ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia5(oa5.get_intrusive_buffer());
   ia5 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_TUPLE deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool fusion_vector_test() {
   boost::fusion::vector<int, double> v1(33, 3.14159265), v2;
   yas::text_oarchive oa;
   oa & v1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & v2;
   if ( v1 != v2 ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   std::set<std::string> set;
   set.insert("2");
   set.insert("3");
   set.insert("4");

   boost::fusion::vector<
      std::string,
      std::set<std::string>
   > v3("1", set), v4;

   yas::text_oarchive oa2;
   oa2 & v3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & v4;
   if ( v3 != v4 ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::vector<int, int> vv;
   yas::text_oarchive oa3;
   oa3 & boost::fusion::make_vector(33,44);

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & vv;

   if ( vv != boost::fusion::make_vector(33,44) ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::vector<boost::uint64_t, std::string> v5(33, "str"), v6;
   yas::text_oarchive oa4;
   oa4 & v5;

   const size_t expected_size =
      4+ // archive information
      sizeof(boost::uint8_t)+ // fusion::vector size marker
      sizeof(boost::uint64_t)+ // first type
      sizeof(size_t) // string size marker
      +3; // string length
   const size_t current_size = oa4.get_intrusive_buffer().size;
   if ( current_size != expected_size ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   yas::text_oarchive oa5;
   oa5 & boost::fusion::make_vector<boost::uint64_t, std::string>(33, "str");

   const size_t current_size2 = oa5.get_intrusive_buffer().size;
   if ( current_size2 != expected_size ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia5(oa5.get_intrusive_buffer());
   ia5 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_VECTOR deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool fusion_list_test() {
   boost::fusion::list<int, double> v1(33, 3.14159265), v2;
   yas::text_oarchive oa;
   oa & v1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & v2;
   if ( v1 != v2 ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   std::set<std::string> set;
   set.insert("2");
   set.insert("3");
   set.insert("4");

   boost::fusion::list<
      std::string,
      std::set<std::string>
   > v3("1", set), v4;

   yas::text_oarchive oa2;
   oa2 & v3;

   yas::text_iarchive ia2(oa2.get_intrusive_buffer());
   ia2 & v4;
   if ( v3 != v4 ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::list<int, int> vv;
   yas::text_oarchive oa3;
   oa3 & boost::fusion::make_list(33,44);

   yas::text_iarchive ia3(oa3.get_intrusive_buffer());
   ia3 & vv;

   if ( vv != boost::fusion::make_list(33,44) ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   boost::fusion::list<boost::uint64_t, std::string> v5(33, "str"), v6;
   yas::text_oarchive oa4;
   oa4 & v5;

   const size_t expected_size =
      4+ // archive information
      sizeof(boost::uint8_t)+ // fusion::list size marker
      sizeof(boost::uint64_t)+ // first type
      sizeof(size_t) // string size marker
      +3; // string length
   const size_t current_size = oa4.get_intrusive_buffer().size;
   if ( current_size != expected_size ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia4(oa4.get_intrusive_buffer());
   ia4 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   yas::text_oarchive oa5;
   oa5 & boost::fusion::make_list<boost::uint64_t, std::string>(33, "str");

   const size_t current_size2 = oa5.get_intrusive_buffer().size;
   if ( current_size2 != expected_size ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   yas::text_iarchive ia5(oa5.get_intrusive_buffer());
   ia5 & v6;
   if ( v5 != v6 ) {
      std::cout << "FUSION_LIST deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool fusion_set_test() {
#if 0

   typedef boost::fusion::set<int, int> set;
   set s1(33, 44), s2;

   std::cout << "size = " << boost::fusion::size(s1) << std::endl;
   std::cout << "0 = " << boost::fusion::at_key<int>(s1) << std::endl;
   std::cout << "1 = " << boost::fusion::at_key<int>(s1) << std::endl;

   yas::text_oarchive oa;
   oa & s1;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & s2;

   if ( s1 != s2 ) {
      std::cout << "FUSION_SET deserialization error!" << std::endl;
      return false;
   }
#endif

   return true;
}

/***************************************************************************/

bool fusion_map_test() {
   return false;
}
#endif // defined(YAS_HAS_BOOST_FUSION)

/***************************************************************************/

bool type_with_one_serializer_flag = false;

struct type_with_one_serializer {
   type_with_one_serializer() {}

   int x;
   int y;
};

template<typename Archive>
void serialize(Archive& ar, type_with_one_serializer& t) {
   ar & t.x
      & t.y;
   type_with_one_serializer_flag = true;
}

bool function_serializer_test() {
   type_with_one_serializer type, type2;
   type.x = 33; type.y = 44;
   yas::text_oarchive oa;
   oa & type;

   if ( !type_with_one_serializer_flag ) {
      std::cout << "free function serialize() is not called!" << std::endl;
      return false;
   }

   type_with_one_serializer_flag = false;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & type2;

   if ( !type_with_one_serializer_flag ) {
      std::cout << "free function serialize() is not called!" << std::endl;
      return false;
   }

   if ( type.x != type2.x || type.y != type2.y ) {
      std::cout << "ONE FUNCTION test failed!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool type_for_split_function_serializers_save_flag = false;
bool type_for_split_function_serializers_load_flag = false;

struct type_for_split_function_serializers {
   type_for_split_function_serializers() {}

   int x;
   int y;
};

template<typename Archive>
void serialize(Archive& ar, const type_for_split_function_serializers& t) {
   ar & t.x
      & t.y;
   type_for_split_function_serializers_save_flag = true;
}

template<typename Archive>
void serialize(Archive& ar, type_for_split_function_serializers& t) {
   ar & t.x
      & t.y;
   type_for_split_function_serializers_load_flag = true;
}

bool split_function_serializer_test() {
   type_for_split_function_serializers t1, t2;
   t1.x = 33; t1.y = 44;

   yas::text_oarchive oa;
   oa & t1;

   if ( !type_for_split_function_serializers_save_flag ) {
      std::cout << "free function serialize() for save is not called!" << std::endl;
      return false;
   }

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & t2;

   if ( !type_for_split_function_serializers_load_flag ) {
      std::cout << "free function serialize() for load is not called!" << std::endl;
      return false;
   }

   if ( t1.x != t2.x || t1.y != t2.y ) {
      std::cout << "SPLIT FUNCTION deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool type_with_one_method_serializer_flag = false;

struct type_with_one_method_serializer {
   type_with_one_method_serializer() {}

   int x;
   int y;

   template<typename Archive>
   void serialize(Archive& ar) {
      ar & x
         & y;
      type_with_one_method_serializer_flag = true;
   }
};

bool method_serializer_test() {
   type_with_one_method_serializer t1, t2;
   t1.x = 33; t1.y = 44;

   yas::text_oarchive oa;
   oa & t1;

   if ( !type_with_one_method_serializer_flag ) {
      std::cout << "method serialize() is not called!" << std::endl;
      return false;
   }

   type_with_one_method_serializer_flag = false;

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & t2;

   if ( !type_with_one_method_serializer_flag ) {
      std::cout << "method serialize() is not called!" << std::endl;
      return false;
   }

   if ( t1.x != t2.x || t1.y != t2.y ) {
      std::cout << "ONE METHOD deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

bool type_with_split_method_serializers_save_flag = false;
bool type_with_split_method_serializers_load_flag = false;

struct type_with_split_method_serializers {
   type_with_split_method_serializers() {}

   int x;
   int y;

   void serialize(yas::text_oarchive& ar) const {
      ar & x
         & y;
      type_with_split_method_serializers_save_flag = true;
   }
   void serialize(yas::text_iarchive& ar) {
      ar & x
         & y;
      type_with_split_method_serializers_load_flag = true;
   }
};

bool split_method_serializer_test() {
   type_with_split_method_serializers t1, t2;
   t1.x = 33; t1.y = 44;

   yas::text_oarchive oa;
   oa & t1;

   if ( !type_with_split_method_serializers_save_flag ) {
      std::cout << "method serialize() for save is not called!" << std::endl;
      return false;
   }

   yas::text_iarchive ia(oa.get_intrusive_buffer());
   ia & t2;

   if ( !type_with_split_method_serializers_load_flag ) {
      std::cout << "method serialize() for load is not called!" << std::endl;
      return false;
   }

   if ( t1.x != t2.x || t1.y != t2.y ) {
      std::cout << "SPLIT METHOD deserialization error!" << std::endl;
      return false;
   }

   return true;
}

/***************************************************************************/

namespace size_test {

struct size_test_pod_type {
   size_test_pod_type() {}

   size_t x;
   size_t y;

   template<typename Archive>
   void serialize(Archive& ar, const unsigned) {
      ar & x
         & y;
   }
   template<typename Archive>
   void serialize(Archive& ar) {
      ar & x
         & y;
   }
};

} // namespace size_test

#include <sstream>
#if defined(YAS_SERIALIZE_BOOST_TYPES)

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

void boost_archive(const size_t iteration) {
   size_test::size_test_pod_type t;
   std::ostringstream os;
   boost::archive::binary_oarchive oa(os);
   for ( size_t idx = 0; idx < iteration; ++idx ) {
      t.x = t.y = idx;
      oa & t;
   }
}
#endif // defined(YAS_SERIALIZE_BOOST_TYPES)

void yas_archive(const size_t iteration) {
   size_test::size_test_pod_type t;
   yas::text_oarchive oa;
   for ( size_t idx = 0; idx < iteration; ++idx ) {
      t.x = t.y = idx;
      oa & t;
   }
}

bool speed_test() {
   const size_t count = 1024*1024*10;
   clock_t start = clock();
   clock_t boost_time=0, yas_time;

#if defined(YAS_SERIALIZE_BOOST_TYPES)
   boost_archive(count);
   std::cout << "boost time: " << (boost_time=(clock()-start)/(CLOCKS_PER_SEC/1000)) << " ms." << std::endl;
#endif
   start = clock();
   yas_archive(count);
   std::cout << "yas time  : " << (yas_time=(clock()-start)/(CLOCKS_PER_SEC/1000)) << " ms." << std::endl;

   std::cout << "speed up  : " << (((double)boost_time)/((double)yas_time)) << std::endl;

   return true;
}

/***************************************************************************/

bool text_tests() {
   const char* passed = "passed";
   const char* failed = "failed!";

   printf("VERSION            test %s\n", (version_test()?passed:failed));
   printf("POD                test %s\n", (pod_test()?passed:failed));
   printf("AUTO_ARRAY         test %s\n", (auto_array_test()?passed:failed));
#if defined(YAS_HAS_BOOST_ARRAY) || defined(YAS_HAS_STD_ARRAY)
   printf("ARRAY              test %s\n", (array_test()?passed:failed));
#endif
   printf("STRING             test %s\n", (string_test()?passed:failed));
   printf("WSTRING            test %s\n", (wstring_test()?passed:failed));
   printf("PAIR               test %s\n", (pair_test()?passed:failed));
#if defined(YAS_HAS_BOOST_TUPLE) || defined(YAS_HAS_STD_TUPLE)
   printf("TUPLE              test %s\n", (tuple_test()?passed:failed));
#endif
   printf("VECTOR             test %s\n", (vector_test()?passed:failed));
   printf("MAP                test %s\n", (map_test()?passed:failed));
   printf("SET                test %s\n", (set_test()?passed:failed));
   printf("MULTIMAP           test %s\n", (multimap_test()?passed:failed));
   printf("MULTISET           test %s\n", (multiset_test()?passed:failed));
#if defined(YAS_HAS_BOOST_UNORDERED) || defined(YAS_HAS_STD_UNORDERED)
   printf("UNORDERED_MAP      test %s\n", (unordered_map_test()?passed:failed));
   printf("UNORDERED_SET      test %s\n", (unordered_set_test()?passed:failed));
   printf("UNORDERED_MULTIMAP test %s\n", (unordered_multimap_test()?passed:failed));
   printf("UNORDERED_MULTISET test %s\n", (unordered_multiset_test()?passed:failed));
#endif
#if defined(YAS_HAS_BOOST_FUSION)
   printf("FUSION_PAIR        test %s\n", (fusion_pair_test()?passed:failed));
   printf("FUSION_TUPLE       test %s\n", (fusion_tuple_test()?passed:failed));
   printf("FUSION_VECTOR      test %s\n", (fusion_vector_test()?passed:failed));
   printf("FUSION_LIST        test %s\n", (fusion_list_test()?passed:failed));
//   printf("FUSION_SET         test %s\n", (fusion_set_test()?passed:failed));
//   printf("FUSION_MAP         test %s\n", (fusion_map_test()?passed:failed));
#endif
   printf("ONE_FUNCTION       test %s\n", (function_serializer_test()?passed:failed));
   printf("SPLIT_FUNCTION     test %s\n", (split_function_serializer_test()?passed:failed));
   printf("ONE_METHOD         test %s\n", (method_serializer_test()?passed:failed));
   printf("SPLIT_METHOD       test %s\n", (split_method_serializer_test()?passed:failed));

   speed_test();

   return true;
}

/***************************************************************************/

#endif // _yas__text__test_hpp_included_
