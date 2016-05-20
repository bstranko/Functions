#include <iostream>
#include <fstream> 
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std; 

const int MaxRows(100); 


void swap_values(double& X1, double& X2); 
void sort(double Array[MaxRows], int Npts); 
void MaxMin(const double Data[MaxRows], int Npts, double& Min, double&Max);
void Statistics(const double Data[MaxRows], int Npts, double& Max,double& Min,double& Mean,double& Std_Dev);
int index_of_smallest(const double A[MaxRows], int start_index, int Npts); 
double Average(const double Data[MaxRows], int Npts); 
double Std_Deviation(const double Data[MaxRows], int Npts, double Average); 


int main()

{
	int ncases, npts[MaxRows], i, j; 
	double data[MaxRows], sort_data[MaxRows],  max, min, total=0, count = 0, average, std_dev; 
	
	ifstream in_stream; 
	ofstream out_stream;

	in_stream.open("input.txt"); 
	in_stream>>ncases;
	
	out_stream.open("output.txt");
	out_stream<<"Number of Cases: " <<ncases<<endl<<endl;

	for (i=0; i < ncases; i++)
	{
		in_stream>>npts[i]; 

		out_stream<<" Case #" << i+1<<endl 
				  <<"\n  Number of Points:  "<<npts[i]     
			      <<"\n  Input Data:  ";
				 
	 for (j=0; j <  npts[i]; j++)
		{
			in_stream>>data[j];
			out_stream<<data[j]<< "  "; 
			sort_data[j] = data[j]; 
		}
	
	    Statistics(data, npts[i], max, min, average, std_dev);

		sort(sort_data,npts[i]);

		if (i==0)
			out_stream<<setw(3);

			out_stream<<"\n  Sorted Data: "; 

		for(j=0; j < npts[i]; j++)
			out_stream<<sort_data[j]<<setw(3);

	
        out_stream<<endl
	    <<"  Mean: " <<average<<endl
	    <<"  Standard Deviation: " <<std_dev<<endl
	    <<"  Minimum Value: " <<min<<endl
	    <<"  Maximum Value: "<<max<<endl<<endl<<endl; 


	}

	in_stream.close(); 
	out_stream.close(); 
	
	cout<<"Output file ready to read"<<endl; 
	system("pause"); 
	return 0;

}

void swap_values(double& X1, double& X2)

{
	double Temp; 
	Temp = X1;
	X1=X2; 
	X2 = Temp;
}

void sort(double Array[MaxRows], int Npts)

{
	int index_of_next_smallest,index; 

	for (index = 0; index <Npts - 1 ; index++)
	{
		index_of_next_smallest = index_of_smallest(Array, index, Npts); 
		swap_values(Array[index], Array[index_of_next_smallest]); 
	}
}

int index_of_smallest(const double A[MaxRows], int start_index, int Npts)

{

	int index_of_min = start_index; 
	double min = A[start_index]; 
	
	for (int index = start_index + 1; index < Npts; index++)
		if (A[index] < min)
		{
			min = A[index]; 
			index_of_min = index; 
		}

		return index_of_min; 
} 

void Statistics(const double Data[MaxRows], int Npts, double& Max,double& Min,double& Mean,double& Std_Dev)
{
	 
	 MaxMin(Data, Npts, Min, Max);
	 Mean= Average(Data, Npts);
	 Std_Dev = Std_Deviation(Data, Npts, Mean);


}


void MaxMin(const double Data[MaxRows], int Npts, double& Min, double&Max)
{
		
	Min = Data[0]; 
 	Max = Data[0]; 

	
	 for (int index = 1; index < Npts; index++)
		 if(Data[index] < Min)
     {
	 		Min = Data[index]; 
 	 }

    for (int index = 1; index < Npts; index++)
		 if(Data[index] > Max)
    {
			Max = Data[index]; 
 	}

}

double Average(const double Data[MaxRows], int Npts)
{
	double total = 0, count =0, Average = 0;

	for (int index = 0; index < Npts; index++)
	 {
		 total = Data[index] + total; 
		 count = index+1; 
	 }

	Average = total/count;
	return Average; 
	 
}

double Std_Deviation(const double Data[MaxRows], int Npts, double Average)
{
	double answer = 0, total_value =0, Std_Dev; 
	
	for (int index = 0; index < Npts; index++)
		{
			answer = (pow((Data[index]-Average), 2)); 
			total_value = total_value + answer;  		
	 }

	Std_Dev = sqrt(total_value/Npts);

	return Std_Dev;
}