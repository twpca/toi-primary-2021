#ifndef TESTER3_LINE_PARSER_HH
#define TESTER3_LINE_PARSER_HH

#include<limits>
#include<optional>
#include<string>
#include<type_traits>
#include<vector>
#include<cctype>
#include<cstdio>

namespace tester3{
inline std::string read_line(std::FILE *fin = stdin){
   std::string s;
   for(int c; (c = std::fgetc(fin)) != EOF; ){
      s += (char)c;
      if(c == '\n') break;
   }
   return s;
}
inline std::vector<std::string> string_split(std::string const &s, std::string const &delimiter = " "){
   if(s.empty()){
      return {};
   }
   std::vector<std::string> res;
   std::string::size_type b = 0, e;
   for(; (e = s.find(delimiter, b)) != std::string::npos; b = e + delimiter.size()){
      res.emplace_back(s.substr(b, e-b));
   }
   res.emplace_back(s.substr(b));
   return res;
}
template<typename T> struct Parser{
   std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char>, std::optional<T>> operator()(std::string const &s) const{
      constexpr T MIN = std::numeric_limits<T>::min(), MAX = std::numeric_limits<T>::max();
      if(s.empty()) return {};
      if(s.size()==1 && s[0]=='0') return 0;
      bool neg = s[0]=='-';
      if(neg && s.size()==1) return {};
      T res = 0;
      for(std::string::size_type i=neg; i<s.size(); ++i){
         if(!std::isdigit(s[i]) ||
            !res && s[i]=='0' ||
            neg && (res<MIN/10 || res==MIN/10 && -(s[i]-'0')<MIN%10) ||
            !neg && (res>MAX/10 || res==MAX/10 && s[i]-'0'>MAX%10)){
            return {};
         }
         if(neg){
            res = 10*res - (s[i]-'0');
         }else res = 10*res + (s[i]-'0');
      }
      return res;
   }
};
template<typename T> struct SequenceParser{
   std::optional<std::vector<T>> operator()(size_t n, std::FILE *fin = stdin) const{
      std::string line = read_line(fin);
      if(line.empty() || line.back()!='\n'){
         return {};
      }
      line.pop_back();
      Parser<T> parse;
      std::vector<T> res;
      res.reserve(n);
      for(auto const &w: string_split(line)){
         std::optional<int> p;
         if(res.size()==n || !(p = parse(w))){
            return {};
         }
         res.push_back(*p);
      }
      if(res.size() < n){
         return {};
      }
      return res;
   }
};
}

#endif
