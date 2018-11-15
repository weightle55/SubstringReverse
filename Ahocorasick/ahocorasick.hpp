#include <iostream>
#include <cstdarg>
#include <sstream>
#include <map>
#include <string>
#include <deque>
#include <vector>

class Node{
//Node variable
private:
  bool is_complete_word;
  bool visited;
  char node_ch;
  std::string node_str;
  Node* failure_link;
  Node* parent_node;

//Node edge
protected:
  std::map<char,Node*> charmap;

public:
  //Constructor :: initializing Node variable
  Node(std::string str,char readch, bool ter){
    std::stringstream sts;
    if(readch=='\0')
      sts << str << "";
    else
      sts << str << readch;
    node_str = sts.str();
    is_complete_word=ter;
    parent_node=this;
    failure_link=this;
    visited=false;
    node_ch=readch;
  };
  std::string node_string();
  bool is_word();
  void set_is_word(bool isword);
  bool is_character(char ch);
  void map_add(char now, Node* node);
  Node* next_char_node(char now);
  void set_failure_link(Node *fail);
  Node* get_failure_link();
  void set_parent_node(Node* node);
  Node* get_parent_node();
  void set_visited(bool visit);
  bool get_visited();
  char get_node_char();

  std::map<char,Node*>::iterator it_begin();
  std::map<char,Node*>::iterator it_end();

};

std::string Node::node_string(){
  return node_str;
}

bool Node::is_word(){
  return is_complete_word;
}

void Node::set_is_word(bool isword){
  is_complete_word=isword;
}

bool Node::is_character(char ch){
  return charmap.find(ch)!=charmap.end();
}

void Node::map_add(char now, Node* node){
  charmap.insert(std::make_pair(now,node));
}

Node* Node::next_char_node(char now){
  return charmap[now];
}

void Node::set_failure_link(Node *fail){
  failure_link=fail;
}

Node* Node::get_failure_link(){
  return failure_link;
}

void Node::set_parent_node(Node *node){
  parent_node=node;
}

Node* Node::get_parent_node(){
  return parent_node;
}

void Node::set_visited(bool visit){
  visited=visit;
}

bool Node::get_visited(){
  return visited;
}

std::map<char,Node*>::iterator Node::it_begin(){
  return charmap.begin();
}

std::map<char,Node*>::iterator Node::it_end(){
  return charmap.end();
}

char Node::get_node_char(){
  return node_ch;
}
//end of Class node

//class Trie
class Trie{
private:
  Node *startnode;

public:
  Trie(){
    init();
  }
  void init(){
    startnode = new Node("",'\0',false);
    startnode->set_failure_link(startnode);
    startnode->set_parent_node(startnode);
    current = startnode;
  }
  void add_keyword(std::string pat);
  void make_failure_link();
  void node_init(){
    current=startnode;
  }
  bool is_start(){
    return current==startnode;
  }
  Node *current;

};

void Trie::add_keyword(std::string pat){
  int pat_cur = 0;
  int end = pat.size();
  current=startnode;

  while(pat_cur<end){
    //is the end of Pattern
    bool is_end=false;
    if(pat_cur == end-1) is_end = true;
    //if there isn't char Node, construct
    if(!current->is_character(pat[pat_cur])){
      Node *newnode = new Node(current->node_string(),pat[pat_cur],is_end);
      //add_new_character_node
      current->map_add(pat[pat_cur],newnode);
      //set parent
      current->next_char_node(pat[pat_cur])->set_parent_node(current);
      //current -> next
      current = current->next_char_node(pat[pat_cur]);
      std::cout << current->node_string() << std::endl;
    }
    //there is char Node, change current
    else{
      current = current->next_char_node(pat[pat_cur]);
      if(is_end) current->set_is_word(is_end);
    }
    pat_cur++;
  }

  current = startnode;
}

void Trie::make_failure_link(){
  std::deque < Node* > dq;
  std::map<char,Node*>::iterator it;
  dq.push_back(startnode);
  startnode->set_visited(true);

  //bfs
  while(!dq.empty()){
    Node* temp=dq.front();
    Node* par_fail=temp->get_parent_node()->get_failure_link();
    dq.pop_front();

    if(par_fail->is_character(temp->get_node_char()) && par_fail->next_char_node(temp->get_node_char()) != temp){
      temp->set_failure_link(par_fail->next_char_node(temp->get_node_char()));
      std::cout <<"fail_link : "<<temp->node_string() << " -> " <<temp->get_failure_link()->node_string() << std::endl;
    }
    else{
      temp->set_failure_link(par_fail->get_failure_link());
      std::cout <<"fail_link : "<<temp->node_string() << " -> " <<temp->get_failure_link()->node_string() << std::endl;
    }


    for(it=temp->it_begin(); it != temp->it_end() ; it++){
      Node* node= it->second;

      if(!node->get_visited()){
        std::cout <<"push "<< (*it).first << std::endl;
        dq.push_back(node);
        node->set_visited(true);
      }
    }
  }

  current = startnode;
}


class ahocorasick{
private:
  Trie tri;
  std::map<std::string, std::vector<int> > keyword_map;
  bool is_keyword;

public:
  ahocorasick(int cnt,...){
    is_keyword=false;
    tri.init();
    va_list pattern;

    va_start(pattern,cnt);

    for(int i=0; i<cnt; i++){
      std::string pat=va_arg(pattern,std::string);
      add_keyword(pat);
    }

    make_failure_link();
  }

  ahocorasick(){
    is_keyword=false;
    tri.init();
  }

  void add_keyword(std::string str){
    std::vector<int> index;
    keyword_map.insert(make_pair(str,index));
    tri.add_keyword(str);
  }

  void make_failure_link(){
    is_keyword=true;
    tri.make_failure_link();
  }

  void matching(std::string text);
  void ret_index_vector(std::string str,std::vector<int> &vec);

  void print_vec(std::string str){
    for(int i=0;i<keyword_map[str].size();i++){
      std::cout << str << " find : " << keyword_map[str][i] <<" ";
    }
    std::cout << std::endl;
  }
};

void ahocorasick::matching(std::string text){
  if(!is_keyword) return;

  int i=0;
  while(i<text.size()){
    if(tri.current->is_character(text[i])){
      tri.current = tri.current->next_char_node(text[i]);
      if(tri.current->is_word()){
        std::string tmp=tri.current->node_string();
        keyword_map[tmp].push_back(i+1-tmp.size());
        std::cout << "match " <<tmp<<" "<< i+1-tmp.size() << " " <<tmp.size() << std::endl;
      }
      i++;
    }
    else{
      bool isstart=tri.is_start();
      tri.current = tri.current->get_failure_link();
      if(isstart){
        i++;
      }
    }

    std::cout << i <<" "<< tri.current->node_string() << std::endl;
  }
}

void ahocorasick::ret_index_vector(std::string str,std::vector<int> &vec){
  vec=keyword_map[str];
}
