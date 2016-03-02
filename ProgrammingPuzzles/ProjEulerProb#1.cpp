#include <iostream>           // std::cout

using namespace std;

int main ()
{
	int sum =0, multi3 =3, multi5 =5;
	int totalNumbers = 0;

	cout<<"Total numbers: ";
	cin>>totalNumbers;
	
	for (int i =1; i<totalNumbers ; i++)
	{
		//cout<<"i ["<<i<<"]"<<'\n';
		if((i%multi3)==0)
		{
			sum += i;
		}
		else if((i%multi5)==0)
		{
			sum+=i;
		}
	}
	cout<<"Sum ["<<sum<<"]"<< '\n';
	return 0;
}

function Test(){
	//testingFileEdition
}
