#include <iostream>
#include "file_manager.h"
#include "errors.h"
#include <cstring>
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
    vector<int> ans1;
    vector<int> ans2;
    for(int page1 = startPage1; page1 <=endPage1; ++page1){
        PageHandler pg1 = file1.PageAt(page1);
        char* ptrToData1 = pg1.GetData();
        int * data1 = (int *)ptrToData1;
        for(int i = 0; i < PAGE_CONTENT_SIZE/sizeof(int); ++i){
            if(&data1[i]==NULL){
                        break;
                    }
            ans1.push_back(data1[i]);
        }
        file1.UnpinPage(page1);
    }
    for(int page1 = startPage2; page1 <=endPage2; ++page1){
        PageHandler pg1 = file2.PageAt(page1);
        char* ptrToData1 = pg1.GetData();
        int * data1 = (int *)ptrToData1;
        for(int i = 0; i < PAGE_CONTENT_SIZE/sizeof(int); ++i){
            if(&data1[i]==NULL){
                        break;
                    }
            ans2.push_back(data1[i]);
        }
        file2.UnpinPage(page1);
    }
    sort(ans1.begin(), ans1.end());
    sort(ans2.begin(), ans2.end());
    
	fm.CloseFile(file1);
    fm.CloseFile(file2);
    if(ans1.size()!=ans2.size()){
        cerr<<"Size of first file is "<<ans1.size()<<" and size of the second file is "<<ans2.size()<<endl;
        for(int i = 0; i< min(ans1.size(), ans2.size()); ++i){
            if(ans1[i]!=ans2[i]){
                cerr<<"There is "<<ans1[i]<<" in the first file and "<<ans2[i]<<" in the second file at position "<<i<<endl;
                return -1;
            }
        }
        cerr<<"There are strictly extra in the larger file at the end (larger numbers)"<<endl;
        return 1;
    } 
    for(int i = 0; i< ans1.size(); ++i){
        if(ans1[i]!=ans2[i]){
            cerr<<"There is "<<ans1[i]<<" in the first file and "<<ans2[i]<<" in the second file at position "<<i<<endl;
            return 1;
        }
        
    }
    cout<<"Passed "<<endl;
    return 0;
}
