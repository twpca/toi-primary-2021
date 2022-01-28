#include"line_parser.hh"
#include<cstdio>
using namespace std;
using namespace tester3;

constexpr int minN = 1;
constexpr int maxN = 1'000;
constexpr int minM = 1;
constexpr int maxM[] = {1'000'000'000, 1'000, 1'000'000'000};
constexpr int minT = 0;
constexpr int maxT = 1'000'000'000;
constexpr int minS = 1;
constexpr int maxS = 1'000'000'000;
constexpr int minD = 0;
constexpr int maxD = 1'000'000'000;

int main(int argc, char **argv) try{
   Parser<int> parse_int;
   int subtask = -1;
   for(int i=1; i<argc; ++i){
      if(argv[i] == "--testcase"s){
         if(i++ == argc-1){
            throw "bad argv";
         }
         auto p = parse_int(argv[i]);
         if(!p || *p<0 || *p>=(int)(sizeof maxM/sizeof*maxM)){
            throw "bad argv";
         }
         subtask = *p;
      }else throw "bad argv";
   }
   if(subtask == -1){
      throw "bad argv";
   }
   SequenceParser<int> read_ints;
   auto nm = read_ints(2).value();
   int n = nm[0], m = nm[1];
   if(n<minN || n>maxN){
      throw "bad n";
   }
   if(m<minM || m>maxM[subtask]){
      throw "bad m";
   }
   auto t = read_ints(n-1).value();
   for(int i=0; i<n-1; ++i){
      if(t[i]<minT || t[i]>maxT){
         throw "bad t_i for some i";
      }
   }
   auto s = read_ints(n).value();
   for(int i=0; i<n; ++i){
      if(s[i]<minS || s[i]>maxS){
         throw "bad s_i for some i";
      }
   }
   auto d = read_ints(n).value();
   for(int i=0; i<n; ++i){
      if(d[i]<minD || d[i]>maxD){
         throw "bad d_i for some i";
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
