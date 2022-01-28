#include"line_parser.hh"
#include<cstdio>
using namespace std;
using namespace tester3;

constexpr int minN = 2;
constexpr int maxN[] = {50'000, 500, 50'000, 50'000, 50'000};
constexpr int minQ = 1;
constexpr int maxQ = 200'000;
constexpr int minW = 1;
constexpr int maxW = 1'000;
constexpr int minP = 1;
constexpr int maxP[] = {6, 6, 1, 6, 6};
constexpr int minH = 0;
constexpr int maxH = 23;
constexpr int minM = 0;
constexpr int maxM = 59;

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
   auto nq = read_ints(2).value();
   int n = nq[0], q = nq[1];
   if(n<minN || n>maxN[subtask]){
      throw "bad n";
   }
   if(q<minQ || q>maxQ){
      throw "bad q";
   }
   vector<int> djs(n, -1);
   auto find = [&djs](int i){
      int r = i;
      while(djs[r] != -1) r = djs[r];
      while(i != r){
         int j = djs[i];
         djs[i] = r;
         i = j;
      }
      return r;
   };
   for(int i=1; i<=n-1; ++i){
      int const minU = subtask==3? i: 1;
      int const maxU = subtask==3? i: n;
      int const minV = subtask==3? i+1: 1;
      int const maxV = subtask==3? i+1: n;
      auto e = read_ints(6).value();
      int u = e[0], v = e[1], w = e[2], a = e[3], b = e[4], p = e[5];
      if(u<minU || u>maxU){
         throw "bad u_i for some i";
      }
      if(v<minV || v>maxV){
         throw "bad v_i for some i";
      }
      --u; --v;
      if(find(u) == find(v)){
         throw "not a tree";
      }
      djs[find(v)] = find(u);
      if(w<minW || w>maxW){
         throw "bad w_i for some i";
      }
      if(p<minP || p>maxP[subtask]){
         throw "bad p_i for some i";
      }
      if(a<0 || a>p-1){
         throw "bad a_i for some i";
      }
      if(b<0 || b>p-1){
         throw "bad b_i for some i";
      }
   }
   while(q-- > 0){
      auto hmst = read_ints(4).value();
      int h = hmst[0], m = hmst[1], s = hmst[2], t = hmst[3];
      if(h<minH || h>maxH){
         throw "bad h_i for some i";
      }
      if(m<minM || m>maxM){
         throw "bad m_i for some i";
      }
      if(s<1 || s>n){
         throw "bad s_i for some i";
      }
      if(t<1 || t>n || t==s){
         throw "bad t_i for some i";
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
