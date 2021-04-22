#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>

using namespace std;

vector<int> ans_pages;
vector<int> offsets;
vector<pair<int, int> > search_results;
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
            search_results.push_back(make_pair(page,i));
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
                search_results.push_back(make_pair(page,i));
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
	// cout<<"here"<<endl;
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
		for(int i=data.size()-1;i>=0;i--)
		{
			if (data[i]==num) 
			{
				ans_pages.push_back(page);
				offsets.push_back(i);
                search_results.push_back(make_pair(page,i));
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
	// cout<<"startpage "<<startpage<<" endpage "<<endpage<<endl;
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
        search_results.push_back(make_pair(mid, offset));
		forwardsearch(mid, offset, num, endpage, fh);
	}
	return ret;
}