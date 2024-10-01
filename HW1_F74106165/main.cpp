#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

int charToInt(char a[],int x,int y);
void trans1(int **in,int **out,int x,int y);
void trans2(int **in,int **out,int s,int y);

int main() {
	//tool to record time
	LARGE_INTEGER START1,END1,START2,END2;
	LARGE_INTEGER nFreq;
	
	//input
	ifstream ifs;
	char input[10000];
	for(int i = 0;i<10000;i++){
		input[i] = -1;
	}
	ifs.open("test1_testing_data.in");    
    ifs.read(input, sizeof(input));
    ifs.close();	

	//method1 start count time
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&START1);
	
    //check size
	int x,y,n = 0,m = 0,p,q,s = 0;
	while(input[m]!=' '){
		m++;
	}
	p = x = charToInt(input,n,m-1);
	m++;
	n = m;
	while(input[m]!='\n'){
		m++;
	}
	q = y = charToInt(input,n,m-1);
	m++;
	n = m;
	//make matrix
	int **input1;
	int **output1;
	input1 = (int**)malloc(p*sizeof(int*));
	output1 = (int**)malloc(q*sizeof(int*));
	for(int i=0;i<p;i++){
		input1[i] = (int*)malloc(sizeof(int)*q);
	}
	for(int i=0;i<q;i++){
		output1[i] = (int*)malloc(sizeof(int)*p);
	}
	for(int i=0;i<q;i++){
    	for(int j=0;j<p;j++){
    		output1[i][j] = 0;
		}
	}
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			input1[i][j] = 0;
		}
	}
	while(true){
		while(input[m]!=' '){
			m++;
		}
		x = charToInt(input,n,m-1);
		m++;
		n = m;
		while(input[m]!=' '){
			m++;
		}
		y = charToInt(input,n,m-1);
		m++;
		n = m;
		while(input[m]!='\n'){
			m++;
		}
		input1[x][y] = charToInt(input,n,m-1);
		m++;
		n = m;
		s++;
		if(input[m] == -1 || input[m] == '\0'){
			break;
		}
	}
	
	//transpose matrix
	trans1(input1,output1,p,q);
	QueryPerformanceCounter(&END1);	
	//method1 end=====================================================================
	
	
	//method2 start count time
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&START2);
	s = n = m = 0;
	
	//check size
	while(true){
		while(input[m]!='\n'){
			m++;
		}
		m++;
		n = m;
		s++;
		if(input[m] == -1|| input[m] == '\0'){
			break;
		}
	}
	
	//make sparse matrix
	int **input2;
	int **output2;
	input2 = (int**)malloc(s*sizeof(int*));
	output2 = (int**)malloc(s*sizeof(int*));
	for(int i=0;i<s;i++){
		input2[i] = (int*)malloc(sizeof(int)*3);
		output2[i] = (int*)malloc(sizeof(int)*3);
	}
	for(int i=0;i<s;i++){
		for(int j=0;j<3;j++){
			output2[i][j] = 0;
		}
	}
	s = n = m = 0;
	while(input[n]!='\n'){
		n++;
	}
	n++;
	m = n;
	while(true){
		while(input[m]!=' '){
			m++;
		}
		input2[s][0] = charToInt(input,n,m-1);
		m++;
		n = m;
		while(input[m]!=' '){
			m++;
		}
		input2[s][1] = charToInt(input,n,m-1);
		m++;
		n = m;
		while(input[m]!='\n'){
			m++;
		}
		input2[s][2] = charToInt(input,n,m-1);
		m++;
		n = m;
		s++;
		if(input[m] == -1|| input[m] == '\0'){
			break;
		}
	}
	
	//transpose sparse matrix
    trans2(input2,output2,s,q);
	QueryPerformanceCounter(&END2);
    //method2 end====================================
    
	//console output
    for(int i=0;i<q;i++){
    	for(int j=0;j<p;j++){
    		cout<<output1[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<s;i++){
    	for(int j=0;j<3;j++){
    		cout<<output2[i][j]<<" ";
		}
		cout<<endl;
	}
  

	//file output
	ofstream ofs;
    ofs.open("p1.out.txt");
    for(int i=0;i<s;i++){
    	ofs<<"("<<input2[i][0]<<", "<<input2[i][1]<<", "<<input2[i][2]<<") ";
    	ofs<<"becomes ";
    	ofs<<"("<<input2[i][1]<<", "<<input2[i][0]<<", "<<input2[i][2]<<") ";
		ofs<<"in the transpose\n";
	}
	ofs<<(double)(END1.QuadPart - START1.QuadPart) / (double)nFreq.QuadPart<<"\n";
	ofs<<(double)(END2.QuadPart - START2.QuadPart) / (double)nFreq.QuadPart<<"\n";
    ofs.close();
    
    
	return 0;
}
	//transpose matrix
void trans1(int **in,int **out,int x,int y){
	int **tmp = (int**)malloc(y*(sizeof(int*)));
	for(int i=0;i<y;i++){
		tmp[i] = (int*)malloc(sizeof(int)*x);
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			tmp[j][i] = in[i][j];
		}
	}
	
	for(int j=0;j<y;j++){
		out[j] = tmp[j];
	}
	return;
}
	//fast transpose sparse matrix
void trans2(int **in,int **out,int s,int y){
	int rowSize[y] = {0};
	int rowStart[y];

	for(int i=0;i<y;i++){
		int c = 0;
		for(int j=0;j<s;j++){
			if(in[j][1] == i){
				c++;
			}
		}
		rowSize[i] = c;
	}
	rowStart[0] = 0;
	for(int i=1;i<y;i++){
		rowStart[i] = rowStart[i-1]+rowSize[i-1];
	}
	int t = 0;
	for(int i=0;i<s;i++){
		t = in[i][1];
		out[rowStart[t]][1] = in[i][0];	
		out[rowStart[t]][0] = in[i][1];	
		out[rowStart[t]][2] = in[i][2];	
		rowStart[t]++;
	}
	return;
}
	//change char array to int
int charToInt(char a[],int x,int y){
	int t = 1,ans = 0;	
	while(y>=x){
		ans+=((a[y]-48)*t);
		y--;
		t*=10;
	}
	return ans;
}




