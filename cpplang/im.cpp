#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <queue>
#include <cstring>

/*
C++ 26분반 Term Project 
- KO-EN 한영타 변환기 (두벌식, 세벌식)
- 202412999 양현성

레퍼런스
https://blex.me/@baealex/%ED%95%9C%EA%B8%80-%EB%B6%84%EB%A6%AC-%EB%B3%91%ED%95%A9
https://intotherealworld.tistory.com/6
https://unluckyjung.github.io/cpp/2020/07/04/Use_Korean/
*/

enum KEYBOARD_TYPE {
   DUBEOLSIK,
   SEBEOLSIK_390,
   SEBEOLSIK_FINAL
};

enum ORDER {
   ORDER_RIGHT,
   ORDER_REVERSE
};

const int UNICODE_KOR_START = 0xAC00;

static char dcmap[] = {
   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', //9
   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', //8
   'z', 'x', 'c', 'v', 'b', 'n', 'm' //6
};

static std::string dvmap[] = {
   "ㅂ", "ㅈ", "ㄷ", "ㄱ", "ㅅ", "ㅛ", "ㅕ", "ㅑ", "ㅐ", "ㅔ",
   "ㅁ", "ㄴ", "ㅇ", "ㄹ", "ㅎ", "ㅗ", "ㅓ", "ㅏ", "ㅣ",
   "ㅋ", "ㅌ", "ㅊ", "ㅍ", "ㅠ", "ㅜ", "ㅡ"
};

static char sfcmap[] = {
   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
   'z', 'x', 'c', 'v', 'b', 'n', 'm',                 '/'
};

static std::string sfvmap[] = {
   "ㅎ", "ㅆ", "ㅂ", "ㅛ", "ㅠ", "ㅑ", "ㅖ", "ㅢ", "ㅜ", "ㅋ",
   "ㅅ", "ㄹ", "ㅕ", "ㅐ", "ㅓ", "ㄹ", "ㄷ", "ㅁ", "ㅊ", "ㅍ",
   "ㅇ", "ㄴ", "ㅣ", "ㅏ", "ㅡ", "ㄴ", "ㅇ", "ㄱ", "ㅈ", "ㅂ", "ㅌ",
   "ㅁ", "ㄱ", "ㅔ", "ㅗ", "ㅜ", "ㅅ", "ㅎ",                  "ㅗ"
};

static std::string s9vmap[] = {
   "ㅎ", "ㅆ", "ㅂ", "ㅛ", "ㅠ", "ㅑ", "ㅖ", "ㅢ", "ㅜ", "ㅋ",
   "ㅅ", "ㄹ", "ㅕ", "ㅐ", "ㅓ", "ㄹ", "ㄷ", "ㅁ", "ㅊ", "ㅍ",
   "ㅇ", "ㄴ", "ㅣ", "ㅏ", "ㅡ", "ㄴ", "ㅇ", "ㄱ", "ㅈ", "ㅂ", "ㅌ",
   "ㅁ", "ㄱ", "ㅔ", "ㅗ", "ㅜ", "ㅅ", "ㅎ",                  "ㅗ"
};

static std::string chosungMap[] = {
   "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ", 
   "ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
};

// "ㅘ", "ㅙ", "ㅚ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅢ" 
static std::string jungsungMap[] = {
   "ㅏ", "ㅐ", "ㅑ", "ㅒ", "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅗ", "ㅘ", 
   "ㅙ", "ㅚ", "ㅛ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ", "ㅣ"
};

// "ㄵ", "ㄶ", "ㄺ", "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅄ"
static std::string jongsungMap[] = {
   "", "ㄱ", "ㄲ", "ᆪ", "ㄴ", "ᆬ", "ᆭ", "ㄷ", "ㄹ", "ᆰ", "ᆱ", "ᆲ", 
   "ᆳ", "ᆴ", "ᆵ", "ᆶ", "ㅁ", "ㅂ", "ᆹ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅊ", 
   "ㅋ", "ㅌ", "ㅍ", "ㅎ"
};

template<typename T, typename U>
class KeyMap {
   typedef typename std::vector<T>::iterator Titerator;
   typedef typename std::vector<U>::iterator Uiterator;

private:
   std::vector<T> keymap;
   std::vector<U> valmap;

public:
   KeyMap()
   {}

   KeyMap(T* key, U* val, size_t size)
   { 
      this->keymap.insert(
         this->keymap.end(),
         key, (key + size)
      );

      this->valmap.insert(
         this->valmap.end(),
         val, (val + size)
      );
   }

   ~KeyMap() 
   { }

   void insert(T key, U val) {
      this->keymap.push_back(key);
      this->valmap.push_back(val);
   }

   U find(T key) const {
      for(size_t i = 0; i < this->keymap.size(); i++) {
         if(this->keymap.at(i) == key)
            return this->valmap.at(i);
      }

      throw new std::runtime_error("no item found");      
   }

   T reverse_find(U key) const {
      for(size_t i = 0; i < this->valmap.size(); i++) {
         if(this->valmap.at(i) == key)
            return this->keymap.at(i);
      }

      throw new std::runtime_error("no item found");
   }

   bool haskey(T key) {
      Titerator i;
      for(i = this->keymap.begin(); i != this->keymap.end(); i++) {
         if(*i == key)
            return true;
      }

      return false;
   }

   bool haskey(U key) {
      Uiterator i;
      for(i = this->valmap.begin(); i != this->valmap.end(); i++) {
         if(*i == key)
            return true;
      }

      return false;
   }

   U operator[] (T idx) const {
      return this->find(idx);
   }

   T operator[] (U idx) const {
      return this->reverse_find(idx);
   }
};

template<typename T>
class AutoIncreaseIndexMap {
   typedef typename std::map<T, int>::iterator TMiterator;
private:
   std::map<T, int> key;

public:
   AutoIncreaseIndexMap(T* data, size_t size) {
      for(int i = 0; i < (size / sizeof(data[i])); i++) {
         this->key.insert(std::pair<T, int>(data[i], i));
      }
   }

   void insert(T data) {
      TMiterator iter = --(this->key.end());
      int last_id = (iter->second)++;

      this->key.insert(std::pair<T, int>(data, last_id));
   }

   int get_idx(T key) const {
      return this->key.at(key);
   }
};

class KeyboardLayout {
protected:
   virtual std::string ConvertStroke(ORDER o, std::string c) {
      return "";
   }

public:
   KeyboardLayout() 
   { }

   virtual ~KeyboardLayout()
   { }

   virtual std::string ConvertFullString(ORDER o, std::string str) {
      return "";
   }
};

class Dubeolsik : public KeyboardLayout {
private:
   KeyMap<char, std::string> map;

protected:
   std::string ConvertStroke(ORDER o, std::string c) {
      if(c.length() > 1) 
         return this->ConvertFullString(o, c);
      else {
         switch (o)
         {
         case ORDER_RIGHT:
            if(!this->map.haskey(c[0]))
               return c;
            else
               return this->map[c[0]];
            break;
         
         case ORDER_REVERSE:
            if(!this->map.haskey(c))
               return c;
            else {
               std::string s;
               s += this->map[c];
               return s;
            }
            break;
         }
      } 
   }

public:
   Dubeolsik() :
      map(dcmap, dvmap, sizeof(dcmap))
   { }

   std::string ConvertFullString(ORDER o, std::string c) {
      std::string converted;
      std::string n;

      for(int i = 0; i < c.length(); i++) {
         n = c[i];
         converted += this->ConvertStroke(o, n);
      }

      return converted;
   }
};

class SebeolsikFinal : public KeyboardLayout {
private:
   KeyMap<char, std::string> map;

protected:
   std::string ConvertStroke(ORDER o, std::string c) {
      if(c.length() > 1) 
         return this->ConvertFullString(o, c);
      else {
         switch (o)
         {
         case ORDER_RIGHT:
            if(!this->map.haskey(c[0]))
               return c;
            else
               return this->map[c[0]];
            break;
         
         case ORDER_REVERSE:
            if(!this->map.haskey(c))
               return c;
            else {
               std::string s;
               s += this->map[c];
               return s;
            }
            break;
         }
      } 
   }

public:
   SebeolsikFinal() :
      map(sfcmap, sfvmap, sizeof(sfcmap))
   { }

   std::string ConvertFullString(ORDER o, std::string c) {
      std::string converted;
      std::string n;

      for(int i = 0; i < c.length(); i++) {
         n = c[i];
         converted += this->ConvertStroke(o, n);
      }

      return converted;
   }
};

class Sebeolsik390 : public KeyboardLayout {
private:
   KeyMap<char, std::string> map;

protected:
   std::string ConvertStroke(ORDER o, std::string c) {
      if(c.length() > 1) 
         return this->ConvertFullString(o, c);
      else {
         switch (o)
         {
         case ORDER_RIGHT:
            if(!this->map.haskey(c[0]))
               return c;
            else
               return this->map[c[0]];
            break;
         
         case ORDER_REVERSE:
            if(!this->map.haskey(c))
               return c;
            else {
               std::string s;
               s += this->map[c];
               return s;
            }
            break;
         }
      } 
   }

public:
   Sebeolsik390() :
      //temp
      map(sfcmap, s9vmap, sizeof(sfcmap))
   { }

   std::string ConvertFullString(ORDER o, std::string c) {
      std::string converted;
      std::string n;

      for(int i = 0; i < c.length(); i++) {
         n = c[i];
         converted += this->ConvertStroke(o, n);
      }

      return converted;
   }
};

AutoIncreaseIndexMap ChosungIdx(chosungMap, sizeof(chosungMap));
AutoIncreaseIndexMap JungsungIdx(jungsungMap, sizeof(jungsungMap));
AutoIncreaseIndexMap JongsungIdx(jongsungMap, sizeof(jongsungMap));

class Jamo {
private:
   std::string merged;
   std::string chosung, jungsung, jongsung;

public:
   Jamo(std::string n) : 
      merged(n)
   {}

   Jamo(std::string chosung, std::string jungsung, std::string jongsung) {
      //Index 기준: (초성 * 21 * 28) + (중성 * 28) + 종성
      int chosung_idx = ChosungIdx.get_idx(chosung);
      int jungsung_idx;
      try {
         jungsung_idx = JungsungIdx.get_idx(jungsung);
      } catch(std::exception e) {
         jungsung_idx = 0;
      }
      int jongsung_idx; 
      try {
         jongsung_idx = JongsungIdx.get_idx(jongsung);
      } catch(std::exception e) {
         jongsung_idx = 0;
      }

      int codepoint = ((chosung_idx * 21 * 28) + (jungsung_idx * 28) + jongsung_idx) + UNICODE_KOR_START;

      char buffer[4];
      buffer[0] = (char)(0xE0 | ((codepoint >> 12) & 0x0F));
      buffer[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
      buffer[2] = (char)(0x80 | (codepoint & 0x3F));
      buffer[3] = '\0';

      std::string result(buffer);
      this->merged = result;
   }

   std::string get_merged() {
      return this->merged;
   }
}; 

class JamoMerge {
   typedef typename std::string::iterator STiterator;
   typedef typename std::vector<Jamo>::iterator Jiterator;
private:
   std::deque<std::string> jamo_atoms;
   std::vector<Jamo> merged;

   int toUnicodeCode(std::string s) {
      const char* str = reinterpret_cast<const char *>(s.c_str());
      int charcode = 0;

      charcode = ((str[0] & 0x0F) << 12) |
                 ((str[1] & 0x3F) << 6) |
                 (str[2] & 0x3F);

      return charcode;
   }

   bool isJaum(std::string s) {
      int charcode = this->toUnicodeCode(s);

      return (
         (charcode >= 0x1100 && charcode <= 0x1112) ||
         (charcode >= 0x11A8 && charcode <= 0x11C2) ||
         (charcode >= 0x3131 && charcode <= 0x314E)
      );
   }

   bool isMoum(std::string s) {
      int charcode = this->toUnicodeCode(s);

      return (
         (charcode >= 0x1161 && charcode <= 0x1175) ||
         (charcode >= 0x314F && charcode <= 0x3163)
      );
   }

   bool isKOR(std::string s) {
      int charcode = this->toUnicodeCode(s);

      return (
         (charcode >= 0x1100 && charcode <= 0x11F9) ||
         (charcode >= 0x3131 && charcode <= 0x318E)
      );
   }

   std::string mergeJongsung(std::string n1, std::string n2) {
      //"ㄵ", "ㄶ", "ㄺ", "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅄ"
      if(n1 == "ㄴ" && n2 == "ㅈ") {
         return "ㄵ";
      }
      if(n1 == "ㄴ" && n2 == "ㅎ") {
         return "ㄶ";
      }
      if(n1 == "ㄹ" && n2 == "ㄱ") {
         return "ㄺ";
      }
      if(n1 == "ㄹ" && n2 == "ㅁ") {
         return "ㄻ";
      }
      if(n1 == "ㄹ" && n2 == "ㅂ") {
         return "ㄼ";
      }
      if(n1 == "ㄹ" && n2 == "ㅅ") {
         return "ㄽ";
      }
      if(n1 == "ㄹ" && n2 == "ㅌ") {
         return "ㄾ";
      }
      if(n1 == "ㄹ" && n2 == "ㅍ") {
         return "ㄿ";
      }if(n1 == "ㄹ" && n2 == "ㅎ") {
         return "ㅀ";
      }
      if(n1 == "ㅂ" && n2 == "ㅅ") {
         return "ㅄ";
      }

      return n1;
   }

   std::string mergeJungsung(std::string n1, std::string n2) {
      // "ㅘ", "ㅙ", "ㅚ", "ㅝ", "ㅞ", "ㅟ", "ㅢ" 
      if(n1 == "ㅗ" && n2 == "ㅏ") {
         return "ㅘ";
      }
      if(n1 == "ㅗ" && n2 == "ㅐ") {
         return "ㅙ";
      }
      if(n1 == "ㅗ" && n2 == "ㅣ") {
         return "ㅚ";
      }
      if(n1 == "ㅜ" && n2 == "ㅣ") {
         return "ㅟ";
      }
      if(n1 == "ㅜ" && n2 == "ㅔ") {
         return "ㅞ";
      }
      if(n1 == "ㅜ" && n2 == "ㅓ") {
         return "ㅝ";
      }
      if(n1 == "ㅡ" && n2 == "ㅣ") {
         return "ㅢ";
      }

      return n1;
   }

   //must used with exception handling
   /*
   첫번째 문자는 무조건 초성(자음) / 두번째 글자는 무조건 중설(모음)

   종성 결정
   - 세번째 글자가 자음인지 모음인지 판별

   -- 만일 모음일 경우
      종성과 합칠수 있는지 확인, 안된다면 넘어가기
   
   -- 만일 자음일 경우
       해당 글자 바로 다음 글자를 검사
       --- 만일 다음 글자가 모음일 경우
           종성은 없음
       --- 만일 다음 글자가 자음일 경우
           다다음 글자가 모음이 아닐 경우 현재 글자와 합치려고 시도
           안될 경우 패스
   */
   void doMerge() {
      while(this->jamo_atoms.size() > 0) {
         std::string chosung, jungsung, jongsung;

         std::string first = this->jamo_atoms.front();
         this->jamo_atoms.pop_front();

         if(!this->isKOR(first)) {
            this->merged.push_back(first);
            continue;
         }

         if(this->isJaum(first))
            chosung = first;

         std::string second = this->jamo_atoms.front();
         this->jamo_atoms.pop_front();

         if(this->isMoum(second))
            jungsung = second;

         std::string third = this->jamo_atoms.front();
         if(this->isJaum(third)) {
            std::string next = this->jamo_atoms[1];
            if(this->isMoum(next)) {
               jongsung = "";
            } else {
               jongsung = this->mergeJongsung(third, next);
               if(jongsung != third) {
                  this->jamo_atoms.pop_front();
                  this->jamo_atoms.pop_front();
               } else {
                  this->jamo_atoms.pop_front();
               }
            }
         } else if(this->isMoum(third)) {
            std::string next = this->jamo_atoms[1];
            std::string rmerged = this->mergeJungsung(third, next);

            if(rmerged == third) {
               this->jamo_atoms.pop_front();
            } else {
               jungsung = rmerged;
               this->jamo_atoms.pop_front();
               this->jamo_atoms.pop_front();
            }
         }

         Jamo r(chosung, jungsung, jongsung);
         this->merged.push_back(r);
      }
   }

public:
   JamoMerge(std::string strings)  
   {
      for(int i = 0; i < strings.size(); i+=3)
         this->jamo_atoms.push_back(strings.substr(i, 3));
   }

   std::string GetConverted() {
      std::string result;
      try {
         this->doMerge();
      } catch(std::exception e) { }

      Jiterator ij;
      for(ij = this->merged.begin(); ij != this->merged.end(); ij++)
         result += (*ij).get_merged();

      return result;
   }
};

class InputConverter {
private:
   ORDER current_convert_order;
   KEYBOARD_TYPE current_type;
   std::map<KEYBOARD_TYPE, KeyboardLayout*> keymaps;

public: 
   InputConverter() :
      current_convert_order(ORDER_RIGHT),
      current_type(DUBEOLSIK)
   { 
      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         DUBEOLSIK,
         new Dubeolsik()
      ));

      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         SEBEOLSIK_390,
         new Sebeolsik390()
      ));

      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         SEBEOLSIK_FINAL,
         new SebeolsikFinal()
      ));
   }

   InputConverter(ORDER o, KEYBOARD_TYPE k) :
      current_convert_order(o),
      current_type(k)
   {
      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         DUBEOLSIK,
         new Dubeolsik()
      ));

      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         SEBEOLSIK_390,
         new Sebeolsik390()
      ));

      this->keymaps.insert(std::pair<KEYBOARD_TYPE, KeyboardLayout*>(
         SEBEOLSIK_FINAL,
         new SebeolsikFinal()
      ));
   }

   void SetConvertOrder(ORDER o) {
      this->current_convert_order = o;
   }

   void SetKeyboardMap(KEYBOARD_TYPE k) {
      this->current_type = k;
   }

   KEYBOARD_TYPE GetCurrentKeyboardMap() {
      return this->current_type;
   }

   ORDER GetCurrentOrder() {
      return this->current_convert_order;
   }

   std::string Convert(std::string input) {
      KeyboardLayout* current_layout = this->keymaps.at(this->current_type);
      return current_layout->ConvertFullString(this->current_convert_order, input);
   }

   ~InputConverter() 
   {}
};

class PromptInterface {
private:
   InputConverter convertor;

   std::string getKeyTypeStr(KEYBOARD_TYPE t) {
      switch (t)
      {
      case DUBEOLSIK:
         return "DUBEOLSIK (두벌식)";
         break;

      case SEBEOLSIK_FINAL:
         return "SEBEOLSIK_FINAL (세벌식 최종)";
         break;

      case SEBEOLSIK_390:
         return "SEBEOLSIK_390 (세벌식 390)";
         break;      

      default:
         return "";
         break;
      }
   }

   std::string getKoConverted(std::string in) {
      std::string seq = this->convertor.Convert(in);
      JamoMerge komerge(seq);

      return komerge.GetConverted();
   }


   void convertPrompt() {
      std::cout << "========================================" << std::endl;
      std::cout << "CONVERTER | CURRENT MODE: " << this->getKeyTypeStr(this->convertor.GetCurrentKeyboardMap()) << std::endl;
      std::cout << "TO EXIT: type 'exit' to prompt" << std::endl;

      while(true) {
         std::string input;
         std::cout << "<- ";
         std::cin >> input;

         if(input == "exit")
            break;

         std::string convd;
         convd = this->getKoConverted(input);

         std::cout << "-> " << convd << std::endl << std::endl;
      }
      
      std::cout << std::endl << "========================================" << std::endl << std::endl;
   }

   void selectKeyboardTypePrompt() {
      int selection;
      bool run = true;

      std::cout << "========================================" << std::endl;
      std::cout << "SELECT KEYBOARD TYPE" << std::endl << std::endl;
      std::cout << "1. " << this->getKeyTypeStr(DUBEOLSIK) << std::endl;
      std::cout << "2. " << this->getKeyTypeStr(SEBEOLSIK_FINAL) << std::endl;
      std::cout << "3. " << this->getKeyTypeStr(SEBEOLSIK_390) << std::endl << std::endl;
      std::cout << "CURRENT: " << this->getKeyTypeStr(this->convertor.GetCurrentKeyboardMap()) << std::endl << std::endl;
      std::cout << "========================================" << std::endl;

      while(run) {
         std::cout << "SELECT: ";
         std::cin >> selection;

         switch (selection)
         {
         case 1:
            this->convertor.SetKeyboardMap(DUBEOLSIK);
            run = false;
            break;

         case 2:
            this->convertor.SetKeyboardMap(SEBEOLSIK_FINAL);
            run = false;
            break;

         case 3: 
            this->convertor.SetKeyboardMap(SEBEOLSIK_390);
            run = false;
            break;

         default:
            std::cout << "INVALID SELECTION!" << std::endl << std::endl;
            break;
         }
      }

      std::cout << "SELECTED: " << this->getKeyTypeStr(this->convertor.GetCurrentKeyboardMap()) << std::endl;
      std::cout << std::endl;
   }

   
public:
   PromptInterface() :
      convertor()
   { }

   void Menu() {
      int selection;
      bool run = true;

      while(run) {
         std::cout << "========================================" << std::endl;
         std::cout << "KEYBOARD INPUT CONVERTER" << std::endl << std::endl;
         std::cout << "1. Convert" << std::endl;
         std::cout << "2. Keymap Setting" << std::endl; 
         std::cout << "3. Exit" << std::endl << std::endl;
         std::cout << "========================================" << std::endl;

         std::cout << "SELECT: ";
         std::cin >> selection;

         switch (selection)
         {
         case 1:
            std::cout << std::endl;
            this->convertPrompt();
            break;

         case 2:
            std::cout << std::endl;
            this->selectKeyboardTypePrompt();
            break;

         case 3:
            run = false;
            break;

         default:
            std::cout << "INVALID SELECTION!" << std::endl << std::endl;
            break;
         }
      }
   }
};


int main() {
   PromptInterface ui;
   ui.Menu();

   return 0;
}