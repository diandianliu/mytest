#ifndef _PERFORMANCE_H__
#define _PERFORMANCE_H__

#include <iostream>
#include<stdio.h>
#include <list>
#include <sys/time.h>

extern int g_iPerfLogFlag;
extern int g_iPerfLogTime;
extern int g_iPerfDetailLogFlag;
extern std::list<void *> g_lPerf;

struct PerformanceData
{
	std::string strName;
	long lTotalTime;
	long lCount;
	long lTimeCount[5];
    struct timeval m_beginPoint;
	struct timeval m_endPoint;
	PerformanceData(std::string str)
	{
		strName = str;
		lTotalTime = 0;
		lCount = 0;
		g_lPerf.push_back(this);
		lTimeCount[0] = 0;
		lTimeCount[1] = 0;
		lTimeCount[2] = 0;
		lTimeCount[3] = 0;
		lTimeCount[4] = 0;
	}
    void begin()
    {
        gettimeofday(&m_beginPoint, NULL);
    }    
	PerformanceData()
	{
		strName = "";
		lTotalTime = 0;
		lCount = 0;
		g_lPerf.push_back(this);
		lTimeCount[0] = 0;
		lTimeCount[1] = 0;
		lTimeCount[2] = 0;
		lTimeCount[3] = 0;
		lTimeCount[4] = 0;
	}
    void begin(std::string str,int iNum)
    {
    	if(0 == g_iPerfLogFlag)
    	{
    		return;
    	}			
    	if(0 == strName.length())
    	{
    		char szNum[32] = {0};
			snprintf(szNum,sizeof(szNum)-1,"_%d",iNum);
			strName = str + szNum;
    	}
        gettimeofday(&m_beginPoint, NULL);
    }   
	void end()
    {
    	if(0 == g_iPerfLogFlag)
    	{
    		return;
    	}			
        gettimeofday(&m_endPoint, NULL);
        long theMicSec= (m_endPoint.tv_sec - m_beginPoint.tv_sec) * 1000000 + (m_endPoint.tv_usec - m_beginPoint.tv_usec);
		lTotalTime += theMicSec;
		lCount++;
		if(theMicSec > 1000000)
		{
			lTimeCount[0]++;
		}
		else if(theMicSec > 100000)
		{
			lTimeCount[1]++;
		}
		else if(theMicSec > 10000)
		{
			lTimeCount[2]++;
		}
		else if(theMicSec > 1000)
		{
			lTimeCount[3]++;
		}
		else
		{
			lTimeCount[4]++;
		}
	}
	char* show()
	{
        char strMsg[2048]={0};
		if(lCount > 0)
		{
			snprintf(strMsg,sizeof(strMsg)-1,"PERF[%-50s] total[%8.2fms] count[%8ld] level[%6.2fms] ([%ld]>s [%ld]0.1s [%ld]0.01s [%ld]ms [%ld]<ms)\n",strName.c_str(),lTotalTime/1000.0,lCount,lTotalTime/(lCount>0?lCount:1)/1000.0,lTimeCount[0],lTimeCount[1],lTimeCount[2],lTimeCount[3],lTimeCount[4]);
            printf("%s",strMsg);
			lTotalTime = 0;
			lCount = 0;
			lTimeCount[0] = 0;
			lTimeCount[1] = 0;
			lTimeCount[2] = 0;
			lTimeCount[3] = 0;
			lTimeCount[4] = 0;
		}
        return strMsg;
	}
};


#if 1
#define  PERF_LOG_START(strFlag)  \
	 static PerformanceData PS##strFlag(#strFlag); \
	 if(g_iPerfDetailLogFlag > 0) { \
	 PS##strFlag.begin();}
	
#define  PERF_LOG_END(strFlag) \
	 if(g_iPerfDetailLogFlag > 0) \
		{ PS##strFlag.end();}

#define  PERF_LOG_START_NUM(strFlag,iNum)  \
	 static PerformanceData PS##strFlag(""); \
	 if(g_iPerfDetailLogFlag > 0) { \
	 PS##strFlag.begin(#strFlag,iNum);}

#define PERF_LOG_SHOW \
     for(auto itr=g_lPerf.begin();itr!=g_lPerf.end();itr++) { \                                                                                                                                           
         PerformanceData *pPerf = (PerformanceData *)(*itr); \
         pPerf->show(); }

#else
    #define PERF_LOG_START(strFlag)
    #define PERF_LOG_END(name)
	#define PERF_LOG_START_NUM(strFlag,iNum)
#endif


#endif

