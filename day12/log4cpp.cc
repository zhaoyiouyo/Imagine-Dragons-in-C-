#include <iostream>
#include "log4cpp/PatternLayout.hh"

using namespace std;
using namespace log4cpp;

void test0(){
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout * ptn2  = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout * ptn3  = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");
    
    OstreamAppender * pos = new OstreamAppender("console",&cout);
    //输出器与布局绑定
    pos->setLayout(ptn1);

    FileAppender * filePos = new FileAppender("file","wd.log");
    filePos->setLayout(ptn2);

    RollingFileAppender * rfPos = new RollingFileAppender("rollingfile",
                                                          "rollingfile.log",
                                                          5 * 1024,
                                                          9);
    rfPos->setLayout(ptn3);
}

int main(){
    test0();
    return 0;
}
