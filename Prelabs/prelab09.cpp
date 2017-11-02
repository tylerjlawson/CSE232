// For the sake of this example, let's assume I got all the includes right!
struct MyStruct{
  string s_;
  map<string,long> m_;

  MyStruct()=default;
  MyStruct(string s, initializer_list<pair<const string,long>> m) :
           s_(s), m_(m) {} ;
  bool   method1(string s, long l); 
  long   method2(string s, long l);
  double method3();
  string method4();
  string method5();
};

bool MyStruct::method1(string s, long l){
  auto result = m_.insert(make_pair(s,l) );      // Line 1, type result?
  return result.second;
}

long MyStruct::method2(string s, long l){
  if (m_.count(s) == 0)
    return l;
  else
    return m_[s];
}

double MyStruct::method3(){
    double result = 0;
    for(auto element : m_)                     // Line 2, type element?
        result += element.second;
    return result/m_.size();
}

string MyStruct::method4(){
    string s;
    long l=0;
    for (auto element : m_){
        if (element.second > l){
            s = element.first;
            l = element.second;
        }
    }
    return s;
}

string MyStruct::method5(){
   ostringstream oss;
   oss << s_ << ": ";
   for (auto element : m_)
     oss << element.first << "-" << element.second << ", ";
   string s = oss.str();
   return s.substr(0, s.size() - 2);
}

int main () {
   cout << boolalpha;
   MyStruct fc ("fred", { {"b", 2}, {"c", 3}, {"a", 1} } );
   cout << fc.method1("d", 4) << endl;  // Line 3
   cout << fc.method1("c", 4) << endl;  // Line 4

   cout << fc.method2("e", 5) << endl;  // Line 5
   cout << fc.method2("d", 5) << endl;  // Line 6

   cout << fc.method3() << endl;        // Line 7
   cout << fc.method4() << endl;        // Line 8
   cout << fc.method5() << endl;        // Line 9
}