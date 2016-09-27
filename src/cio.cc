#include <iostream>
#include <string>
#include <node.h>

namespace cio {

using v8::FunctionCallbackInfo;
using v8::Exception;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::String;
using v8::Value;

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Input(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  string str, type;
  double num;
  Local<String> jsType;
  if(args.Length() < 1){
    cin>>str;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
  } else {
    jsType = Local<String>::Cast(args[1]);
    type = string(*String::Utf8Value(jsType));
    cout<<type<<endl;
    if(type == "Number"){
      cin>>num;
      args.GetReturnValue().Set(Number::New(isolate, num));
    } else if(type == "String"){
      cin>>str;
      args.GetReturnValue().Set(String::NewFromUtf8(isolate, str.c_str()));
    }
  }
}

void Output(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "input", Input);
  NODE_SET_METHOD(exports, "output", Output);
}

NODE_MODULE(cio, init)

}  // namespace cio