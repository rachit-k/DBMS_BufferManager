#include <iostream>
#include "file_manager.h"
#include "errors.h"
#include <cstring>
#include "constants.h"
#include <bits/stdc++.h>
#include "binary_search.h"
using namespace std;
int main(int argc, const char* argv[]) {
	FileManager fm;

	// Create a brand new file
	FileHandler file1 = fm.OpenFile(argv[1]);
	//cout << "File 1 opened " << endl;
	FileHandler file2 = fm.OpenFile(argv[2]);;
    //cout << "File 2 opened " << endl;

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
    for(int page1 = startPage1; page1 <=endPage1; ++page1){
        PageHandler pg1 = file1.PageAt(page1);
        char* ptrToData1 = pg1.GetData();
        int * data1 = (int *)ptrToData1;
        for(int i = 0; i < PAGE_CONTENT_SIZE/sizeof(int); ++i){
            if(&data1[i]==NULL){
                break;
            }

            int num = data1[i];
            //cout<<"Num is "<<num<<endl;
            bool ret =  bsearch(startPage2, endPage2, data1[i], file2);
            //cout<<"Number of times "<<num<<" was found is "<<search_results.size()<<"  "<<ans_pages.size()<<endl;
            // for(auto x: search_results){
            //     cout<<x.first<<" -> "<<x.second<<endl;
            // }
            if(ret && num!=INT_MIN){
                for(int j = 0; j < search_results.size(); ++j){
                    ans.push_back(num);
                }
            }
            search_results.clear();
            ans_pages.clear();
            offsets.clear();
        }
        file1.UnpinPage(page1);	
    }
    // for(int i = 0; i< ans.size(); ++i){
    //     cout<<ans[i]<<" "<<endl;
    // }
    //cout<<ans.size();
	// Close the files
	fm.CloseFile(file1);
    fm.CloseFile(file2);

    FileHandler outFile=fm.CreateFile(argv[3]);	
	PageHandler outPage = outFile.NewPage ();
	char *outptr = outPage.GetData ();
    int j = 0, pageNum = 0;
    for(int i = 0; i<ans.size(); ++i){
        memcpy(&outptr[j], &ans[i], sizeof(int));
		j=j+sizeof(int);
        if(j>=PAGE_CONTENT_SIZE){
            if(i+1==ans.size()) continue;
            outFile.UnpinPage(pageNum);
            outPage = outFile.NewPage();
            outptr = outPage.GetData();
            j=0;
            pageNum++;
        }
    }
    //cout<<"Here, j is "<<j<<endl;
    while(j<PAGE_CONTENT_SIZE){
        int minint = INT_MIN;
        memcpy(&outptr[j], &minint, sizeof(int));
        j = j + sizeof(int);
    }
    fm.CloseFile(outFile);
    ans.clear();
    return 0;
}
