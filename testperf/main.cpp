#include<unistd.h>
#include "perf.h"

int g_iPerfLogFlag = 1;
int g_iPerfLogTime = 100;
int g_iPerfDetailLogFlag = 1;
std::list<void *> g_lPerf;

void test1()
{
	usleep(1000);
}
void test2()
{
	usleep(5000);
}

int main()
{
    printf("----main--------\n");
	int iCount = 0;
    while(true)
    {
        if(0 ==  ++iCount % g_iPerfLogTime)
        {     
            printf("PERF\n");
            PERF_LOG_SHOW
            /*
            for(auto itr=g_lPerf.begin();itr!=g_lPerf.end();itr++)                                                                                                                                                
            {    
                PerformanceData *pPerf = (PerformanceData *)(*itr);
                pPerf->show();
            }    
            */
        }

        PERF_LOG_START(test1)
        test1();
        PERF_LOG_END(test1)
        
        PERF_LOG_START(test2)
        test2();
        PERF_LOG_END(test2)

       if(iCount>500)
			break;
    }
    return 0;
}
