#ifndef HELPERS_H
#define HELPERS_H

#include<iostream>
#include<vector>
using namespace std;

class helper{
public:
    static vector<string> split(string str, string token){
        vector<string>result;
        while(str.size()){
            int index = str.find(token);
            if(index!=string::npos){
                result.push_back(str.substr(0,index));
                str = str.substr(index+token.size());
                if(str.size()==0)result.push_back(str);
            }else{
                result.push_back(str);
                str = "";
            }
        }
        return result;
    }
};


#endif // HELPERS_H
