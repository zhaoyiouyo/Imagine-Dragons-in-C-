#include <54func.h>
#include <iostream>
#include <string>
#include <workflow/WFFacilities.h>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>

using namespace std;


static WFFacilities::WaitGroup gWaitGroup(1);

void handler(int signum){
    printf("signum = %d\n", signum);
    gWaitGroup.done();
}


void redisCallback(WFRedisTask *redisTask){
    protocol::RedisRequest * req = redisTask->get_req();
    protocol::RedisResponse * resp = redisTask->get_resp();
    protocol::RedisValue value; //将要用来获取redis返回的结果
    int state = redisTask->get_state();
    int error = redisTask->get_error(); //error只能处理网络连接和系统错误
    switch(state){
    case WFT_STATE_SYS_ERROR:
        cout << "system error:" << strerror(error) << "\n";
        break;
    case WFT_STATE_DNS_ERROR:
        cout << "dns error: " << gai_strerror(error) << "\n";
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(value); //将redis的结果已经存在value中了
        if(value.is_error()){
            cout << "redis error\n";
            state = WFT_STATE_TASK_ERROR; // 任务层面的错误
        }
        break;
    }

    if(state == WFT_STATE_SUCCESS){
        cout << "SUCCESS\n";
    }
    else{
        cout << "FAILED\n";
        return;
    }
}

int main(){
    signal(SIGINT, handler);

    WFHttpTask *httpTask = WFTaskFactory::create_http_task("http://www.taobao.com", 10, 0,
        [](WFHttpTask *httpTask){
            protocol::HttpRequest *req = httpTask->get_req();
            protocol::HttpResponse *resp = httpTask->get_resp();


            int state = httpTask->get_state();
            int error = httpTask->get_error();
            switch(state){
            case WFT_STATE_SYS_ERROR:
                cout << "system error:" << strerror(error) << "\n";
                break;
            case WFT_STATE_DNS_ERROR:
                cout << "dns error: " << gai_strerror(error) << "\n";
                break;
            case WFT_STATE_SUCCESS:
                break;
            }
            if(state == WFT_STATE_SUCCESS){
                const void *body;
                size_t size;
                resp->get_parsed_body(&body,&size);
                cout << string((char *)body,size) << endl;

                WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
                                "redis://127.0.0.1:6379", 0, redisCallback);
                protocol::RedisRequest * req = redisTask->get_req();
                req->set_request("SET",{"www.taobao.com", string((char *)body,size)});
                series_of(httpTask)->push_back(redisTask);
            }
            else{
                cout << "FAILED\n";
                return;
            }


        }
    );


    protocol::HttpRequest *req = httpTask->get_req();
    req->add_header_pair("Accept","*/*");
    // 将任务派给框架，由框架异步调用
    httpTask->start();

    gWaitGroup.wait();
}
