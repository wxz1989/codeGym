
typedef void (*FUNC_PTR) (int);FUNC_PTR myFunc;
static void MyFunctionTakingInt(int);

class TestCCPP
{
public:
	TestCCPP();
	~TestCCPP();
	void CFunctionCall(FUNC_PTR);
};

TestCCPP::TestCCPP()
{
	cout<<"Object Created";
}

TestCCPP::~TestCCPP()
{
	cout<<"Object deleted";
}

void 
TestCCPP::CFunctionCall(FUNC_PTR ptr)
{
	if ( ptr != NULL  )
		ptr(10);
}

void MyFunctionTakingInt(int)
{
	std::cout<<"MyFunction Taking Int Enter++";
	std::cout<<"MyFunction Taking Int Exit--";
}


int main()
{
	TestCCPP obj;
	obj.CFunctionCall(MyFunctionTakingInt);

}

