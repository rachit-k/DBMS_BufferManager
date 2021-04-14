#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include "constants.h"
#include <bits/stdc++.h>

using namespace std;

bool bsearch(int startpage, int endpage, int *mid, int *offset, int num, FileHandler fh)
{
	bool ret=false;
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
			int *ptr=(int*)ptrToData;
			// memcpy(&temp, &ptrToData[i*sizeof(int)], sizeof(int));
			data.push_back(ptr[i]);
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
			*mid=midpage;
			for (int i=0; i <data.size(); i++) 
			{
				if (data[i]==num) 
				{
					*offset = i;
					ret = true;
					break;
				}
			}
			break;
		}
		fh.UnpinPage(midpage);		
	}
	return ret;
}


int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler fh = fm.OpenFile(argv[1]);
	cout << "File opened " << endl;
	int num=stoi(argv[2]);

	// Create a new page
	PageHandler ph = fh.FirstPage();
	int startpage= ph.GetPageNum();
	fh.UnpinPage(startpage);
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);
	
	int mid, offset; //change to vectors
	cout<<"entering"<<endl;
	bool ans=bsearch(startpage, endpage, &mid, &offset, num, fh);

	if(ans){
		cout << (mid+1)<<","<<(offset+1)<<endl;
	}
	cout << "-1,-1"<<endl;
	// Close the file
	fm.CloseFile(fh);
}

// int main(int argc, const char* argv[]) {
// 	FileManager fm;
// 	int i=0, pageno=0;
// 	// Create a brand new file
// 	while(true)
// 	{
// 		cout<<"entry"<<endl;
// 		FileHandler fh = fm.OpenFile(argv[2]);
// 		PageHandler ph = fh.PageAt(pageno);
// 		char* ptrToNum=ph.GetData();
// 		int num;
// 		if(8*i+11<=PAGE_CONTENT_SIZE)
// 		{
// 			memcpy (&num, &ptrToNum[8*i+7], sizeof(int));
// 			i++;
// 		}
// 		else
// 		{
// 			i=0;
// 			pageno++;
// 			ph=fh.LastPage();
// 			if(ph.GetPageNum()==pageno)
// 				break;
// 			memcpy (&num, &ptrToNum[8*i+7], sizeof(int));
// 		}
// 		ph=fh.LastPage();
// 		if(ph.GetPageNum()==pageno)
// 			break;
// 		fm.CloseFile(fh);

// 		fh = fm.OpenFile(argv[1]);
// 		cout << "File opened " << endl;
		
// 		// Create a new page
// 		ph = fh.FirstPage();
// 		int startpage= ph.GetPageNum();
// 		fh.UnpinPage(startpage);
// 		ph = fh.LastPage();
// 		int endpage= ph.GetPageNum();
// 		fh.UnpinPage(endpage);
		
// 		int mid, offset; //change to vectors
// 		cout<<"entering"<<endl;
// 		bool ans=bsearch(startpage, endpage, &mid, &offset, num, fh);

// 		if(ans){
// 			cout << (mid+1)<<","<<(offset+1)<<endl;
// 		}
// 		cout << "-1,-1"<<endl;
// 		// Close the file
// 		fm.CloseFile(fh);
// 	}
// }
