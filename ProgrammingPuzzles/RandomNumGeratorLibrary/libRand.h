#ifndef _RAND_NUM_GENERATOR_
#define _RAND_NUM_GENERATOR_

class RandomNumberGenerator{
private:
	int m_RandomNumRange;
	static RandomNumberGenerator* m_Instance;
private:
	RandomNumberGenerator();
public:
	//RandomNumberGenerator();
	static const RandomNumberGenerator& GetInstance();
	static void AtExit();
	~RandomNumberGenerator();

	void SetRandomNumRange(int range);
	int GetRandomNumber(int range = 10);
	void GetRandomNumberList(int array[], int size,int range = 10);

};

RandomNumberGenerator* RandomNumberGenerator::m_Instance = NULL;

#endif  //_RAND_NUM_GENERATOR_