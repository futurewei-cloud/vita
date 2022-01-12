    #include <iostream>
    #include <vector>
    #include <string>
    #include <pthread.h>
    #include "rapidcsv.h"
    #include "pulsar_producer.h"
    #include "kafka_producer.h"
    #include "randomstringgenerator.h"

    #define NUM_THREADS 16

    #define TIME_LIMIT_EXEC(interval) \
            static uint64_t __last_time = 0;\
            uint64_t __time = get_current_ms();\
            bool do_exec = false;\
            if (__time > __last_time + interval){ \
                __last_time = __time;\
                do_exec = true;\
            }\
            if (do_exec)
            
    static long get_current_us() {
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::
                    duration_cast<std::chrono::microseconds>(now.time_since_epoch());
        return duration.count();
    }

    static long get_current_ms() {
        return get_current_us() / 1000;
    }

    using std::string;
    using message_kafka::KafkaProducer;
    using message_pulsar::PulsarProducer;
    void* publish(void *id)
    {
        rapidcsv::Document doc("../alg/output/random_greedy.csv");
        //rapidcsv::Document doc("../alg/output/ng.csv");
        rapidcsv::Document mes("../alg/output/random_size.csv");
        std::vector<string> topics = doc.GetColumn<string>("topic");
        std::vector<int> sizes = mes.GetColumn<int>("size");
        std::vector<int> vpcs = mes.GetColumn<int>("vpc");
      
        KafkaProducer producer()
        int tid = *((int*)id);
        for(int i = 0; i < sizes.length; i++){
            TIME_LIMIT_EXEC(250*NUM_THREADS/){
                loc = (tid + i)% sizes.length;
                string message =  SRG::RandomStringGenerator:getString(sizes[loc]);
                producer.setTopicName(topics(vpcs[loc]))
                producer.publish(message);
            }
        }
    }

    int main()
    {
        pthread_t tids[NUM_THREADS];
        int indexes[NUM_THREADS];
        for(int i = 0; i < NUM_THREADS; i++)
        {
            indexes[i] = i;
            int ret = pthread_create(&tids[i], NULL, publish, (void *)&(indexes[i]));
            if (ret != 0):
                cout << "pthread_create error: error_code=" << ret << endl;
                exit(-1);
        }
        pthread_exit(NULL);
        return 0;
    }