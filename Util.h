#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

string extractFilename(const char* filename);
void quit();

bool PrimeTest(unsigned long long p);

inline unsigned long long Rand64(){
//	unsigned long long randnum;

	if(RAND_MAX==0x7fff){
//		randnum=((unsigned long long)rand()) | ((unsigned long long)rand() << 15) | ((unsigned long long)rand() << 30) | ((unsigned long long)rand() << 45) | (((unsigned long long)rand() & 0xf) << 60);
		return ((unsigned long long)rand()) | ((unsigned long long)rand() << 15) | ((unsigned long long)rand() << 30) | ((unsigned long long)rand() << 45) ;
	}else if(RAND_MAX==0x7fffffff){
//		randnum=((unsigned long long)rand()) | ((unsigned long long)rand() << 31) | (((unsigned long long)rand() & 0x3) << 62);
		return ((unsigned long long)rand()) | ((unsigned long long)rand() << 31);
	}

//	return randnum;
}

template<class T>
void VectorPreprocessing(vector<T>& v, T u){
	if(v.size()<2)
		return ;

	int p1, p2;
	
	sort(v.begin(), v.end());
	p1=0;
	p2=1;
	while(v[0]==u){
		v.erase(v.begin());
	}

	while(p2<v.size()){
		if(v[p2]==u || v[p1]==v[p2]){
			v.erase(v.begin()+p2);
			continue;
		}
		p1++;
		p2++;
	}
	
}

template<class T>
int IntersectionSize(const vector<T>& v1, const vector<T>& v2){
	int i=0, j=0;
	int count=0;

	while(i<v1.size()&&j<v2.size()){
		if(v1[i]==v2[j]){
			count++;
			i++;
			j++;
			continue;
		}
		if(v1[i]<v2[j]){
			i++;
			continue;
		}
		if(v1[i]>v2[j]){
			j++;
			continue;
		}
	}

	return count;
}


template<class T>
bool VectorEq(const vector<T>& v1, const vector<T>& v2){
	if(v1.size()!=v2.size())
		return false;

	for(int i=0; i<v1.size(); i++){
		if(v1[i]!=v2[i])
			return false;
	}

	return true;
}


class MySet{
	vector<int> setmap;
public:
	MySet(int size=0){
		setmap=vector<int> (size);
		for(int i=0; i<size; i++){
			setmap[i]=i;
		}
	}

	int SetKey(int element){
		if(element>=setmap.size()){
			cout << "SetKey: Input Parameter is too large." << endl;
			quit();
		}

		int tmp;

		if(element==setmap[element])
			return setmap[element];

		tmp=SetKey(setmap[element]);
		setmap[element]=tmp;

		return setmap[element];
	}

	bool IsKey(int s){
		if(s>=setmap.size()){
			cout << "IsKey: Input Parameter is too large." << endl;
			quit();
		}

		if(setmap[s]==s)
			return true;
		else
			return false;
	}

	void SetUnion(int s1key, int s2key){
		if(IsKey(s1key)==false || IsKey(s2key)==false){
			cout << "The parameter of SetUnion shouble be the key of sets" << endl;
			return ;
		}
		if(s1key<s2key)
			setmap[s2key]=s1key;
		else
			setmap[s1key]=s2key;
	}

	void Print(){
		for(int i=0; i<setmap.size(); i++){
			cout << i << ":" << setmap[i] << "\t" << endl;
		}
	}
};


template<class T>
bool IsIntersect(const vector<T>& v1, const vector<T>& v2){
        int i=0, j=0;

        while(i<v1.size()&&j<v2.size()){
                if(v1[i]==v2[j]){
			return true;
                }
                if(v1[i]<v2[j]){
                        i++;
                }
                if(v1[i]>v2[j]){
                        j++;
                }
        }

        return false;
}

template<class T1, class T2>
class PairCompare{
	bool flag;

public:
	PairCompare(bool in){
		flag=in;
	}
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2){
		if(flag)
			return p1.second < p2.second;
		else
			return p1.second > p2.second;
	}

};

template<class T1, class T2>
class PairComparePointer{
public:
	bool operator()(const pair<T1, T2>& p1, const pair<T1, T2>& p2){
		return *(p1.second) > *(p2.second);
	}
};

template<class T>
inline T MyMin(const T& left, const T& right){
	if(left<right)
		return left;
	else
		return right;
}


template<class T1, class T2>
class ReRank{
	const vector<T2>& value;
public:
	ReRank(vector<T2>& v): value(v){
	}

	bool operator()(const T1& left, const T1& right){
		return value[left] < value[right];
	}

};

#endif

