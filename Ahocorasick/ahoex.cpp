#include "ahocorasick.hpp"

using namespace std;

int main(){
  ahocorasick ab(4,string("she"),string("he"),string("hers"),string("his"));
  // ab.add_keyword("she");
  // ab.add_keyword("he");
  // ab.add_keyword("hers");
  // ab.add_keyword("his");
  //
  // ab.make_failure_link();

  vector <int> ex;
  ab.matching("hershishissherserershe");

  ab.print_vec("his");
  ab.ret_index_vector("his",ex);

  cout << "result\n";
  for(int a : ex){
    cout << a << endl;
  }

  return 0;
}
