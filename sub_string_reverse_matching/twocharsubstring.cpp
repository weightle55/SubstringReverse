#include <iostream>
#include <string>
#include <map>
using namespace std;

//matching pattern and sub reverse pattern with substring of text with pattern length
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

  if(psi > p_size - pei - 1){
    return true;
  }

  rev_s=psi;
  rev_e=p_size-pei-1;

  for(int i=0;i<rev_e-rev_s;i++){
    if(sub_text[rev_s+i] != pattern[rev_e - i]) return false;
    if(i==rev_e-rev_s-1) return true;
  }
  return false;

}

//
void twochar_matching(string text, string pattern, map<char,int> &cmap){
  char last_char=pattern.back();
  char b_last_char=pattern[pattern.size()-2];

  for(int i=0;i<pattern.size();i++){
    cmap[text[i]]++;
  }

  for(int i=pattern.size()-1;i<text.size();i++){
    char sub_last_char=text[i];
    char sub_b_last_char=text[i-1];
    int subs_front= i-pattern.size()+1;
    int subs_rear = i;
    string st;
    string sp;
    bool ismatch=false;

    //case that last two characters all matched
    if(last_char == sub_last_char && b_last_char == sub_b_last_char){
      st=text.substr(subs_front,pattern.size()-2);
      sp=pattern.substr(0,pattern.size()-2);
      ismatch=substr_rev_match(st,sp);
    }

    //case that last two characters reverse matched
    else if(last_char == sub_b_last_char && b_last_char == sub_last_char){
      for(int k=0;k<pattern.size()-2;k++){
        text[subs_front+k];
      }
    }

    //case that only last one character matched
    //and the other one is in substring of text
    else if(last_char == sub_last_char && cmap[b_last_char]>0){
      st=text.substr(subs_front,pattern.size()-1);
      sp=pattern.substr(0,pattern.size()-1);
      ismatch=substr_rev_match(st,sp);
    }

    //two characters are all in substring of text
    else if(cmap[last_char]>0 && cmap[b_last_char]>0){
      st=text.substr(subs_front,pattern.size());
      sp=pattern.substr(0,pattern.size());
      ismatch=substr_rev_match(st,sp);
    }

    if(ismatch) cout << text.substr(subs_front,pattern.size()) <<" "<<subs_front << endl;

    if(i!=text.size()-1){
      cmap[text[i+1]]++;
      cmap[text[subs_front]]--;
    }
  }

}

void make_p_map(map<char,int> &cmap){
  for(int i='A'; i<='Z';i++)
  cmap.insert(make_pair(i,0));
  for(int i='a'; i<='z';i++)
  cmap.insert(make_pair(i,0));
}

int main(){
  string T, P;
  cin >> T >> P;

  map<char,int> char_map;

  make_p_map(char_map);

  twochar_matching(T,P,char_map);

  return 0;
}
