#include"line_parser.hh"
#include<unordered_set>
#include<cstdio>
using namespace std;
using namespace tester3;

constexpr int minN = 1;
constexpr int maxN[] = {1'000, 7, 1'000};
constexpr int minA = 1;
constexpr int maxA[] = {1'024, 7, 1'024};

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
   auto a = read_ints(n).value();
   unordered_set<int> ina(n);
   for(int i=0; i<n; ++i){
      if(a[i]<minA || a[i]>maxA[subtask]){
         throw "bad a_i for some i";
      }
      if(!ina.insert(a[i]).second){
         throw "a_i = a_j for some i != j";
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
