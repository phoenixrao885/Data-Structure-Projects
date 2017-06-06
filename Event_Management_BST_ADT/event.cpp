//event.cpp for Program# 4 by Tejas Menon, CS163, last edited on 5/28.
//Purpose: This file contains the structure implementations for the node, event and keyword used as fundamental
//         data types throughout the program
#include "header.h"

keyword::keyword() 
{
 word = NULL;
}

keyword::~keyword()
{
 if (word) delete[]word;
}

//adds a keyword
bool keyword::add(char keyword[])
{
 if (!keyword) return 0;
 word = new char[strlen(keyword)+1]; strcpy(word,keyword);
 return 1;
}

event::event()
{
 title = venue = desc = NULL;
 words = NULL;
 s_time = num_key = 0;
}

event::~event()
{
 if (title) delete[]title;
 if (venue) delete[]venue;
 if (desc) delete[]desc;
 if (words) delete[]words;
}

//initializes the members of an event if the arguments are valid
bool event::add(char name[],char place[],char info[],time_t start_time,int keywords,keyword*all_words)
{
 if (!name || !place || !info || !start_time || !keywords || !all_words) return 0;
 bool is_empty = false;
 for (int i=0;i<keywords;++i) { //if any of the keywords are NULL. (Rigorous testing required to weed out all possible invalidities as we are working with structures)
  if (!(all_words[i].word)) is_empty = true;
 }
 if (is_empty) return 0;
 
 title = new char[strlen(name)+1]; strcpy(title,name);
 venue = new char[strlen(place)+1]; strcpy(venue,place);
 desc = new char[strlen(info)+1]; strcpy(desc,info);
 s_time = start_time; 
 num_key = keywords;
 words = new keyword[keywords];
 for (int i=0;i<keywords;++i) {
  words[i].add(all_words[i].word);
 }
 return 1;
}

//deep copy an event
bool event::copy(event&to_copy)
{
 return (add(to_copy.title,to_copy.venue,to_copy.desc,to_copy.s_time,to_copy.num_key,to_copy.words));
}

//displays an event if valid
bool event::display()
{
 if (!(title && venue && desc && s_time)) return 0;
 if (title) cout << title << endl;
 if (venue) cout << venue << endl;
 if (desc) cout << desc << endl;
 if (s_time) cout << ctime(&s_time);
 cout << "Tags: ";
 for(int i=0;i<num_key;++i) {
  cout << words[i].word << ", ";
 }
 cout << "\n\n";
 return 1;
}
