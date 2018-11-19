#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;

map<char,deque<int> > one_c_map;
map<string,deque<int> > two_c_map;
vector<pair<string,int> > result;

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

void twochar_matching(string text, string pattern){
  char last_char=pattern[pattern.size()-1];
  char b_last_char=pattern[pattern.size()-2];

  //character map in text (o ~ pattern length)
  for(int i=0;i<pattern.size();i++){
    one_c_map[text[i]].emplace_back(i);
  }

  //two character map in text (0 ~ pattern length)
  for(int i=0;i<pattern.size()-1;i++){
    stringstream sts;
    sts << text[i] << text[i+1];
    two_c_map[sts.str()].emplace_back(i);
  }

  for(int i=pattern.size()-1;i<text.size();i++){
    char sub_last_char=text[i];
    char sub_b_last_char=text[i-1];
    int subs_front= i-pattern.size()+1;
    int subs_rear = i;
    string st=text.substr(subs_front,pattern.size());
    bool ismatch=false;

    stringstream ordered;
    stringstream rev_ordered;

    ordered << sub_b_last_char << sub_last_char;
    rev_ordered << sub_last_char << sub_b_last_char;

    //cout << ordered.str() << " " << rev_ordered.str() << endl;

    //last two characters
    if(last_char == sub_last_char && b_last_char == sub_b_last_char){
      ismatch=substr_rev_match(st,pattern);
    }
    // else if(last_char == sub_b_last_char && b_last_char == sub_last_char){
    //   ismatch=substr_rev_match(st,pattern);
    // }
    else if(!one_c_map[b_last_char].empty()){
      ismatch=substr_rev_match(st,pattern);
    }
    else if(!two_c_map[rev_ordered.str()].empty()){
      ismatch=substr_rev_match(st,pattern);
    }

    //if matched, push_back to result vector
    if(ismatch){
      result.emplace_back(make_pair(st,subs_front));
    }

    //refresh character maps
    if(i!=text.size()-1){
      one_c_map[text[i+1]].emplace_back(i+1);
      one_c_map[text[subs_front]].pop_front();

      stringstream next;
      stringstream pre;
      next << text[i] << text[i+1];
      two_c_map[next.str()].emplace_back(i);
      pre << text[subs_front] << text[subs_front+1];
      two_c_map[pre.str()].pop_front();
      //cout <<st <<" "<< pre.str() << " out " << next.str() << " in " << ismatch << endl;
    }
  }
}


int main(){
  string T, P;
  cin >> T >> P;

  twochar_matching(T,P);

  for(int i=0;i<result.size();i++){
    cout << result[i].first <<" " << result[i].second <<endl;
  }

  return 0;
}
