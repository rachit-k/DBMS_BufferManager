#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include <bits/stdc++.h>

using namespace std;

void shiftdata(int topage, int tooffset, int frompage, int fromoffset, FileHandler fh, int endpage)
{
	// cout<<"frompage "<<frompage<<" topage "<<topage<<endl;
	// cout<<"fromoffset "<<fromoffset<<" tooffset "<<tooffset<<endl;
    int intmin=INT_MIN;
	// topage--; frompage--;
    PageHandler toph = fh.PageAt(topage);
    char* toptr=toph.GetData();

    PageHandler fromph = fh.PageAt(frompage);
    char* fromptr = fromph.GetData();

    int j=tooffset*sizeof(int), i=fromoffset*sizeof(int);
    while(frompage<=endpage)
    {
        int temp;
        memcpy(&temp,&fromptr[i], sizeof(int));
        if(temp==INT_MIN)
            break;

        memcpy(&toptr[j], &temp, sizeof(int));
		// cout<<"copying "<<temp<<" from page "<<frompage<<" offset "<<i/sizeof(int)<<" to page "<<topage<<" offset "<<j/sizeof(int)<<endl;
        memcpy(&fromptr[i], &intmin, sizeof(int));
		j=j+sizeof(int);
		i=i+sizeof(int);

        if(j>=PAGE_CONTENT_SIZE && topage<endpage)
        {
			fh.MarkDirty(topage);
			fh.UnpinPage(topage);
			// fh.FlushPage(topage);
            topage++;
            toph = fh.PageAt(topage);
            toptr= toph.GetData();
            j=0;
        }
        if(i>=PAGE_CONTENT_SIZE && frompage<endpage)
        {
			fh.MarkDirty(frompage);
			fh.UnpinPage(frompage);
			// fh.FlushPage(frompage);
            frompage++;
            fromph = fh.PageAt(frompage);
            fromptr= fromph.GetData();
            i=0;
        }
    }
	fh.MarkDirty(topage);
	fh.UnpinPage(topage);	
	fh.MarkDirty(frompage);
	fh.UnpinPage(frompage);
	fh.FlushPages();

    // delete pages at the end starting next to "topage"
	for(int i=endpage; i>topage;i--)
	{
		fh.DisposePage(i);
	}
	int temp;
	toph = fh.LastPage();
	int temppage=toph.GetPageNum();
	toptr= toph.GetData();
	memcpy(&temp,&toptr[0], sizeof(int));
    if(temp==INT_MIN)
		fh.DisposePage(temppage);
	fh.UnpinPage(temppage);

	fh.FlushPages();
}

void del(int startpage, int endpage, int num, FileHandler fh)
{
    int page=startpage;
    int topage=startpage;
    int j=-1;
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
                if(j==-1)
                {
                    j=i;
                    topage=page;
                }
                continue;
			}
            if(j!=-1)
            {
                shiftdata(topage, j, page, i, fh, endpage);
                fh.UnpinPage(page);	
				fh.FlushPage(page);
                return;
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
	// cout << "File opened " << endl;
	ifstream fin;
	fin.open(argv[2]);
	string s;
	vector<int> nums;
	while(fin)
	{
		fin>>s;
		int num;
		fin>>num;
		nums.push_back(num);
	}
	PageHandler ph = fh.FirstPage();
	int startpage= ph.GetPageNum();
	fh.UnpinPage(startpage);
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);
	
	for(int i=0;i<nums.size();i++)
	{
		int num=nums[i];
		del(startpage, endpage, num, fh);
	}
	fm.CloseFile(fh);
}

