#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>

using namespace std;

vector<int> ans_pages;
vector<int> offsets;

void forwardsearch(int page, int offset, int num, int endpage, FileHandler fh)
{
	PageHandler ph = fh.PageAt(page);
	vector<int> data;
	char* ptrToData=ph.GetData();
	for(int i=0;i<PAGE_CONTENT_SIZE/sizeof(int); i++)
	{
		if(ptrToData==NULL)
			break;
		int temp;
		memcpy(&temp, &ptrToData[i*sizeof(int)], sizeof(int));
		if(temp==INT_MIN)
			break;
		data.push_back(temp);
	}
	for(int i=offset+1;i<data.size();i++)
	{
		if (data[i]==num) 
		{
			ans_pages.push_back(page);
			offsets.push_back(i);
		}
		else
			return;
	}
	fh.UnpinPage(page);
	page++;

	while(page<=endpage)
	{
		ph = fh.PageAt(page);
		vector<int> data2;
		char* ptr=ph.GetData();
		for(int i=0;i<PAGE_CONTENT_SIZE/sizeof(int); i++)
		{
			if(ptr==NULL)
				break;
			int temp;
			memcpy(&temp, &ptr[i*sizeof(int)], sizeof(int));
			if(temp==INT_MIN)
				break;
			data2.push_back(temp);
		}
		for(int i=0;i<data2.size();i++)
		{
			if (data2[i]==num) 
			{
				ans_pages.push_back(page);
				offsets.push_back(i);
			}
			else
				return;
		}
		fh.UnpinPage(page);		
		page++;
	}
}

void backwardsearch(int page, int num, int startpage, FileHandler fh)
{
	while(page>=startpage)
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
		for(int i=data.size();i>=0;i--)
		{
			if (data[i]==num) 
			{
				ans_pages.push_back(page);
				offsets.push_back(i);
			}
			else
				return;
		}
		fh.UnpinPage(page);		
		page++;
	}
}

bool bsearch(int startpage, int endpage, int num, FileHandler fh)
{
	bool ret=false;
	int offset, mid;
	cout<<"startpage "<<startpage<<" endpage "<<endpage<<endl;
	// while(startpage <= endpage && !ret)
	while(true)
	{
		if(startpage > endpage)
		{
			break;
		}
		int midpage=startpage+(endpage-startpage)/2;
		PageHandler ph = fh.PageAt(midpage);
		char* ptrToData=ph.GetData();
		vector<int> data; //read from page using vector?

		for(int i=0;i<PAGE_CONTENT_SIZE/sizeof(int); i++)
		{
			if(ptrToData==NULL)
				break;
			// int *ptr=(int*)ptrToData;
			int temp;
			memcpy(&temp, &ptrToData[i*sizeof(int)], sizeof(int));
			if(temp==INT_MIN)
				break;
			data.push_back(temp);
		}
		// cout<<"page  no"<<midpage<<endl;
		bool pageFound=false;

		//bsearch
		if(num>=data[0] && num <= data[data.size()-1])
			pageFound=true;
		else if(num>data[data.size()-1])
			startpage=midpage+1;
		else
			endpage=midpage-1;

		if(pageFound)
		{
			mid=midpage;
			for (int i=0; i<data.size(); i++) 
			{
				if (data[i]==num) 
				{
					offset = i;
					ret = true;
					break;
				}
			}
			break;
		}
		fh.UnpinPage(midpage);		
	}
	if(ret)
	{
		if(offset==0)
			backwardsearch(mid-1, num, startpage, fh);
		ans_pages.push_back(mid);
		offsets.push_back(offset);
		forwardsearch(mid, offset, num, endpage, fh);
	}
	return ret;
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
		int j=0;
		for(int i=0;i<ans_pages.size();i++)
		{
			memcpy(&outptr[j], &ans_pages[i], sizeof(int));
			j=j+sizeof(int);
			memcpy(&outptr[j], &offsets[i], sizeof(int));
			j=j+sizeof(int);
			cout<<ans_pages[i]<<","<<offsets[i]<<endl;
			if(j>=PAGE_CONTENT_SIZE)
			{
				ph2=fh2.NewPage();
				outptr=ph2.GetData();
				j=0;
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
			ph2=fh2.NewPage();
			outptr=ph2.GetData();
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
	// Close the file
	fm.CloseFile(fh);
	fm.CloseFile(fh2);
}

