#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

struct WordBlock{
     string word;
     int lineNr;
};
 

int main()
{
     vector<WordBlock> WordStr;
     vector<string> splited;
     WordBlock TempWords;
     string temp, temp2, temp3 = "www.", temp4 = "https:", eil;
     int templine = 0;
     multimap<string, int> block;
     multimap<string, int>::iterator itr;
     set<string, greater<int> >::iterator itr2;
     set<string> s;
     ifstream open_f("WordFile.txt");
     while (open_f){ 
          if (!open_f.eof()) {
               getline(open_f, eil);
               splited.push_back(eil);
          }
          else break;
     }
     open_f.close(); 
     for(auto &el : splited){
          templine++;
          stringstream ss(el);

          while(ss >> temp) 
          {
               bool found = temp.find(temp4) != std::string::npos;
               bool found2 = temp.find(temp3) != std::string::npos;
               if (found || found2){
                    cout << "String found" << endl;
                    temp2 = temp;
                    cout << temp;
                    if(temp2 != ""){
                    TempWords.word = temp2;
                    TempWords.lineNr = templine;
                    WordStr.push_back(TempWords); 
               }
               }
               else{
                    temp2 = "";
                    for(auto &el2 : temp){                     
                         if ((el2 >= 'a' && el2 <= 'z') || (el2 >= 'A' && el2 <= 'Z')) {
                              temp2 = temp2 + el2;
                         }
                    }
                    if(temp2 != ""){
                         TempWords.word = temp2;
                         TempWords.lineNr = templine;
                         WordStr.push_back(TempWords); 
                    }
               }
     
          }
     }
     for(auto i:WordStr){
          block.insert(pair<string, int>(i.word, i.lineNr));
     }
     for (itr = block.begin(); itr != block.end(); ++itr) {
          s.insert(itr->first);
     }
     ofstream out_f("WordFile_edited.txt");
     for (itr2 = s.begin(); itr2 != s.end(); itr2++) {
          if(itr2 != s.begin() && block.count(*itr2) > 1){
               out_f << endl;
          }
          if(block.count(*itr2) > 1){
               out_f << setw(20) << left << *itr2 << right <<"Pasikartojo: " << right << setw(5) << block.count(*itr2) << setw(6) << "kart.";
          }
     }
     out_f << endl << "--------------------------------------------------------------------------------------------------------------------------";
     for (itr2 = s.begin(); itr2 != s.end(); itr2++){
          if(block.count(*itr2) > 1){
               if(itr2 != s.begin()){
               out_f << endl;
               }
               out_f << *itr2;
               for (itr = block.begin(); itr != block.end(); ++itr){
                    if(itr != block.begin() && itr -> first == *itr2){
                    out_f << "  ";
                    }
                    if (itr -> first == *itr2){
                         out_f << itr -> second;
                    }
               }
          }
     }
     out_f << endl << "--------------------------------------------------------------------------------------------------------------------------" << endl;
     for (itr2 = s.begin(); itr2 != s.end(); itr2++){
          temp = *itr2;
          if((temp.find(temp3) != std::string::npos) || (temp.find(temp4) != std::string::npos)){
               out_f << temp;
          }
     }
     out_f.close();

     return 0;
}