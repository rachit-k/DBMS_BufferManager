#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>

using namespace std;

vector<int> ans_pages;
vector<int> offsets;

void lsearch(int startpage, int endpage, int num, FileHandler fh)
{
    int page=startpage;
	while(page<=endpage)
	{
		PageHandler ph = fh.PageAt(page);
		vector<int> data;
		char* ptr=ph.GetData();
		for(int i=0;i<PAGE_CONTENT_SIZE/sizeof(int); i++)
		{
			if(ptr==NULL)
				break;
			int temp;
			memcpy(&temp, &ptr[i*sizeof(int)], sizeof(int));
			if(temp==INT_MIN)
				break;
			data.push_back(temp);
		}
		for(int i=0;i<data.size();i++)
		{
			if (data[i]==num) 
			{
				ans_pages.push_back(page);
				offsets.push_back(i);
			}
		}
		fh.UnpinPage(page);	
		fh.FlushPage(page);	
		page++;
	}
}

int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler fh = fm.OpenFile(argv[1]);
	cout << "File opened " << endl;
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
	fh.FlushPage(startpage);
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);
	fh.FlushPage(endpage);

	for(int i=0;i<nums.size();i++)
	{
		int num=nums[i];
		lsearch(startpage, endpage, num, fh);

		for(int i=0;i<ans_pages.size();i++)
		{
			memcpy(&outptr[j], &ans_pages[i], sizeof(int));
			j=j+sizeof(int);
			memcpy(&outptr[j], &offsets[i], sizeof(int));
			j=j+sizeof(int);
			cout<<ans_pages[i]<<","<<offsets[i]<<endl;
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
		cout << "-1,-1"<<endl;
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
	
	fm.CloseFile(fh);
	fm.CloseFile(fh2);
}

