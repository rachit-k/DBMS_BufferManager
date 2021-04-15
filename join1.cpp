#include<iostream>
#include "file_manager.h"
#include "errors.h"
#include<cstring>
#include "constants.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler file1 = fm.OpenFile(argv[1]);
	cout << "File 1 opened " << endl;
	FileHandler file2 = fm.OpenFile(argv[2]);;
    cout << "File 2 opened " << endl;

	// Get start and end page for file1
	PageHandler ph = file1.FirstPage();
	int startPage1 = ph.GetPageNum();
	file1.UnpinPage(startPage1);
	ph = file1.LastPage();
	int endPage1 = ph.GetPageNum();
	file1.UnpinPage(endPage1);
	
    //Get start and end page for file2
    ph = file2.FirstPage();
	int startPage2 = ph.GetPageNum();
	file2.UnpinPage(startPage2);
	ph = file2.LastPage();
	int endPage2= ph.GetPageNum();
	file2.UnpinPage(endPage2);
    vector<int> ans;
    for(int page1 = startPage1; page1 < endPage1; ++page1){
        PageHandler pg1 = file1.PageAt(page1);
        char* ptrToData1 = pg1.GetData();
        int * data1 = (int *)ptrToData1;
        for(int page2 = startPage2; page2 < endPage2; ++page2){
            PageHandler pg2 = file2.PageAt(page2);
            char* ptrToData2 = pg2.GetData();
            int * data2 = (int *)ptrToData2;
            for(int i = 0; i < PAGE_CONTENT_SIZE/sizeof(int); ++i){
                for(int j = 0; j< PAGE_CONTENT_SIZE/sizeof(int); ++j){
                    if(data1==NULL or data2==NULL){
                        break;
                    }
                    if(data1[i]==data2[j]){
                        ans.push_back(data1[i]);
                    }
                }
            }
            file2.UnpinPage(page2);	
        }
        file1.UnpinPage(page1);	
    }
    for(int i = 0; i< ans.size(); ++i){
        cout<<ans[i]<<" "<<endl;
    }
	ans.clear();
	// Close the files
	fm.CloseFile(file1);
    fm.CloseFile(file2);
    return 0;
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
