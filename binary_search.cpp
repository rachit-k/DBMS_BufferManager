#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include "constants.h"

using namespace std;

bool bsearch(int startpage, int endpage, int *mid, int *offset, int num, FileHandler fh)
{
	bool ret=false;

	while(startpage <= endpage && !ret)
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
			int *ptr=ptrToData;
			// memcpy(&temp, &ptrToData[i*sizeof(int)], sizeof(int));
			data.push_back(ptr[i]);
		}
		bool pageFound=false;

		//do bsearch

		if(pageFound)
		{
			mid=midpage;
			for (int i=0; i <data.size(); i++) 
			{
				if (data[i]==num) 
				{
					offset = i;
					ret = true;
					break;
				}
			}
		}		
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
	PageHandler ph = fh.FirstPage ();
	int startpage= ph.GetPageNum();
	fh.UnpinPage(startpage);
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);
	
	int mid, offset; //change to vectors
	bool ans=bsearch(startpage, endpage, &mid, &offset, num, fh);

	if(ans){
		cout << (mid+1)<<","<<(offset+1)<<endl;
	}
	cout << "-1,-1"<<endl;
	// Close the file and destory it
	fm.CloseFile (fh);
}
