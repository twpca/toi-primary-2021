#include"line_parser.hh"
#include<algorithm>
#include<cstdio>
using namespace std;
using namespace tester3;

constexpr int minN = 1;
constexpr int maxN[] = {500, 20, 70, 70, 500};
constexpr int minC = 0;
constexpr int maxC[] = {2'000'000, 1, 1, 2'000'000, 2'000'000};

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
   auto cij_check = [subtask](int cij){
      return minC<=cij && cij<=maxC[subtask];
   };
   for(int i=0; i<n; ++i){
      auto ci = read_ints(n).value();
      if(!all_of(ci.cbegin(), ci.cend(), cij_check)){
         throw "bad c_{ij} for some i and j";
      }
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
