#include <fstream>
#include <iostream>
#include <string>
#include<chrono>
#include<vector>
using namespace std;
using namespace std::chrono;


/*Misordered some functions so here is a prototype to solve it */
vector<vector<int>> memoCacheInit(int rows,int cols);
int lcsRecursive(string string1, string string2, int x, int y);

/**
*  @brief Class that maintains that data needed for task1 (bottom-up) dynamic programming solution
*/  
class program1Data {
  public:
    //Holds the copied table from that was generated from the dynamic LCS function
    vector<vector<int>> table;
    //holds sequence values
    string seq1;
    string seq2;
    //Holds the calculated LCS value
    int lcsValue=-1;
    //Holds lcsSting
   string lcsString;
    //Set in dynamic LSC function after checking string lengths
    bool greater_than_ten;
    //Execution time of the dynamic LCS function set from the outside.
    int runTime=-1;
    //writes data to a specified outfile
    void writeData (char *);
    //Dyanmic LCS implementation
    void dynamicLcs(string,string,int,int);
   //Function to computer the actual longest common subsequence
   void compute_lcs_string();
};


void program1Data::compute_lcs_string(){
	int x = seq1.length();
	int y = seq2.length();
	int index = lcsValue;
	//The length of the vector is obviously the length computed.
	vector<char> result(index);
	while(x > 0 && y > 0){
		if(seq1[x-1] == seq2[y-1]){
			//If last 2 chars match then that char is in the result
			result[index-1]= seq1[x-1]; //Could be seq2[y-1] as well
			x--;
			y--;
			index--;
		}else if(table[x-1][y] > table[x][y-1]){
			x--;
		}else{
			y--;
		}
	}

	 string res_string = string( result.begin(), result.end());
	 lcsString = res_string;
}

void program1Data::writeData (char* fileName) {
	ofstream output(fileName);
  	if(greater_than_ten){
		/* Display table*/
		 for(int i=0;i<table.size();i++){
        		for (int j=0;j<table[i].size();j++){
           			output<<table[i][j]<<" ";
    			}
			output<<endl;//new line new row
		}
		output<<lcsString<<"\n";
		output<<runTime<<"\n";
	}else{
		output<<lcsValue<<"\n";
		output<<runTime<<"\n";
	}
	output.close();
}





/**
    Returns the integer value of the longest common subsequence (non-contigious) for 2 strings.
    @param string1 The 1st sequence
    @param string2 The 2nd sequence
    @param x Index of starting char to examine within the 1st sequence. x=1 denotes the first char of the sequence.
    @param y Index of starting char to examine within the 2nd sequence. y=1 denotes the first char of the sequence.
    @return result: If either x=0 or y=0 return 0 (base case), if the last characters in the specified range matches for 
    both sequences reutrn 1 + lcs(seq1,seq2,cur_char_x-1,cur_char_y-1), if last characters in the specified ranges do not match
    for both sequences return the maximum value of either lcs(seq1,seq2, cur_char_x-1,cur_char_y) OR lsc(seq1,seq2,cur_char_x,cur_char_y-1)
*/

int lcsRecursive(string string1, string string2,int x,int y){
	/*A variable for sorting the result of the lsc value for the current subcall */
	int result;
	if(x==0 || y==0){
		result= 0;
	}else if(string1[x-1]==string2[y-1]){
		/*Since x or y =1 represents the first char, and string are indexed starting from 0, we need a negative offset */
		/*If the end chars of both current seequences match add 1 to length and call the function again with one less char. Shift to left */
		result = 1+ lcsRecursive(string1,string2,x-1,y-1);
	}else if(string1[x-1]!=string2[y-1]){
		/*Last chars of the sequences do not current match */
		/*Take the max LCS value/length by choosing between seq1 (without final char), and seq2 (with final char) and seq1 (with final char) and
		seq2 (without) final char. This way you can see which ending char produces the longest subsequence. */
		int value1  = lcsRecursive(string1,string2,x-1,y);
		int value2 = lcsRecursive(string1,string2,x,y-1);
		/* Return the max of the 2 values and continue executing*/
		result = (value1 > value2) ? value1 : value2;
	}
	return result;
}



/**
    Returns the length of the longest common subsequence of 2 sequences using the top down approach (Recursion). Idential to the recursive computation
    except values that are already calculated in other recursive calls are cached in a 2D array consisting of x rows and y columns. When a already computated value
    is obtained the value from the cache is used as opposed to propagating more recursive calls.
    @param string1 The 1st sequence
    @param string2 The second sequence
    @param x Index of the first char to examine within the sequence. x=1 denotes the first char in the sequence.
    @param y Index of the first char to examine within the sequence. y=1 denotes the first char in the sequence.
    @return result: If calculated value of x,y is stored in the cache then return that value. If not compute the lsc recursively as outlined in the function above.
    OR lsc(seq1,seq2,cur_char_x_,cur_char_y-1)
*/

int lcsMemoization(string string1, string string2, int x, int y){
	/*cache contains the already calculated values of LCS calculated during recursive calls. The helper function returns the initailzed vector
	all container values of NULL/0. We add 1 extra row and column to hold the necessary 0 row/col*/
	vector<vector<int>> memoCache = memoCacheInit(x+1,y+1);
	/*Holding the ret value that either gets a cache value or a calculated value from the subcall */
	int retVal;
	//cout<<"SEG FAULT"<<endl;
	//cout<<"memoCache[x-1][y-1] = "<<memoCache[x-1][y-1]<<endl;
	if(memoCache[x][y]>0){
		 retVal = memoCache[x][y];
	}else{
		/* Compute the value recursively normal as described in the function above*/
		retVal = lcsRecursive(string1,string2,x,y);
		/* save the computed value in the cache*/
		memoCache[x][y]=retVal;
	}
	return retVal;
}

/**
   @param rows The number of chars in the first sequence
   @param cols The number of chars in the second sequence
   @return Returns a vector of vectors (2D table/cache) with everyspace
   intialized to -1 (nothing in index).
*/
vector<vector<int>> memoCacheInit(int rows, int cols){
	/* The constructed 2D vector*/
	 vector<vector<int>> cache(rows,vector<int>(cols,-1));
	return cache;
}

/**
   @param string1 first sequence 
   @param string2 second sequence
   @param x Index of first char to examine in the sequence. x=1 denotes the first character. Orignally passed in as string1.length()
   @param y Index of first char to examine in the sequence. y=1 denotes the first character. Originally passed in as string2.length()
   @return (No return value, it is set in class member var) Since this is a tabular dynamic programming solution we do not have recurive calls, but we keep the table from the memoization but instead of calculating
   the indicies through recursive calls of the lsc function we instead loop through the rows and cols of the cache/table filling in one row (the inner j loop) at a
   time and with the same cases 1. A char matches the last index of the string 2. The chars don't match at the end of the strings.The table ends in the upper right 
   hand corner (bottom-up) which is index i,j (where i=string1 length and j=string2 legnth) so the lsc of the 2 strings is the cahce[string1 length][string2 length]
*/
void program1Data::dynamicLcs(string string1, string string2, int x, int y){
	/* Initialize the table the first row and col is filled with 0s for initialization in the table.
	This means that if either x=0 or y=0 (for table access) then that index is 0. Because lcs of 0 and anything is 0 */
	vector<vector<int>> memoCache = memoCacheInit(x+1,y+1);
	for(int i=0;i<=x;i++){
		for(int j=0;j<=y;j++){
			if(i==0 || j==0){
				/*See explaination above */
				memoCache[i][j]=0;
			}else if(string1[i-1]==string2[j-1]){
				memoCache[i][j]= (memoCache[i-1][j-1]) +1;
			}else{
				/*2nd case where the ending chars do not match*/
				int val1 = memoCache[i-1][j];
				int val2 = memoCache[i][j-1];
				int max  = (val1 > val2) ? val1: val2;
				memoCache[i][j]=max;
			}
		}/*End of j loop */
	}/*End of i loop */

	/*The calculated LCS value*/
	lcsValue= memoCache[x][y];
	/*Checking string lengths >10 or <10 */
	if(x>=10 && y>=10){
	 	greater_than_ten=true;
	}else{
		greater_than_ten=false;
	}
	/* Set memeber var reference to populated table*/
	table=memoCache;
	/*Set string values */
	seq1= string1;
	seq2= string2;
}/*end of function */



int main(int argc,char *argv[]){
	if(argc!=5){
		cout<<"Invalid number of command line args. Format is program# [input_file_x.txt] [input_file_2.txt][output_file.txt]. (Where # =1,2, or 3)"<<endl;
		exit(1);
	}else{
		string programNum(argv[1]);
		ifstream inFile_x;
		ifstream inFile_y;
		ofstream output;
		string seq1="";
		string seq2="";
		inFile_x.open(argv[2]);
		inFile_y.open(argv[3]);
		if(!inFile_x || !inFile_y){
			/*If either file is unable to be opened */
			cout<<"One or more files are unable to be opened."<<endl;
			exit(1);
		}
		/*Get 2 input strings from files */
		getline(inFile_x,seq1);
		getline(inFile_y,seq2);
		inFile_y.close();
		inFile_x.close();
		int seq1Len = seq1.length();
		int seq2Len = seq2.length();
		/*Testing purposes */
		//cout<<"String 1: "<<seq1<<" string 2: "<<seq2<<endl;
		if(programNum.compare("program1")==0){
		//	cout<<"Executing program 1"<<endl;
			/*
			Task 1: Bottom-up dynamic LCS programming solution
			If both strings are 10 chars or more...
				a) Print out 2d cache representation
				b) On the proceeding line (#rows+1 line) put LCS value
				c) On the proceeding line(#rows+2 line) put the running time of the function
			*/
			/*Create object from class run function between the clocks to get the running time*/
			program1Data program1;
			high_resolution_clock::time_point startTime = high_resolution_clock::now();
   			program1.dynamicLcs(seq1,seq2,seq1Len,seq2Len);
    			high_resolution_clock::time_point endTime = high_resolution_clock::now();
    			auto runTime = duration_cast<microseconds>( endTime - startTime ).count();
		//	cout<<"RUN TIME:: "<<runTime<<endl; 
 			program1.runTime = runTime;
			program1.compute_lcs_string();
			//output.open(argv[4]);
			program1.writeData(argv[4]);
		}else if(programNum.compare("program2")==0){
		//	cout<<"Executing program 2"<<endl;
			/*
			Task 2: Recusrive LCS tree with output being
			Line 1 - The length of the LCS
			Line 2 - The running time of the algorithm
			Uses var output2 for the write-out file
			*/
			high_resolution_clock::time_point startTime = high_resolution_clock::now();
			int recursive_lcs_ret = lcsRecursive(seq1,seq2,seq1Len,seq2Len);
			high_resolution_clock::time_point endTime = high_resolution_clock::now();
			auto runningTime = duration_cast<microseconds>(endTime-startTime).count();
		//	cout<<"Running time is "<<runningTime<<" microseconds"<<endl;
		//	cout<<"LCS is "<< recursive_lcs_ret<<endl;
			output.open(argv[4]);
			output<<recursive_lcs_ret<<"\n";
			output<<runningTime<<"\n";
			output.close();
		}else if(programNum.compare("program3")==0){
		//	cout<<"Executing program 3"<<endl;
			/*
			Task 3: Recusrively compute LCS with dynamic-top down programming and memoization.
			Line 1 - The length of the LCS
			Line 2 - The running time of the algorithm
			*/
			high_resolution_clock::time_point startTime = high_resolution_clock::now();
			int memo_ret_val  = lcsMemoization(seq1,seq2,seq1Len, seq2Len);
    			high_resolution_clock::time_point endTime = high_resolution_clock::now();
    			auto runningTime = duration_cast<microseconds>( endTime - startTime ).count();
		//	cout<<"LCS is "<<memo_ret_val<<endl;
		//	cout<<"Running time is "<<runningTime<<endl;
			output.open(argv[4]);
			output<<memo_ret_val<<"\n";
			output<<runningTime<<"\n";
			output.close();
		}else{
		//	cout<<"Invalid 1st argument, should be program1, program2 or program3"<<endl;
		}/*end of else statement for which program to run */
	}/*End of if statement for number of arguments */
}/* End of main*/

