void delayms(int n)
{
	for (int i =0 ; i < n * 6167; i++)
	{

		__asm("nop");
	}
}

void delayus(int n)
{
	for (int i =0 ; i < n * 7; i++)
	{

		__asm("nop");
	}
}