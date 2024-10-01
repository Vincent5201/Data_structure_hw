#include <iostream>
#include <string>
#include <stack>

using namespace std;

void parenthesize(string &s);
string in_posfix(string s);
string pos_prefix(string s);

int main(){
    string s;
    int i = 0;
    cin >> s ;
    //parenthesize(s);
    //s = in_posfix(s);
    s = pos_prefix(s);
    cout << s;
    return 0;
}

string in_posfix(string s){
    stack<string> number;
    stack<string> token;
    int i = 0;
    string tmp = "",ans = "";
    while(s[i]!='\0'){
        if(s[i] == ')'){           
            while(!number.empty()){
                tmp = number.top() + tmp;
                number.pop();
            }
            tmp += token.top();
            token.pop();
            ans += tmp;
            tmp = "";
        }else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){       
            token.push(s.substr(i,1));
        }else if(s[i]!='('){           
            number.push(s.substr(i,1));        
        }
        i++;  
    }
    
    return ans;
}

string pos_prefix(string s){
    stack<string> number;
    int i = 0;
    while(s[i]!='\0'){
        if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){       
            string tmp = "";
            tmp = number.top();
            number.pop();
            tmp = number.top() + tmp;
            number.pop();
            tmp = s[i] + tmp;
            number.push(tmp);
        }else{           
            number.push(s.substr(i,1));
        }
        i++;
    }
    return number.top();

}

void parenthesize(string &s){
    int i = 0;
    while(s[i]!='\0'){        
        if(s[i] == '*' || s[i] == '/'){
            int a = 1,z = 0;
            while(s[i+a]!='\0'){
                if(s[i+a] == '('){
                    z--;
                }else if(s[i+a] == ')'){
                    z++;
                }
                if(z >= 1){
                    break;
                }
                a++;
            }
        
            if(!(z == 1)){
                if(s[i+1]!='('){
                    s.insert(i+2,")");
                }else{
                    int l = 1,r = 0,n = 2;
                    while(1){
                        if(s[i+n] == '('){
                            l++;
                        }else if(s[i+n] == ')'){
                            r++;
                            if(l == r){
                                break;
                            }
                        }
                        n++;
                    }
                    s.insert(i+n,")");
                }
                if(s[i-1]!=')'){
                    s.insert(i-1,"(");
                }else{
                    int l = 0,r = 1,n = 1;
                    while(1){
                        if(s[i-n-1] == '('){
                            l++;
                            if(l == r){
                                break;
                            }
                        }else if(s[i-n-1] == ')'){
                            r++;
                        }
                        n++;
                    }
                    s.insert(i-n,"(");
                }
                i+=2;
            }else{
                i++;
            }          
        }else{
            i++;
        }
    }
    i = 0;
    while(s[i]!='\0'){
        if(s[i] == '+' || s[i] == '-'){
            int a = 1,z = 0;
            while(s[i+a]!='\0'){
                if(s[i+a] == '('){
                    z--;
                }else if(s[i+a] == ')'){
                    z++;
                }
                if(z >= 1){
                    break;
                }
                a++;
            }
            if(!(z == 1)){
                if(s[i+1]!='('){
                    s.insert(i+2,")");
                }else{
                    int l = 1,r = 0,n = 2;
                    while(1){
                        if(s[i+n] == '('){
                            l++;
                        }else if(s[i+n] == ')'){
                            r++;
                            if(l == r){
                                break;
                            }
                        }
                        n++;
                    }
                    s.insert(i+n,")");
                }
                if(s[i-1]!=')'){
                    s.insert(i-1,"(");
                }else{
                    int l = 0,r = 1,n = 1;
                    while(1){
                        if(s[i-n-1] == '('){
                            l++;
                            if(l == r){
                                break;
                            }
                        }else if(s[i-n-1] == ')'){
                            r++;
                        }
                        n++;
                    }
                    s.insert(i-n,"(");
                }
                i+=2;
            }else{
                i++;
            }
        }
        else{
            i++;
        }            
    }
}