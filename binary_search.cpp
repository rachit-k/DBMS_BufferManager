#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>
#include "binary_search.h"
using namespace std;


int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler fh = fm.OpenFile(argv[1]);
	// cout << "File opened " << endl;
	ifstream fin;
	fin.open(argv[2]);
	// int num=stoi(argv[2]);
	string s;
	vector<int> nums;
	while(fin)
	{
		fin>>s;
		int num;
		fin>>num;
		nums.push_back(num);
	}

	FileHandler fh2=fm.CreateFile(argv[3]);	
	PageHandler ph2 = fh2.NewPage ();
	char *outptr = ph2.GetData ();
	int j=0;
	int curpage=0;

	PageHandler ph = fh.FirstPage();
	int startpage= ph.GetPageNum();
	fh.UnpinPage(startpage);	
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);
	
	for(int i=0;i<nums.size();i++)
	{
		int num=nums[i];
		bool ans=bsearch(startpage, endpage, num, fh);
		// char lpara='(', rpara=')', comma=',', endline= '\n';
		for(int i=0;i<ans_pages.size();i++)
		{
			memcpy(&outptr[j], &ans_pages[i], sizeof(int));
			j=j+sizeof(int);
			memcpy(&outptr[j], &offsets[i], sizeof(int));
			j=j+sizeof(int);
			// cout<<ans_pages[i]<<","<<offsets[i]<<endl;
			if(j>=PAGE_CONTENT_SIZE)
			{
				fh2.MarkDirty(curpage);
				fh2.UnpinPage(curpage);	
				fh2.FlushPage(curpage);
				ph2=fh2.NewPage();
				outptr=ph2.GetData();
				j=0;
				curpage++;
			}
		}
		int minus1=-1;
		memcpy(&outptr[j], &minus1, sizeof(int));
		j=j+sizeof(int);
		memcpy(&outptr[j], &minus1, sizeof(int));
		j=j+sizeof(int);
		// cout << "-1,-1"<<endl;
		if(j>=PAGE_CONTENT_SIZE && i!=nums.size()-1)
		{
			fh2.MarkDirty(curpage);
			fh2.UnpinPage(curpage);	
			fh2.FlushPage(curpage);
			ph2=fh2.NewPage();
			outptr=ph2.GetData();
			j=0;
			curpage++;
		}
		// memcpy(&outptr[(4+2*sizeof(int))*i], &lpara, sizeof(char));
		// memcpy(&outptr[(4+2*sizeof(int))*i + 1 + sizeof(int)], &comma, sizeof(char));
		// memcpy(&outptr[(4+2*sizeof(int))*i + 2 + 2*sizeof(int)], &rpara, sizeof(char));
		// memcpy(&outptr[(4+2*sizeof(int))*i + 3 + 2*sizeof(int)], &endline, sizeof(char));

		// for(int i=0;i<ans_pages.size();i++)
		// 	cout<<ans_pages[i]<<","<<offsets[i]<<endl;
		// cout << "-1,-1"<<endl;
		ans_pages.clear();
		offsets.clear();
	}
	while(j<PAGE_CONTENT_SIZE)
	{
		int intmin=INT_MIN;
		memcpy(&outptr[j], &intmin, sizeof(int));
		j=j+sizeof(int);
	}
	fh2.MarkDirty(curpage);
	fh2.UnpinPage(curpage);	
	// Close the file
	fm.CloseFile(fh);
	fm.CloseFile(fh2);
}

