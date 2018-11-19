#include "ahocorasick.hpp"
#include <algorithm>
using namespace std;

int main(){
  string T,P;
  cin >> T >> P;

  cout << P << endl;

  int a[P.size()];

  for(int i=0;i<P.size();i++)
    a[i]=i;

  ahocorasick ahotrie;


  map<string , vector<int> > resultmap;
  vector<string> key_vec;

  ahotrie.add_keyword(P);

  for(int i=0;i<P.size()-1;i++){
    for(int j=i+1;j<P.size();j++){

      string temp,pre,mid,post;
      stringstream sts;

      pre = P.substr(0,a[i]);
      mid = P.substr(a[i],a[j]-a[i]+1);
      reverse(mid.begin(),mid.end());
      if(j<P.size()-1){
        post = P.substr(a[j],P.size()-a[j]-1);
        sts << pre << mid << post;
      }
      else{
        sts << pre << mid;
      }
      temp = sts.str();

      ahotrie.add_keyword(temp);

      vector<int> index_vec;
      resultmap.insert(make_pair(temp,index_vec));
      key_vec.push_back(temp);
      cout << temp << endl;
    }
  }

  ahotrie.make_failure_link();

  ahotrie.matching(T);

  for(int i=0;i<key_vec.size();i++){
    string key=key_vec[i];
    vector<int> ve;
    ahotrie.ret_index_vector(key,ve);
    //ahotrie.print_vec(key);
    cout << key;
    for(int index : ve){
       cout << " " << index;
    }
    cout << endl;
  }


  return 0;
}
