#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <functional>
#include <climits>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "Graph.h"
#include "Util.h"

using namespace std;

void usage(){
	cout << "Usage:\n"
		"ProReach [--help] <filename> [-i] [-k <k>] [-h <h>] [-mu <mu>] [-q <queryfilename>] [-in <input method>]\n"
		"Description:\n"
		"\t --help \t\t  print the help message\n"
		"\t -k \t\t  set the value of parameter k, default value is 2\n"
		"\t -h \t\t  set the value of parameter h, default value is 2\n"
		"\t -mu \t\t  set the value of parameter mu, default value is 100\n"
		"\t -i \t\t  index construction\n"
		"\t -q <queryfilename> set the query file\n"
		"\t -in <input method> set the input method, default value is 1\n"
	<< endl;

}


int main(int argc, char* argv[]){
	Graph g;
	ifstream input;
	string queryfilename;
	string filename;
	bool IndexConstruction=false;
	bool Query=false;
	bool tf=false, pwah8=false, ferrari=false;
	bool dag=false;
	int input_method=1;
	clock_t start, end;

	g.KEYNUM=g.HUGENODENUM=2;
	g.hugenode=100;

	if(argc==1){
		usage();
		exit(0);
	}

	int i=1;
	while(i<argc){
		if (strcmp("--help", argv[i]) == 0) {
                        usage();
                        exit(0);
                }
                if (strcmp("-k", argv[i]) == 0) {
                        i++;
                        g.KEYNUM = atoi(argv[i++]);
                }
                else if (strcmp("-h", argv[i]) == 0) {
                        i++;
                        g.HUGENODENUM = atoi(argv[i++]);
                }
                else if (strcmp("-mu", argv[i]) == 0) {
                        i++;
                        g.hugenode = atoi(argv[i++]);
                }
                else if (strcmp("-i", argv[i]) == 0) {
                        IndexConstruction = true;
                        i++;
                }
                else if (strcmp("-q", argv[i]) == 0) {
                        i++;
			Query = true;
			queryfilename=argv[i++];
                }
		else if (strcmp("-in", argv[i]) == 0) {
			i++;
                        input_method = atoi(argv[i++]);
			if(input_method!=1 && input_method!=2 && input_method!=3){
				cout << "Wrong input method" << endl;
				exit(0);
			}
                }
		else {
                        filename = argv[i++];
                }
	}

	string name;
	name=extractFilename(filename.c_str());
	g.setFilename(name);

	start=clock();
	input.open(filename.c_str());
	if(!input.is_open()){
		cout << "Fail to open the file." << endl;
		exit(0);
	}
	if(input_method==1)
		g.readGraph(input);
	else if(input_method==2)
		g.readGraph2(input);
	else if(input_method==3)
		g.readGraph3(input);
	input.close();
	cout << name << " readGraph is complete." << endl;
	end=clock();
	cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;


	double timesum=0;
	if(IndexConstruction){
                cout << "KEYNUM: " << g.KEYNUM << "\tHUGENODENUM: " << g.HUGENODENUM << "\thugenode: " << g.hugenode << endl;
                start=clock();
                g.ComputeLayerLabel();
                end=clock();
                cout << name << " ComputeLayer is complete." << endl;
                cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
                timesum+=(double)(end-start)/CLOCKS_PER_SEC;

                int count1=0;

                start=clock();
                g.ComputeHugeNodeList();
                end=clock();
                cout << name << " ComputeHugeNodeList is complete." << endl;
                cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
                timesum+=(double)(end-start)/CLOCKS_PER_SEC;

                if(g.HUGENODENUM!=0){
                        for(int i=0; i<g.vsize; i++){
                                count1+=g.HugeNodeList[i].size();
                        }
                }
                cout << "Number of HugeNode is " << count1 << endl;

                double timeprolabel=0;
                start=clock();
                g.InitialProLabel();
                end=clock();
                cout << name << " InitialProLabel is complete." << endl;
                cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
                timesum+=(double)(end-start)/CLOCKS_PER_SEC;
                timeprolabel+=(double)(end-start)/CLOCKS_PER_SEC;


                start=clock();
                g.ComputeProLabelIn();
                end=clock();
                cout << name << " ComputeProLabelIn is complete." << endl;
                cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
                timesum+=(double)(end-start)/CLOCKS_PER_SEC;
                timeprolabel+=(double)(end-start)/CLOCKS_PER_SEC;

                start=clock();
                g.ComputeProLabelOut();
                end=clock();
                cout << name << " ComputeProLabelOut is complete." << endl;
                cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
                timesum+=(double)(end-start)/CLOCKS_PER_SEC;
                timeprolabel+=(double)(end-start)/CLOCKS_PER_SEC;

                int count2=0;
                for(int i=0; i<g.vsize; i++){
                        count2+=g.ProLabelOut[i].size();
                        count2+=g.ProLabelIn[i].size();
                }
                
                cout << "Number of ProLabel is " << count2 << '(' << (double)count2*4/(1024*1024) << " MB)" << endl;
                cout << "Number of index item: " << count1+count2+2*g.vsize << endl;
                cout << "Constructing ProLabel Time: " << timeprolabel << endl;
                cout << "Total Time Used: " << timesum << endl;
                cout << "Total Index Size(MB): " << (double)4*(count1+count2+g.vsize)/(1024*1024) << endl;
                g.PrintIndex((name+".index").c_str());

	}

	if(Query){
		g.IndexQueryTest((name+".index").c_str(), queryfilename);
	}

	cout << endl << endl;
}

