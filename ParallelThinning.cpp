///This code requires ISO C++11 in order to run
//Project by Ismael Deka, Anthony Finch, Nayeen Hakim - 11/24/2021
//
// Parallel Thinning Algorthm

#include <omp.h>
#include <iostream>
#include <chrono>
#include <windows.h>


#define MAX_ROWS_LARGE 34
#define MAX_COLUMNS_LARGE 34

#define MAX_ROWS_MED 14
#define MAX_COLUMNS_MED 14

#define MAX_ROWS_SMALL 8
#define MAX_COLUMNS_SMALL 12

#define LARGE 1
#define MED 2
#define SMALL 3


int IT_LARGE [MAX_ROWS_LARGE][MAX_COLUMNS_LARGE] =   			{{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
											{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1}};
											
											
int IT_MED [MAX_ROWS_MED][MAX_COLUMNS_MED] =   {{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1},
									{1,1,1,0,0,0,0,0,0,0,0,1,1,1}};
									
int IT_SMALL [MAX_ROWS_SMALL][MAX_COLUMNS_SMALL]  = {{1,1,0,0,0,0,0,0,0,0,1,1},
									{1,1,0,0,0,0,0,0,0,0,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1,1,1},
									{1,1,0,0,0,0,0,0,0,0,1,1},
									{1,1,0,0,0,0,0,0,0,0,1,1}};
									
int getValue(int i, int j, int size){
	
		switch(size){
		case LARGE:	
			return IT_LARGE[i][j];
		
		case MED:
			return IT_MED[i][j];
			break;
		case SMALL:
			return IT_SMALL[i][j];
			break;
		default:
			return IT_LARGE[i][j];
			break;
	}
	
}
									
int A(int i, int j, int maxColumns, int maxRows,int size){
		
	int count = 0;
	
	if(i-1 >= 0 && j+1 < maxColumns){ // Check if point is a bottom-left corner
	
		if(getValue(i-1,j,size) != 1 && getValue(i-1,j+1,size)==1){ //comparing p2 and p3
			count++;
		}
		if(getValue(i-1,j+1,size) != 1 && getValue(i,j+1,size)==1){ //comparing p3 and p4
			count++;
		}
	}
	if(i+1 >= maxRows && j+1 < maxColumns){  //Check  if point is a top-left corner
	
		if(getValue(i,j+1,size)!= 1 && getValue(i+1,j+1,size)==1){ //comparing p4 and p5
				count++;
			}
		if( getValue(i+1,j+1,size) != 1 && getValue(i+1,j,size)==1){ //comparing p5 and p6
				count++;
			}
	}
	
	if(i+1 < maxRows && j-1 >= 0){ // Check  if point is a top-right corner
		if( getValue(i+1,j,size) != 1 && getValue(i+1,j-1,size)==1){  //comparing p6 and p7
					count++;
				}
		if( getValue(i+1,j-1,size) != 1 && getValue(i,j-1,size)==1){  //comparing p7 and p8
					count++;
				}
		
	}
	if(i-1 >= 0 && j-1 >= 0){ // Check  if point is a bottom-right corner
	
		if( getValue(i,j-1,size) != 1 && getValue(i-1,j-1,size)==1){ //comparing p8 and p9
						count++;
					
			}
	}

	return count;		

}

int B(int i, int j,int size){
	

	int count = 0;

		if(getValue(i-1,j,size) == 1)       //P2
			count++;
			
		if(getValue(i-1,j+1, size) == 1)	  //P3
			count++;
			
		if(getValue(i-1,j+1, size) ==1 )     //P4
			count++;
			
		if(getValue(i+1,j+1, size) ==1)     //P5
			count++;
			
		if(getValue(i+1,j, size)==1)		  //P6
			count++;

		if(getValue(i+1,j-1, size) ==1)     //P7
			count++;
			
		if(getValue(i,j-1, size) ==1)		  //P8
			count++;

		if(getValue(i-1,j-1, size) ==1)     //P9
			count++;

	
	return count;		
	
}


int C(int i, int j,int size){

	int product = 1;
	

		product *= getValue(i-1,j,size);

		product *= getValue(i,j+1,size);

		product *= getValue(i+1,j,size);
	
	return product;
}

int D(int i, int j,int size){

	
	int product = 1;
	
product *= getValue(i,j+1,size);

		product *= getValue(i+1,j,size);

		product *= getValue(i,j-1,size);
	
	return product;
	
}
int C_Two(int i, int j,int size){
	
	
	int product = 1;
	
	product *= getValue(i-1,j,size);

	product *= getValue(i,j+1,size);

	product *= getValue(i+1,j,size);
	
	return product;
}

int D_Two(int i, int j,int size){
	
	int product = 1;
	
	
	product *= getValue(i-1,j,size);

	product *= getValue(i+1,j,size);

	product *= getValue(i,j-1,size);
	
	return product;
	
}

bool isPointSkeletonOne(int i, int j,int maxColumns, int maxRows,int size){  //First subiteration
	int ZeroOneCount = A(i,j,maxColumns, maxRows,size);
	int NonZeroNeighborCount = B(i,j,size);
	int SideNeighborProduct = C(i,j,size);
	int CornerNeighborProduct = D(i,j, size);
	
	if(ZeroOneCount == 1 && (NonZeroNeighborCount >= 2 && NonZeroNeighborCount <= 6) 
	&& SideNeighborProduct == 0 && CornerNeighborProduct == 0){
				
		return false;				
	}else{
		return true;
	}
	

}

bool isPointSkeletonTwo(int i, int j,int maxColumns, int maxRows,int size){ //Second subiteration
	int ZeroOneCount = A(i,j,maxColumns, maxRows,size);
	int NonZeroNeighborCount = B(i,j,size);
	int SideNeighborProduct = C_Two(i,j,size);
	int CornerNeighborProduct = D_Two(i,j,size);


	if(ZeroOneCount == 1 && (NonZeroNeighborCount >= 2 && NonZeroNeighborCount <= 6) 
	&& SideNeighborProduct == 0 && CornerNeighborProduct == 0){
				
		return false;				
	}else{
		return true;
	}
	

}

int main(int *argc, char *argv[]){
	omp_set_num_threads(2);
	/*#pragma omp parallel 
	{
		
		printf("Hello World \n");
	}*/
	std::cout << "Starting Image(Large):" << std::endl;
	
	for(int i = 0; i < MAX_ROWS_LARGE; i++){
			for(int j = 0; j < MAX_COLUMNS_LARGE; j++ ){
				if(IT_LARGE[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Running Thinning algorithm in Parallel...\n" << std::endl;
	
    auto started = std::chrono::high_resolution_clock::now();
	
	int numDeletedPoints;
	do{
		numDeletedPoints = 0;
			
	#pragma omp parallel
	#pragma omp single
	{		
		#pragma omp task
		{ for(int i = 0; i < MAX_ROWS_LARGE; i++){
					for(int j = 0; j < MAX_COLUMNS_LARGE; j++ ){
						if(!isPointSkeletonOne(i,j,MAX_COLUMNS_LARGE, MAX_ROWS_LARGE,LARGE) && IT_LARGE[i][j] == 1){
							IT_LARGE[i][j] = 0;
							numDeletedPoints++;
						}			
							
						
					}
				}
		}
		#pragma omp task
		{
			for(int i = 0; i < MAX_ROWS_LARGE; i++){
				for(int j = 0; j < MAX_COLUMNS_LARGE; j++ ){
					if(!isPointSkeletonTwo(i,j,MAX_COLUMNS_LARGE, MAX_ROWS_LARGE,LARGE) && IT_LARGE[i][j] == 1){
						IT_LARGE[i][j] = 0;
						numDeletedPoints++;
					}
				}
			}
		}
	}

		
		/*if(numDeletedPoints == 0){
			break;
		}else{
			
			numDeletedPoints = 0;
			

			
			
		}*/
		
		
	}while(numDeletedPoints != 0);

	
	auto done = std::chrono::high_resolution_clock::now();

	
	std::cout << std::endl;
	std::cout << std::endl;
		double timeCompleteLarge = std::chrono::duration_cast<std::chrono::microseconds>(done-started).count();
	
	std::cout << "Complete. " <<timeCompleteLarge<< "(ms)" <<std::endl;
	
	
	
	for(int i = 0; i < MAX_ROWS_LARGE; i++){
			for(int j = 0; j < MAX_COLUMNS_LARGE; j++ ){
				if(IT_LARGE[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "Starting Image(Medium):" << std::endl;
	
	for(int i = 0; i < MAX_ROWS_MED; i++){
			for(int j = 0; j < MAX_COLUMNS_MED; j++ ){
				if(IT_MED[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Running Thinning algorithm in Parallel...\n" << std::endl;
	
    started = std::chrono::high_resolution_clock::now();
	
	numDeletedPoints;
	do{
		numDeletedPoints = 0;
		#pragma omp parallel
	#pragma omp single
	{		
		#pragma omp task
		{ for(int i = 0; i < MAX_ROWS_MED; i++){
					for(int j = 0; j < MAX_COLUMNS_MED; j++ ){
						if(!isPointSkeletonOne(i,j,MAX_COLUMNS_MED, MAX_ROWS_MED,MED) && IT_MED[i][j] == 1){
							IT_MED[i][j] = 0;
							numDeletedPoints++;
						}			
							
						
					}
				}
		}
		#pragma omp task
		{
			for(int i = 0; i < MAX_ROWS_MED; i++){
				for(int j = 0; j < MAX_COLUMNS_MED; j++ ){
					if(!isPointSkeletonTwo(i,j,MAX_COLUMNS_MED, MAX_ROWS_MED,MED) && IT_MED[i][j] == 1){
						IT_MED[i][j] = 0;
						numDeletedPoints++;
					}
				}
			}
		}
	}
		
		
		
	}while(numDeletedPoints != 0);

	
	done = std::chrono::high_resolution_clock::now();

	
	std::cout << std::endl;
	std::cout << std::endl;
		double timeCompleteMed = std::chrono::duration_cast<std::chrono::microseconds>(done-started).count();
	
	std::cout << "Complete. " <<timeCompleteMed<< "(ms)" <<std::endl;
	
		for(int i = 0; i < MAX_ROWS_MED; i++){
			for(int j = 0; j < MAX_COLUMNS_MED; j++ ){
				if(IT_MED[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	
	std::cout << "Starting Image(Small):" << std::endl;
	
	for(int i = 0; i < MAX_ROWS_SMALL; i++){
			for(int j = 0; j < MAX_COLUMNS_SMALL; j++ ){
				if(IT_SMALL[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Running Thinning algorithm in Parallel...\n" << std::endl;
	
    started = std::chrono::high_resolution_clock::now();
	
	numDeletedPoints;
	do{
		numDeletedPoints = 0;
		#pragma omp parallel
	#pragma omp single
	{		
		#pragma omp task
		{ for(int i = 0; i < MAX_ROWS_SMALL; i++){
					for(int j = 0; j < MAX_COLUMNS_SMALL; j++ ){
						if(!isPointSkeletonOne(i,j,MAX_COLUMNS_SMALL, MAX_ROWS_SMALL,SMALL) && IT_SMALL[i][j] == 1){
							IT_SMALL[i][j] = 0;
							numDeletedPoints++;
						}			
							
						
					}
				}
		}
		#pragma omp task
		{
			for(int i = 0; i < MAX_ROWS_SMALL; i++){
				for(int j = 0; j < MAX_COLUMNS_SMALL; j++ ){
					if(!isPointSkeletonTwo(i,j,MAX_COLUMNS_SMALL, MAX_ROWS_SMALL,SMALL) && IT_SMALL[i][j] == 1){
						IT_SMALL[i][j] = 0;
						numDeletedPoints++;
					}
				}
			}
		}
	}
	}while(numDeletedPoints != 0);

	
	done = std::chrono::high_resolution_clock::now();

	
	std::cout << std::endl;
	std::cout << std::endl;
		double timeCompleteSmall = std::chrono::duration_cast<std::chrono::microseconds>(done-started).count();
	
	std::cout << "Complete. " <<timeCompleteSmall<< "(ms)" <<std::endl;
	
		for(int i = 0; i < MAX_ROWS_SMALL; i++){
			for(int j = 0; j < MAX_COLUMNS_SMALL; j++ ){
				if(IT_SMALL[i][j] == 0)
					std::cout << ".";
				else
				    std::cout << "@";
			}
			std::cout << std::endl;
		}
	
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "Matrix Size\tParallel(ms)" << std::endl;
	std::cout << "-------------------------------------------------------------"<< std::endl;
	std::cout << "34 X 34\t\t"<< timeCompleteLarge<<std::endl;
	std::cout << "14 X 14\t\t"<< timeCompleteMed<< std::endl;
	std::cout << "8 X 12\t\t"<<  timeCompleteSmall<< std::endl;
		
	
}
	



