#include"line_parser.hh"
#include<algorithm>
#include<unordered_set>
#include<cstdio>
using namespace std;
using namespace tester3;

constexpr int minN = 1;
constexpr int maxN[] = {200'000, 10, 100, 200'000};
constexpr int minA = 0;

int main(int argc, char **argv) try{
   Parser<int> parse_int;
   int subtask = -1;
   for(int i=1; i<argc; ++i){
      if(argv[i] == "--testcase"s){
         if(i++ == argc-1){
            throw "bad argv";
         }
         auto p = parse_int(argv[i]);
         if(!p || *p<0 || *p>=(int)(sizeof maxN/sizeof*maxN)){
            throw "bad argv";
         }
         subtask = *p;
      }else throw "bad argv";
   }
   if(subtask == -1){
      throw "bad argv";
   }
   SequenceParser<int> read_ints;
   int n = read_ints(1).value()[0];
   if(n<minN || n>maxN[subtask]){
      throw "bad n";
   }
   auto good_ai = [maxA=subtask==1? n-1: 1'000'000'000](int ai){
      return minA<=ai && ai<=maxA;
   };
   auto a = read_ints(n).value();
   if(!all_of(a.cbegin(), a.cend(), good_ai)){
      throw "bad a";
   }
   auto b = read_ints(n).value();
   if(!all_of(b.cbegin(), b.cend(), good_ai)){
      throw "bad b";
   }
   unordered_set<int> sa(a.cbegin(), a.cend()), sb(b.cbegin(), b.cend());
   if((int)sa.size()!=n || sa!=sb){
      throw "|{a_i}| != n or {a_i} != {b_i}";
   }
   if(!read_line().empty()){
      throw "bad format";
   }
}catch(bad_optional_access const&){
   puts("bad format");
   return 1;
}catch(char const *mesg){
   puts(mesg);
   return 1;
}
