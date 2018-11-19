#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

//sum of ascii from text's substring of which size is pattern size;
int preprocessing(string pattern,int num){
  int sum=0;
  for(int i=0;i<num;i++){
    sum+=pattern[i];
  }
  return sum;
}

/**
Verificating pattern and it's reverse of substring if matching or not
if
*/
bool substr_rev_match(string sub_text, string pattern){
  int tsi=0,tei=0,psi=0,pei=0;
  int rev_s=0, rev_e=0;
  int p_size=pattern.size();
  while(sub_text[tsi] == pattern[psi] && psi<p_size){
    tsi++;
    psi++;
  }

  while(sub_text[p_size-tei-1] == pattern[p_size-pei-1] && p_size-pei-1>0){
    tei++;
    pei++;
  }

  if(psi > p_size - pei -1){
    return true;
  }

  rev_s=psi;
  rev_e=p_size-pei-1;

  for(int i=0;i<rev_e-rev_s+1;i++){
    if(sub_text[rev_s+i] != pattern[rev_e - i]) return false;
    if(i==rev_e-rev_s) return true;
  }
  return false;
}


void matching(string text, string pattern, map< string, int> &str_map){
  int pat_size=pattern.size();
  int pat_sum=preprocessing(pattern,pat_size);
  int text_sum=preprocessing(text,pat_size);

  int i=0;
  while(i<text.size()-pat_size+1){
    // cout << "textsum : "<<text_sum << endl;
    // cout << "patsum : " <<pat_sum << endl;
    if(text_sum==pat_sum){
      string text_tmp=text.substr(i,pat_size);
      bool match=false;
      if(sub_match(text_tmp,pattern)){
        match=true;
      }

      if(match){
        string key=text.substr(i,pat_size);

        if(str_map.find(key)==str_map.end()){
          str_map.insert(make_pair(key,i));
          cout <<key << " matching"<<endl;
        }
        else{
          str_map[key]=i;
          cout <<key << " matching"<<endl;
        }
      }
    }
    text_sum = text_sum-text[i]+text[i+pat_size];
    i++;
  }

}

int main(){
  string T,P;
  map<string,int> mmap;

  cin >> T >> P;

  matching(T,P,mmap);

  for( pair<string,int> tempo : mmap){
    cout << tempo.first << " " << tempo.second << endl;
  }

  return 0;
}
