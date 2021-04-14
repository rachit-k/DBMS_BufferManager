//Sample file for students to get their code running

#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>

using namespace std;

int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler fh = fm.OpenFile(argv[1]);
	cout << "File opened " << endl;

	// int pageno=0, i=0;
	PageHandler ph = fh.FirstPage();
	int startpage= ph.GetPageNum();
	fh.UnpinPage(startpage);
	ph = fh.LastPage();
	int endpage= ph.GetPageNum();
	fh.UnpinPage(endpage);

	int pageno=startpage;
    
    while(pageno<=endpage)
    {
        cout<<"pageno: "<<pageno<<endl;
        ph = fh.PageAt(pageno);
		char* ptr=ph.GetData();
        for(int i=0;i<PAGE_CONTENT_SIZE/sizeof(int); i++)
		{
			if(ptr==NULL)
				break;
			int num;
			memcpy(&num, &ptr[i*sizeof(int)], sizeof(int));
			cout<<num<<endl;
		}
        fh.UnpinPage(pageno);
        pageno++;
    }

    fm.CloseFile(fh);
}